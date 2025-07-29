"""
Clears the workshop reloaded directory
"""

from build_workshop import get_workshop_path

import os
import shutil

ROOT: str = os.getcwd()
WORKSHOP_FOLDER = os.path.join(get_workshop_path(), "reloaded")


def clean():
    shutil.rmtree(WORKSHOP_FOLDER)
    print("Cleaned workshop build folder")
    os.system("pause")


if __name__ == "__main__":
    clean()
