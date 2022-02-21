# 06-HL LiveCD Simple Metasploit Linux Reverse Shell
## Security Questions
- Explain how the reverse shell works:
    - Who opens the TCP connection and to which IP / Port?
        192.168.178.99:8080 -> 192.168.178.99:39850
        Victim opens the sessions on port 8080.
    - Who opens the shell? Who has control over it? Which computer runs the commands entered?
    The shell gets open by the victim, meterpreter provide a shell and other tools like makeing screenshots, enable webcam, etc.
    The sended stage runs the commands, the victim.
- Add a screenshot of the reverse shell, similar to the one in step 6 (make sure to show the active sessions and run at least one command on it)
![](.\01.png)