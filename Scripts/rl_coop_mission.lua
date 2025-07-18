--[[
=======================================
*   Battlezone: Reloaded
*   
*   Coop Mission Module
*
*   Multiplayer safe wrapper for
*   missions. Automatically handles
*   synchronization.
*
*   Required Event Handlers:
*   - Start()
*   - Update(dt)
*   - CreateObject(h)
=======================================
--]]

local mission = require("rl_mission")
local team = require("rl_team")

local vsp = require("vsp")

local rl_coop_mission = {}
do
    --- @class coop_mission : mission, object
    local coop_mission = vsp.object.make_class("coop_mission", mission.mission_class)

    coop_mission.enemy_team = 15

    function coop_mission:coop_mission(team)
        -- even though the base constructor takes no parameters we still need to pass one
        -- since otherwise it just returns the base class instance to get methods from
        self:super(true)

        self.team = team
        self.spawn_directions = {}
        self.state_lock = vsp.distributed_lock.make_lock()
    end

    --- Makes a coop mission instance with the given team
    --- @param team team
    --- @return coop_mission
    function rl_coop_mission.make_coop(team)
        return coop_mission:new(team)
    end

    vsp.net.set_function("coop_change_state", coop_mission:super().change_state)

    local function host_broadcast_state_change(new_state)
        assert(vsp.net.is_hosting(), "Reloaded: Non host called broadcast state change")

        local self = mission.get_current_mission()

        -- Pass self as nil because it can't be sent over the net, client will use
        -- their own mission instance that should be in sync as long as you didn't
        -- mess anything up.

        local acknowledgements = {}

        -- TODO: refactor this is voodoo and should all be handled in net.async
        for _, player in pairs(vsp.net_player.get_player_list()) do
            if player.id ~= exu.GetMyNetID() then
                local a = vsp.net.async(player.id, "coop_change_state", nil, new_state)
                table.insert(acknowledgements, a)
            end
        end

        vsp.future.wait_all(acknowledgements, function (results)
            self:super().change_state(self, new_state)
            self.state_lock:unlock()
        end)
    end

    vsp.net.set_function("host_broadcast_state_change", host_broadcast_state_change)

    --- Synchronized host authoritative state change
    --- @param new_state any state id
    function coop_mission:change_state(new_state)
        if vsp.net.is_singleplayer_or_solo() then
            self:super().change_state(self, new_state)
            return
        end

        if self.current_state_id == new_state then return end
        if vsp.net.is_hosting() then
            self.state_lock:try_lock():wait(function (acquired)
                if acquired then
                    host_broadcast_state_change(new_state)
                end
            end)
        else
            self.state_lock:try_lock():wait(function (acquired)
                if acquired then
                    vsp.net.async(vsp.net.host_id, "host_broadcast_state_change", new_state)
                end
            end)
        end
    end

    local apply_my_spawn_direction = function () end

    --- Sets the direction that the player of the given team number will be facing when they spawn.
    --- @param player integer team number
    --- @param direction any vector direction
    function coop_mission:set_spawn_direction(player, direction)
        self.spawn_directions[player] = direction

        apply_my_spawn_direction = function ()
            local me = GetPlayerHandle()
            local pos = GetPosition(me)
            SetTransform(me, BuildDirectionalMatrix(pos, self.spawn_directions[team.my_team_num()]))
        end
    end

    vsp.net.set_function("set_remote_lives", exu.SetLives)

    local apply_starting_lives = function () end

    --- Sets the life count for the current mission
    --- @param count number
    function coop_mission:set_life_count(count)
        apply_starting_lives = function () -- this is hacky but it works lol, SetLives needs to be called in Start or post
            if not vsp.net.is_hosting() then return end
            for player_id in self.team.team_nums:iterator() do
                vsp.net.async(player_id, "set_remote_lives", count)
            end
            exu.SetLives(count)
        end
    end

    --- Forwards the arguments to BuildObject() and constructs a single synchronized object for the host only.
    --- Overrides the mission class method.
    --- @param ... any params forwarded to BuildObject
    --- @return userdata | nil handle
    function coop_mission:build_single_object(...)
        if vsp.net.is_hosting() then
            return self:super():build_single_object(...)
        end
    end

    --- Build multiple objects around the given area from the host only
    --- @param odfname string
    --- @param teamnum integer
    --- @param position any
    --- @return table<userdata> | table<nil>
    function coop_mission:build_multiple_objects(odfname, teamnum, count, position)
        if vsp.net.is_singleplayer_or_solo() then
            return self:super():build_multiple_objects(odfname, teamnum, count, position)
        end
        if not vsp.net.is_hosting() then return {} end
        return self:super():build_multiple_objects(odfname, teamnum, count, position)
    end

    --- These are fooked right now do not use

    vsp.net.set_function("sync_mission_var", function (name, var)
        local m = mission.get_current_mission()
        assert(m, "Reloaded: Current mission is nil")

        m.var[name] = var

        return true
    end)

    vsp.net.set_function("sync_state_var", function (state, name, var)
        local m = mission.get_current_mission()
        assert(m, "VSP: Current mission is nil")

        m.states[state][name] = var

        return true
    end)

    function coop_mission:sync_mission_var(name, var, callback, ...)
        if vsp.net.is_hosting() then
            self.var[name] = var

            local results = vsp.net.async(vsp.net.all_players, "sync_mission_var", name, var)
            local params = {...}

            vsp.future.wait_all(results, function ()
                callback(unpack(params))
            end)
        end
    end

    function coop_mission:sync_state_var(state, name, var, callback, ...)
        if vsp.net.is_hosting() then
            local results = vsp.net.async(vsp.net.all_players, "sync_state_var", state, name, var)
            vsp.future.wait_all(results, callback)
        end
    end

    --- Synchronized immediate mission success
    --- @param filename string
    function coop_mission:succeed(filename)
        vsp.net.wait_for_all_clients(function ()
            vsp.net.async(vsp.net.all_players, "SucceedMission", GetTime(), filename)
            SucceedMission(GetTime(), filename)
        end)
    end

    --- Synchronized immediate mission failure
    --- @param filename string
    function coop_mission:fail(filename)
        vsp.net.wait_for_all_clients(function ()
            vsp.net.async(vsp.net.all_players, "FailMission", GetTime(), filename)
            FailMission(GetTime(), filename)
        end)
    end

    vsp.net.set_function("make_shared_satellite", function ()
        local s_power = exu.BuildAsyncObject("abspow", GetTeamNum(GetPlayerHandle()), GetPosition(GetPlayerHandle()) + (vsp.math3d.east * 1000))
        local comm_tower = exu.BuildAsyncObject("abcomm", GetTeamNum(GetPlayerHandle()), GetPosition(GetPlayerHandle()) + (vsp.math3d.east * 1000))
        Hide(s_power)
        Hide(comm_tower)
    end)

    -- todo refactor
    local function apply_shared_satellite()
        for obj in AllObjects() do
            if not IsRemote(obj) and GetClassLabel(obj) == "commtower" then
                vsp.net.async(vsp.net.all_players, "make_shared_satellite")
                break
            end
        end
    end

    local function apply_mission_alliances()
        mission.get_current_mission().team:do_ally()
    end

    function rl_coop_mission.Start()
        if not mission.get_current_mission() then return end

        apply_my_spawn_direction()
        apply_starting_lives()
        apply_shared_satellite()
        apply_mission_alliances()
    end

    function rl_coop_mission.Update(dt)

    end

    function rl_coop_mission.CreateObject(h)
        if not mission.get_current_mission() then return end
    end
end
return rl_coop_mission