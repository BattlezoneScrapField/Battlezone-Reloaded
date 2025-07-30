--[[
=======================================
*   Battlezone: Reloaded
*   
*   Mission Module
*
*   Simple state machine for
*   singleplayer missions
*
*   Required Event Handlers:
*   - Start()
*   - Update(dt)
*   - CreateObject(h)
=======================================
--]]

local vsp = require("vsp")

local rl_mission = {}
do
    --- @class mission : object
    local mission = vsp.object.make_class("mission")

    --- @class mission
    local current_mission = nil

    --- Gets the current mission instance if it exists.
    --- @return mission
    function rl_mission.get_current_mission()
        return current_mission
    end

    function mission:mission(config)
        self.cfg = config
        self.states = {}
        self.states.null_state = {
            update = function (state, dt) end,
            enter_callback = function (state) end,
            exit_callback = function (state) end,
            var = {},
            event_listeners = {}
        }
        self.initial_state = nil
        self.current_state = self.states.null_state
        self.var = {}
        self.global_listeners = {}

        current_mission = self
    end

    --- Creates or gets the mission instance
    --- @param config? table mission configuration file
    --- @return mission
    function rl_mission.make_mission(config)
        if current_mission then return current_mission end
        return mission:new(config)
    end

    --- Initializes a new mission state, does not change the current state
    --- @param id any
    --- @param update? fun(state: table, dt: number)
    --- @param enter_callback? fun(state: table)
    --- @param exit_callback? fun(state: table)
    --- @return mission
    function mission:define_state(id, update, enter_callback, exit_callback)
        self.states[id] = {
            update = update or function (state, dt) end,
            enter_callback = enter_callback or function (state) end,
            exit_callback = exit_callback or function (state) end,
            var = {},
            event_listeners = {}
        }
        return self
    end

    --- Changes the state of the mission.
    --- @param new_state any state id
    function mission:change_state(new_state)
        -- when this is called by a remote player self will not be sent over the net,
        -- so use your own mission instance which should be in sync if set up properly
        self = self or current_mission
        if self.current_state_id == new_state then return end

        assert(self.states[new_state], string.format("Reloaded: Requested state %s is undefined", new_state))

        DisplayMessage("changing state to " .. tostring(new_state))

        self.current_state_id = new_state

        self.current_state:exit_callback()

        self.current_state = self.states[new_state]

        self.current_state:enter_callback()
    end

    function mission:set_initial_state(state_id)
        self.initial_state = state_id
    end

    local valid_events = vsp.set.make_set(
        "Start",
        "Update",
        "CreateObject",
        "DeleteObject"
    )

    --- Defines a per-state event listener for any stock event handler. CreateObject(h) for example.
    --- The `state` parameter is the id of the state you wish to attach the listener to.
    --- `what` is the exact string name of the stock event handler.
    --- `fun` is the function you wish to execute on trigger the event,
    --- it's signature should match the event handler exactly,
    --- so `function(h) end` for a CreateObject(h) listener,
    --- or `function(id, name, team) end` for a CreatePlayer(id, name, team) listener.
    --- @param state any state id to attach listener
    --- @param what string name of the event handler
    --- @param func fun(...: any)
    --- @return self
    function mission:define_event_listener(state, what, func)
        vsp.utility.required_param(state, "state", "any", "Reloaded")
        vsp.utility.required_param(what, "what", "string", "Reloaded")
        vsp.utility.required_param(func, "func", "function", "Reloaded")
        assert(valid_events:contains(what), string.format("Reloaded: requested event %s is invalid", what))
        assert(self.states[state], string.format("Reloaded: Requested state %s does not exist", state))
        assert(what ~= "Start", "Reloaded: Start event listeners are forbidden, just use Start()")
        assert(what ~= "Update", "Reloaded: Update event listeners are forbidden, use the state update function")

        self.states[state].event_listeners[what] = self.states[state].event_listeners[what] or {}
        table.insert(self.states[state].event_listeners[what], func)

        return self
    end

    --- Defines a global event listener. Use this SPARINGLY because it can quickly devolve
    --- to voodoo code. If you find yourself storing condition variables to activate/deactivate
    --- global listeners that's a sign to refactor the mission script.
    --- @param what string name of the event handler
    --- @param func fun(...: any)
    --- @return integer listener_handle handle you can save in case you need to undefine it later
    function mission:define_global_listener(what, func)
        vsp.utility.required_param(what, "what", "string", "Reloaded")
        vsp.utility.required_param(func, "func", "function", "Reloaded")
        assert(valid_events:contains(what), string.format("Reloaded: requested event %s is invalid", what))
        assert(what ~= "Start", "Reloaded: Start global listeners are forbidden, just use Start()")

        self.global_listeners[what] = self.global_listeners[what] or {}
        table.insert(self.global_listeners[what], func)

        return #self.global_listeners[what]
    end

    --- Undefines a global listener for the given event with the given handle
    --- @param what string event name
    --- @param handle integer global listener handle
    function mission:undefine_global_listener(what, handle)
        vsp.utility.required_param(what, "what", "string", "Reloaded")
        vsp.utility.required_param(handle, "handle", "number", "Reloaded")
        assert(valid_events:contains(what), string.format("Reloaded: requested event %s is invalid", what))
        assert(self.global_listeners[what][handle], "Reloaded: Global listener handle is invalid")

        self.global_listeners[what][handle] = function () end
    end

    --- Builds a single object (this is just here so that it works in both SP and MP)
    --- @param ... any build object params
    function mission:build_single_object(...)
        return exu.BuildSyncObject(...)
    end

    --- Build multiple objects around the given area
    --- @param odfname string
    --- @param teamnum integer
    --- @param count integer
    --- @param position any
    --- @return table handles
    function mission:build_multiple_objects(odfname, teamnum, count, position)
        position = vsp.utility.get_any_position(position)
        local return_handles = {}
        local max_radius = 10 * count
        for i = 1, count do
            local h = self:build_single_object(odfname, teamnum, GetPositionNear(position, 10, max_radius))
            table.insert(return_handles, h)
        end
        return return_handles
    end

    --- Immediately succeeds the mission
    --- @param filename string
    function mission:succeed(filename)
        SucceedMission(GetTime(), filename)
    end

    --- Immediately fails the mission
    --- @param filename string
    function mission:fail(filename)
        SucceedMission(GetTime(), filename)
    end

    function mission:do_state(dt)
        self.current_state:update(dt)
    end

    function rl_mission.Start()
        if not current_mission then return end

        assert(current_mission.initial_state, "Reloaded: Initial mission state is undefined")
        -- the syntax is important here, we want to call the base class change state method
        -- because the initial state does not require synchronization in coop, but it should still
        -- use the current mission (which could be a coop mission) as the self parameter.
        mission.change_state(current_mission, current_mission.initial_state)

        -- some initialization will break if done before Start()
        -- is called, so we need to track that
        current_mission.post_start = true
    end

    function rl_mission.Update(dt)
        if not current_mission then return end

        current_mission:do_state(dt)

        if current_mission.global_listeners.Update then
            for _, listener in ipairs(current_mission.global_listeners.Update) do
                listener(dt)
            end
        end
    end

    function rl_mission.CreateObject(h)
        if not current_mission then return end
        if not current_mission.post_start then return end

        if current_mission.current_state.event_listeners.CreateObject then
            for _, listener in ipairs(current_mission.current_state.event_listeners.CreateObject) do
                listener(h)
            end
        end

        if current_mission.global_listeners.CreateObject then
            for _, listener in ipairs(current_mission.global_listeners.CreateObject) do
                listener(h)
            end
        end
    end

    rl_mission.mission_class = mission
end
return rl_mission
