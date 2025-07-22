--[[
=======================================
*   Battlezone: Reloaded
*   
*   Coop Campaign
*
*	NSDF01 - Red Arrival
=======================================
--]]

local reloaded = require("reloaded")

local exu = require("exu")
local vsp = require("vsp")

-- Global rule preset config file
local coop_config = require("rl_coop_campaign")

-- This helper makes a table with the same string as both a key and value,
-- it will serve as a nice constant for defining mission states
local mission_phase = vsp.enum.make_string_enum(
	"intro_cinematic_1",
	"intro_cinematic_2",
	"wait_for_first_scavenger",
	"escort_first_scavenger",
	"first_fighter_attack",
	"second_fighter_attack",
	"first_scavenger_retreat",
	"escort_second_scavenger",
	"mission_success",
	"mission_failed"
)

-- 4 player coop: assigns teamnums from 1 to 4 (max) as part of a team and allies them
local my_team = reloaded.team.make_team("4th Platoon", vsp.utility.sequence(coop_config.max_players))

local enemy_team = reloaded.team.make_team("Bogeys", coop_config.enemy_team_num)

-- this initializes the coop mission wrappuh, this object inherits all methods
-- from the regular mission class, and also contains special methods that we'll
-- use for coop synchronization
local mission = reloaded.coop_mission.make_coop(my_team, coop_config)

-- This will be the state that the mission starts in when it's
-- initialized in Start(), most things are initialized in Start()
-- under the hood, so you should be calling these setup functions
-- "loose" in the script pre-start
mission:set_initial_state(mission_phase.intro_cinematic_1)

-- set all 4 players to be facing towards their ships at the start
for i = 1, mission.team:get_player_count() do
	mission:set_spawn_direction(i, vsp.math3d.east)
end

-- You define a mission state by giving it a name, an update function, an enter function, and an exit function.
-- In this case the name is defined in a table to keep things organized, strings are always good if you need
-- to inspect the name of the state easily at runtime. The update function will run every frame while the mission
-- is in the given state, it should be responsible for listening for the right condition to advance the mission.
-- The other method is by defining an event listener like for CreateObject for example that will be attached to the
-- current state, we'll see that used later.
-- 
-- These two methods should not perform logic other than propagating a state
-- change. This is due to a race condition when multiple players are waiting for a condition to change, the first player
-- will set their variables and tell the others to change state prematurely. To avoid this, perform logic in the enter
-- and exit functions which are called when the state is entered or exited respectively. The only caveat is that if you
-- need to perform logic in an event listener, you will need to call wait_for_all_clients() to wait for all players to
-- fire off the event and set their variables before changing state. You can also use this in the update function,
-- but it's not recommended since it's simpler to just perform logic in enter/exit.
--
-- Finally, a mission has a .var field that you should use to store global variables to the mission.
-- DO NOT USE LUA GLOBAL VARIABLES. Each state additionally has a .var field to store state-local variables,
-- the state instance is passed in as the first parameter to each of the three functions so you can use that to
-- access the variables between them, again do not use global variables.

mission:define_state(mission_phase.intro_cinematic_1,
function (state, dt) -- update function
	-- the update function of the state should only be listening for conditions,
	-- the AFFECTS of the conditions should be in the on_enter or on_exit functions,
	-- that way the mission state is correctly propagated to remote players
	if CameraPath("fixcam", 1200, 250, state.var.lander) or vsp.cinematic.skipped() then
		mission:change_state(mission_phase.intro_cinematic_2)
	end
end,
function (state) -- enter function, since this is also the initial state it will be called immediately upon loading
	mission.var.local_player = GetPlayerHandle()

	local pos = GetPosition(mission.var.local_player)
	SetPosition(mission.var.local_player, pos + (vsp.math3d.down * 10)) -- prevent pilot from making sound when spawning and hitting the ground

	mission.var.dummy_player = GetHandle("fake_player")
	mission.var.my_comm_tower = GetHandle("abcomm1_i76building")
	mission.var.my_recycler = GetHandle("avrecy-1_recycler")

	-- first failure condition: comm tower destroyed
	mission:define_global_listener("Update", function ()
		if not IsAlive(mission.var.my_comm_tower) then
			mission:change_state(mission_phase.mission_failed)
		end
	end)

	-- second failure condition: recycler destroyed
	mission:define_global_listener("Update", function ()
		if not IsAlive(mission.var.my_recycler) then
			mission:change_state(mission_phase.mission_failed)
		end
	end)

	mission.var.bbase = GetHandle("apbase-1_camerapod")
	mission.var.bgoal = GetHandle("apscrap-1_camerapod")

	SetUserTarget(mission.var.bgoal)

	mission.var.scrap_piece_1 = GetHandle("sscr_171_scrap")
	mission.var.scrap_piece_2 = GetHandle("sscr_176_scrap")

	state.var.lander = GetHandle("avland0_wingman")

	mission.var.message = AudioMessage("misn0230.wav")
	vsp.cinematic.try_ready()
end,
function (state) end
)

