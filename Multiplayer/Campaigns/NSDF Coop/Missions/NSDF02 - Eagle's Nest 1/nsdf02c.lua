--[[
=======================================
*   Battlezone: Reloaded
*
*   Coop Campaign
*
*   NSDF02 - Eagle's Nest 1
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
    "strike_cinematic_2",
    "transports_arrived",
    "evacuate_transports",
    "mission_failed"
)

local my_team = reloaded.team.make_team("4th Platoon", vsp.utility.sequence(coop_config.max_players))
local enemy_team = reloaded.team.make_team("6th Tank Battalion", coop_config.enemy_team_num)

local mission = reloaded.coop_mission.make_coop(my_team, coop_config)

mission:set_initial_state(mission_phase.startup)

for i = 1, mission.team:get_player_count() do
    mission:set_spawn_direction(i, vsp.math3d.east)
end

mission.var.wave_time = 30.0 -- Time in between soviet attack waves

-- Some objects will need to be deleted for the final cutscene, so we track them here
mission.var.objects_to_delete = {}
mission.var.deletable = vsp.set.make_set(
    "avturr",
    "avscav"
)
mission:define_global_listener("CreateObject", function(h)
    if mission.var.deletable:contains(GetOdf(h)) then
        table.insert(mission.var.objects_to_delete, h)
    end
end)


mission:define_state(mission_phase.startup,
nil,
function(state)
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
    mission.var.command_regen = vsp.time.make_timer(1.0, true, function()
        if not IsAlive(mission.var.command_tower) then return end
        if not vsp.net.is_hosting() then return end -- we only want to apply the healing once not once per player
        AddHealth(mission.var.command_tower, 50.0)
    end):start()

    -- The command tower will paint nearby targets
    mission.var.command_target_painting = vsp.time.make_timer(5.0, true, function()
        for obj in ObjectsInRange(100.0, mission.var.command_tower) do
            if GetTeamNum(obj) == mission.cfg.enemy_team_num then
                SetObjectiveOn(obj)
            end
        end
    end):start()

    -- This failure condition will last until the evacuation sequence, so we keep a handle
    -- to it to undefine it later
    mission.var.keep_command_alive = mission:define_global_listener("Update", function(dt)
        if not IsAlive(mission.var.command_tower) then
            mission.var.fail_delay = 5.0

            -- You lost the command tower grizzly one...
            AudioMessage("misn0302.wav")
            ClearObjectives()
            AddObjective("misn0311.otf", "red")
            AddObjective("misn0312.otf", "white")

            if mission.var.turrets_set then
                mission.var.fail_message = "misn03f1.des" -- forgot to build turrets and lost command tower?
            else
                mission.var.fail_message = "misn03f2.des" -- lost command tower
            end

            mission:change_state(mission_phase.mission_failed)
        end
    end)

    mission.var.keep_spower_alive = mission:define_global_listener("Update", function(dt)
        -- In the original script it checks if turrets are set, but it fails the mission with the same message so it was presumably cut from the game
        if not IsAlive(mission.var.s_powers.solar_2) then
            AudioMessage("misn0303.wav") -- commander you lost the solar arrays...
            ClearObjectives()
            AddObjective("misn0311.otf", "red")
            AddObjective("misn0312.otf", "white")

            mission.var.fail_delay = 5.0
            mission.var.fail_message = "misn03f3.des" -- you lost the solar array
            mission:change_state(mission_phase.mission_failed)
        end
    end)

    -- This is General Collins commander, you're just in time...
    AudioMessage("misn0311.wav")

    mission:change_state(mission_phase.wait_for_recycler)
end,
nil
)

mission:define_state(mission_phase.wait_for_recycler,
function(state, dt)
    if GetDistance(mission.var.recycler, "recycle_point") < 50.0 then
        mission:change_state(mission_phase.first_wave)
    end
end,
nil,
function (state)
    Stop(mission.var.recycler, 0)
end
)

mission:define_state(mission_phase.first_wave,
function(state, dt) -- Send the first wave retreating after one of them dies
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
function(state)
    state.var.fighter_1 = GetHandle("svfigh1")
    state.var.fighter_2 = GetHandle("svfigh2")

    Attack(state.var.fighter_1, mission.var.command_tower, 1)
    Attack(state.var.fighter_2, mission.var.command_tower, 1)
end,
nil
)

mission:define_state(mission_phase.recycler_ready,
nil,
function(state)
    vsp.utility.defer_for(5.0, function()
        -- The soviet forces are withdrawing commander...
        AudioMessage("misn0312.wav")
        ClearObjectives()
        AddObjective("misn0302.otf", "white")
        AddObjective("misn0301.otf", "white")
        mission:change_state(mission_phase.build_defenses)
    end)
end,
nil
)

mission:define_state(mission_phase.build_defenses,
function(state, dt)
    if CountUnitsNearObject(mission.var.command_tower, 200.0, 1, "avturr") > 3 then
        mission:change_state(mission_phase.second_wave)
    end
end,
nil,
function (state)
    mission.var.turrets_set = true
end
)

