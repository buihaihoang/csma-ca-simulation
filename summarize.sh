#! /usr/bin/bash

if [ -z $1 ]
then
	echo "You have to provide a configuration (e.g.: sv0-ps512)"
	exit 1
fi

if [ ! -d "analyzedData/$1" ]
then
	echo "$1 is invalid"
	exit 1
fi

for nNodes in {2..30}; 
do 
	echo "$nNodes nodes - " 
	grep -F "Lost" < analyzedData/$1/$nNodes-nodes.txt; 
done;
