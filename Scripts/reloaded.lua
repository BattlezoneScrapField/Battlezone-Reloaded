--[[
=======================================
*   Battlezone: Reloaded
*   
*   Standard script entry point
*
*	Required Event Handlers:
*	- Update(dt)
=======================================
--]]

local RequireFix = require("RequireFix")
RequireFix.Initialize("3522264415")

local vsp = require("vsp")

local reloaded = {}
do
    reloaded.coop_mission     = require("rl_coop_mission")
    reloaded.mission          = require("rl_mission")
    reloaded.service_building = require("rl_service_building")
    reloaded.team             = require("rl_team")

    function reloaded.Start()
        vsp.Start()

        reloaded.coop_mission.Start()
        reloaded.mission.Start()
    end

    function reloaded.Update(dt)
        vsp.Update(dt)

        reloaded.coop_mission.Update(dt)
        reloaded.mission.Update(dt)
    end

    function reloaded.CreateObject(h)
        vsp.CreateObject(h)

        reloaded.coop_mission.CreateObject(h)
        reloaded.mission.CreateObject(h)
    end

    function reloaded.DeleteObject(h)
        vsp.DeleteObject(h)
    end

    function reloaded.CreatePlayer(id, name, team)
        vsp.CreatePlayer(id, name, team)
    end

    function reloaded.DeletePlayer(id, name, team)
        vsp.DeletePlayer(id, name, team)
    end

    function reloaded.Receive(from, type, ...)
        vsp.Receive(from, type, ...)
    end

    function reloaded.AddScrap(team, amount)
        vsp.AddScrap(team, amount)
    end
end
return reloaded