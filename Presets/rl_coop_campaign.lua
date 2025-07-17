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
local vsp = require("vsp")

assert(not vsp.utility.post_start(), "Reloaded: preset config must be loaded before Start()")

local rl_coop_campaign = {}
do
    local cfg = {}

    -- Define config
    cfg.max_players = 4
    cfg.starting_lives = 1
    cfg.starting_recyclers = false
    cfg.service_buildings = true
    cfg.enemy_team_num = 15

    -- Apply runnable options
    
    -- This needs to run post Start()
    vsp.utility.defer(function ()
        exu.SetLives(cfg.starting_lives)
    end)

    if cfg.starting_recyclers == false then
        exu.DisableStartingRecycler()
    end

    if cfg.service_buildings then
        reloaded.service_building.autodetect(true)
    end

    setmetatable(rl_coop_campaign, {
        __index = cfg,
        __newindex = function (t, k, v)
            error("Reloaded: attempted to modify preset config")
        end
    })
end
return rl_coop_campaign