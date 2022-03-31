#! /usr/bin/bash

# Make a folder to store analysed data
mkdir -p analyzedData 

# Loop through all files from 2 to 30 nodes and save result in text file
for nNodes in {2..30}
do
echo $nNodes/30
python3 analyze.py flowData/final-$nNodes-nodes.xml > analyzedData/$nNodes-nodes.txt
done
echo Done
