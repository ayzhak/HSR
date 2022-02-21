#!/usr/bin/python

import sys
import paramiko

try:
    client = paramiko.SSHClient()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy)
    print(sys.argv[1], ' - ', sys.argv[2], ' - ', sys.argv[3])
    client.connect(sys.argv[1], username=sys.argv[2], password=sys.argv[3], timeout=500)
    exit(0)
except:
    exit(1)