mission:define_state(mission_phase.intro_cinematic_2,
function (state, dt) -- update
	if CameraPath("zoomcam", 1200, 800, mission.var.dummy_player) or vsp.cinematic.skipped() then
		mission:change_state(mission_phase.wait_for_first_scavenger)
	end
end,
function () -- enter
	Goto(mission.var.dummy_player, "player_path")
end,
function () -- exit
	vsp.cinematic.try_finish()

	vsp.net.remove_sync_object(mission.var.dummy_player)

	StopAudioMessage(mission.var.message)
	AudioMessage("misn0224.wav")
	AddObjective("misn02b1.otf", "WHITE")

	SetMaxPilot(GetTeamNum(GetPlayerHandle()), 10)
	SetMaxScrap(GetTeamNum(GetPlayerHandle()), 30)
	SetPilot(GetTeamNum(GetPlayerHandle()), 2)
	SetScrap(GetTeamNum(GetPlayerHandle()), 5)

	vsp.shared_resource.make_scrap_shared()
end
)

-- This state is purely waiting on the event listener that we will define later, technically we don't
-- have to define functions at all if we don't use them (or pass in nil), but I'm just showing what an
-- empty state definition looks like
mission:define_state(mission_phase.wait_for_first_scavenger,
function (state, dt) end,
function (state) end,
function (state) end
)

-- An event listener is defined by first attaching it to a prexisting state, and inputing the
-- string name of the stock event handler (CreateObject in this case), as well as a function that
-- will be called, and should take all parameters that the event handler passes in (h in this case).
-- 
-- This listener is what will trigger the next mission state, but we also need to store the handle of
-- the scavenger that's built, so in order for all players to receive this data we need to synchronize it
-- manually. Once all players have acknowledged that they have the data, the mission can change state.
mission:define_event_listener(mission_phase.wait_for_first_scavenger, "CreateObject", function (h)
	if GetTeamNum(h) == 1 and IsOdf(h, "avscav") then
		mission.var.first_scav = h
		-- This is where we need to use manual synchronization, we will wait until all players fire off this event
		-- and save the handle of the scav.
		-- Remember that since we are calling a method, we need to manually pass in "self" (the mission variable)
		-- as the first parameter to the callback. Only the host will call this function as well.
		vsp.net.wait_for_all_clients(mission.change_state, mission, mission_phase.escort_first_scavenger)
	end
end
)

mission:define_state(mission_phase.escort_first_scavenger,
function (state, dt)
	if GetDistance(mission.var.first_scav, mission.var.scrap_piece_1) < 75.0 then
		mission:change_state(mission_phase.first_fighter_attack)
	end
end,
function (state)
	SetCritical(mission.var.first_scav, true)
	-- every update this event will now check to see if the scav is alive,
	-- and if it dies it will fail the mission regardless of state due to being global
	mission:define_global_listener("Update", function (dt)
		if not IsAlive(mission.var.first_scav) then
			mission:change_state(mission_phase.mission_failed)
		end
	end
	)
end,
function (state) end
)

mission:define_state(mission_phase.first_fighter_attack,
function (state, dt)
	if GetDistance(mission.var.first_scav, mission.var.scrap_piece_2) < 200.0 then
		mission:change_state(mission_phase.second_fighter_attack)
	end

	-- This condition starts immediately after the first fighter attack,
	-- you can skip the second attack if you want
	if GetDistance(mission.var.my_comm_tower, mission.var.first_scav) < 300.0 then
		mission:change_state(mission_phase.escort_second_scavenger)
	end
end,
function (state)
	mission:build_scaled("svfigh", mission.enemy_team, 1, GetPosition("spawn1"))

	AudioMessage("misn0233.wav")
end,
function (state) end
)

mission:define_event_listener(mission_phase.first_fighter_attack,
"CreateObject",
function (h)
	if IsOdf(h, "svfigh") then
		Goto(h, "patrol1", 0)
		SetObjectiveOn(h)
	end
end
)

mission:define_state(mission_phase.second_fighter_attack,
function (state, dt)
	-- This is where the mission has a possibility to branch!
	-- If the scav gets shot it will trigger the forced retreat state, which
	-- can be avoided if the fighters are killed and scav returns to base
	-- unharmed, this will trigger the final objective
	if GetLastEnemyShot(mission.var.first_scav) > 0 then
		mission:change_state(mission_phase.first_scavenger_retreat)
	end

	-- this condition is also defined in this state because it can occur from both
	if GetDistance(mission.var.my_comm_tower, mission.var.first_scav) < 300.0 then
		mission:change_state(mission_phase.escort_second_scavenger)
	end
end,
function (state)
	mission:build_scaled("svfigh", mission.enemy_team, 1, GetPosition("spawn2"))
end,
function (state) end
)

