--[[
=======================================
*   Battlezone: Reloaded
*   
*   AI Squad Module
*
*	Required Event Handlers:
*	- Update(dt)
=======================================
--]]

local vsp = require("vsp")

local rl_ai_squad = {}
do
    --- @class ai_squad : object
    local ai_squad = vsp.object.make_class("ai_squad")

    function ai_squad:ai_squad(leader, ...)
        self.leader = vsp.utility.required_param(leader, "leader", "userdata", "Reloaded")
        self.members = vsp.set.make_set(self.leader, ...)
    end

    --- Creates a squad from the given units
    --- @param leader userdata squad leader unit
    --- @param ...? userdata remaining members
    --- @return ai_squad
    function rl_ai_squad.make_squad(leader, ...)
        return ai_squad:new(leader, ...)
    end

    function ai_squad:attack(target)
        self:for_each(Attack, target)
    end

    --- Calls the provided function on each squad member, passing in their handle as the first
    --- argument, with any user supplied arguments passed in after in order 
    --- @param func fun(unit: userdata, ...?)
    --- @param ...? any
    function ai_squad:for_each(func, ...)
        vsp.utility.required_param(func, "func", "function", "Reloaded")
        for unit in self.members:iterator() do
            func(unit, ...)
        end
    end
end
return rl_ai_squad