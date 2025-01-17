#!/bin/bash

# Change these variables to match your content and directory
content="This is my multi-line content.\nIt goes on multiple lines."
directory="/path/to/directory"

# Loop through all files in the directory
for file in "$directory"/*; do
	# Use sed to insert the content at the beginning of the file
	sed -i "1s/^/$content\n/" "$file"
done
