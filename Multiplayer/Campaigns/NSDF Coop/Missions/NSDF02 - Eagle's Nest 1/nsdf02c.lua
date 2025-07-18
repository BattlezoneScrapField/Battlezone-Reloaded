--[[
=======================================
*   Battlezone: Reloaded
*   
*   Coop Campaign
*
*	NSDF02 - Eagle's Nest 1
=======================================
--]]

local reloaded = require("reloaded")

local exu = require("exu")
local vsp = require("vsp")

local coop_config = require("rl_coop_campaign")

local mission_phase = vsp.enum.make_string_enum(
	"startup",
	"wait_for_recycler",
	"first_wave",
	"recycler_ready",
	"build_defenses",
	"second_wave",
	"third_wave",
	"fourth_wave"
)

local my_team = reloaded.team.make_team("4th Platoon", vsp.utility.sequence(coop_config.max_players))
local enemy_team = reloaded.team.make_team("6th Tank Battalion", coop_config.enemy_team_num)

local mission = reloaded.coop_mission.make_coop(my_team)

mission:set_initial_state(mission_phase.startup)

for i = 1, mission.team:get_player_count() do
	mission:set_spawn_direction(i, vsp.math3d.east)
end

mission:define_state(mission_phase.startup,
function (state, dt) end,
function (state)
	mission.var.command_tower = GetHandle("command") -- this is errorneouSly called "solar1" in the original script
	mission.var.s_powers = {
		solar_2 = GetHandle("solar2"),
		solar_3 = GetHandle("solar3"),
		solar_4 = GetHandle("solar4")
	}
	mission.var.recycler = GetHandle("avrec3-1_recycler")
	
	SetScrap(reloaded.team.my_team_num(), 8)
	SetPilot(reloaded.team.my_team_num(), 10)

	SetObjectiveOn(mission.var.command_tower)
	SetObjectiveName(mission.var.command_tower, "Command Tower")

	SetObjectiveOn(mission.var.s_powers.solar_2)
	SetObjectiveName(mission.var.s_powers.solar_2, "Solar Array")

	Goto(mission.var.recycler, "recycle_point")
	ClearObjectives()
	AddObjective("misn0301.otf")

	-- The command tower slowly regenerates over time
	mission.var.command_regen = vsp.time.make_timer(1.0, true, function ()
		if not IsAlive(mission.var.command_tower) then return end
		AddHealth(mission.var.command_tower, 50.0)
	end):start()

	-- The command tower will paint nearby targets
	mission.var.command_target_painting = vsp.time.make_timer(5.0, true, function ()
		for obj in ObjectsInRange(100.0, mission.var.command_tower) do
			if GetTeamNum(obj) == coop_config.enemy_team_num then
				SetObjectiveOn(obj)
			end
		end
	end):start()

	-- This is General Collins commander, you're just in time...
	AudioMessage("misn0311.wav")

	mission:change_state(mission_phase.wait_for_recycler)
end,
function (state) end
)

mission:define_state(mission_phase.wait_for_recycler,
function (state, dt)
	if GetDistance(mission.var.recycler, "recycle_point") < 50.0 then
		mission:change_state(mission_phase.first_wave)
	end
end,
function (state)
	
end,
function (state)
	
end
)

mission:define_state(mission_phase.first_wave,
function (state, dt) -- Send the first wave retreating after one of them dies
	local done = false
	if not IsAlive(state.var.fighter_1) then
		Retreat(state.var.fighter_2, "retreat_path", 1)
		done = true
	elseif not IsAlive(state.var.fighter_2) then
		Retreat(state.var.fighter_1, "retreat_path", 1)
		done = true
	end
	
	if done then
		mission:change_state(mission_phase.recycler_ready)
	end
end,
function (state)
	Stop(mission.var.recycler, 0)

	state.var.fighter_1 = GetHandle("svfigh1")
	state.var.fighter_2 = GetHandle ("svfigh2")

	Attack(state.var.fighter_1, mission.var.command_tower, 1)
	Attack(state.var.fighter_2, mission.var.command_tower, 1)
end,
function (state)

end
)

mission:define_state(mission_phase.recycler_ready,
function (state, dt) end,
function (state)
	vsp.utility.defer_for(10.0, function ()
		-- The soviet forces are withdrawing commander...
		AudioMessage("misn0312.wav")
		ClearObjectives()
		AddObjective("misn0302.otf", "white")
		AddObjective("misn0301.otf", "white")
		mission:change_state(mission_phase.build_defenses)
	end)
end,
function (state) end)

mission:define_state(mission_phase.build_defenses,
function (state, dt)
	if CountUnitsNearObject(mission.var.command_tower, 200.0, 1, "avturr") > 3 then
		mission:change_state(mission_phase.second_wave)
	end
end,
function (state) end,
function (state) end
)

mission:define_state(mission_phase.second_wave,
function (state, dt) end,
function (state)
	local fighters = mission:build_multiple_objects("svfigh", coop_config.enemy_team_num, 2, "spawn_scrap1")
	reloaded.ai.squad.make_squad(unpack(fighters)):attack(mission.var.command_tower)

	vsp.utility.defer_for(30.0, mission.change_state, mission, mission_phase.third_wave)
end,
function (state) end
)

mission:define_state(mission_phase.third_wave,
function (state, dt)
	
end,
function (state)
	
end,
function (state)
	
end)

--- Stock event handlers

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

--- Extra Utilities event handlers

function exu.AddScrap(team, amount)
	reloaded.AddScrap(team, amount)
end