mission:define_event_listener(mission_phase.second_fighter_attack, "CreateObject", function (h)
	if IsOdf(h, "svfigh") then
		if GetDistance(mission.var.first_scav, mission.var.bgoal) < 200.0 then
			Attack(h, mission.var.first_scav)
		else
			Goto(h, "patrol2", 0) -- attack scrap field
		end
	end
end
)

-- This state may or not be triggered depending on if the scav takes damage
-- or not, it's possible to skip by immediately sending the scav back to base
-- after the first fighter attacks
mission:define_state(mission_phase.first_scavenger_retreat,
function (state, dt)
	-- this condition is also defined in this state because it can occur from both
	if GetDistance(mission.var.my_comm_tower, mission.var.first_scav) < 300.0 then
		mission:change_state(mission_phase.escort_second_scavenger)
	end
end,
function (state)
	Follow(mission.var.first_scav, mission.var.my_comm_tower, 0)
	ClearObjectives();
		AddObjective("misn02b2.otf", "WHITE")
		--[[
			misn0225
			Commander our insturments show that you are heavily
			ounumbered..
		--]]
		AudioMessage("misn0225.wav")
		SetUserTarget(mission.var.bbase)
end,
function (state) end
)

mission:define_state(mission_phase.escort_second_scavenger,
function (state, dt)
	-- Final win condition
	if GetDistance(mission.var.my_comm_tower, mission.var.second_scav) < 200.0 then
		mission:change_state(mission_phase.mission_success)
	end
end,
function (state)
		--[[
			Now rescue the second
			scavenger
		--]]
		Follow(mission.var.first_scav, mission.var.my_comm_tower)
		-- Remember that only the host builds objects, so when we need
		-- all clients to get their handle and perform actions we need to use
		-- an event listener for CreateObject (defined below)
		mission:build_single_object("avscav", 1, GetPosition("spawn3"))

		vsp.utility.defer_for(10, mission.build_scaled, mission, "svfigh", mission.enemy_team, 1, GetPosition("spawn4"))
end,
function (state) end
)

mission:define_event_listener(mission_phase.escort_second_scavenger, "CreateObject", function (h)
	if IsOdf(h, "avscav") then
		mission.var.second_scav = h
		SetCritical(h, true)
		Retreat(h, "retreat")
		SetObjectiveOn(h)
		AudioMessage("misn0228.wav")

		-- track the scav and make sure it stays alive
		mission:define_global_listener("Update", function (dt)
			if not IsAlive(mission.var.second_scav) then
				mission:change_state(mission_phase.mission_failed)
			end
		end)
	end
end
)

-- This tells the built fighter(s) to attack the second scav
mission:define_event_listener(mission_phase.escort_second_scavenger, "CreateObject", function (h)
	if IsOdf(h, "svfigh") then
		Attack(h, mission.var.second_scav)
	end
end
)

mission:define_state(mission_phase.mission_success,
function (state, dt)
	if IsAudioMessageDone(state.var.message) then
		mission:succeed("misn02w1.des") -- this is a synchronized wrapper
	end
end,
function (state)
	ClearObjectives()
	AddObjective("misn02b3.otf", "GREEN")
	AddHealth(mission.var.first_scav, 1000.0)
	AddHealth(mission.var.second_scav, 1000.0)

	state.var.message = AudioMessage("misn0234.wav")
end,
function (state) end
)

mission:define_state(mission_phase.mission_failed,
function (state, dt)
	if IsAudioMessageDone(state.var.message) then
		mission:fail("misn02l1.des") -- this is a synchronized wrapper
	end
end,
function (state)
	ClearObjectives()
	AddObjective("misn02b4.otf","RED")
	state.var.message = AudioMessage("misn0227.wav")
end,
function (state) end
)

-- Hack to get rid of the anomalous team 0 grizzly that constantly
-- respawns and causes a volcano glitch if deleted lol
local function banish_fking_neutral_grizzly(h)
	if GetTeamNum(h) == 0 and GetClassLabel(h) == "wingman" then
		local pos = GetPosition(h)
		SetPosition(h, pos + (vsp.math3d.east * 500))
	end
end

--- Stock event handlers

function Start()
	reloaded.Start()
end

function Update(dt)
	reloaded.Update(dt)
end

function CreateObject(h)
	reloaded.CreateObject(h)

	banish_fking_neutral_grizzly(h)
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