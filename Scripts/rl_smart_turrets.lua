--[[
=======================================
*   Battlezone: Reloaded
*
*   Smart Turrets Module
*
*   Handles smart turrets, towers, and
*   other related static defense units
=======================================
--]]

local ai_manager = require("rl_ai_manager")
local ai_targeting = require("rl_ai_targeting")

local vsp = require("vsp")

local rl_smart_turrets = {}
do
    --- @class smart_turret : managed_ai, object
    --- @field targeting_program target_function_t
    local smart_turret = vsp.object.make_class("smart_turret", ai_manager.managed_ai)

    --- @param h Handle
    --- @param creation_attributes? table
    function smart_turret:smart_turret(h, creation_attributes)
        self:super(h)

        self.team = GetTeamNum(h)
        self.range = 150.0
        self.targeting_program = ai_targeting.program.target_closest
    end

    function smart_turret:find_best_target()
        local function is_enemy(h)
            return GetPerceivedTeam(h) ~= self.team
        end
        return self.targeting_program(self.handle, self.range, is_enemy)
    end

    function smart_turret:__update(dt)
        local target = self:find_best_target()
        if target then
            Attack(self.handle, target)
        end
    end

    --- @param h Handle
    function rl_smart_turrets.make_smart_turret(h)
        return smart_turret:new(h)
    end
end
return rl_smart_turrets
