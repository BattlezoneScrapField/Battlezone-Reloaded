--[[
=======================================
*   Battlezone: Reloaded
*   
*   Singleplayer testing playground
=======================================
--]]

local reloaded = require("reloaded")

local exu = require("exu")
local vsp = require("vsp")

reloaded.smart_turrets.enable_smart_turrets()
reloaded.smart_turrets.auto_detect()

function GameKey(key)
    if key == "G" then
        reloaded.smart_turrets.make_smart_turret(GetTarget(GetPlayerHandle()))
    end
    if key == "B" then

    end
    if key == "N" then

    end
end

function Start()
    reloaded.Start()
end

function Update(dt)
    reloaded.Update(dt)
end

function CreateObject(h)
    reloaded.CreateObject(h)
end

function DeleteObject(h)
    reloaded.DeleteObject(h)
end

function CreatePlayer(id, name, team)
    reloaded.CreatePlayer(id, name, team)
end

function DeletePlayer(id, name, team)
    reloaded.DeletePlayer(id, name, team)
end

function Receive(from, type, ...)
    reloaded.Receive(from, type, ...)
end

function AddScrap(team, amount)
    reloaded.AddScrap(team, amount)
end
