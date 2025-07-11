-- This module lets you grab your steam workshop directory 
-- in order to require modules from any mod, including DLLs

-- Module by DivisionByZero, GrizzlyOne95, and VTrider

-- Version 1.0

local RequireFix = {}
do

    local version = "1.0"

    -- Function to print field names of an object
    local function splitAtSemicolon(str)
        local results = {}
        for substr in string.gmatch(str, '([^;]+)') do
            table.insert(results, substr)
        end
        return results
    end

    local function getGameDirectory()
        local path = splitAtSemicolon(package.cpath)[2]
        return string.match(path, "(.*)\\%?")
    end

    -- directory = getGameDirectory()
    -- print("bz directory is: " .. directory)

    local function getSteamWorkshopDirectory()
        local gameDirectory = getGameDirectory()
        local workshopRelativePath = "steamapps/workshop/content/301650"

        -- Remove the common directory from the game directory
        local commonDirectory = "steamapps\\common\\Battlezone 98 Redux"
        local commonDirectoryIndex = string.find(gameDirectory, commonDirectory)

        if commonDirectoryIndex then
            gameDirectory = gameDirectory:sub(1, commonDirectoryIndex - 2)
        end

        -- Combine paths using path.join
        local steamWorkshopDirectory = gameDirectory .. "\\" .. workshopRelativePath:gsub("/", "\\")

        return steamWorkshopDirectory
    end

    -- This sets the path and cpath to the user defined value, it can take a 
    -- single workshop ID or a table of IDs and add them sequentially to the 
    -- correct path -VTrider
    local function Initialize(workshopID)
        local workshopDirectory = getSteamWorkshopDirectory()
        local defaultPath = package.path
        local defaultCPath = package.cpath
        local LuaPath = defaultPath
        local DLLPath = defaultCPath

        if type(workshopID) == "table" then
            for key, value in pairs(workshopID) do
                local modDirectory = workshopDirectory .. "\\" .. value
                LuaPath = LuaPath .. ";" .. modDirectory .. "\\?.lua"
                DLLPath = DLLPath .. ";" .. modDirectory .. "\\?.dll"
            end

            package.path = LuaPath
            package.cpath = DLLPath
            return
        end

        local modDirectory = workshopDirectory .. "\\" .. workshopID
        local LuaPath = defaultPath .. ";" .. modDirectory .. "\\?.lua"
        local DLLPath = defaultCPath .. ";" .. modDirectory .. "\\?.dll"

        package.path = LuaPath
        package.cpath = DLLPath
    end

    -- Example usage
    -- local steamWorkshopDirectory = getSteamWorkshopDirectory()
    -- print("Steam Workshop Directory:" .. steamWorkshopDirectory)
    RequireFix.version                   = version
    RequireFix.getSteamWorkshopDirectory = getSteamWorkshopDirectory
    RequireFix.Initialize                = Initialize

end
return RequireFix