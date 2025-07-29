--- BZ98R ScriptUtils Stub.
--
-- Modified for stock lua by VTrider
--
-- Stubs for ScriptUtils LDoc
--
-- @module ScriptUtils

-------------------------------------------------------------------------------
-- Types
-------------------------------------------------------------------------------
-- @section
-- Type declarations

--- A handle to a game object. This is a unique identifier for the object in the game world.
--- @alias Handle userdata

--- A handle to an audio message.
--- @alias AudioMessage integer

--- Team Number
--- @alias TeamNum 0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15

--- ODF ParameterDB
--- @class ParameterDB

--- Objective Color Label
--- @alias ColorLabel string

-------------------------------------------------------------------------------
-- Globals
-------------------------------------------------------------------------------
-- @section
-- The Lua scripting system defines some global variables that can be of use to user scripts.

--- Contains current build version
---
--- Battlezone 1.5 versions start with "1"
---
--- Battlezone 98 Redux versions start with "2"
---
--- For example "1.5.2.27u1"
--- \@field GameVersion string
GameVersion = "1.5.2.27u1"

--- Contains the index of the current language.
--- <ol>
---     <li>English</li>
---     <li>French</li>
---     <li>German</li>
---     <li>Spanish</li>
---     <li>Italian</li>
---     <li>Portuguese</li>
---     <li>Russian</li>
--- </ol>
--- [2.0+]
--- \@field Language integer
Language = 1

--- Contains the full name of the current language in all-caps: "ENGLISH", "FRENCH", "GERMAN", "SPANISH", "ITALIAN", "PORTUGUESE", or "RUSSIAN"
--- [2.0+]
--- \@field LanguageName string
LanguageName = "ENGLISH"

--- Contains the two-letter language code of the current language: "en", "fr", "de", "es", "it", "pt" or "ru"
--- [2.0+]
--- \@field LanguageSuffix string
LanguageSuffix = "en"

--- Contains the most recently pressed game key (e.g. "Ctrl+Z")
--- \@field LastGameKey string
LastGameKey = "Ctrl+Z"

-------------------------------------------------------------------------------
-- Audio Messages
-------------------------------------------------------------------------------
-- @section
-- These functions control audio messages, 2D sounds typically used for radio messages, voiceovers, and narration.
-- Audio messages use the Voice Volume setting from the Audio Options menu.

--- Repeat the last audio message.
function RepeatAudioMessage() end

--- Plays the given audio file, which must be an uncompressed RIFF WAVE (.WAV) file.
--- Returns an audio message handle.
--- @param filename string
--- @return AudioMessage
function AudioMessage(filename)
    error("This function is provided by the engine.")
end

--- Returns true if the audio message has stopped. Returns false otherwise.
--- @param msg AudioMessage
--- @return boolean
function IsAudioMessageDone(msg)
    error("This function is provided by the engine.")
end

--- Stops the given audio message.
--- @param msg AudioMessage
function StopAudioMessage(msg) end

--- Returns true if <em>any</em> audio message is playing. Returns false otherwise.
--- @return boolean
function IsAudioMessagePlaying()
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Sound Effects
-------------------------------------------------------------------------------
-- @section
-- These functions control sound effects, either positional 3D sounds attached to objects or global 2D sounds.
-- Sound effects use the Effects Volume setting from the Audio Options menu.

--- Plays the given audio file, which must be an uncompressed RIFF WAVE (.WAV) file.
--- Specifying an object handle creates a positional 3D sound that follows the object as it moves and stops automatically when the object goes away. Otherwise, the sound plays as a global 2D sound.
--- Priority ranges from 0 to 100, with higher priorities taking precedence over lower priorities when there are not enough channels. The default priority is 50 if not specified.
--- Looping sounds will play forever until explicitly stopped with StopSound or the object to which it is attached goes away. Non-looping sounds will play once and stop. The default is non-looping if not specified.
--- Volume ranges from 0 to 100, with 0 being silent and 100 being maximum volume. The default volume is 100 if not specified.
--- Rate overrides the playback rate of the sound file, so a value of 22050 would cause a sound file recorded at 11025 Hz to play back twice as fast. The rate defaults to the file's native rate if not specified.
--- @param filename string
--- @param h? Handle
--- @param priority? integer
--- @param loop? boolean
--- @param volume? integer
--- @param rate? integer
function StartSound(filename, h, priority, loop, volume, rate) end

--- Stops the sound using the given filename and associated with the given object. Use a handle of none or nil to stop a global 2D sound.
--- @param filename string
--- @param h? Handle
function StopSound(filename, h) end

-------------------------------------------------------------------------------
-- Game Object
-------------------------------------------------------------------------------
-- @section
-- These functions create, manipulate, and query game objects (vehicles, buildings, people, powerups, and scrap) and return or take as a parameter a game object handle.
-- Object handles are always safe to use, even if the game object itself is missing or destroyed.

--- Returns the handle of the game object with the given label. Returns nil if none exists.
--- @param label string
--- @return Handle?
function GetHandle(label)
    error("This function is provided by the engine.")
end

--- Creates a game object with the given odf name, team number, and location.
---
--- Multiplayer remarks: Objects built by the host are always synchronized, objects built by clients will always be desynchronized initially,
--- but can be synchronized by calling SetLocal(). To build a desynchronized object as the host, use exu.BuildAsyncObject().
--- @param odfname string
--- @param teamnum TeamNum
--- @param location Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer If the location is a path this is the path point index, defaults to 0.
--- @return Handle?
function BuildObject(odfname, teamnum, location, point)
    error("This function is provided by the engine.")
end

--- Removes the game object with the given handle.
---
--- Remarks: Unsafe to use on a handle passed in by CreateObject(h), doing so will crash the game. If you need this functionality,
--- you should defer the deletion until the next Update(dt).
---
--- Multiplayer remarks: Very dangerous. There are innumerable cases which can cause objects to be improperly deleted and/or
--- spawn explosion chunks which may only be visible to certain players. In order to safely delete a distributed object,
--- ALL players must call RemoveObject(h) on the target object simultaneously. Additionally, attempting to delete the starting
--- recycler in a strategy or MPI game will crash the game, if you need this functionality use exu.DisableStartingRecycler().
--- @param h Handle
function RemoveObject(h) end

--- Returns true if the game object's odf name matches the given odf name. Returns false otherwise.
--- @param h Handle
--- @param odfname string
--- @return boolean
function IsOdf(h, odfname)
    error("This function is provided by the engine.")
end

--- Returns the odf name of the game object. Returns nil if none exists.
--- @param h Handle
--- @return string?
function GetOdf(h)
    error("This function is provided by the engine.")
end

--- Returns the base config of the game object which determines what VDF/SDF model it uses. Returns nil if none exists.
--- @param h Handle
--- @return string?
function GetBase(h)
    error("This function is provided by the engine.")
end

--- Returns the label of the game object (e.g. "avtank0_wingman"). Returns nil if none exists.
--- @param h Handle
--- @return string?
function GetLabel(h)
    error("This function is provided by the engine.")
end

--- Set the label of the game object (e.g. "tank1").
--- @param h Handle
--- @param label string
function SetLabel(h, label) end

--- Returns the four-character class signature of the game object (e.g. "WING"). Returns nil if none exists.
--- @param h Handle
--- @return string?
function GetClassSig(h)
    error("This function is provided by the engine.")
end

--- Returns the class label of the game object (e.g. "wingman"). Returns nil if none exists.
--- @param h Handle
--- @return string?
function GetClassLabel(h)
    error("This function is provided by the engine.")
end

--- Returns the numeric class identifier of the game object. Returns nil if none exists.
--- Looking up the class id number in the ClassId table will convert it to a string. Looking up the class id string in the ClassId table will convert it back to a number.
--- @param h Handle
--- @return integer?
function GetClassId(h)
    error("This function is provided by the engine.")
end

--- This is a global table that converts between class identifier numbers and class identifier names.
--- Many of these values likely never appear in game and are leftover from Interstate '76
--- @enum ClassId
ClassId = {
    NONE = 0,                 -- 0

    HELICOPTER = 1,           -- 1
    STRUCTURE1 = 2,           -- 2 (Wooden Structures)
    POWERUP = 3,              -- 3
    PERSON = 4,               -- 4
    SIGN = 5,                 -- 5
    VEHICLE = 6,              -- 6
    SCRAP = 7,                -- 7
    BRIDGE = 8,               -- 8 (A structure which can contain the floor)
    FLOOR = 9,                -- 9 (The floor in a bridge)
    STRUCTURE2 = 10,          -- 10 (Metal Structures)
    SCROUNGE = 11,            -- 11
    SPINNER = 15,             -- 15

    HEADLIGHT_MASK = 38,      -- 38

    EYEPOINT = 40,            -- 40
    COM = 42,                 -- 42

    WEAPON = 50,              -- 50
    ORDNANCE = 51,            -- 51
    EXPLOSION = 52,           -- 52
    CHUNK = 53,               -- 53
    SORT_OBJECT = 54,         -- 54
    NONCOLLIDABLE = 55,       -- 55

    VEHICLE_GEOMETRY = 60,    -- 60
    STRUCTURE_GEOMETRY = 61,  -- 61
    WEAPON_GEOMETRY = 63,     -- 63
    ORDNANCE_GEOMETRY = 64,   -- 64
    TURRET_GEOMETRY = 65,     -- 65
    ROTOR_GEOMETRY = 66,      -- 66
    NACELLE_GEOMETRY = 67,    -- 67
    FIN_GEOMETRY = 68,        -- 68
    COCKPIT_GEOMETRY = 69,    -- 69

    WEAPON_HARDPOINT = 70,    -- 70
    CANNON_HARDPOINT = 71,    -- 71
    ROCKET_HARDPOINT = 72,    -- 72
    MORTAR_HARDPOINT = 73,    -- 73
    SPECIAL_HARDPOINT = 74,   -- 74

    FLAME_EMITTER = 75,       -- 75
    SMOKE_EMITTER = 76,       -- 76
    DUST_EMITTER = 77,        -- 77

    PARKING_LOT = 81,         -- 81

    [0] = "NONE",             -- NONE
    [1] = "HELICOPTER",       -- HELICOPTER
    [2] = "STRUCTURE1",       -- STRUCTURE1
    [3] = "POWERUP",          -- POWERUP
    [4] = "PERSON",           -- PERSON
    [5] = "SIGN",             -- SIGN
    [6] = "VEHICLE",          -- VEHICLE
    [7] = "SCRAP",            -- SCRAP
    [8] = "BRIDGE",           -- BRIDGE
    [9] = "FLOOR",            -- FLOOR
    [10] = "STRUCTURE2",      -- STRUCTURE2
    [11] = "SCROUNGE",        -- SCROUNGE
    [15] = "SPINNER",         -- SPINNER
    [38] = "HEADLIGHT_MASK",  -- HEADLIGHT_MASK
    [40] = "EYEPOINT",        -- EYEPOINT
    [42] = "COM",             -- COM
    [50] = "WEAPON",          -- WEAPON
    [51] = "ORDNANCE",        -- ORDNANCE
    [52] = "EXPLOSION",       -- EXPLOSION
    [53] = "CHUNK",           -- CHUNK
    [54] = "SORT_OBJECT",     -- SORT_OBJECT
    [55] = "NONCOLLIDABLE",   -- NONCOLLIDABLE
    [60] = "VEHICLE_GEOMETRY", -- VEHICLE_GEOMETRY
    [61] = "STRUCTURE_GEOMETRY", -- STRUCTURE_GEOMETRY
    [63] = "WEAPON_GEOMETRY", -- WEAPON_GEOMETRY
    [64] = "ORDNANCE_GEOMETRY", -- ORDNANCE_GEOMETRY
    [65] = "TURRET_GEOMETRY", -- TURRET_GEOMETRY
    [66] = "ROTOR_GEOMETRY",  -- ROTOR_GEOMETRY
    [67] = "NACELLE_GEOMETRY", -- NACELLE_GEOMETRY
    [68] = "FIN_GEOMETRY",    -- FIN_GEOMETRY
    [69] = "COCKPIT_GEOMETRY", -- COCKPIT_GEOMETRY
    [70] = "WEAPON_HARDPOINT", -- WEAPON_HARDPOINT
    [71] = "CANNON_HARDPOINT", -- CANNON_HARDPOINT
    [72] = "ROCKET_HARDPOINT", -- ROCKET_HARDPOINT
    [73] = "MORTAR_HARDPOINT", -- MORTAR_HARDPOINT
    [74] = "SPECIAL_HARDPOINT", -- SPECIAL_HARDPOINT
    [75] = "FLAME_EMITTER",   -- FLAME_EMITTER
    [76] = "SMOKE_EMITTER",   -- SMOKE_EMITTER
    [77] = "DUST_EMITTER",    -- DUST_EMITTER
    [81] = "PARKING_LOT",     -- PARKING_LOT
}

