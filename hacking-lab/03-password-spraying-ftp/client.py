import ftplib
import sys

host = sys.argv[1]
username = sys.argv[2]
password = sys.argv[3]

print(host, username, password)

try:
    with ftplib.FTP(host, user=username, passwd=password) as ftp:
        ftp.retrlines('LIST')
        ftp.quit()
        exit(0)
except:
    exit(1)
