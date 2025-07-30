--[[
=======================================
*   Battlezone: Reloaded
*   
*   AI Subsystem Header
=======================================
--]]

local rl_ai = {}
do
    rl_ai.scaling = require("rl_ai_scaling")
    rl_ai.squad   = require("rl_ai_squad")

    -- Top level defintions for commonly used functions
    rl_ai.make_squad = rl_ai.squad.make_squad
end
return rl_ai
