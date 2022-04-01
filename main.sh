#! /usr/bin/bash

file="main"
dir="NSFinalProject"

# Set the parameters 
nNodes=7
packetSize=512
verbose="false"
pcap="false"
collectData="true" # Set collect data to true to run the experiment with 2 to 30 nodes
param="--nNodes=$nNodes --verbose=$verbose --pcap=$pcap --collectData=$collectData --packetSize=$packetSize"

if [ "$collectData" == "false" ]
then
echo "Running $file with $nNodes nodes...";
fi

# Copy the  file to scratch and run
cp $dir/$file.cc scratch/
./waf --run "scratch/$file $param"

# Create folder to store data about flows 
mkdir -p $dir/flowData
mkdir -p $dir/animData

# Store the data in the flowData folder 
mv final*.xml $dir/flowData
mv anim*.xml $dir/animData
