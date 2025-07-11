"""
Squishes all the required files into a single folder
to upload to the steam workshop
"""

import os
import shutil

ROOT: str = os.getcwd()
WORKSHOP_FOLDER: str = os.path.join(ROOT, "Workshop")

excluded_file_types: set[str] = set([
    ".exp", # Unnnecesary binaries from exu compilation
    ".lib"
])

required_items: list[str] = [
    "exu.dll"
]

source_paths: list[str] = []

# Helper to add source directories
def add_item_recurse(*path_from_root: str) -> None:
    final_path: str = ROOT
    for dir in path_from_root:
        final_path = os.path.join(final_path, dir)

    source_paths.append(final_path)


add_item_recurse("Multiplayer")
add_item_recurse("Scripts")

add_item_recurse("External", "ExtraUtilities", "Release")
add_item_recurse("External", "VTScrapPool", "src")
add_item_recurse("External", "RequireFix")


def squish() -> None:
    os.makedirs("Workshop", exist_ok = True)
    for path in source_paths:
        for path, _, files in os.walk(path):
            for file in files:
                _, extension = os.path.splitext(file)
                if extension in excluded_file_types:
                    continue
                shutil.copyfile(os.path.join(path, file), os.path.join(WORKSHOP_FOLDER, file))


def verify_files() -> list[str]:
    missing_files: list[str] = []
    for _, _, files in os.walk(WORKSHOP_FOLDER):
        for required_file in required_items:
            if required_file not in files:
                missing_files.append(required_file)
    return missing_files


if __name__ == "__main__":
    squish()

    missing_files: list[str] = verify_files()
    if len(missing_files) == 0:
        print("Built workshop release")
    else:
        print("Failed to build workshop release, missing file(s):")
        shutil.rmtree(WORKSHOP_FOLDER)
        for missing_file in missing_files:
            print(missing_file)
        print("\nDid you remember to compile the binaries?")
