#!/bin/bash

# Define array of directory names
directories=("includes" "libft" "srcs")

# Define array to store filenames with the specified extensions
file_list=()

# Loop through directories and find files with specified extensions
for directory in "${directories[@]}"; do
  while IFS= read -r -d '' file; do
    if [[ "$file" == *".c" || "$file" == *".h" ]]; then
      file_list+=("$file")
    fi
  done < <(find "$directory" -type f -print0)
done

# Iterate through file list and execute norminette command
error_count=0
for file in "${file_list[@]}"; do
  norminette_output=$(norminette "$file" 2>&1)
  norminette_status=$?
  if [[ "$norminette_status" -ne 0 ]]; then
    if [[ $(echo "$norminette_output" | wc -l) -ne 2 || $(echo "$norminette_output" | tail -n 1 | grep -q "Missing or invalid 42 header") ]]; then
      echo -e "\r\033[K$norminette_output"
      error_count=$((error_count+1))
    else
      echo -ne "\r\033[K$file: OK!"
    fi
  else
    echo -ne "\r\033[K$file: OK!"
  fi
done

echo -e "\r\033[K"

# Set exit status based on error count
if [[ "$error_count" -gt 0 ]]; then
  exit 1
else
  exit 0
fi