--- Returns the one-letter nation code of the game object (e.g. "a" for American, "b" for Black Dog, "c" for Chinese, and "s" for Soviet).
--- The nation code is usually but not always the same as the first letter of the odf name. The ODF file can override the nation in the [GameObjectClass] section, and player.odf is a hard-coded exception that uses "a" instead of "p".
--- @param h Handle
--- @return string
function GetNation(h)
    error("This function is provided by the engine.")
end

--- Returns true if the game object exists. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsValid(h)
    error("This function is provided by the engine.")
end

--- Returns true if the game object exists and (if the object is a vehicle) controlled. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsAlive(h)
    error("This function is provided by the engine.")
end

--- Returns true if the game object exists and (if the object is a vehicle) controlled and piloted. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsAliveAndPilot(h)
    error("This function is provided by the engine.")
end

--- Returns true if the game object exists and is a vehicle. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsCraft(h)
    error("This function is provided by the engine.")
end

--- Returns true if the game object exists and is a building. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsBuilding(h)
    error("This function is provided by the engine.")
end

--- Returns true if the game object exists and is a person. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsPerson(h)
    error("This function is provided by the engine.")
end

--- Returns true if the game object exists and has less health than the threshold. Returns false otherwise.
--- @param h Handle
--- @param threshold? number float
--- @return boolean
function IsDamaged(h, threshold)
    error("This function is provided by the engine.")
end

--- Returns true if the game object was recycled by a Construction Rig on the given team.
--- [2.1+]
--- @param h Handle
--- @param team TeamNum
--- @return boolean
function IsRecycledByTeam(h, team)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Team Number
-------------------------------------------------------------------------------
-- @section
-- These functions get and set team number. Team 0 is the neutral or environment team.

--- Returns the game object's team number.
--- @param h Handle
--- @return TeamNum
function GetTeamNum(h)
    error("This function is provided by the engine.")
end

--- Sets the game object's team number.
--- @param h Handle
--- @param team TeamNum
function SetTeamNum(h, team) end

--- Returns the game object's perceived team number (as opposed to its real team number).
--- The perceived team will differ from the real team when a player enters an empty enemy vehicle without being seen until they attack something.
--- @param h Handle
--- @return TeamNum
function GetPerceivedTeam(h)
    error("This function is provided by the engine.")
end

--- Set the game object's perceived team number (as opposed to its real team number).
--- Units on the game object's perceived team will treat it as friendly until it "blows its cover" by attacking, at which point it will revert to its real team.
--- Units on the game object's real team will treat it as friendly regardless of its perceived team.
--- @param h Handle
--- @param t TeamNum
function SetPerceivedTeam(h, t) end

-------------------------------------------------------------------------------
-- Target
-------------------------------------------------------------------------------
-- @section
-- These function get and set a unit's target.

--- Sets the local player's target.
--- @param t Handle
function SetUserTarget(t) end

--- Returns the local player's target. Returns nil if it has none.
--- @return Handle?
function GetUserTarget()
    error("This function is provided by the engine.")
end

--- Sets the game object's target.
--- @param h Handle
--- @param t Handle
function SetTarget(h, t) end

--- Returns the game object's target. Returns nil if it has none.
--- @param h Handle
--- @return Handle?
function GetTarget(h)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Owner
-------------------------------------------------------------------------------
-- @section
-- These functions get and set owner. The default owner for a game object is the game object that created it.

--- Sets the game object's owner.
--- @todo confirm o can be nil
--- @param h Handle
--- @param o Handle?
function SetOwner(h, o) end

--- Returns the game object's owner. Returns nil if it has none.
--- @param h Handle
--- @return Handle?
function GetOwner(h)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Pilot Class
-------------------------------------------------------------------------------
-- @section
-- These functions get and set vehicle pilot class.

--- Sets the vehicle's pilot class to the given odf name. This does nothing useful for non-vehicle game objects. An odf name of nil resets the vehicle to the default assignment based on nation.
--- @param h Handle
--- @param odfname string?
function SetPilotClass(h, odfname) end

--- Returns the odf name of the vehicle's pilot class. Returns nil if none exists.
--- @param h Handle
--- @return string?
function GetPilotClass(h)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Position and Orientation
-------------------------------------------------------------------------------
-- @section
-- These functions get and set position and orientation.

--- Teleports the game object to a target location.
--- @param h Handle
--- @param target Vector|Matrix|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer If the target is a path this is the path point index, defaults to 0.
function SetPosition(h, target, point) end

--- Returns the game object's or path point's position vector. Returns nil if none exists.
--- @param target Handle|string
--- @param point? integer If the target is a path this is the path point index, defaults to 0.
--- @return Vector?
function GetPosition(target, point)
    error("This function is provided by the engine.")
end

--- Returns the game object's front vector. Returns nil if none exists.
--- @param h Handle
--- @return Vector?
function GetFront(h)
    error("This function is provided by the engine.")
end

--- Teleports the game object to the given transform matrix.
--- @param h Handle
--- @param transform Matrix
function SetTransform(h, transform) end

--- Returns the game object's transform matrix. Returns nil if none exists.
--- @param h Handle
--- @return Matrix?
function GetTransform(h)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Linear Velocity
-------------------------------------------------------------------------------
-- @section
-- These functions get and set linear velocity.

--- Returns the game object's linear velocity vector. Returns nil if none exists.
--- @param h Handle
--- @return Vector
function GetVelocity(h)
    error("This function is provided by the engine.")
end

--- Sets the game object's angular velocity vector.
--- @param h Handle
--- @param velocity Vector
function SetVelocity(h, velocity) end

-------------------------------------------------------------------------------
-- Angular Velocity
-------------------------------------------------------------------------------
-- @section
-- These functions get and set angular velocity.

--- Returns the game object's angular velocity vector. Returns nil if none exists.
--- @param h Handle
--- @return Vector
function GetOmega(h)
    error("This function is provided by the engine.")
end

--- Sets the game object's angular velocity vector.
--- @param h Handle
--- @param omega Vector
function SetOmega(h, omega) end

-------------------------------------------------------------------------------
-- Position Helpers
-------------------------------------------------------------------------------
-- @section
-- These functions help generate position values close to a center point.

--- Returns a ground position offset from the center by the radius in a direction controlled by the angle.
--- If no radius is given, it uses a default radius of zero.
--- If no angle is given, it uses a default angle of zero.
--- An angle of zero is +X (due east), pi * 0.5 is +Z (due north), pi is -X (due west), and pi * 1.5 is -Z (due south).
--- @param center Vector
--- @param radius? number
--- @param angle? number
--- @return Vector
function GetCircularPos(center, radius, angle)
    error("This function is provided by the engine.")
end

--- Returns a ground position in a ring around the center between minradius and maxradius with roughly the same terrain height as the terrain height at the center.
--- This is good for scattering spawn positions around a point while excluding positions that are too high or too low.
--- If no radius is given, it uses the default radius of zero.
--- @param center Vector
--- @param minradius? number
--- @param maxradius? number
--- @return Vector
function GetPositionNear(center, minradius, maxradius)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Shot
-------------------------------------------------------------------------------
-- @section
-- These functions query a game object for information about ordnance hits.

--- Returns who scored the most recent hit on the game object. Returns nil if none exists.
--- @param h Handle
--- @return Handle
function GetWhoShotMe(h)
    error("This function is provided by the engine.")
end

--- Returns the last time an enemy shot the game object.
--- @param h Handle
--- @return number float
function GetLastEnemyShot(h)
    error("This function is provided by the engine.")
end

--- Returns the last time a friend shot the game object.
--- @param h Handle
--- @return number float
function GetLastFriendShot(h)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Alliances
-------------------------------------------------------------------------------
-- @section
-- These functions control and query alliances between teams.
-- The team manager assigns each player a separate team number, starting with 1 and going as high as 15. Team 0 is the neutral "environment" team.
-- Unless specifically overridden, every team is friendly with itself, neutral with team 0, and hostile to everyone else.

--- Sets team alliances back to default.
function DefaultAllies() end

--- Sets whether team alliances are locked. Locking alliances prevents players from allying or un-allying, preserving alliances set up by the mission script.
--- @param lock boolean
function LockAllies(lock) end

--- Makes the two teams allies of each other.
--- This function affects both teams so Ally(1, 2) and Ally(2, 1) produces the identical results, unlike the "half-allied" state created by the "ally" game key.
--- @param team1 integer
--- @param team2 integer
function Ally(team1, team2) end

--- Makes the two teams enemies of each other.
--- This function affects both teams so UnAlly(1, 2) and UnAlly(2, 1) produces the identical results, unlike the "half-enemy" state created by the "unally" game key.
--- @param team1 integer
--- @param team2 integer
function UnAlly(team1, team2) end

--- Returns true if team1 considers team2 an ally. Returns false otherwise.
--- Due to the possibility of player-initiated "half-alliances", IsTeamAllied(team1, team2) might not return the same result as IsTeamAllied(team2, team1).
--- @param team1 integer
--- @param team2 integer
--- @return boolean
function IsTeamAllied(team1, team2)
    error("This function is provided by the engine.")
