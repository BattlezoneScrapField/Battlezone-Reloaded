--[[
=======================================
*   Battlezone: Reloaded
*
*   AI Targeting Module
*
*   Required Event Handlers:
*   - Update(dt)
=======================================
--]]

local vsp = require("vsp")

local rl_ai_targeting = {}
do
    --- A target function should take a position value `where`, a number in meters `range`,
    --- and a predicate function `valid_target` which should match the signature `fun(h: Handle): boolean`.
    --- This function should return true if the target is valid, and false if not, according to any additional
    --- logic required by the targeting program. The target function returns a target if one is found and validated,
    --- or nil if there are no targets matching the criteria in range.
    --- @alias target_function_t fun(where: position_t, range: number, valid_target: fun(h:Handle): boolean): Handle | nil

    local function feuker() end

    --- Basic targeting programs
    --- @type table<string, target_function_t>
    local program = {}

    function program.target_closest(where, range, valid_target)
        -- Handle the base case first before proceeding to the more
        -- intensive search
        local closest_obj = GetNearestObject(where)
        if GetDistance(closest_obj, where) < range and valid_target(closest_obj) then
            return closest_obj
        end

        local objs = {}
        for obj in ObjectsInRange(range, where) do
            objs[#objs+1] = obj
        end

        table.sort(objs, function (a, b)
            local dist_a = Distance3D(vsp.utility.get_any_position(where), GetPosition(a))
            local dist_b = Distance3D(vsp.utility.get_any_position(where), GetPosition(b))
            return dist_a < dist_b
        end)

        for _, obj in ipairs(objs) do
            if valid_target(obj) then
                return obj
            end
        end
    end

    function program.target_weakest(where, range)
        
    end

    function program.target_strongest(where, range)
        
    end

    function program.target_player(where, range)
        
    end

    rl_ai_targeting.program = program
end
return rl_ai_targeting
