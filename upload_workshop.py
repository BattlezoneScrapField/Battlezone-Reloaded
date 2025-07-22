"""
Generates a manifest file and uploads the mod to the 
steam workshop using steamcmd

Use the .bat file after running install_requirements.bat to run it in the venv
to get the required dependency if you don't have it installed already
"""

from dotenv import load_dotenv

from enum import Enum
import os
import subprocess


class Visiblity(Enum):
    PUBLIC = 0
    FRIENDS_ONLY = 1
    PRIVATE = 2


ROOT: str = os.getcwd()
BUILD_FOLDER: str = os.path.join(ROOT, "Build")
MANIFEST_PATH: str = os.path.join(ROOT, "workshop.vdf")

APPID: int = 301650
WORKSHOP_ID: int = 3522264415
CONTENT_FOLDER: str = BUILD_FOLDER
preview_file: str = ''
visbility: Visiblity = Visiblity.PRIVATE
TITLE: str = "Battlezone: Reloaded (Beta)"
description: str = ''
changenote: str = ''


def get_workshop_txts() -> tuple[str, str]:
    with open("workshop_description.txt", 'r') as des:
        description = des.read()

    with open("workshop_changenote.txt", 'r') as cn:
        changenote = cn.read()

    return (description, changenote)


def generate_manifest() -> None:
    if os.path.exists(MANIFEST_PATH):
        os.remove(MANIFEST_PATH)

    description, changenote = get_workshop_txts()

    with open("workshop.vdf", "w") as manifest:
        manifest.write('"workshopitem"\n')
        manifest.write('{\n')
        manifest.write(f'    "appid" "{APPID}"\n')
        manifest.write(f'    "publishedfileid" "{WORKSHOP_ID}"\n')
        manifest.write(f'    "contentfolder" "{CONTENT_FOLDER}"\n')
        manifest.write(f'    "previewfile" "{preview_file}"\n')
        manifest.write(f'    "visibility" "{visbility.value}"\n')
        manifest.write(f'    "title" "{TITLE}"\n')
        manifest.write(f'    "description" "{description}"\n')
        manifest.write(f'    "changenote" "{changenote}"\n')
        manifest.write('}\n')

    print("Generated manifest: workshop.vdf")


def upload() -> None:
    print("Uploading to workshop...")

    load_dotenv()

    steamcmd_path = os.getenv("steamcmd_path")
    steam_username = os.getenv("steam_username")

    try:
        if not steamcmd_path:
            raise RuntimeError("Steamcmd path not found, did you put it in your .env?")
        if not steam_username:
            raise RuntimeError("Steam username not found, did you put it in your .env?")
    except Exception as e:
        print(e)
        os.system("pause")
        return
    
    cmd = [steamcmd_path, "+login", steam_username, "+workshop_build_item", MANIFEST_PATH, "+quit"]

    try:
        subprocess.run(cmd)
    except Exception as e:
        print(f"An error occured in steamcmd: {e}")

    print("Done")
    os.system("pause")


if __name__ == "__main__":
    generate_manifest()
    upload()
