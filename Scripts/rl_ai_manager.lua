--[[
=======================================
*   Battlezone: Reloaded
*
*   AI Manager Module
*
*   Handles AI units managed by
*   reloaded
*
*   Exported Classes:
*   - managed_ai
*
*	Required Event Handlers:
*	- Update(dt)
=======================================
--]]

local vsp = require("vsp")

local rl_ai_manager = {}
do
    local all_managed_ai = vsp.set.make_set()

    --- @class managed_ai : object
    local managed_ai = vsp.object.make_class("managed_ai")

    --- @param h Handle
    function managed_ai:managed_ai(h)
        self.handle = vsp.utility.required_param(h, "h", "userdata", "Reloaded")

        all_managed_ai:insert(self)
    end

    function managed_ai:__update(dt)
        self:abstract("__update")
    end

    --- Marks an AI unit as managed by Reloaded
    --- @param h Handle
    function rl_ai_manager.make_managed_ai(h)
        return managed_ai:new(h)
    end

    local function update_all_managed_ai(dt)
        for ai in all_managed_ai:iterator() do
            if not IsValid(ai.handle) then
                all_managed_ai:remove(ai)
            else
                ai:__update(dt)
            end
        end
    end

    rl_ai_manager.managed_ai = managed_ai

    function rl_ai_manager.Update(dt)
        update_all_managed_ai(dt)
    end
end
return rl_ai_manager
