"""
Clears the Addon reloaded directory
"""

from build_addon import get_addon_path

import os
import shutil

ROOT: str = os.getcwd()
ADDON_FOLDER = os.path.join(get_addon_path(), "reloaded")


def clean():
    shutil.rmtree(ADDON_FOLDER)
    print("Cleaned addon build folder")
    os.system("pause")


if __name__ == "__main__":
    clean()
