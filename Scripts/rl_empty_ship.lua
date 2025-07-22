--[[
=======================================
*   Battlezone: Reloaded
*   
*   Empty Ship Module
*
*   Removes the pilots from ships that
*   are supposed to be built empty  
*
*   Required Event Handlers:
*   - CreateObject(h)
=======================================
--]]

local vsp = require("vsp")

local rl_empty_ship = {}
do
    local empty_ships = vsp.set.make_set(
        "avempty"
    )

    -- Todo not working
    local function handle_empty_ships(h)
        if IsRemote(h) then return end
        local odf = GetOdf(h)
        if empty_ships:contains(odf) then
            DisplayMessage("Got here")
            vsp.utility.defer(KillPilot, h)
        end
    end

    function rl_empty_ship.CreateObject(h)
        handle_empty_ships(h)
    end
end
return rl_empty_ship