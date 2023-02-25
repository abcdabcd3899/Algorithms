#!/bin/bash

# Create an array to store the words
declare -A words

# Read the file line by line
while read line; do
  # Split the line into words and loop through each word
  for word in $line; do
    # Increment the count for the current word
    words[$word]=$(( ${words[$word]} + 1 ))
  done
done < words.txt

# Sort the array by frequency and print the results
for word in "${!words[@]}"; do
  echo "$word ${words[$word]}"
done | sort -nrk2