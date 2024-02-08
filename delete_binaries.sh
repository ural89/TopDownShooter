#!/bin/bash

# Function to delete folders
delete_folders() {
    local project_path="$1"
    local folders=("Binaries" "Intermediate" "Saved")

    for folder in "${folders[@]}"; do
        folder_path="${project_path}/${folder}"
        if [ -d "$folder_path" ]; then
            echo "Deleting $folder_path"
            rm -rf "$folder_path"
        else
            echo "Folder $folder_path not found."
        fi
    done
}

# Main script starts here
if [ $# -ne 1 ]; then
    echo "Usage: $0 <path_to_project>"
    exit 1
fi

project_path="$1"

if [ ! -d "$project_path" ]; then
    echo "Project path '$project_path' not found."
    exit 1
fi

delete_folders "$project_path"

