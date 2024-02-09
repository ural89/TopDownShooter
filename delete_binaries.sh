#!/bin/bash

# Function to delete folders
delete_folders() {
    local current_dir="$(pwd)"
    local folders=("Binaries" "Intermediate" "Saved")

    for folder in "${folders[@]}"; do
        folder_path="${current_dir}/${folder}"
        if [ -d "$folder_path" ]; then
            echo "Deleting $folder_path"
            rm -rf "$folder_path"
        else
            echo "Folder $folder_path not found."
        fi
    done
}

# Main script starts here
delete_folders

