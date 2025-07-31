--[[
=======================================
*   Battlezone: Reloaded
*
*   AI Scaling Module
*
*	Required Event Handlers:
*	- Update(dt)
=======================================
--]]

local vsp = require("vsp")

local rl_ai_scaling = {}
do
    -- Constants for scaling types
    rl_ai_scaling.count = 1
    rl_ai_scaling.damage = 2
    rl_ai_scaling.damage_taken = 3
    rl_ai_scaling.health = 4
    rl_ai_scaling.ammo = 5

    local scaling_methods = {
        -- This function adjusts the count of AI units spawned in groups
        count_method = function (initial_count) return initial_count end,

        -- This function adjusts the damage AI units deal to enemies 
        damage_method = function (initial_damage) return initial_damage end,

        -- This function adjusts the amount of damage AI units take
        damage_taken_method = function (initial_damage) return initial_damage end,

        -- This function adjusts the max health of a unit
        health_method = function(initial_health) return initial_health end,

        -- This function adjusts the max ammo of a unit
        ammo_method = function(initial_ammo) return initial_ammo end
    }

    --- Gets a scaled value depending on the 
    --- @param type integer a scaling type constant defined in rl_ai_scaling.lua
    --- @param initial_value any the initial value, make sure it's valid for the current scaling method
    --- @return any scaled_result
    function rl_ai_scaling.get_scaled(type, initial_value)
        vsp.utility.required_param(type, "type", "number", "Reloaded")
        vsp.utility.required_param(initial_value, "initial_value", "any", "Reloaded")
        assert(scaling_methods[type], string.format("Scaling type is invalid"))

        return scaling_methods[type](initial_value)
    end

    --- Sets the scaling method for the given type
    --- @param type integer a scaling type constant defined in rl_ai_scaling.lua
    --- @param method fun(initial_value: any): any
    function rl_ai_scaling.set_scaling_method(type, method)
        vsp.utility.required_param(type, "type", "number", "Reloaded")
        vsp.utility.required_param(method, "method", "function", "Reloaded")

        scaling_methods[type] = method
    end
end
return rl_ai_scaling