end

--- Returns true if game object "me" considers game object "him" an ally. Returns false otherwise.
--- Due to the possibility of player-initiated "half-alliances", IsAlly(me, him) might not return the same result as IsAlly(him, me).
--- @param me Handle
--- @param him Handle
--- @return boolean
function IsAlly(me, him)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Objective Marker
-------------------------------------------------------------------------------
-- @section
-- These functions control objective markers.
-- Objectives are visible to all teams from any distance and from any direction, with an arrow pointing to off-screen objectives. There is currently no way to make team-specific objectives.

--- Sets the game object as an objective to all teams.
---
--- Multiplayer remarks: The object `h` must be local to the caller and synchronized.
--- Calling this function on a desynchronized object will result in the status not being propagated to remote players.
--- @param h Handle
function SetObjectiveOn(h) end

--- Sets the game object back to normal.
---
--- Multiplayer remarks: The object `h` must be local to the caller and synchronized.
--- Calling this function on a desynchronized object will result in the status not being propagated to remote players.
--- @param h Handle
function SetObjectiveOff(h) end

--- Get the objective on status of object.
--- [UNRELEASED]
--- @param h Handle
--- @return boolean
function IsObjectiveOn(h)
    error("This function is provided by the engine.")
end

--- Gets the game object's visible name.
--- @param h Handle
--- @return string
function GetObjectiveName(h)
    error("This function is provided by the engine.")
end

--- Sets the game object's visible name.
--- @param h Handle
--- @param name string
function SetObjectiveName(h, name) end

--- Sets the game object's visible name. This function is effectively an alias for SetObjectiveName.
--- [2.1+]
--- @param h Handle
--- @param name string
function SetName(h, name) end

-------------------------------------------------------------------------------
-- Distance
-------------------------------------------------------------------------------
-- @section
-- These functions measure and return the distance between a game object and a reference point.

--- Returns the distance in meters between the game object and a position vector, transform matrix, another object, or point on a named path.
--- @param h1 Handle
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer If the target is a path this is the path point index, defaults to 0.
--- @return number
function GetDistance(h1, target, point)
    error("This function is provided by the engine.")
end

--- Returns true if the units are closer than the given distance of each other. Returns false otherwise.
--- (This function is equivalent to GetDistance (h1, h2) < d)
--- @param h1 Handle
--- @param h2 Handle
--- @param dist number
--- @return boolean
function IsWithin(h1, h2, dist)
    error("This function is provided by the engine.")
end

--- Returns true if the bounding spheres of the two game objects are within the specified tolerance. The default tolerance is 1.3 meters if not specified.
--- [2.1+]
--- @param h1 Handle
--- @param h2 Handle
--- @param tolerance? number
--- @return boolean
function IsTouching(h1, h2, tolerance)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Nearest
-------------------------------------------------------------------------------
-- @section
-- These functions find and return the game object of the requested type closest to a reference point.

--- Returns the game object closest to a position vector, transform matrix, another object, or point on a named path.
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer If the target is a path this is the path point index, defaults to 0.
--- @return Handle
function GetNearestObject(target, point)
    error("This function is provided by the engine.")
end

--- Returns the craft closest to a position vector, transform matrix, another object, or point on a named path.
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer If the target is a path this is the path point index, defaults to 0.
--- @return Handle
function GetNearestVehicle(target, point)
    error("This function is provided by the engine.")
end

--- Returns the building closest to a position vector, transform matrix, another object, or point on a named path.
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer If the target is a path this is the path point index, defaults to 0.
--- @return Handle
function GetNearestBuilding(target, point)
    error("This function is provided by the engine.")
end

--- Returns the enemy closest to a position vector, transform matrix, another object, or point on a named path.
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer If the target is a path this is the path point index, defaults to 0.
--- @return Handle
function GetNearestEnemy(target, point)
    error("This function is provided by the engine.")
end

--- Returns the friend closest to a position vector, transform matrix, another object, or point on a named path.
--- [2.0+]
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer If the target is a path this is the path point index, defaults to 0.
--- @return Handle
function GetNearestFriend(target, point)
    error("This function is provided by the engine.")
end

--- Returns the friend closest to the given reference point. Returns nil if none exists.
--- [2.1+]
--- @diagnostic disable: undefined-doc-param
--- @overload fun(h: Handle): Handle? --- [2.0+]
--- @overload fun(path: string, point?: integer): Handle? --- [2.1+]
--- @overload fun(position: Vector): Handle? --- [2.1+]
--- @overload fun(transform: Matrix): Handle? --- [2.1+]
--- @param h Handle The reference game object.
--- @param path string The path name.
--- @param point? integer The point on the path (optional).
--- @param position Vector The position vector.
--- @param transform Matrix The transform matrix.
--- @return Handle? handle closest friend, or nil if none exists.
--- @diagnostic enable: undefined-doc-param
function GetNearestUnitOnTeam(...) end

--- Returns the craft or person on the given team closest to the given game object. Returns nil if none exists.
-- [2.0+]
-- @param h Handle
-- @param team int
-- @return Handle
-- @function GetNearestUnitOnTeam

--- Returns the craft or person on the given team closest to a point on the path. It uses the start of the path if no point is given. Returns nil if none exists.
-- [2.1+]
-- @param path string
-- @param point? integer
-- @param team int
-- @return Handle
-- @function GetNearestUnitOnTeam

--- Returns the craft or person on the given team closest to the position of the transform matrix. Returns nil if none exists.
-- [2.1+]
-- @param position vector
-- @param team int
-- @return Handle
-- @function GetNearestUnitOnTeam

--- Returns the craft or person on the given team closest to the position vector. Returns nil if none exists.
-- [2.1+]
-- @param transform matrix
-- @param team int
-- @return Handle
-- @function GetNearestUnitOnTeam

--- Returns how many objects with the given team and odf name are closer than the given distance.
--- @param h Handle
--- @param dist number
--- @param team TeamNum
--- @param odfname string
--- @return integer
function CountUnitsNearObject(h, dist, team, odfname)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Iterators
-------------------------------------------------------------------------------
-- @section
-- These functions return iterator functions for use with Lua's "for <variable> in <expression> do ... end" form. For example: "for h in AllCraft() do print(h, GetLabel(h)) end" will print the game object handle and label of every craft in the world.

--- Enumerates game objects within the given distance a target.
--- @param dist number
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer If the target is a path this is the path point index, defaults to 0.
--- @return fun():Handle iterator
function ObjectsInRange(dist, target, point)
    error("This function is provided by the engine.")
end

--- Enumerates all game objects.
--- Use this function sparingly at runtime since it enumerates <em>all</em> game objects, including every last piece of scrap. If you're specifically looking for craft, use AllCraft() instead.
--- @return fun():Handle iterator
function AllObjects()
    error("This function is provided by the engine.")
end

--- Enumerates all craft.
--- @return fun():Handle iterator
function AllCraft()
    error("This function is provided by the engine.")
end

--- Enumerates all game objects currently selected by the local player.
--- @return fun():Handle iterator
function SelectedObjects()
    error("This function is provided by the engine.")
end

--- Enumerates all game objects marked as objectives.
--- @return fun():Handle iterator
function ObjectiveObjects()
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Scrap Management
-------------------------------------------------------------------------------
-- @section
-- These functions remove scrap, either to reduce the global game object count or to remove clutter around a location.

--- While the global scrap count is above the limit, remove the oldest scrap piece. It no limit is given, it uses the default limit of 300.
--- @param limit? integer
function GetRidOfSomeScrap(limit) end

--- Clear all scrap within the given distance of a position vector, transform matrix, game object, or named path.
--- It uses the start of the path if no point is given.
--- @param distance number
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer
function ClearScrapAround(distance, target, point) end

-------------------------------------------------------------------------------
-- Team Slots
-------------------------------------------------------------------------------
-- @section
-- These functions look up game objects in team slots.

--- This is a global table that converts between team slot numbers and team slot names. For example, TeamSlot.PLAYER or TeamSlot["PLAYER"] returns the team slot (0) for the player; TeamSlot[0] returns the team slot name ("PLAYER") for team slot 0. For maintainability, always use this table instead of raw team slot numbers.
--- Slots starting with MIN_ and MAX_ represent the lower and upper bound of a range of slots.
--- @enum TeamSlot
TeamSlot = {
    UNDEFINED = -1,     -- invalid, -1
    PLAYER = 0,         -- 0

    RECYCLER = 1,       -- 1
    FACTORY = 2,        -- 2
    ARMORY = 3,         -- 3
    CONSTRUCT = 4,      -- 4

    MIN_OFFENSE = 5,    -- 5
    MAX_OFFENSE = 14,   -- 14
    MIN_DEFENSE = 15,   -- 15
    MAX_DEFENSE = 24,   -- 24
    MIN_UTILITY = 25,   -- 25
    MAX_UTILITY = 34,   -- 34

    MIN_BEACON = 35,    -- 35
    MAX_BEACON = 44,    -- 44

    MIN_POWER = 45,     -- 45
    MAX_POWER = 54,     -- 54
    MIN_COMM = 55,      -- 55
    MAX_COMM = 59,      -- 59
    MIN_REPAIR = 60,    -- 60
    MAX_REPAIR = 64,    -- 64
    MIN_SUPPLY = 65,    -- 65
    MAX_SUPPLY = 69,    -- 69
    MIN_SILO = 70,      -- 70
    MAX_SILO = 74,      -- 74
    MIN_BARRACKS = 75,  -- 75
    MAX_BARRACKS = 79,  -- 79
    MIN_GUNTOWER = 80,  -- 80
    MAX_GUNTOWER = 89,  -- 89

    PORTAL = 90,        -- 90 [2.2.315+]

    [-1] = "UNDEFINED", -- UNDEFINED
    [0] = "PLAYER",     -- PLAYER

    [1] = "RECYCLER",   -- RECYCLER
    [2] = "FACTORY",    -- FACTORY
    [3] = "ARMORY",     -- ARMORY
    [4] = "CONSTRUCT",  -- CONSTRUCT

    [5] = "MIN_OFFENSE", -- MIN_OFFENSE
    [14] = "MAX_OFFENSE", -- MAX_OFFENSE
    [15] = "MIN_DEFENSE", -- MIN_DEFENSE
    [24] = "MAX_DEFENSE", -- MAX_DEFENSE
    [25] = "MIN_UTILITY", -- MIN_UTILITY
    [34] = "MAX_UTILITY", -- MAX_UTILITY

    [35] = "MIN_BEACON", -- MIN_BEACON
    [44] = "MAX_BEACON", -- MAX_BEACON

    [45] = "MIN_POWER", -- MIN_POWER
    [54] = "MAX_POWER", -- MAX_POWER
    [55] = "MIN_COMM",  -- MIN_COMM
    [59] = "MAX_COMM",  -- MAX_COMM
    [60] = "MIN_REPAIR", -- MIN_REPAIR
    [64] = "MAX_REPAIR", -- MAX_REPAIR
    [65] = "MIN_SUPPLY", -- MIN_SUPPLY
    [69] = "MAX_SUPPLY", -- MAX_SUPPLY
    [70] = "MIN_SILO",  -- MIN_SILO
    [74] = "MAX_SILO",  -- MAX_SILO
    [75] = "MIN_BARRACKS", -- MIN_BARRACKS
    [79] = "MAX_BARRACKS", -- MAX_BARRACKS
    [80] = "MIN_GUNTOWER", -- MIN_GUNTOWER
    [89] = "MAX_GUNTOWER", -- MAX_GUNTOWER

    [90] = "PORTAL",    -- PORTAL [2.2.315+]
}

