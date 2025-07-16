--[[
=======================================
*   Battlezone: Reloaded
*   
*   Coop Campaign preset configuration
*   
*   require() this after all libraries
*   have been loaded but before the
*   mission script begins
*
=======================================
--]]

assert(package.loaded["reloaded"], "Reloaded: preset config must be loaded after the library")
local reloaded = require("reloaded")

local exu = require("exu")

local rl_coop_campaign = {}
do
    local cfg = {}

    cfg.max_players = 4
    cfg.starting_lives = 1
    cfg.starting_recyclers = false

    if cfg.starting_recyclers == false then
        exu.DisableStartingRecycler()
    end

    setmetatable(rl_coop_campaign, {
        __index = cfg,
        __newindex = function (t, k, v)
            error("Reloaded: attempted to modify preset config")
        end
    })
end
return rl_coop_campaign