mission:define_state(mission_phase.second_wave,
nil,
function(state)
    local fighters = mission:build_scaled("svfigh", mission.cfg.enemy_team_num, 2, "spawn_scrap1")
    -- Note from VT, I think it's cleaner to just return nil for clients and then in the script handle it as:
    -- if (the local player owns these uses) then do stuff with them, as opposed to using a create object listener
    if fighters then
        reloaded.ai.squad.make_squad(fighters):attack(mission.var.command_tower)
        vsp.utility.defer_for(mission.var.wave_time, mission.change_state, mission, mission_phase.third_wave)
    end
end,
nil
)

mission:define_state(mission_phase.third_wave,
nil,
function(state)
    local fighters = mission:build_scaled("svfigh", mission.cfg.enemy_team_num, 2, "spawn_scrap1")
    if fighters then
        reloaded.ai.squad.make_squad(fighters):attack(mission.var.command_tower)
        vsp.utility.defer_for(mission.var.wave_time, mission.change_state, mission, mission_phase.fourth_wave)
    end
end,
nil
)

mission:define_state(mission_phase.fourth_wave,
function(state, dt)

end,
function(state)
    local apcs = mission:build_scaled("svapc", mission.cfg.enemy_team_num, 1, "spawn_scrap1")
    local tanks = mission:build_scaled("svtank", mission.cfg.enemy_team_num, 1, "spawn_scrap1")
    local fighters = mission:build_scaled("svfigh", mission.cfg.enemy_team_num, 1, "spawn_scrap1")

    -- Clients will not have a handle to these objects so only the host
    -- runs the following code
    if not apcs or not tanks or not fighters then return end

    local apc_strike_force = reloaded.ai.squad.make_squad(unpack(apcs), unpack(fighters))
    if IsAlive(mission.var.recycler) then
        apc_strike_force:attack(mission.var.recycler)
    elseif IsAlive(mission.var.s_powers.solar_3) then
        apc_strike_force:attack(mission.var.s_powers.solar_3)
    elseif IsAlive(mission.var.s_powers.solar_4) then
        apc_strike_force:attack(mission.var.s_powers.solar_4)
    end

    local tank_force = reloaded.ai.squad.make_squad(unpack(tanks))
    tank_force:attack(mission.var.s_powers.solar_2)

    vsp.utility.defer_for(mission.var.wave_time, mission.change_state, mission, mission_phase.backup_arrived)
end,
nil
)

mission:define_state(mission_phase.backup_arrived,
function(state, dt) -- which unit in the backup table doesn't really matter
    if state.var.wait_for_cinematic == true then return end -- we only want this to run once and since it's such a small part it's not worth making a new state for it
    if GetDistance(state.var.my_backup.leader, mission.var.s_powers.solar_2) < 75.0 then
        state.var.wait_for_cinematic = true
        state.var.my_backup:stop(0)
        vsp.utility.defer_for(mission.var.wave_time, mission.change_state, mission, mission_phase.strike_cinematic_1)
    end
end,
function(state)
    -- This code runs per player
    local my_scout = exu.BuildSyncObject("avfigh", exu.GetMyNetID(), "spawn_scrap2")
    local my_tank = exu.BuildSyncObject("avtank", exu.GetMyNetID(), "spawn_scrap2")

    state.var.my_backup = reloaded.ai.squad.make_squad(my_tank, my_scout)

    state.var.my_backup:goto(mission.var.s_powers.solar_2)

    -- Commander, reinforcements are returning from outpost 2...
    AudioMessage("misn0314.wav")

    state.var.wait_for_cinematic = false
end,
nil
)

mission:define_state(mission_phase.strike_cinematic_1,
function(state, dt)
    if not state.var.cinematic_ready then return end
    CameraPath("movie_path", 175, 850, mission.var.prop1)
    if mission.var.prop1 then
        Defend(mission.var.prop1, 1)
    end
end,
function(state)
    local mvar = mission.var -- alias for brevity

    -- The host manages the props, but clients need a handle to prop1 for the cinematic
    local prop1 = mission:build_single_object("svrecy", mission.cfg.enemy_team_num, "recy_spawn")
    mission:sync_mission_var("prop1", prop1, function ()
        -- Satellite recon indicates that a massive soviet strike force has landed...
        mission.var.audmsg = AudioMessage("misn0305.wav")
        vsp.cinematic.try_ready()

        mvar.prop2 = mission:build_single_object("svmuf", mission.cfg.enemy_team_num, "muf_spawn")
        mvar.prop3 = mission:build_single_object("svtank", mission.cfg.enemy_team_num, "tank1_spawn")
        mvar.prop4 = mission:build_single_object("svtank", mission.cfg.enemy_team_num, "tank2_spawn")
        mvar.prop5 = mission:build_single_object("svfigh", mission.cfg.enemy_team_num, "fighter1_spawn")

        mvar.guy1 = mission:build_single_object("sssold", mission.cfg.enemy_team_num, "guy1_spawn")
        mvar.guy2 = mission:build_single_object("sssold", mission.cfg.enemy_team_num, "guy2_spawn")
        mvar.guy3 = mission:build_single_object("sssold", mission.cfg.enemy_team_num, "guy1_spawn")
        mvar.guy4 = mission:build_single_object("sssold", mission.cfg.enemy_team_num, "guy2_spawn")

        -- All props are host-managed so we just need to check one
        if mvar.prop2 then
            Defend(mvar.prop1, 1)
            Goto(mvar.prop2, "tank1_spawn", 1)
            Goto(mvar.prop3, "that_path", 1)
            Goto(mvar.prop4, "cool_path", 1)
            Goto(mvar.prop5, "cool_path", 1)
            Goto(mvar.guy1, "guy_spot", 1)
            Goto(mvar.guy2, "guy_spot", 1)
            Goto(mvar.guy3, "guy_spot", 1)
            Goto(mvar.guy4, "guy_spot", 1)
        end

        state.var.cinematic_ready = true

        vsp.utility.defer_for(7.5, mission.change_state, mission, mission_phase.strike_cinematic_2)
        end)
    end,
nil
)