--- Get the game object in the specified team slot.
--- It uses the local player team if no team is given.
--- @param slot TeamSlotInteger
--- @param team? TeamNum
--- @return Handle
function GetTeamSlot(slot, team)
    error("This function is provided by the engine.")
end

--- Returns the game object controlled by the player on the given team. Returns nil if none exists.
--- It uses the local player team if no team is given.
--- @param team? TeamNum
--- @return Handle
function GetPlayerHandle(team)
    error("This function is provided by the engine.")
end

--- Returns the Recycler on the given team. Returns nil if none exists.
--- It uses the local player team if no team is given.
--- @param team? TeamNum
--- @return Handle
function GetRecyclerHandle(team)
    error("This function is provided by the engine.")
end

--- Returns the Factory on the given team. Returns nil if none exists.
--- It uses the local player team if no team is given.
--- @param team? TeamNum
--- @return Handle
function GetFactoryHandle(team)
    error("This function is provided by the engine.")
end

--- Returns the Armory on the given team. Returns nil if none exists.
--- It uses the local player team if no team is given.
--- @param team? TeamNum
--- @return Handle
function GetArmoryHandle(team)
    error("This function is provided by the engine.")
end

--- Returns the Constructor on the given team. Returns nil if none exists.
--- It uses the local player team if no team is given.
--- @param team? TeamNum
--- @return Handle
function GetConstructorHandle(team)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Team Pilots
-------------------------------------------------------------------------------
-- @section
-- These functions get and set pilot counts for a team.

--- Adds pilots to the team's pilot count, clamped between zero and maximum count.
--- Returns the new pilot count.
--- @param team TeamNum
--- @param count integer
--- @return integer
function AddPilot(team, count)
    error("This function is provided by the engine.")
end

--- Sets the team's pilot count, clamped between zero and maximum count.
--- Returns the new pilot count.
--- @param team TeamNum
--- @param count integer
--- @return integer
function SetPilot(team, count)
    error("This function is provided by the engine.")
end

--- Returns the team's pilot count.
--- @param team TeamNum
--- @return integer
function GetPilot(team)
    error("This function is provided by the engine.")
end

--- Adds pilots to the team's maximum pilot count.
--- Returns the new pilot count.
--- @param team TeamNum
--- @param count integer
--- @return integer
function AddMaxPilot(team, count)
    error("This function is provided by the engine.")
end

--- Sets the team's maximum pilot count.
--- Returns the new pilot count.
--- @param team TeamNum
--- @param count integer
--- @return integer
function SetMaxPilot(team, count)
    error("This function is provided by the engine.")
end

--- Returns the team's maximum pilot count.
--- @param team TeamNum
--- @return integer
function GetMaxPilot(team)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Team Scrap
-------------------------------------------------------------------------------
-- @section
-- These functions get and set scrap values for a team.

--- Adds to the team's scrap count, clamped between zero and maximum count.
--- Returns the new scrap count.
--- @param team TeamNum
--- @param count integer
--- @return integer
function AddScrap(team, count)
    error("This function is provided by the engine.")
end

--- Sets the team's scrap count, clamped between zero and maximum count.
--- Returns the new scrap count.
--- @param team TeamNum
--- @param count integer
--- @return integer
function SetScrap(team, count)
    error("This function is provided by the engine.")
end

--- Returns the team's scrap count.
--- @param team TeamNum
--- @return integer
function GetScrap(team)
    error("This function is provided by the engine.")
end

--- Adds to the team's maximum scrap count.
--- Returns the new maximum scrap count.
--- @param team TeamNum
--- @param count integer
--- @return integer
function AddMaxScrap(team, count)
    error("This function is provided by the engine.")
end

--- Sets the team's maximum scrap count.
--- Returns the new maximum scrap count.
--- @param team TeamNum
--- @param count integer
--- @return integer
function SetMaxScrap(team, count)
    error("This function is provided by the engine.")
end

--- Returns the team's maximum scrap count.
--- @param team TeamNum
--- @return integer
function GetMaxScrap(team)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Deploy
-------------------------------------------------------------------------------
-- @section
-- These functions control deployable craft (such as Turret Tanks or Producer units).

--- Returns true if the game object is a deployed craft. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsDeployed(h)
    error("This function is provided by the engine.")
end

--- Tells the game object to deploy.
--- @param h Handle
function Deploy(h) end

-------------------------------------------------------------------------------
-- Selection
-------------------------------------------------------------------------------
-- @section
-- These functions access selection state (i.e. whether the player has selected a game object)

--- Returns true if the game object is selected. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsSelected(h)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Mission-Critical [2.0+]
-------------------------------------------------------------------------------
-- @section
-- The "mission critical" property indicates that a game object is vital to the success of the mission and disables the "Pick Me Up" and "Recycle" commands that (eventually) cause IsAlive() to report false.

--- Returns true if the game object is marked as mission-critical. Returns false otherwise.
--- [2.0+]
--- @param h Handle
--- @return boolean
function IsCritical(h)
    error("This function is provided by the engine.")
end

--- Sets the game object's mission-critical status.
--- If critical is true or not specified, the object is marked as mission-critical. Otherwise, the object is marked as not mission critical.
--- [2.0+]
--- @param h Handle
--- @param critical? boolean
function SetCritical(h, critical) end

-------------------------------------------------------------------------------
-- Weapon
-------------------------------------------------------------------------------
-- @section
-- These functions access unit weapons and damage.

--- Sets what weapons the unit's AI process will use.
--- To calculate the mask value, add up the values of the weapon hardpoint slots you want to enable.
--- weaponHard1: 1 weaponHard2: 2 weaponHard3: 4 weaponHard4: 8 weaponHard5: 16
--- @param h Handle
--- @param mask integer
function SetWeaponMask(h, mask) end

--- Gives the game object the named weapon in the given slot. If no slot is given, it chooses a slot based on hardpoint type and weapon priority like a weapon powerup would. If the weapon name is empty, nil, or blank and a slot is given, it removes the weapon in that slot.
--- Returns true if it succeeded. Returns false otherwise.
--- @param h Handle
--- @param weaponname? string
--- @param slot? integer
function GiveWeapon(h, weaponname, slot) end

--- Returns the odf name of the weapon in the given slot on the game object. Returns nil if the game object does not exist or the slot is empty.
--- For example, an "avtank" game object would return "gatstab" for index 0 and "gminigun" for index 1.
--- @param h Handle
--- @param slot integer
--- @return string
function GetWeaponClass(h, slot)
    error("This function is provided by the engine.")
end

--- Tells the game object to fire at the given target.
--- @param me Handle
--- @param him Handle
function FireAt(me, him) end

--- Applies damage to the game object.
--- @param h Handle
--- @param amount number
function Damage(h, amount) end

-------------------------------------------------------------------------------
-- Time
-------------------------------------------------------------------------------
-- @section
-- These function report various global time values.

--- Returns the elapsed time in seconds since the start of the mission.
--- @return number
function GetTime()
    error("This function is provided by the engine.")
end

--- Returns the simulation time step in seconds.
--- @return number
function GetTimeStep()
    error("This function is provided by the engine.")
end

--- Returns the current system time in milliseconds. This is mostly useful for performance profiling.
--- @return number
function GetTimeNow()
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Mission
-------------------------------------------------------------------------------
-- @section
-- These functions control general mission properties like strategic AI and mission flow

--- Enables (or disables) strategic AI control for a given team. As of version 1.5.2.7, mission scripts must enable AI control for any team that intends to use an AIP.
--- IMPORTANT SAFETY TIP: only call this function from the "root" of the Lua mission script! The strategic AI gets set up shortly afterward and attempting to use SetAIControl later will crash the game.
--- @param team TeamNum
--- @param control? boolean, defaults to true
function SetAIControl(team, control) end

--- Returns true if a given team is AI controlled. Returns false otherwise.
--- Unlike SetAIControl, this function may be called at any time.
--- @param team TeamNum
--- @return boolean
function GetAIControl(team)
    error("This function is provided by the engine.")
end

--- Returns the current AIP for the team. It uses team 2 if no team number is given.
--- @param team? TeamNum
--- @return string
--- @function GetAIP
function GetAIP(team)
    error("This function is provided by the engine.")
end

--- Switches the team's AI plan. It uses team 2 if no team number is given.
--- @param aipname string
--- @param team? TeamNum
function SetAIP(aipname, team) end

--- Fails the mission after the given time elapses. If supplied with a filename (usually a .des), it sets the failure message to text from that file.
--- @param time number
--- @param filename? string
function FailMission(time, filename) end

--- Succeeds the mission after the given time elapses. If supplied with a filename (usually a .des), it sets the success message to text from that file.
--- @param time number
--- @param filename? string
function SucceedMission(time, filename) end

-------------------------------------------------------------------------------
-- Objective Messages
-------------------------------------------------------------------------------
-- @section
-- These functions control the objective panel visible at the right of the screen.

--- Clears all objective messages.
function ClearObjectives() end

--- Adds an objective message with the given name and properties.
--- @param name string Unique name for objective, usually a filename ending with otf from which data is loaded
--- @param color? ColorLabel Default to "WHITE".
--- @param duration? number defaults to 8 seconds
--- @param text? string Override text from the target objective file. [2.0+]
function AddObjective(name, color, duration, text) end

--- Updates the objective message with the given name. If no objective exists with that name, it does nothing.
--- @param name string Unique name for objective, usually a filename ending with otf from which data is loaded
--- @param color? ColorLabel Default to "WHITE".
--- @param duration? number defaults to 8 seconds
--- @param text? string Override text from the target objective file. [2.0+]
function UpdateObjective(name, color, duration, text) end

--- Removes the objective message with the given file name. Messages after the removed message will be moved up to fill the vacancy. If no objective exists with that file name, it does nothing.
--- @param name string
function RemoveObjective(name) end

-------------------------------------------------------------------------------
-- Cockpit Timer
-------------------------------------------------------------------------------
-- @section
-- These functions control the large timer at the top of the screen.

--- Starts the cockpit timer counting down from the given time. If a warn time is given, the timer will turn yellow when it reaches that value. If an alert time is given, the timer will turn red when it reaches that value. All time values are in seconds.
--- The start time can be up to 35999, which will appear on-screen as 9:59:59. If the remaining time is an hour or less, the timer will show only minutes and seconds.
--- @param time integer
--- @param warn? integer
--- @param alert? integer
function StartCockpitTimer(time, warn, alert) end

