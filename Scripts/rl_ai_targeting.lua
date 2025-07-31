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
    local smart_targeting_enabled = false

    function rl_ai_targeting.set_smart_targeting()
        
    end

    local my_ai_units = vsp.set.make_set()

    local excluded_odfs = vsp.set.make_set()
    local excluded_obj_classes = vsp.set.make_set()

    --- Check if an object is allowed to use smart targeting
    --- @param h Handle
    --- @return boolean
    local function can_smart_target(h)
        return not excluded_odfs:contains(GetOdf(h)) and not excluded_obj_classes:contains(GetClassLabel(h))
    end

    local function register_starting_objects()
        if not smart_targeting_enabled then return end
        for _, obj in ipairs(vsp.object_service.get_start_objects():get()) do
            if can_smart_target(obj) then
                my_ai_units:insert(obj)
            end
        end
    end

    function rl_ai_targeting.Start()
        register_starting_objects()
    end

    function rl_ai_targeting.Update(dt)
        
    end
end
return rl_ai_targeting
