#! /usr/bin/bash
for nNodes in {2..30}; 
do 
	echo -n "$nNodes nodes - " 
	grep -F "Loss Flow Ratio" < analyzedData/$nNodes-nodes.txt; 
done;