--- Starts the cockpit timer counting up from the given time. If a warn time is given, the timer will turn yellow when it reaches that value. If an alert time is given, the timer will turn red when it reaches that value. All time values are in seconds.
--- The on-screen timer will always show hours, minutes, and seconds The hours digit will malfunction after 10 hours.
--- @param time integer
--- @param warn? integer
--- @param alert? integer
function StartCockpitTimerUp(time, warn, alert) end

--- Stops the cockpit timer.
function StopCockpitTimer() end

--- Hides the cockpit timer.
function HideCockpitTimer() end

--- Returns the current time in seconds on the cockpit timer.
--- @return integer
function GetCockpitTimer()
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Earthquake
-------------------------------------------------------------------------------
-- @section
-- These functions control the global earthquake effect.

--- Starts a global earthquake effect.
--- @param magnitude number
function StartEarthquake(magnitude) end

--- Changes the magnitude of an existing earthquake effect.
--- Important: note the inconsistent capitalization, which matches the internal C++ script utility functions.
--- @param magnitude number
function UpdateEarthQuake(magnitude) end

--- Stops the global earthquake effect.
function StopEarthquake() end

-------------------------------------------------------------------------------
-- Path Type
-------------------------------------------------------------------------------
-- @section
-- These functions get and set the looping type of a path.
-- Looking up the path type number in the PathType table will convert it to a string. Looking up the path type string in the PathType table will convert it to a number.
-- <ul>
--     <li>0: one-way</li>
--     <li>1: round-trip</li>
--     <li>2: loop</li>
-- </ul>

--- Changes the named path to the given path type.
--- [2.0+]
--- @param path string
--- @param type integer
function SetPathType(path, type) end

--- Returns the type of the named path.
--- [2.0+]
--- @param path string
--- @return integer
function GetPathType(path)
    error("This function is provided by the engine.")
end

--- Changes the named path to one-way. Once a unit reaches the end of the path, it will stop.
--- @param path string
function SetPathOneWay(path) end

--- Changes the named path to round-trip. Once a unit reaches the end of the path, it will follow the path backwards to the start and begin again.
--- @param path string
function SetPathRoundTrip(path) end

--- Changes the named path to looping. Once a unit reaches the end of the path, it will continue along to the start and begin again.
--- @param path string
function SetPathLoop(path) end

-------------------------------------------------------------------------------
-- Path Points [2.0+]
-------------------------------------------------------------------------------
-- @section

--- Returns the number of points in the named path, or 0 if the path does not exist.
--- [2.0+]
--- @param path string
--- @return integer
function GetPathPointCount(path)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Path Area [2.0+]
-------------------------------------------------------------------------------
-- @section
-- These functions treat a path as the boundary of a closed polygonal area.

--- Returns how many times the named path loops around the given position vector, transform matrix, or object.
--- Each full counterclockwise loop adds one and each full clockwise loop subtracts one.
--- [2.0+]
--- @param path string
--- @param target Vector|Matrix|string
--- @return integer
function GetWindingNumber(path, target)
    error("This function is provided by the engine.")
end

--- Returns true if the given position vector, transform matrix, or object is inside the area bounded by the named path. Returns false otherwise.
--- This function is equivalent to <pre>GetWindingNumber( path, h ) ~= 0</pre>
--- [2.0+]
--- @param path string
--- @param target Vector|Matrix|Handle
--- @return boolean
function IsInsideArea(path, target)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
--- Unit Commands
-------------------------------------------------------------------------------
-- @section
-- These These functions send commands to units or query their command state.

--- This is a global table that converts between command numbers and command names. For example, AiCommand.GO or AiCommand["GO"] returns the command number (3) for the "go" command; AiCommand[3] returns the command name ("GO") for command number 3. For maintainability, always use this table instead of raw command numbers.
--- @enum AiCommand
AiCommand = {
    NONE = 0,           -- 0
    SELECT = 1,         -- 1
    STOP = 2,           -- 2
    GO = 3,             -- 3
    ATTACK = 4,         -- 4
    FOLLOW = 5,         -- 5
    FORMATION = 6,      -- 6
    PICKUP = 7,         -- 7
    DROPOFF = 8,        -- 8
    NO_DROPOFF = 9,     -- 9
    GET_REPAIR = 10,    -- 10
    GET_RELOAD = 11,    -- 11
    GET_WEAPON = 12,    -- 12
    GET_CAMERA = 13,    -- 13
    GET_BOMB = 14,      -- 14
    DEFEND = 15,        -- 15
    GO_TO_GEYSER = 16,  -- 16
    RESCUE = 17,        -- 17
    RECYCLE = 18,       -- 18
    SCAVENGE = 19,      -- 19
    HUNT = 20,          -- 20
    BUILD = 21,         -- 21
    PATROL = 22,        -- 22
    STAGE = 23,         -- 23
    SEND = 24,          -- 24
    GET_IN = 25,        -- 25
    LAY_MINES = 26,     -- 26
    CLOAK = 27,         -- 27 [2.1+]
    DECLOAK = 28,       -- 28 [2.1+]
    [0] = "NONE",       -- NONE
    [1] = "SELECT",     -- SELECT
    [2] = "STOP",       -- STOP
    [3] = "GO",         -- GO
    [4] = "ATTACK",     -- ATTACK
    [5] = "FOLLOW",     -- FOLLOW
    [6] = "FORMATION",  -- FORMATION
    [7] = "PICKUP",     -- PICKUP
    [8] = "DROPOFF",    -- DROPOFF
    [9] = "NO_DROPOFF", -- NO_DROPOFF
    [10] = "GET_REPAIR", -- GET_REPAIR
    [11] = "GET_RELOAD", -- GET_RELOAD
    [12] = "GET_WEAPON", -- GET_WEAPON
    [13] = "GET_CAMERA", -- GET_CAMERA
    [14] = "GET_BOMB",  -- GET_BOMB
    [15] = "DEFEND",    -- DEFEND
    [16] = "GO_TO_GEYSER", -- GO_TO_GEYSER
    [17] = "RESCUE",    -- RESCUE
    [18] = "RECYCLE",   -- RECYCLE
    [19] = "SCAVENGE",  -- SCAVENGE
    [20] = "HUNT",      -- HUNT
    [21] = "BUILD",     -- BUILD
    [22] = "PATROL",    -- PATROL
    [23] = "STAGE",     -- STAGE
    [24] = "SEND",      -- SEND
    [25] = "GET_IN",    -- GET_IN
    [26] = "LAY_MINES", -- LAY_MINES
    [27] = "CLOAK",     -- CLOAK [2.1+]
    [28] = "DECLOAK",   -- DECLOAK [2.1+]
}

--- Returns true if the game object can be commanded. Returns false otherwise.
--- @param me Handle
--- @return boolean
function CanCommand(me)
    error("This function is provided by the engine.")
end

--- Returns true if the game object is a producer that can build at the moment. Returns false otherwise.
--- @param me Handle
--- @return boolean
function CanBuild(me)
    error("This function is provided by the engine.")
end

--- Returns true if the game object is a producer and currently busy. Returns false otherwise.
--- @param me Handle
--- @return boolean
function IsBusy(me)
    error("This function is provided by the engine.")
end

--- Returns the current command for the game object. Looking up the command number in the AiCommand table will convert it to a string. Looking up the command string in the AiCommand table will convert it back to a number.
--- @param me Handle
--- @return AiCommand
function GetCurrentCommand(me)
    error("This function is provided by the engine.")
end

--- Returns the target of the current command for the game object. Returns nil if it has none.
--- @param me Handle
--- @return Handle
function GetCurrentWho(me)
    error("This function is provided by the engine.")
end

--- Gets the independence of a unit.
--- @param me Handle
--- @return integer
function GetIndependence(me)
    error("This function is provided by the engine.")
end

--- Sets the independence of a unit. 1 (the default) lets the unit take initiative (e.g. attack nearby enemies), while 0 prevents that.
--- @param me Handle
--- @param independence integer
function SetIndependence(me, independence) end

--- Commands the unit using the given parameters. Be careful with this since not all commands work with all units and some have strict requirements on their parameters.
--- "Command" is the command to issue, normally chosen from the global AiCommand table (e.g. AiCommand.GO).
--- "Priority" is the command priority; a value of 0 leaves the unit commandable by the player while the default value of 1 makes it uncommandable.
--- "Who" is an optional target game object.
--- "Where" is an optional destination, and can be a matrix (transform), a vector (position), or a string (path name).
--- "When" is an optional absolute time value only used by command AiCommand.STAGE.
--- "Param" is an optional odf name only used by command AiCommand.BUILD.
--- @param me Handle
--- @param command integer
--- @param priority? integer
--- @param who? Handle
--- @param where Matrix|Vector|string?
--- @param when? number
--- @param param? string
function SetCommand(me, command, priority, who, where, when, param) end

--- Commands the unit to attack the given target.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param him Handle
--- @param priority? integer
function Attack(me, him, priority) end

--- Commands the unit to go to the position vector, transform matrix, game object location, or named path.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param priority? integer
function Goto(me, target, priority) end

--- Commands the unit to lay mines at the given position vector, transform matrix, or named path.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param target Vector|Matrix|string
--- @param priority? integer
function Mine(me, target, priority) end

--- Commands the unit to follow the given target.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param him Handle
--- @param priority? integer
function Follow(me, him, priority) end

--- Returns true if the unit is currently following the given target.
--- [2.1+]
--- @param me Handle
--- @param him Handle
--- @return boolean
function IsFollowing(me, him)
    error("This function is provided by the engine.")
end

--- Commands the unit to defend its current location.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param priority? integer
function Defend(me, priority) end

--- Commands the unit to defend the given target.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param him Handle
--- @param priority? integer
--- @function Defend2
function Defend2(me, him, priority) end

--- Commands the unit to stop at its current location.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param priority? integer
function Stop(me, priority) end

--- Commands the unit to patrol along the named path. This is equivalent to Goto with an independence of 1.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param path string
--- @param priority? integer
function Patrol(me, path, priority) end

--- Commands the unit to retreat to the given target or named path.
--- This is equivalent to Goto with an independence of 0.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param target Handle|string
--- @param priority? integer
function Retreat(me, target, priority) end

--- Commands the pilot to get into the target vehicle.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param him Handle
--- @param priority? integer
function GetIn(me, him, priority) end

--- Commands the unit to pick up the target object. Deployed units pack up (ignoring the target), scavengers pick up scrap, and tugs pick up and carry objects.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param him Handle
--- @param priority? integer
function Pickup(me, him, priority) end

--- Commands the unit to drop off at the position vector, transform matrix, or named path.
--- Tugs drop off their cargo and Construction Rigs build the selected item at the location using their current facing.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param target Vector|Matrix|string
--- @param priority? integer
function Dropoff(me, target, priority) end

