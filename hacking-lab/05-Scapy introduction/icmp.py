#!/usr/bin/env python3
from scapy.all import*
# Creating two new objects, IP and ICMP.
# IP - is an object of an IP header, setting it's src and dst IP's.
# ICMP - is an object of an ICMP header, setting it's type to 8 (request).
a=IP(src="1.2.3.4", dst="10.0.2.4") / ICMP(type=8, code=0)
send(a)