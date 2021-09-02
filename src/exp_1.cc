/* -- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/nstime.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("ScratchSimulator");

int main (int argc, char *argv[])
{
  NS_LOG_UNCOND ("Experiment-1");

  NS_LOG_INFO ("Create nodes.");
  NodeContainer c;
  c.Create(6);

  NodeContainer n0n4 = NodeContainer (c.Get (0), c.Get (4));
  NodeContainer n1n4 = NodeContainer (c.Get (1), c.Get (4));
  NodeContainer n2n5 = NodeContainer (c.Get (2), c.Get (5));
  NodeContainer n3n5 = NodeContainer (c.Get (3), c.Get (5));
  NodeContainer n4n5 = NodeContainer (c.Get (4), c.Get (5));

  InternetStackHelper internet;
  internet.Install (c);

  NS_LOG_INFO ("Create channels.");
  PointToPointHelper p2p;

  p2p.SetDeviceAttribute ("DataRate", StringValue ("1Gbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("10us"));

  NetDeviceContainer d0d4 = p2p.Install (n0n4);
  NetDeviceContainer d1d4 = p2p.Install (n1n4);
  NetDeviceContainer d4d5 = p2p.Install (n4n5);
  NetDeviceContainer d2d5 = p2p.Install (n2n5);
  NetDeviceContainer d3d5 = p2p.Install (n3n5);

  NS_LOG_INFO ("Assign IP Addresses.");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i0i4 = ipv4.Assign (d0d4);

  ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i1i4 = ipv4.Assign (d1d4);

  ipv4.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer i4i5 = ipv4.Assign (d4d5);

  ipv4.SetBase ("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer i2i5 = ipv4.Assign (d2d5);

  ipv4.SetBase ("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer i3i5 = ipv4.Assign (d3d5);

  NS_LOG_INFO ("Enable static global routing.");
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  // TcpBic connection from N0 to N2

  uint16_t sinkPort = 8080;
  uint32_t bytes = 5e7;
  Address sinkLocalAddress (InetSocketAddress (i2i5.GetAddress (0), sinkPort));
  BulkSendHelper source ("ns3::TcpSocketFactory", sinkLocalAddress);
  source.SetAttribute("MaxBytes",UintegerValue(bytes));

  ApplicationContainer sourceApp = source.Install(n0n4.Get(0));
  sourceApp.Start (Seconds (0.0));
  sourceApp.Stop (Seconds (1.0));

  OnOffHelper clientHelper ("ns3::TcpSocketFactory", Address ());
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::TcpBic"));

  TypeId tid = TypeId::LookupByName ("ns3::TcpBic");
  std::stringstream nodeId;
  nodeId << c.Get (0)->GetId ();
  std::string specificNode = "/NodeList/" + nodeId.str () + "/$ns3::TcpL4Protocol/SocketType";
  Config::Set (specificNode, TypeIdValue (tid));
  Ptr<Socket> localSocket = Socket::CreateSocket (c.Get (0), TcpSocketFactory::GetTypeId ());

  PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", sinkLocalAddress);
  ApplicationContainer sinkApp = sinkHelper.Install (c.Get (2));
  sinkApp.Start (Seconds (0.0));
  sinkApp.Stop (Seconds (1.0));

  AsciiTraceHelper ascii;
  p2p.EnableAsciiAll(ascii.CreateFileStream("exp_1.tr"));

  AnimationInterface anim("exp_1.xml");
  anim.SetMaxPktsPerTraceFile(99999999999999);
  anim.SetConstantPosition(c.Get(0),20.0,20.0);
  anim.SetConstantPosition(c.Get(1),20.0,80.0);
  anim.SetConstantPosition(c.Get(2),80.0,20.0);
  anim.SetConstantPosition(c.Get(3),80.0,80.0);
  anim.SetConstantPosition(c.Get(4),40.0,50.0);
  anim.SetConstantPosition(c.Get(5),60.0,50.0);

  Simulator::Run ();
  Simulator::Destroy ();
}