--- Commands a producer to build the given odf name. The Armory and Construction Rig need an additional Dropoff to give them a location to build but first need at least one simulation update to process the Build.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param odfname string
--- @param priority? integer
function Build(me, odfname, priority) end

--- Commands a producer to build the given odf name at the position vector, transform matrix, game object location, or named path.
--- A Construction Rig will build at the location and an Armory will launch the item to the location. Other producers will ignore the location.
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- @param me Handle
--- @param odfname string
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param priority? integer
function BuildAt(me, odfname, target, priority) end

--- Commands the unit to follow the given target closely. This function is equivalent to SetCommand(me, AiCommand.FORMATION, priority, him).
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- [2.1+]
--- @param me Handle
--- @param him Handle
--- @param priority? integer
function Formation(me, him, priority) end

--- Commands the unit to hunt for targets autonomously. This function is equivalent to SetCommand(me, AiCommand.HUNT, priority).
--- Priority 0 leaves the unit commandable while the default priority 1 makes it uncommandable.
--- [2.1+]
--- @param me Handle
--- @param priority? integer
function Hunt(me, priority) end

-------------------------------------------------------------------------------
-- Tug Cargo
-------------------------------------------------------------------------------
-- @section
-- These functions query Tug and Cargo.

--- Returns true if the unit is a tug carrying cargo.
--- @param tug Handle
--- @return boolean
function HasCargo(tug)
    error("This function is provided by the engine.")
end

--- Returns the handle of the cargo if the unit is a tug carrying cargo. Returns nil otherwise.
--- [2.1+]
--- @param tug Handle
--- @return Handle?
function GetCargo(tug)
    error("This function is provided by the engine.")
end

--- Returns the handle of the tug carrying the object. Returns nil if not carried.
--- @param cargo Handle
--- @return Handle
function GetTug(cargo)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Pilot Actions
-------------------------------------------------------------------------------
-- @section
-- These functions control the pilot of a vehicle.

--- Commands the vehicle's pilot to eject.
--- @param h Handle
function EjectPilot(h) end

--- Commands the vehicle's pilot to hop out.
--- @param h Handle
function HopOut(h) end

--- Kills the vehicle's pilot as if sniped.
--- @param h Handle
function KillPilot(h) end

--- Removes the vehicle's pilot cleanly.
--- @param h Handle
function RemovePilot(h) end

--- Returns the vehicle that the pilot most recently hopped out of.
--- @param h Handle
--- @return Handle
function HoppedOutOf(h)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Health Values
-------------------------------------------------------------------------------
-- @section
-- These functions get and set health values on a game object.

--- Returns the fractional health of the game object between 0 and 1.
--- @param h Handle
--- @return number
function GetHealth(h)
    error("This function is provided by the engine.")
end

--- Returns the current health value of the game object.
--- @param h Handle
--- @return number
function GetCurHealth(h)
    error("This function is provided by the engine.")
end

--- Returns the maximum health value of the game object.
--- @param h Handle
--- @return number
function GetMaxHealth(h)
    error("This function is provided by the engine.")
end

--- Sets the current health of the game object.
--- @param h Handle
--- @param health number
function SetCurHealth(h, health) end

--- Sets the maximum health of the game object.
--- @param h Handle
--- @param health number
function SetMaxHealth(h, health) end

--- Adds to the current health of the game object.
--- @param h Handle
--- @param health number
function AddHealth(h, health) end

--- Sets the unit's current health to maximum.
--- [2.1+]
--- @param h Handle
function GiveMaxHealth(h) end

-------------------------------------------------------------------------------
-- Ammo Values
-------------------------------------------------------------------------------
-- @section
-- These functions get and set ammo values on a game object.

--- Returns the fractional ammo of the game object between 0 and 1.
--- @param h Handle
--- @return number
function GetAmmo(h)
    error("This function is provided by the engine.")
end

--- Returns the current ammo value of the game object.
--- @param h Handle
--- @return number
function GetCurAmmo(h)
    error("This function is provided by the engine.")
end

--- Returns the maximum ammo value of the game object.
--- @param h Handle
--- @return number
function GetMaxAmmo(h)
    error("This function is provided by the engine.")
end

--- Sets the current ammo of the game object.
--- @param h Handle
--- @param ammo number
function SetCurAmmo(h, ammo) end

--- Sets the maximum ammo of the game object.
--- @param h Handle
--- @param ammo number
function SetMaxAmmo(h, ammo) end

--- Adds to the current ammo of the game object.
--- @param h Handle
--- @param ammo number
function AddAmmo(h, ammo) end

--- Sets the unit's current ammo to maximum.
--- [2.1+]
--- @param h Handle
function GiveMaxAmmo(h) end

