#! /usr/bin/bash
for nNodes in {2..30}; 
do 
	echo "$nNodes nodes - " 
	grep -F "Lost" < analyzedData/$nNodes-nodes.txt; 
done;
