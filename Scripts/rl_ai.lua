--[[
=======================================
*   Battlezone: Reloaded
*
*   AI Subsystem Header
=======================================
--]]

local rl_ai = {}
do
    rl_ai.manager   = require("rl_ai_manager")
    rl_ai.scaling   = require("rl_ai_scaling")
    rl_ai.squad     = require("rl_ai_squad")
    rl_ai.targeting = require("rl_ai_targeting")

    -- Top level defintions for commonly used functions
    rl_ai.make_squad = rl_ai.squad.make_squad

    function rl_ai.Start()
    end

    function rl_ai.Update(dt)
        rl_ai.manager.Update(dt)
    end
end
return rl_ai
