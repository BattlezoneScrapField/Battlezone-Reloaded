"""
Clears the Workshop output directory
"""

import os
import shutil

ROOT: str = os.getcwd()
BUILD_FOLDER = os.path.join(ROOT, "Build")


def clean():
    shutil.rmtree(BUILD_FOLDER)
    print("Cleaned build folder")
    os.system("pause")


if __name__ == "__main__":
    clean()
    