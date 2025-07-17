--[[
=======================================
*   Battlezone: Reloaded
*   
*   Manages service buildings such as
*   the stock supply/field HQ, and
*   hangar, to provide AOE service
*   and other features
*
*	Required Event Handlers:
*	- Update(dt)
=======================================
--]]

local vsp = require("vsp")

local rl_service_building = {}
do
    --- @type enum
    local creation_attributes = vsp.enum.make_enum(
        "start_enabled",
        "start_disabled"
    )
    --- @type enum
    local service_attributes = vsp.enum.make_enum(
        "service_all",
        "service_team"
    )

    --- @class basic_service_building : object
    local basic_service_building = vsp.object.make_class("basic_service_building")

    --- Object handle -> service building
    --- @type table<userdata, basic_service_building>
    local all_service_buildings = {}
    rl_service_building.all_service_buildings = all_service_buildings

    --- Table of searching methods that return true if the object is of the right characteristics,
    --- andd false otherwise to determine if something should be serviced
    --- @type table<fun(obj: userdata): boolean>
    local service_searchers = {
        [service_attributes.service_all] = function (obj)
            return true
        end,
        [service_attributes.service_team] = function (obj)
            return GetTeamNum(obj) == GetTeamNum(GetPlayerHandle())
        end
    }

    --- Service building base class constructor
    --- @param building userdata handle
    --- @param range number range in meters to apply service
    --- @param interval number interval in seconds to apply service
    --- @param amount number amount of service to apply
    --- @param creation_attribute? enum
    --- @param service_function fun(self: basic_service_building, service_target: userdata)
    function basic_service_building:basic_service_building(building, range, interval, amount, creation_attribute, service_function)
        self.handle = vsp.utility.required_param(building, "building", "userdata", "Reloaded")
        self.odf = self.odf or vsp.odf.open(self.handle)
        self.range = vsp.utility.required_param(range, "range", "number", "Reloaded")
        self.interval = vsp.utility.required_param(interval, "interval", "number", "Reloaded")
        self.amount = vsp.utility.required_param(amount, "amount", "number", "Reloaded")
        vsp.utility.required_param(service_function, "service_function", "function", "Reloaded")
        
        self.service_mode = service_attributes.service_team
        
        local wrapped_service_function = function ()
            for obj in ObjectsInRange(self.range, self.handle) do
                if service_searchers[self.service_mode](obj) then
                   service_function(self, obj)
                end
            end
        end
        
        self.timer = vsp.time.make_timer(self.interval, true, wrapped_service_function)
        
        self.timer:start()

        if creation_attribute then
            local attribute = assert(creation_attributes[creation_attribute], "VSP: Invalid creation attribute for class basic_service_building")
            if attribute == creation_attributes.start_disabled then
                self.timer:pause()
            end
        end

        all_service_buildings[self.handle] = self
    end

    function basic_service_building:is_enabled()
        return self.timer:is_active()
    end

    function basic_service_building:enable()
        self.timer:resume()
    end

    function basic_service_building:disable()
        self.timer:pause()
    end

    --- @class repair_building : basic_service_building, object
    local repair_building = vsp.object.make_class("repair_building", basic_service_building)

    repair_building.default_range = 50.0
    repair_building.defaut_interval = 1.0
    repair_building.default_amount = 50
    repair_building.default_sound = "abhange2.wav"

    function repair_building:repair_building(building, range, interval, amount, sound, creation_attribute)
        self.odf = vsp.odf.open(building)
        range = range or self.odf:get_float("Reloaded", "repairRange", self.default_range)
        interval = interval or self.odf:get_float("Reloaded", "repairInterval", self.defaut_interval)
        amount = amount or self.odf:get_int("Reloaded", "repairAmount", self.default_amount)

        self:super(building, range, interval, amount, creation_attribute, function (self, object)
            if not (IsCraft(object) or IsPerson(object)) then return end -- service criteria from DBZ
            if GetHealth(object) < 1.0 then
                AddHealth(object, self.amount)
                StartSound(self.sound, object)
            end
        end)

        self.sound = sound or self.odf:get_string("Reloaded", "repairSound", self.default_sound)
    end

    --- Creates a repair building, with the stats of a stock hangar if all parameters are left nil
    --- @param building userdata handle
    --- @param range? number range in meters to apply service
    --- @param interval? number interval in seconds to apply service
    --- @param amount? number amount of service to apply
    --- @param sound? string sound file to play when applying service
    --- @param creation_attribute? enum creation attribute to spawn disabled
    --- @return repair_building
    function rl_service_building.make_repair_building(building, range, interval, amount, sound, creation_attribute)
        return repair_building:new(building, range, interval, amount, sound, creation_attribute)
    end

    local function register_start_objects()
        local objs = vsp.object_service.get_start_objects():get()
    end

    function rl_service_building.Start()
        register_start_objects()
    end

    function rl_service_building.Update(dt)

    end

    rl_service_building.creation_attributes = creation_attributes
    rl_service_building.service_attributes = service_attributes
    rl_service_building.basic_service_building = basic_service_building
end
return rl_service_building