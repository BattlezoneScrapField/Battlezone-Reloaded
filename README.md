# Battlezone-Reloaded

All the bugfixes none of the BS! This mod will include the coop campaign, deathmatch improvements, and the mythic BZP fork!

This readme is temporary and will be redone at some point.

# How to build

Included are a bunch of scripts to help in building the mod for both local addon testing as well as workshop deployment.

## What you'll need:
- A good text editor
- Python 3
- Visual Studio 2022 (for C++ with windows sdk)
- Steamcmd

---

Once you have those installed clone the repo:

```
git clone --recursive https://github.com/BattlezoneScrapField/Battlezone-Reloaded.git
```

## Build steps

First navigate to External/ExtraUtilities and open the solution file in visual studio. On the top bar set the build mode to `Release` and `x86`, and then go to `Build` and click `Build Solution (F7)`. Once this is done you can close visual studio and head back to the mod's root folder.

Next run `install_requirements.bat` to set up the python environment. If you already have `python-dotenv` installed globally you can skip this step, or install it manually with `pip install python-dotenv`.

Now run `squish.py` to squish all of the organized files into the mess that BZR expects, to add folders to the search path open the script and use `add_item_recurse()` as descibed in the file.

Once you have built the /Workshop folder it is ready to use in-game. `build_addon.py` will build the mod in your addon folder, and `clean_addon.py` will remove that folder. `clean.py` will remove the main /Workshop folder from the root directory, use it when you are preparing a new release.

To upload to the steam workshop, first create a `.env` file in the root of the project, this will contain the path to your steamcmd executable as well as your steam username. The file should look like this (with your own name and path):

```
steamcmd_path = "C:\Users\vtrider\Desktop\steamcmd\steamcmd.exe"
steam_username = "vtrider"
```

Finally, run `upload_workshop.bat` to generate the upload manifest and upload it to the workshop. It may prompt you for your steam password if you have never logged in to steamcmd before, that is normal. If you have steam guard (2FA) enabled, you will also have to verify the code on the mobile app. After logging in you should not have to re-enter your credentials in subsequent uploads. Optionally if you have `python-dotenv` installed globally you can run it directly from the .py script. 
