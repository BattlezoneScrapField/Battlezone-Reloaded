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
	"fourth_wave",
	"backup_arrived",
	"strike_cinematic_1",
	"strike_cinematic_2"
)

local my_team = reloaded.team.make_team("4th Platoon", vsp.utility.sequence(coop_config.max_players))
local enemy_team = reloaded.team.make_team("6th Tank Battalion", coop_config.enemy_team_num)

local mission = reloaded.coop_mission.make_coop(my_team, coop_config)

mission:set_initial_state(mission_phase.startup)

for i = 1, mission.team:get_player_count() do
	mission:set_spawn_direction(i, vsp.math3d.east)
end

mission.var.wave_time = 30.0 -- Time in between soviet attack waves

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
	
	SetScrap(reloaded.team.my_team_num(), 80)
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
			if GetTeamNum(obj) == mission.cfg.enemy_team_num then
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
	local fighters = mission:build_scaled("svfigh", mission.cfg.enemy_team_num, 2, "spawn_scrap1")
	-- Note from VT, I think it's cleaner to just return nil for clients and then in the script handle it as:
	-- if (the local player owns these uses) then do stuff with them, as opposed to using a create object listener
	if fighters then
		reloaded.ai.squad.make_squad(fighters):attack(mission.var.command_tower)
		vsp.utility.defer_for(mission.var.wave_time, mission.change_state, mission, mission_phase.third_wave)
	end
end,
function (state) end
)

mission:define_state(mission_phase.third_wave,
function (state, dt) end,
function (state)
	local fighters = mission:build_scaled("svfigh", mission.cfg.enemy_team_num, 2, "spawn_scrap1")
	if fighters then
		reloaded.ai.squad.make_squad(fighters):attack(mission.var.command_tower)
		vsp.utility.defer_for(mission.var.wave_time, mission.change_state, mission, mission_phase.fourth_wave)
	end
end,
function (state) end
)

mission:define_state(mission_phase.fourth_wave,
function (state, dt)

end,
function (state)
	local apcs = mission:build_scaled("svapc", mission.cfg.enemy_team_num, 1, "spawn_scrap1")
	local tanks = mission:build_scaled("svtank", mission.cfg.enemy_team_num, 1, "spawn_scrap1")
	local fighters = mission:build_scaled("svfigh", mission.cfg.enemy_team_num, 1, "spawn_scrap1")

	if not apcs or not tanks or not fighters then return end

	local apc_strike_force = reloaded.ai.make_squad(unpack(apcs), unpack(fighters))
	if IsAlive(mission.var.recycler) then
		apc_strike_force:attack(mission.var.recycler)
	elseif IsAlive(mission.var.s_powers.solar_3) then
		apc_strike_force:attack(mission.var.s_powers.solar_3)
	elseif IsAlive(mission.var.s_powers.solar_4) then
		apc_strike_force:attack(mission.var.s_powers.solar_4)
	end

	local tank_force = reloaded.ai.make_squad(unpack(tanks))
	tank_force:attack(mission.var.s_powers.solar_2)

	vsp.utility.defer_for(mission.var.wave_time, mission.change_state, mission, mission_phase.backup_arrived)
end,
function (state)
	
end
)

mission:define_state(mission_phase.backup_arrived,
function (state, dt)
	if not state.var.backup then return end
	if GetDistance(state.var.backup.leader, mission.var.s_powers.solar_2) < 75.0 then
		state.var.backup:stop()
		vsp.utility.defer_for(mission.var.wave_time, mission.change_state, mission, mission_phase.strike_cinematic_1)
	end
end,
function (state)
	local scouts = mission:build_scaled("avfigh", 1, 1, "spawn_scrap2")
	local tanks = mission:build_scaled("avtank", 1, 1, "spawn_scrap2")
	AudioMessage("misn0314.wav")
	if scouts and tanks then
		state.var.backup = reloaded.ai.make_squad(unpack(tanks), unpack(scouts))
		backup:goto(mission.var.s_powers.solar_2)
	end
end,
function (state) end
)

mission:define_state(mission_phase.strike_cinematic_1,
function (state, dt)
	CameraPath("movie_path", 175, 850, mission.var.prop1)
end,
function (state)
	mission.var.audmsg = AudioMessage("misn0305.wav")
	vsp.cinematic.try_ready()

	-- Using async objects here since they are "props" and makes the netcode simpler
	mission.var.prop1 = exu.BuildAsyncObject("svrecy", mission.cfg.enemy_team_num, "recy_spawn")
	mission.var.prop2 = exu.BuildAsyncObject("svmuf", mission.cfg.enemy_team_num, "muf_spawn")
	mission.var.prop3 = exu.BuildAsyncObject("svtank", mission.cfg.enemy_team_num, "tank1_spawn")
	mission.var.prop4 = exu.BuildAsyncObject("svtank", mission.cfg.enemy_team_num, "tank2_spawn")
	mission.var.prop5 = exu.BuildAsyncObject("svfigh", mission.cfg.enemy_team_num, "fighter1_spawn")
	mission.var.guy1 = exu.BuildAsyncObject("sssold", mission.cfg.enemy_team_num, "guy1_spawn")
	mission.var.guy2 = exu.BuildAsyncObject("sssold", mission.cfg.enemy_team_num, "guy2_spawn")
	mission.var.guy3 = exu.BuildAsyncObject("sssold", mission.cfg.enemy_team_num, "guy1_spawn")
	mission.var.guy4 = exu.BuildAsyncObject("sssold", mission.cfg.enemy_team_num, "guy2_spawn")

	vsp.utility.defer_for(7.5, mission.change_state, mission, mission_phase.strike_cinematic_2)

end,
function (state) end
)

mission:define_state(mission_phase.strike_cinematic_2,
function (state, dt)
	CameraPath("movie_path", 175, 850, mission.var.prop1)
end,
function (state)
	mission.var.prop8 = exu.BuildAsyncObject("svfigh", 2, "muf_spawn")
	mission.var.prop9 = exu.BuildAsyncObject("svfigh", 2, "muf_spawn")
	Goto(prop8, "tank2_spawn", 1)
	Goto(prop9, "fighter1_spawn", 1)
end,
function (state)
	
end
)

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