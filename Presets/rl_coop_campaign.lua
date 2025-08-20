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
    cfg.service_buildings = true      -- Use enhanced service buildings (like BZP)
    cfg.enemy_team_num = 15
    cfg.shot_convergence = true       -- Enable hovercraft shot convergence (like BZ2)
    cfg.extended_smart_reticle = true -- Extend the range of the smart reticle (like BZ2)
    cfg.smart_reticle_range = 500.0   -- The new range of the reticle of extended range is enabled
    cfg.enemy_count_scaling = true    -- Set built in AI scaling methods to scale linearly with player count if used
    cfg.smart_turrets = true          -- Enable enhanced turret/tower AI (like BZP)

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

    if cfg.shot_convergence then
        exu.SetShotConvergence(true)
    end

    if cfg.extended_smart_reticle then
        exu.SetReticleRange(cfg.smart_reticle_range)
    end

    if cfg.enemy_count_scaling then
        vsp.utility.defer(function () -- player count is defined post Start()
            reloaded.ai.scaling.set_scaling_method(reloaded.ai.scaling.count, function (initial_count)
                return initial_count * vsp.net_player.get_player_count()
            end)
        end)
    end

    if cfg.smart_turrets then
        reloaded.smart_turrets.enable_smart_turrets()
        reloaded.smart_turrets.auto_detect()
    end

    -- Make cfg read only
    setmetatable(rl_coop_campaign, {
        __index = cfg,
        __newindex = function (t, k, v)
            error("Reloaded: attempted to modify preset config")
        end
    })
end
return rl_coop_campaign
