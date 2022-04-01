#! /usr/bin/bash

file="main"
dir="NSFinalProject"

# Set the parameters 
nNodes=7
packetSize=512
serverNode=$(echo $(($nNodes / 2)))
maxPackets=10
interval=1
verbose="false"
pcap="false"
collectData="true" # Set collect data to true to run the experiment with 2 to 30 nodes
param="--nNodes=$nNodes --verbose=$verbose --pcap=$pcap --collectData=$collectData --packetSize=$packetSize --maxPackets=$maxPackets --interval=$interval"

storeDir="/svmid-ps$packetSize"

if [ "$collectData" == "false" ]
then
echo "Running $file with $nNodes nodes...";
storeDir="/"
fi

if [ -d $dir/flowData$storeDir -a $collectData == "true" ]
then
	echo "Experiment has already been done. Results are stored at $storeDir."
	exit 0
fi

# Copy the  file to scratch and run
cp $dir/$file.cc scratch/
./waf --run "scratch/$file $param"

# Create folder to store data about flows 
mkdir -p $dir/flowData$storeDir
mkdir -p $dir/animData$storeDir

# Store the data in the flowData$storeDir folder 
mv final*.xml $dir/flowData$storeDir
mv anim*.xml $dir/animData$storeDir
