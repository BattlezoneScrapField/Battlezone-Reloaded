-- Single Player Playground Mission Lua conversion, created by General BlackDragon. 

-- Single Table for all our save/load variables. This SP mission has too many variables to function with them independently. ("main function has > 200 local variables", or "Load having > 197 variables in assignment")
local M = {

-- bools

-- Floats (really doubles in Lua)

-- Handles

-- Ints

}

function Save()
    return 
		M
end

function Load(...)	
    if select('#', ...) > 0 then
		M
		 =  ...
    end
end


function Start()


end

function AddObject(h)


end

function Update()

-- START OF SCRIPT


-- END OF SCRIPT
	
end