mission:define_state(mission_phase.strike_cinematic_2,
function(state, dt)
    CameraPath("movie_path", 175, 850, mission.var.prop1)
end,
function(state)
    mission.var.prop8 = mission:build_single_object("svfigh", mission.cfg.enemy_team_num, "muf_spawn")
    mission.var.prop9 = mission:build_single_object("svfigh", mission.cfg.enemy_team_num, "muf_spawn")
    if mission.var.prop8 then
        Goto(mission.var.prop8, "tank2_spawn", 1)
        Goto(mission.var.prop9, "fighter1_spawn", 1)
    end

    -- The cinematic automatically ends after 7 seconds
    state.var.end_timer = vsp.time.make_timer(7.0, false, mission.change_state, mission,
        mission_phase.transports_arrived):start()
end,
function(state)
    StopAudioMessage(mission.var.audmsg)

    local mvar = mission.var

    vsp.net.remove_sync_object(mvar.prop1)
    vsp.net.remove_sync_object(mvar.prop2)
    vsp.net.remove_sync_object(mvar.prop3)
    vsp.net.remove_sync_object(mvar.prop4)
    vsp.net.remove_sync_object(mvar.prop5)
    vsp.net.remove_sync_object(mvar.prop6)
    vsp.net.remove_sync_object(mvar.prop7)
    vsp.net.remove_sync_object(mvar.prop8)
    vsp.net.remove_sync_object(mvar.prop9)
    vsp.net.remove_sync_object(mvar.guy1)
    vsp.net.remove_sync_object(mvar.guy2)
    vsp.net.remove_sync_object(mvar.guy3)
    vsp.net.remove_sync_object(mvar.guy4)
end
)

mission:define_state(mission_phase.transports_arrived,
nil,
function(state)
    vsp.cinematic.try_finish()

    -- Once the transports arrive the command and solar arrays are allowed to die, and we stop healing the command tower and disable it's target painting
    mission:undefine_global_listener("Update", mission.var.keep_command_alive)
    mission:undefine_global_listener("Update", mission.var.keep_spower_alive)
    mission.var.command_regen:stop()
    mission.var.command_target_painting:stop()

    mission.var.rescue_1 = mission:build_single_object("avapc", 1, "apc1_spawn")
    mission.var.rescue_2 = mission:build_single_object("avapc", 1, "apc2_spawn")

    SetObjectiveOff(mission.var.command_tower)
    SetObjectiveOff(mission.var.s_powers[1])

    SetObjectiveOn(mission.var.rescue_1)
    SetObjectiveName(mission.var.rescue_1, "Transport 1")

    SetObjectiveOn(mission.var.rescue_2)
    SetObjectiveName(mission.var.rescue_2, "Transport 2")

    mission.var.launch_pad = GetHandle("launch_pad")

    ClearObjectives()
    AddObjective("misn0311.otf", "green")
    AddObjective("misn0312.otf", "green")
    AddObjective("misn0303.otf", "white")

    vsp.utility.defer_for(30.0, mission.change_state, mission, mission_phase.evacuate_transports)
end,
nil
)

mission:define_state(mission_phase.evacuate_transports,
function(state, dt)

end,
function(state)
    if mission.var.rescue_1 then
        Retreat(mission.var.rescue_1, "rescue_path")
        Retreat(mission.var.rescue_2, "rescue_path")
    end

    -- Relocate turrets from the crater to block the path to the launch pad
    Retreat(GetHandle("enemyturret_1"), "turret_path1")
    Retreat(GetHandle("enemyturret_2"), "turret_path2")
    Retreat(GetHandle("enemyturret_3"), "turret_path3")
    Retreat(GetHandle("enemyturret_4"), "base")

    -- Commander, take up a position in front of the transports...
    AudioMessage("misn0315.wav")
end,
function(state)

end)


mission:define_state(mission_phase.mission_failed,
nil,
function (state)
    vsp.utility.defer_for(mission.var.fail_delay, mission.fail, mission, mission.var.fail_message)
end,
nil)

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
