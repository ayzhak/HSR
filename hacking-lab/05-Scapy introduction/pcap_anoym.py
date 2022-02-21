#! /usr/bin/env python3
from scapy.utils import rdpcap, wrpcap
from scapy.layers.inet import IP, TCP, UDP  # import needed!
import sys

INFILE = "ipp.pcap"
OUTFILE = "ipp_an.pcap"

packets = rdpcap(INFILE)

new_packets = []
for packet in packets:
    if packet.haslayer("IP"):
        packet[IP].src = "1.1.1.1"
        packet[IP].dst = "2.2.2.2"

    new_packets.append(packet)

wrpcap(OUTFILE, new_packets)
