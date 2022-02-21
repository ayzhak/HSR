#!/usr/bin/env python3
from scapy.all import*
def print_pkt(pkt):
# Printing the packet 
	pkt.show()
# Calling a sniffing function from scapy library.
# iface is the interface the sniff should listen to.
# filter is the filter expression which is compiled to bpf.
# prn is a pointer to a function the packet that is sniffed is sent to.
pkt = sniff(iface=['eth0'], filter='icmp', prn=print_pkt)