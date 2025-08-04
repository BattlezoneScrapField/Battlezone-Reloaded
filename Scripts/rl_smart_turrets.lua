--[[
=======================================
*   Battlezone: Reloaded
*
*   Smart Turrets Module
*
*   Handles smart turrets, towers, and
*   other related static defense units
*
*   Required Event Handlers:
*   - CreateObject(h)
=======================================
--]]

local ai_manager = require("rl_ai_manager")
local ai_targeting = require("rl_ai_targeting")

local vsp = require("vsp")

local rl_smart_turrets = {}
do
    local smart_turrets_enabled = false
    local auto_smart_turrets = false

    --- @type parameter_pack
    local default_attributes = vsp.functional.parameter_pack({
        targeting_program = ai_targeting.program.target_closest,
        occluded_retry_time = 5.0
    })

    --- @type parameter_pack
    local auto_attributes

    --- Enable smart turrets, this is a one-way trip! It irreversibly breaks
    --- the stock ai.
    function rl_smart_turrets.enable_smart_turrets()
        smart_turrets_enabled = true
    end

    --- Enables automatic smart AI on newly built turrets
    function rl_smart_turrets.auto_detect()
        assert(smart_turrets_enabled, "Reloaded: smart turrets are disabled")
        auto_smart_turrets = true
    end

    function rl_smart_turrets.set_auto_attributes(creation_attributes)
        
    end

    --- @class smart_turret : managed_ai, object
    --- @field targeting_program target_function_t
    local smart_turret = vsp.object.make_class("smart_turret", ai_manager.managed_ai)

    smart_turret.type = vsp.enum.make_enum(
        "turret",
        "tower"
    )

    local type_conversion_table = {
        turrettank = "turret",
        turret     = "tower"
    }

    local function class_label_to_type(class_label)
        return type_conversion_table[class_label]
    end

    local valid_class_labels = vsp.set.make_set(
        "turrettank",
        "turret"
    )

    --- @param h Handle
    --- @param creation_attributes? table
    function smart_turret:smart_turret(h, creation_attributes)
        local class_label = GetClassLabel(h)
        if not valid_class_labels:contains(class_label) then -- turret or gun tower
            error(string.format("Reloaded: class label of %s is incompatible with smart turret", class_label))
        end

        self:super(h)

        local pack
        if creation_attributes then
            pack = vsp.functional.parameter_pack(creation_attributes)
        else
            pack = default_attributes
        end

        self.odf = vsp.odf.open(h)
        self.type = smart_turret.type[class_label_to_type(class_label)]
        self.team = GetTeamNum(h)
        self.range = self:__find_longest_range()

        self.targeting_program = pack:required("targeting_program")

        self.current_target = nil
        self.occluded_retry_time = pack:required("occluded_retry_time")
    end

    --- Scans all weapons and picks the one with the longest range to be the smart turret's
    --- engagement range
    --- @return number longest_range
    function smart_turret:__find_longest_range()
        local longest_range = 0
        for i = 0, 4 do
            local weapon_class = GetWeaponClass(self.handle, i)
            if weapon_class then
                local weapon_odf = vsp.odf.open(weapon_class)
                local ordnance, found = weapon_odf:get_string("WeaponClass", "ordName")
                local ord_range = 0.0
                if found then
                    local ord_odf = vsp.odf.open(ordnance)
                    local ord_life_span = ord_odf:get_float("OrdnanceClass", "lifeSpan")
                    local ord_shot_speed = ord_odf:get_float("OrdnanceClass", "shotSpeed")
                    ord_range = ord_life_span * ord_shot_speed
                elseif weapon_class == "gmaggun" then
                    ord_range = 250.0 -- default value from dbz's original script, probably good enough
                end
                if ord_range > longest_range then
                    longest_range = ord_range
                end
            end
        end
        return longest_range
    end

    --- Returns the best target according to the current targeting program
    --- @return Handle? best_target
    function smart_turret:__find_best_target()
        local function target_conditions(h)
            if GetPerceivedTeam(h) == self.team then return false end
            if not IsCraft(h) or not IsBuilding(h) then return false end
            if GetClassLabel(h) == "scrap" then return false end
            --- @diagnostic disable-next-line:param-type-mismatch current target will always have a position
            if vsp.math3d.is_occluded(self.position, GetPosition(self.current_target)) then return false end
            return true
        end

        local function target_conditions()
            return true
        end

        return self.targeting_program(self.handle, self.range, target_conditions)
    end

    function smart_turret:__update(dt)
        if not smart_turrets_enabled then return end
        if not IsDeployed(self.handle) then return end -- Gun towers are always "deployed" too

        if not IsAlive(self.current_target) then
            self.current_target = nil
        end

        local best_target = self:__find_best_target()

        if best_target ~= self.current_target then
            self.current_target = best_target
            -- Stop(self.handle)
            Attack(self.handle, self.current_target)
        end
    end

    --- @param h Handle
    function rl_smart_turrets.make_smart_turret(h)
        return smart_turret:new(h)
    end

    --- To override stock turret ai first remove all weapons when it's created,
    --- and give them back the next frame
    local function override_turret_ai(h)
        if not smart_turrets_enabled then return end
        if GetClassLabel(h) ~= "turrettank" then return end

        for i = 0, 4 do
            GiveWeapon(h, nil, i)
        end

        --- @diagnostic disable-next-line: param-type-mismatch Anything in CreateObject should have an odf
        local turret_odf = vsp.odf.open(h)
        local starting_weapons = {}

        for i = 0, 4 do
            starting_weapons[i] = turret_odf:get_string("GameObjectClass", string.format("weaponName%d", i), "EMPTY")
        end

        vsp.utility.defer(function ()
            for i = 0, 4 do
                if starting_weapons[i] ~= "EMPTY" then
                    GiveWeapon(h, starting_weapons[i], i)
                end
            end
        end)
    end

    local function auto_register_smart_turret(h)
        if not smart_turrets_enabled then return end
        if not auto_smart_turrets then return end
        if valid_class_labels:contains(GetClassLabel(h)) then
            vsp.utility.defer(rl_smart_turrets.make_smart_turret, h)
        end
    end

    function rl_smart_turrets.Start()
        if not smart_turrets_enabled then return end
        if not auto_smart_turrets then return end
        for _, obj in ipairs(vsp.object_service.get_start_objects():get()) do
            if valid_class_labels:contains(GetClassLabel(obj)) then
                vsp.utility.defer(rl_smart_turrets.make_smart_turret, h)
            end
        end
    end

    function rl_smart_turrets.CreateObject(h)
        override_turret_ai(h)
        auto_register_smart_turret(h)
    end
end
return rl_smart_turrets
