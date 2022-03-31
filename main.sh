#! /usr/bin/bash

# Create folder to store data about flows 
file="main"
dir="NSFinalProject"
mkdir -p $dir/flowData

# Set the parameters 
nNodes=20
packetSize=512
verbose="false"
pcap="true"
collectData="false" # Set collect data to true to run the experiment with 2 to 30 nodes
param="--nNodes=$nNodes --verbose=$verbose --pcap=$pcap --collectData=$collectData --packetSize=$packetSize"
echo "Running $file with $nNodes nodes...";

# Copy the  file to scratch and run
cp $dir/$file.cc scratch/
./waf --run "scratch/$file $param"

# Store the data in the flowData folder 
mv final*.xml $dir/flowData

