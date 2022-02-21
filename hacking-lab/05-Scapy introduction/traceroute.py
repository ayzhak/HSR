#!/usr/bin/env python3
from scapy.all import*
# Variable i is a counter of the number of routers.
i=1
# Sending a request with ttl i to the destination - 8.8.8.8
ans=sr1(IP(dst='8.8.8.8',ttl=i)/ICMP(),verbose=0, timeout=1)
print(i,""+ans.src)
# Loop while the packet recv isn't from our destination
while ans.src!= '8.8.8.8':
	# Incrementing the ttl time by 1.
	i+=1
	# Re-sending the ping request with incremented ttl.
	ans_temp=sr1(IP(dst='8.8.8.8',ttl=i)/ICMP(),verbose=0, timeout=1)
	# Checking for an unresponding router.
	if ans_temp is None: 
		print(i,"******")
		continue
	else:
		ans=ans_temp
		# Printing router src address.
		print(i,""+ans.src)