-------------------------------------------------------------------------------
-- Cinematic Camera
-------------------------------------------------------------------------------
-- These functions control the cinematic camera for in-engine cut scenes (or "cineractives" as the Interstate '76 team at Activision called them).
-- @section

--- Starts the cinematic camera and disables normal input.
--- Always returns true.
--- @return boolean
function CameraReady()
    error("This function is provided by the engine.")
end

--- Moves a cinematic camera along a path at a given height and speed while looking at a target game object.
--- Returns true when the camera arrives at its destination. Returns false otherwise.
--- @param path string
--- @param height integer
--- @param speed integer
--- @param target Handle
--- @return boolean
function CameraPath(path, height, speed, target)
    error("This function is provided by the engine.")
end

--- Moves a cinematic camera long a path at a given height and speed while looking along the path direction.
--- Returns true when the camera arrives at its destination. Returns false otherwise.
--- @param path string
--- @param height integer
--- @param speed integer
--- @return boolean
function CameraPathDir(path, height, speed)
    error("This function is provided by the engine.")
end

--- Moves a cinematic camera along a path at a given height and speed while looking at a target path.
--- Returns true when the camera arrives at its destination. Returns false otherwise.
--- @param path string
--- @param height integer
--- @param speed integer
--- @param target string
--- @return boolean
function CameraPathPath(path, height, speed, target)
    error("This function is provided by the engine.")
end

--- Returns true when the camera arrives at its destination. Returns false otherwise.
--- @return boolean
function PanDone()
    error("This function is provided by the engine.")
end

--- Offsets a cinematic camera from a base game object while looking at a target game object. The right, up, and forward offsets are in centimeters.
--- Returns true if the base or handle game object does not exist. Returns false otherwise.
--- @param base Handle
--- @param right integer
--- @param up integer
--- @param forward integer
--- @param target Handle
--- @return boolean
function CameraObject(base, right, up, forward, target)
    error("This function is provided by the engine.")
end

--- Finishes the cinematic camera and enables normal input.
--- Always returns true.
--- @return boolean
function CameraFinish()
    error("This function is provided by the engine.")
end

--- Returns true if the player canceled the cinematic. Returns false otherwise.
--- @return boolean
function CameraCancelled()
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Info Display
-------------------------------------------------------------------------------
-- @section

--- Returns true if the game object inspected by the info display matches the given odf name.
--- @param odfname string
--- @return boolean
function IsInfo(odfname)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Network
-------------------------------------------------------------------------------
-- @section
-- LuaMission currently has limited network support, but can detect if the mission is being run in multiplayer and if the local machine is hosting.

--- Returns true if the game is a network game. Returns false otherwise.
--- @return boolean
function IsNetGame()
    error("This function is provided by the engine.")
end

--- Returns true if the local machine is hosting a network game. Returns false otherwise.
--- @return boolean
function IsHosting()
    error("This function is provided by the engine.")
end

--- Sets the game object as local to the machine the script is running on, transferring ownership from its original owner if it was remote. Important safety tip: only call this on one machine at a time!
---
--- Multiplayer remarks: Safe to call in singleplayer, has no function. If called on a remote object, it will break their ai irreversibly.
--- @param h Handle
function SetLocal(h) end

--- Returns true if the game is local to the machine the script is running on. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsLocal(h)
    error("This function is provided by the engine.")
end

--- Returns true if the game object is remote to the machine the script is running on. Returns false otherwise.
--- @param h Handle
--- @return boolean
function IsRemote(h)
    error("This function is provided by the engine.")
end

--- Adds a system text message to the chat window on the local machine.
---
--- Multiplayer remarks: The displayed message is entirely local regardless of hosting status, if you want a message to be visible to all players
--- you should Send() a message to all players to display the given message.
--- @param message string
function DisplayMessage(message) end

--- Send a script-defined message across the network.
--- To is the player network id of the recipient. None, nil, or 0 broadcasts to all players.
--- Type is a one-character string indicating the script-defined message type.
--- Other parameters will be sent as data and passed to the recipient's Receive function as parameters. Send supports nil, boolean, handle, integer, number, string, vector, and matrix data types. It does not support function, thread, or arbitrary userdata types.
--- The sent packet can contain up to 244 bytes of data (255 bytes maximum for an Anet packet minus 6 bytes for the packet header and 5 bytes for the reliable transmission header)
--- <table style="border-collapse:collapse;border:3px solid black;"><tbody>
---   <tr><th style="border:2px solid black;" colspan="2">Type</th><th style="border:2px solid black;">Bytes</th></tr>
---   <tr><td style="border:2px solid black;" colspan="2">nil</td><td style="border:2px solid black;">1</td></tr>
---   <tr><td style="border:2px solid black;" colspan="2">boolean</td><td style="border:2px solid black;">1</td></tr>
---   <tr><td style="border:2px solid black;" rowspan="2">handle</td><td style="border:2px solid black;">invalid (zero)</td><td style="border:2px solid black;">1</td></tr>
---   <tr><td style="border:2px solid black;">valid (nonzero)</td><td style="border:2px solid black;">1 + sizeof(int) = 5</td></tr>
---   <tr><td style="border:2px solid black;" rowspan="5">number</td><td style="border:2px solid black;">zero</td><td style="border:2px solid black;">1</td></tr>
---   <tr><td style="border:2px solid black;">char (integer -128 to 127)</td><td style="border:2px solid black;">1 + sizeof(char) = 2</td></tr>
---   <tr><td style="border:2px solid black;">short (integer -32768 to 32767)</td><td style="border:2px solid black;">1 + sizeof(short) = 3</td></tr>
---   <tr><td style="border:2px solid black;">int (integer)</td><td style="border:2px solid black;">1 + sizeof(int) = 5</td></tr>
---   <tr><td style="border:2px solid black;">double (non-integer)</td><td style="border:2px solid black;">1 + sizeof(double) = 9</td></tr>
---   <tr><td style="border:2px solid black;" rowspan="2">string</td><td style="border:2px solid black;">length &lt; 31</td><td style="border:2px solid black;">1 + length</td></tr>
---   <tr><td style="border:2px solid black;">length &gt;= 31</td><td style="border:2px solid black;">2 + length</td></tr>
---   <tr><td style="border:2px solid black;" rowspan="2">table</td><td style="border:2px solid black;">count &lt; 31</td><td style="border:2px solid black;">1 + count + size of keys and values</td></tr>
---   <tr><td style="border:2px solid black;">count &gt;= 31</td><td style="border:2px solid black;">2 + count + size of keys and values</td></tr>
---   <tr><td style="border:2px solid black;" rowspan="2">userdata</td><td style="border:2px solid black;">VECTOR_3D</td><td style="border:2px solid black;">1 + sizeof(VECTOR_3D) = 13</td></tr>
---   <tr><td style="border:2px solid black;">MAT_3D</td><td style="border:2px solid black;">1 + sizeof(REDUCED_MAT) = 12</td></tr>
--- </tbody></table>
--- @param to integer
--- @param type string
--- @vararg any
function Send(to, type, ...) end

-------------------------------------------------------------------------------
-- Read ODF
-------------------------------------------------------------------------------
-- @section
-- These functions read values from an external ODF, INI, or TRN file.

--- Opens the named file as an ODF. If the file name has no extension, the function will append ".odf" automatically.
--- If the file is not already open, the function reads in and parses the file into an internal database. If you need to read values from it relatively frequently, save the handle into a global variable to prevent it from closing.
--- Returns the file handle if it succeeded. Returns nil if it failed.
--- @param filename string
--- @return ParameterDB
function OpenODF(filename)
    error("This function is provided by the engine.")
end

--- Reads a boolean value from the named label in the named section of the ODF file. Use a nil section to read labels that aren't in a section.
--- It considers values starting with 'Y', 'y', 'T', 't', or '1' to be true and value starting with 'N', 'n', 'F', 'f', or '0' to be false. Other values are considered undefined.
--- If a value is not found or is undefined, it uses the default value. If no default value is given, the default value is false.
--- Returns the value and whether the value was found.
--- @param odf ParameterDB
--- @param section? string
--- @param label string
--- @param default? boolean
--- @return boolean
--- @return boolean
function GetODFBool(odf, section, label, default)
    error("This function is provided by the engine.")
end

--- Reads an integer value from the named label in the named section of the ODF file. Use nil as the section to read labels that aren't in a section.
--- If no value is found, it uses the default value. If no default value is given, the default value is 0.
--- Returns the value and whether the value was found.
--- @param odf ParameterDB
--- @param section? string
--- @param label string
--- @param default? integer
--- @return integer
--- @return boolean
function GetODFInt(odf, section, label, default)
    error("This function is provided by the engine.")
end

--- Reads a floating-point value from the named label in the named section of the ODF file. Use nil as the section to read labels that aren't in a section.
--- If no value is found, it uses the default value. If no default value is given, the default value is 0.0.
--- Returns the value and whether the value was found.
--- @param odf ParameterDB
--- @param section? string
--- @param label string
--- @param default? number
--- @return number
--- @return boolean
function GetODFFloat(odf, section, label, default)
    error("This function is provided by the engine.")
end

--- Reads a string value from the named label in the named section of the ODF file. Use nil as the section to read labels that aren't in a section.
--- If a value is not found, it uses the default value. If no default value is given, the default value is nil.
--- Returns the value and whether the value was found.
--- @param odf ParameterDB
--- @param section? string
--- @param label string
--- @param default? string
--- @return string
--- @return boolean
function GetODFString(odf, section, label, default)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Terrain
-------------------------------------------------------------------------------
-- @section
-- These functions return height and normal from the terrain height field.

--- Returns the terrain height and normal vector at a position vector, transform matrix, object, or point on a named path.
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer
--- @return number
--- @return Vector
function GetTerrainHeightAndNormal(target, point)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Floor
-------------------------------------------------------------------------------
-- These functions return height and normal from the terrain height field and the upward-facing polygons of any entities marked as floor owners.
-- @section

--- Returns the floor height and normal vector at a position vector, transform matrix, object, or point on a named path.
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
--- @param point? integer
--- @return number
--- @return Vector
function GetFloorHeightAndNormal(target, point)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Map
-------------------------------------------------------------------------------
-- @section

--- Returns the name of the BZN file for the map. This can be used to generate an ODF name for mission settings.
--- [2.0+]
--- @return string
function GetMissionFilename()
    error("This function is provided by the engine.")
end

--- Returns the name of the TRN file for the map. This can be used with OpenODF() to read values from the TRN file.
--- @return string
function GetMapTRNFilename()
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Files [2.0+]
-------------------------------------------------------------------------------
-- @section

--- Returns the contents of the named file as a string, or nil if the file could not be opened.
--- [2.0+]
--- @param filename string
--- @function string UseItem
function UseItem(filename) end

-------------------------------------------------------------------------------
-- Effects [2.0+]
-------------------------------------------------------------------------------
-- @section

--- Starts a full screen color fade.
--- Ratio sets the opacity, with 0.0 transparent and 1.0 almost opaque
--- Rate sets how fast the opacity decreases over time.
--- R, G, and B set the color components and range from 0 to 255
--- [2.0+]
--- @param ratio number
--- @param rate number
--- @param r integer
--- @param g integer
--- @param b integer
function ColorFade(ratio, rate, r, g, b) end

-------------------------------------------------------------------------------
-- Vector
-------------------------------------------------------------------------------
-- @section
-- This is a custom userdata representing a position or direction. It has three number components: x, y, and z.

--- A Vector in 3D space
--- @class Vector
--- @field x number The x-coordinate.
--- @field y number The y-coordinate.
--- @field z number The z-coordinate.
--- @operator unm: Vector
--- @operator add(Vector): Vector
--- @operator sub(Vector): Vector

local Vector = {}

--- Returns a vector whose components have the given number values. If no value is given for a component, the default value is 0.0.
--- @param x? number
--- @param y? number
--- @param z? number
--- @return Vector
function SetVector(x, y, z)
    error("This function is provided by the engine.")
end

--- Returns the <a href="http://en.wikipedia.org/wiki/Dot_product">dot product</a> between vectors a and b.
--- Equivalent to a.x * b.x + a.y * b.y + a.z * b.z.
--- @param a Vector
--- @param b Vector
--- @return number
function DotProduct(a, b)
    error("This function is provided by the engine.")
end

--- Returns the <a href="http://en.wikipedia.org/wiki/Cross_product">cross product</a> between vectors a and b.
--- Equivalent to SetVector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x).
--- @param a Vector
--- @param b Vector
--- @return Vector
function CrossProduct(a, b)
    error("This function is provided by the engine.")
end

--- Returns the vector scaled to unit length.
--- Equivalent to SetVector(v.x * scale, v.y * scale, v.z * scale) where scale is 1.0f / sqrt(v.x<sup>2</sup> + v.y<sup>2</sup> + v.z<sup>2</sup>).
--- @param v Vector
--- @return Vector
function Normalize(v)
    error("This function is provided by the engine.")
end

--- Returns the length of the vector.
--- Equivalent to sqrt(v.x<sup>2</sup> + v.y<sup>2</sup> + v.z<sup>2</sup>).
--- @param v Vector
--- @return number
function Length(v)
    error("This function is provided by the engine.")
end

--- Returns the squared length of the vector.
--- Equivalent to v.x<sup>2</sup> + v.y<sup>2</sup> + v.z<sup>2</sup>.
--- @param v Vector
--- @return number
function LengthSquared(v)
    error("This function is provided by the engine.")
end

--- Returns the 2D distance between vectors a and b.
--- Equivalent to sqrt((b.x - a.x)<sup>2</sup> + (b.z - a.z)<sup>2</sup>).
--- @param a Vector
--- @param b Vector
--- @return number
--- @function Distance2D
function Distance2D(a, b)
    error("This function is provided by the engine.")
end

--- Returns the squared 2D distance of the vector.
--- Equivalent to (b.x - a.x)<sup>2</sup> + (b.z - a.z)<sup>2</sup>.
--- @param a Vector
--- @param b Vector
--- @return number
--- @function Distance2DSquared
function Distance2DSquared(a, b)
    error("This function is provided by the engine.")
end

--- Returns the 3D distance between vectors a and b.
--- Equivalent to sqrt((b.x - a.x)<sup>2</sup> + (b.y - a.y)<sup>2</sup> + (b.z - a.z)<sup>2</sup>).
--- @param a Vector
--- @param b Vector
--- @return number
--- @function Distance3D
function Distance3D(a, b)
    error("This function is provided by the engine.")
end

--- Returns the squared 3D distance of the vector.
--- Equivalent to (b.x - a.x)<sup>2</sup> + (b.y - a.y)<sup>2</sup> + (b.z - a.z)<sup>2</sup>.
--- @param a Vector
--- @param b Vector
--- @return number
--- @function Distance3DSquared
function Distance3DSquared(a, b)
    error("This function is provided by the engine.")
end

--- Negate the vector.
---
--- Equivalent to SetVector(-vector.x, -vector.y, -vector.z).
--- @param v Vector
--- @return Vector v
--- @function Vector.__unm
function Vector.__unm(v)
    error("This function is provided by the engine.")
end

--- Add two vectors.
---
--- Equivalent to SetVector(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z).
--- @param v1 Vector
--- @param v2 Vector
--- @return Vector v
--- @function Vector.__add
function Vector.__add(v1, v2)
    error("This function is provided by the engine.")
end

--- Subtract two vectors.
---
--- Equivlent to SetVector(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z).
--- @param v1 Vector
--- @param v2 Vector
--- @return Vector v
--- @function Vector.__sub
function Vector.__sub(v1, v2)
    error("This function is provided by the engine.")
end

--- Multiply a number by a vector.
--
-- Equivalent to SetVector( number * vector.x, number * vector.y, number * vector.z).
-- @tparam number number
-- @tparam Vector vector
-- @treturn Vector
-- @function Vector.__mul

--- Multiply a vector by a number.
--
-- Equivalent to SetVector(vector.x * number, vector.y * number, vector.z * number).
-- @tparam Vector vector
-- @tparam number number
-- @treturn Vector
-- @function Vector.__mul

--- Multiply two vectors.
--
-- Equivlent to SetVector(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z)
-- @tparam Vector vector1
-- @tparam Vector vector2
-- @treturn Vector
-- @function Vector.__mul

--- Multiply a vector by a number, number by a vector, or vector by a vector.
---
--- Equivalent to SetVector( number * vector.x, number * vector.y, number * vector.z).
---
--- Equivalent to SetVector(vector.x * number, vector.y * number, vector.z * number).
---
--- Equivlent to SetVector(vector1.x * vector2.x, vector1.y * vector2.y, vector1.z * vector2.z)
--- @overload fun(a: Vector, b: number): Vector
--- @overload fun(a: number, b: Vector): Vector
--- @overload fun(a: Vector, b: Vector): Vector
--- @param a Vector|number The vector or number to multiply.
--- @param b Vector|number The vector or number to multiply.
--- @return Vector vector The resulting vector after multiplication.
--- @function Vector.__mul
function Vector.__mul(a, b)
    error("This function is provided by the engine.")
end

