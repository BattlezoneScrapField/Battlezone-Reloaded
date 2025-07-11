"""
Clears the Workshop output directory
"""

import os
import shutil

ROOT: str = os.getcwd()
WORKSHOP_FOLDER = os.path.join(ROOT, "Workshop")


def clean():
    shutil.rmtree(WORKSHOP_FOLDER)
    print("Cleaned workshop build folder")
    os.system("pause")


if __name__ == "__main__":
    clean()
    