#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/flow-monitor.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/netanim-module.h"
#include <cstdio>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("FinalProject");

void experiment(uint32_t nNodes, uint32_t packetSize, bool verbose, bool pcap, uint32_t simTime, uint32_t maxPackets, uint32_t interval, uint32_t serverNode)
{
  std::cout << "Running simulation with " << nNodes << " nodes..." << std::endl;

  if (verbose)
  {

    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
  }
  // Enable or Disable RTS/CTS by setting the RTS/CTS threshold
  UintegerValue threshold = 1000; // original value:500
  Config::SetDefault("ns3::WifiRemoteStationManager::RtsCtsThreshold", threshold);

  // Make sure that there are at least 2 nodes
  nNodes = (nNodes < 2) ? 2 : nNodes;

  // Create the nodes that compose the network
  NodeContainer nodes;
  nodes.Create(nNodes);

  // Configure the PHY and channel helpers
  YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
  YansWifiPhyHelper phy;
  /* Create a channel object and associate it to PHY layer  object manager to make sure that
    all the PHY layer objects created by the YansWifiPhyHelper share the same underlying channel*/
  phy.SetChannel(channel.Create());

  // WifiMacHelper is used to set MAC parameters.
  WifiMacHelper mac;

  /* Instantiate WifiHelper (By default, configure the standard in use to be 802.11ax
    and configure a compatible rate control algorithm - IdealWifiManager)*/
  WifiHelper wifi;

  // Configure the MAC layer
  mac.SetType("ns3::AdhocWifiMac");

  NetDeviceContainer devices;
  devices = wifi.Install(phy, mac, nodes);

  // Instantiate a MobilityHelper object and set some attributes controlling the "position allocator" functionality
  MobilityHelper mobility;
  mobility.SetPositionAllocator("ns3::GridPositionAllocator", 
                                "MinX", DoubleValue(0.0), 
                                "MinY", DoubleValue(0.0), 
                                "DeltaX", DoubleValue(5.0), 
                                "DeltaY", DoubleValue(5.0), 
                                "GridWidth", UintegerValue(5), 
                                "LayoutType", StringValue("RowFirst"));

  // Set the mobility model to be ns3::ConstantPositionMoblityModel to fixed the position of the devices
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.Install(nodes);

  // Use InternetStackHelper to install protocol stacks
  InternetStackHelper stack;
  stack.Install(nodes);

  // Use Ipv4AddressHelper to assign IP addresses to our device interfaces
  Ipv4AddressHelper address;
  // Use the network 10.1.1.0 to create the addresses needed for our devices
  address.SetBase("10.1.1.0", "255.255.255.0");
  // Save the created interfaces in a container to make it easy to pull out addressing information later for use in setting up the applications
  Ipv4InterfaceContainer nodeInterfaces;
  nodeInterfaces = address.Assign(devices);

  // Create a UdpEchoServerHelper and provide the required Attribute - the server port number
  UdpEchoServerHelper echoServer(9);

  // Instantiate the server on the node choosen
  ApplicationContainer serverApps = echoServer.Install(nodes.Get(serverNode));
  serverApps.Start(Seconds(2.0));
  serverApps.Stop(Seconds(simTime));

  // Create a UdpEchoClientHelper and provide the required Attributes - the remote address and port
  UdpEchoClientHelper echoClient(nodeInterfaces.GetAddress(serverNode), 9);
  echoClient.SetAttribute("MaxPackets", UintegerValue(maxPackets)); // Default is 10
  echoClient.SetAttribute("Interval", TimeValue(Seconds(interval)));// Default is 1s
  echoClient.SetAttribute("PacketSize", UintegerValue(packetSize)); // Default is 512B
  // Install the client on every other node except the serverNode
  for (uint32_t i = 0; i < nNodes; i++)
  {
    if (i == serverNode) continue; // Exclude the server node
    ApplicationContainer clientApp = echoClient.Install(nodes.Get(i));
    clientApp.Start(Seconds(2.0));
    clientApp.Stop(Seconds(simTime));
  }

  // Enable pcap
  if (pcap)
  {
    // phy.EnablePcapAll("final", true);
    phy.EnablePcap("final", devices.Get(2), true);
  }

  // Install flowMonitor to collect data
  Ptr<FlowMonitor> flowMonitor;
  FlowMonitorHelper flowHelper;
  flowMonitor = flowHelper.InstallAll();

  // Use netanim to visualize the experiment
  char animfile[100];
  sprintf(animfile, "anim-%d-nodes.xml", nNodes); // Save the result in an xml file
  AnimationInterface anim(animfile);
  Simulator::Stop(Seconds(simTime));
  Simulator::Run();

  char filename[100];
  sprintf(filename, "final-%d-nodes.xml", nNodes);
  flowMonitor->SerializeToXmlFile(filename, true, true); // Save the result of flow monitor in an xml file
  
  Simulator::Destroy();
}

int main(int argc, char *argv[])
{

  uint32_t nNodes = 2;       // Initialize number of nodes in the network
  uint32_t packetSize = 512; // Initialize the packet size
  uint32_t simTime = 15;     // Simulation Time in seconds
  uint32_t maxPackets = 10;  // Max packets to send
  uint32_t interval = 1;     // Interval between packets
  uint32_t serverNode = 0;   // Node to install server app
  bool verbose = false;      // Disable logging by default
  bool pcap = false;         // Disable pcap by default
  bool collectData = false;  // Do not collect data by default

  // Allow you to change the parameters via command line argument
  CommandLine cmd;
  cmd.AddValue("nNodes", "Number of nodes/devices", nNodes);
  cmd.AddValue("packetSize", "size of the packet (> 1000 to enable RTS/CTS)", packetSize);
  cmd.AddValue("maxPackets", "Max packets to send", maxPackets);
  cmd.AddValue("interval", "Interval between packets", interval);
  cmd.AddValue("verbose", "Enable logging", verbose);
  cmd.AddValue("pcap", "Enable pcap", pcap);
  cmd.AddValue("collectData", "Start collect data for 2 to 30 nodes", collectData);
  cmd.Parse(argc, argv);

  if (collectData)
  {
    for (uint32_t i = 2; i <= 30; i++)
    {
      experiment(i, packetSize, verbose, pcap, simTime, maxPackets, interval, serverNode);
    }
  }
  else
  {
    experiment(nNodes, packetSize, verbose, pcap, simTime, maxPackets, interval, serverNode);
  }
}
