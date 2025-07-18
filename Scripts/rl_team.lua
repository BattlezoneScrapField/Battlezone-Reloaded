--[[
=======================================
*   Battlezone: Reloaded
*   
*   Team Module
=======================================
--]]

local vsp = require("vsp")

local exu = require("exu")

local rl_team = {}
do
    --- @type team | nil
    local my_team = nil

    function rl_team.my_team_num()
        return GetTeamNum(GetPlayerHandle())
    end

    --- @return team | nil
    function rl_team.get_my_team()
        return my_team
    end

    --- @class team : object
    --- @field team_nums set
    local team = vsp.object.make_class("team")

    function team:team(name, ...)
        self.name = name
        -- Map assigned team numbers for players (1, 2, 3, 4... etc.)
        self.team_nums = vsp.set.make_set(...)
        self.player_count = self.team_nums:size()

        for team_num in self.team_nums:iterator() do
            exu.SetCustomKillMessage(team_num, self.name)
        end

        self:do_ally()
    end

    function team:get_player_count()
        return self.player_count
    end

    --- Makes a team object
    --- @param name string identifier for the team
    --- @param ... integer team nums
    --- @return team
    function rl_team.make_team(name, ...)
        return team:new(name, ...)
    end

    function rl_team.leave_team()
        my_team = nil
    end

    function team:do_ally()
        for i in self.team_nums:iterator() do
            for j in self.team_nums:iterator() do
                Ally(i, j)
            end
        end
    end
end
return rl_team