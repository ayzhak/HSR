#!/usr/bin/env python3
from scapy.all import*

source = SniffSource(iface=conf.iface)
wire = WiresharkSink()
def transf(pkt):
    if not pkt or IP not in pkt:
        return pkt
    pkt[IP].src = "1.1.1.1"
    pkt[IP].dst = "2.2.2.2"
    return pkt

source > TransformDrain(transf) > wire
p = PipeEngine(source)
p.start()
p.wait_and_stop()