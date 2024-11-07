#!/bin/bash

# Get a list of modified files
files=$(git diff --name-only)

# Check if there are modified files
if [[ -z "$files" ]]; then
    echo "No modified files to compare."
    exit 0
fi

# Create a temporary directory for the committed version files
tmpdir=$(mktemp -d)

# Ensure temporary directory is deleted on exit
trap 'rm -rf "$tmpdir"' EXIT

# Copy each modified file's committed version to the temp directory
for file in $files; do
    # Only process files that exist in the working directory
    if [[ -f "$file" ]]; then
        # Create necessary subdirectories within temp directory
        mkdir -p "$tmpdir/$(dirname "$file")"
        
        # Retrieve the committed version and save it to the temporary directory
        git show HEAD:"$file" > "$tmpdir/$file"
    else
        echo "Skipping deleted file: $file"
    fi
done

# Open Beyond Compare in folder comparison mode to compare tmpdir with working directory
"C:\\Program Files\\Beyond Compare 4\\BComp.exe" "$tmpdir" "$(git rev-parse --show-toplevel)"
