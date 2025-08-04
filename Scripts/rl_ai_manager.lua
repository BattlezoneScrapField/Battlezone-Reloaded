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
    --- @type table<Handle, managed_ai>
    local all_managed_ai = {}

    --- @class managed_ai : object
    local managed_ai = vsp.object.make_class("managed_ai")

    --- @param h Handle
    function managed_ai:managed_ai(h)
        self.handle = vsp.functional.required_param(h, "h", "userdata", "Reloaded")

        all_managed_ai[h] = self
    end

    function managed_ai:__update(dt)
        self.position = GetPosition(self.handle)
    end

    --- Marks an AI unit as managed by Reloaded
    --- @param h Handle
    function rl_ai_manager.make_managed_ai(h)
        return managed_ai:new(h)
    end

    --- Checks if an object is a managed ai, returns
    --- a handle to the managed ai if it is, else false
    --- @param h Handle
    --- @return managed_ai | nil
    function rl_ai_manager.check_managed_ai(h)
        if all_managed_ai[h] then
            return all_managed_ai[h]
        else
            return nil
        end
    end

    local function update_all_managed_ai(dt)
        for h, ai in pairs(all_managed_ai) do
            if not IsValid(h) then
                all_managed_ai[h] = nil
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