--- Divide a number by a vector.
--
-- Equivalent to SetVector( number / vector.x, number / vector.y, number / vector.z).
-- @tparam number number
-- @tparam vector vector
-- @treturn Vector
-- @function Vector.__div

--- Divide a vector by a number.
--
-- Equivalent to SetVector(vector.x / number, vector.y / number, vector.z / number).
-- @tparam vector vector
-- @tparam number number
-- @treturn Vector
-- @function Vector.__div

--- Divide two vectors.
--
-- Equivalent to SetVector(vector1.x / vector2.x, vector1.y / vector2.y, vector1.z / vector2.z)
-- @tparam vector vector1
-- @tparam vector vector2
-- @treturn Vector
-- @function Vector.__div

--- Divide a vector by a number, number by a vector, or vector by a vector.
---
--- Equivalent to SetVector( number / vector.x, number / vector.y, number / vector.z).
---
--- Equivalent to SetVector(vector.x / number, vector.y / number, vector.z / number).
---
--- Equivalent to SetVector(vector1.x / vector2.x, vector1.y / vector2.y, vector1.z / vector2.z)
--- @overload fun(a: Vector, b: number): Vector
--- @overload fun(a: number, b: Vector): Vector
--- @overload fun(a: Vector, b: Vector): Vector
--- @param a Vector|number The vector or number to multiply.
--- @param b Vector|number The vector or number to multiply.
--- @return Vector vector The resulting vector after division.
--- @function Vector.__mul
function Vector.__div(a, b)
    error("This function is provided by the engine.")
end

--- Check if two vectors are equal.
---
--- @param v1 Vector
--- @param v2 Vector
--- @return boolean
--- @function Vector.__eq
function Vector.__eq(v1, v2)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Matrix
-------------------------------------------------------------------------------
-- @section
-- This is a custom userdata representing an orientation and position in space. It has four vector components (right, up, front, and posit) sharing space with twelve number components (right_x, right_y, right_z, up_x, up_y, up_z, front_x, front_y, front_z, posit_x, posit_y, posit_z).

--- A Matrix
--- @class Matrix
--- @field right_x number
--- @field right_y number
--- @field right_z number
--- @field up_x number
--- @field up_y number
--- @field up_z number
--- @field front_x number
--- @field front_y number
--- @field front_z number
--- @field posit_x number
--- @field posit_y number
--- @field posit_z number

--- Returns a matrix whose components have the given number values. If no value is given for a component, the default value is zero. Be careful with this since it's easy to build a non-orthonormal matrix that will break all kinds of built-in assumptions.
--- @param right_x? number
--- @param right_y? number
--- @param right_z? number
--- @param up_x? number
--- @param up_y? number
--- @param up_z? number
--- @param front_x? number
--- @param front_y? number
--- @param front_z? number
--- @param posit_x? number
--- @param posit_y? number
--- @param posit_z? number
--- @return Matrix
function SetMatrix(right_x, right_y, right_z, up_x, up_y, up_z, front_x, front_y, front_z, posit_x, posit_y, posit_z)
    error("This function is provided by the engine.")
end

local Matrix = {}

--- Global value representing the identity matrix.
--- Equivalent to SetMatrix(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0).
--- @return Matrix
--- @function matrix IdentityMatrix
function IdentityMatrix()
    error("This function is provided by the engine.")
end

--- Build a matrix representing a rotation by an angle around an axis. The angle is in radians. If no value is given for the angle or an axis component, the default value is zero. The axis must be unit-length (i.e. axis_x<sup>2</sup> + axis_y<sup>2</sup> + axis_z<sup>2</sup> = 1.0 or the resulting matrix will be wrong.
--- @param angle? number
--- @param axis_x? number
--- @param axis_y? number
--- @param axis_z? number
--- @return Matrix
function BuildAxisRotationMatrix(angle, axis_x, axis_y, axis_z)
    error("This function is provided by the engine.")
end

--- Build a matrix representing a rotation by an angle around an axis. The angle is in radians. If no value is given for the angle, the default value is zero. The axis must be unit-length (i.e. axis.x<sup>2</sup> + axis.y<sup>2</sup> + axis.z<sup>2</sup> = 1.0 or the resulting matrix will be wrong.
--- @param angle? number
--- @param axis Vector
--- @return Matrix
function BuildAxisRotationMatrix(angle, axis)
    error("This function is provided by the engine.")
end

--- Build a matrix with the given pitch, yaw, and roll angles and position. The angles are in radians. If no value is given for a component, the default value is zero.
--- @param pitch? number
--- @param yaw? number
--- @param roll? number
--- @param posit_x? number
--- @param posit_y? number
--- @param posit_z? number
--- @return Matrix
function BuildPositionRotationMatrix(pitch, yaw, roll, posit_x, posit_y, posit_z)
    error("This function is provided by the engine.")
end

--- Build a matrix with the given pitch, yaw, and roll angles and position. The angles are in radians. If no value is given for a component, the default value is zero.
--- @param pitch? number
--- @param yaw? number
--- @param roll? number
--- @param position Vector
--- @return Matrix
function BuildPositionRotationMatrix(pitch, yaw, roll, position)
    error("This function is provided by the engine.")
end

--- Build a matrix with zero position, its up axis along the specified up vector, oriented so that its front axis points as close as possible to the heading vector. If up is not specified, the default value is the Y axis. If heading is not specified, the default value is the Z axis.
--- @param up? Vector
--- @param heading? Vector
--- @return Matrix
function BuildOrthogonalMatrix(up, heading)
    error("This function is provided by the engine.")
end

--- Build a matrix with the given position vector, its front axis pointing along the direction vector, and zero roll. If position is not specified, the default value is a zero vector. If direction is not specified, the default value is the Z axis.
--- @param position? Vector
--- @param direction? Vector
--- @return Matrix
function BuildDirectionalMatrix(position, direction)
    error("This function is provided by the engine.")
end

--- Multiply two matrices.
-- @tparam Matrix matrix1
-- @tparam Matrix matrix2
-- @treturn Matrix
-- @function matrix.__mul

--- Transform a vector by a matrix.
-- @tparam Matrix matrix
-- @tparam Vector vector
-- @treturn Matrix
-- @function matrix.__mul

--- Multiply a matrix by a vector or matrix.
--- @overload fun(a: Matrix, b: Matrix): Matrix
--- @overload fun(a: Matrix, b: Vector): Matrix
--- @param a Matrix The Matrix to multiply.
--- @param b Matrix|Vector The Matrix or Vector to multiply.
function Matrix:__mul(a, b)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Portal Functions [2.1+]
-------------------------------------------------------------------------------
-- @section
-- These functions control the Portal building introduced in The Red Odyssey expansion.

--- Sets the specified Portal direction to "out", indicated by a blue visual effect while active.
--- [2.1+]
--- @param portal Handle
function PortalOut(portal) end

--- Sets the specified Portal direction to "in", indicated by an orange visual effect while active.
--- [2.1+]
--- @param portal Handle
function PortalIn(portal) end

--- Deactivates the specified Portal, stopping the visual effect.
--- [2.1+]
--- @param portal Handle
function DeactivatePortal(portal) end

--- Activates the specified Portal, starting the visual effect.
--- [2.1+]
--- @param portal Handle
function ActivatePortal(portal) end

--- Returns true if the specified Portal direction is "in". Returns false otherwise.
--- [2.1+]
--- @param portal Handle
--- @return boolean
function IsIn(portal)
    error("This function is provided by the engine.")
end

--- Returns true if the specified Portal is active. Returns false otherwise.
--- Important: note the capitalization!
--- [2.1+]
--- @param portal Handle
--- @return boolean
--- @diagnostic disable-next-line: lowercase-global
function isPortalActive(portal)
    error("This function is provided by the engine.")
end

--- Creates a game object with the given odf name and team number at the location of a portal.
--- The object is created at the location of the visual effect and given a 50 m/s initial velocity.
--- [2.1+]
--- @param odfname string
--- @param teamnum TeamNum
--- @param portal Handle
--- @return Handle
function BuildObjectAtPortal(odfname, teamnum, portal)
    error("This function is provided by the engine.")
end

-------------------------------------------------------------------------------
-- Cloak [2.1+]
-------------------------------------------------------------------------------
-- @section
-- These functions control the cloaking state of craft capable of cloaking.

--- Makes the specified unit cloak if it can.
--- Note: unlike SetCommand(h, AiCommand.CLOAK), this does not change the unit's current command.
--- [2.1+]
--- @param h Handle
function Cloak(h) end

--- Makes the specified unit de-cloak if it can.
--- Note: unlike SetCommand(h, AiCommand.DECLOAK), this does not change the unit's current command.
--- [2.1+]
--- @param h Handle
function Decloak(h) end

--- Instantly sets the unit as cloaked (with no fade out).
--- [2.1+]
--- @param h Handle
function SetCloaked(h) end

--- Instant sets the unit as uncloaked (with no fade in).
--- [2.1+]
--- @param h Handle
function SetDecloaked(h) end

--- Returns true if the unit is cloaked. Returns false otherwise
--- [2.1+]
--- @param h Handle
--- @return boolean
function IsCloaked(h)
    error("This function is provided by the engine.")
end

--- Enable or disable cloaking for a specified cloaking-capable unit.
--- Note: this does not grant a non-cloaking-capable unit the ability to cloak.
--- [2.1+]
--- @param h Handle
--- @param enable boolean
function EnableCloaking(h, enable) end

--- Enable or disable cloaking for all cloaking-capable units.
--- Note: this does not grant a non-cloaking-capable unit the ability to cloak.
--- [2.1+]
--- @param enable boolean
function EnableAllCloaking(enable) end

-------------------------------------------------------------------------------
-- Hide [2.1+]
-------------------------------------------------------------------------------
-- @section
-- These functions hide and show game objects. When hidden, the object is invisible (similar to Phantom VIR and cloak) and undetectable on radar (similar to RED Field and cloak). The effect is similar to but separate from cloaking. For the most part, AI units ignore the hidden state.

--- Hides a game object.
--- [2.1+]
--- @param h Handle
function Hide(h) end

--- Un-hides a game object.
--- [2.1+]
--- @param h Handle
function UnHide(h) end

-------------------------------------------------------------------------------
-- Explosion [2.1+]
-------------------------------------------------------------------------------
-- @section
-- These functions create explosions at a specified location. They do not return a handle because explosions are not game objects and thus not visible to the scripting system.

--- Creates an explosion with the given odf name at the target position vector, transform matrix, object, or the start of the named path.
--- [2.1+]
---
--- Multiplayer remarks: Explosions are entirely local, this includes the visuals and the damage. This can be used to create clientside graphics.
--- @param odfname string
--- @param target Vector|Matrix|Handle|string Position vector, ransform matrix, Object, or path name.
function MakeExplosion(odfname, target) end

--- @alias TeamSlotInteger -1|0|1|2|3|4|5|14|15|24|25|34|35|44|45|54|55|59|60|64|65|69|70|74|75|79|80|89|90
