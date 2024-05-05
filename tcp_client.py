#!/usr/bin/env python3
#
# Author : easytojoin@163.com (Jok)
# Date   : Sun May 05 21:09:54 CST 2024
#

import socket

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(("0.0.0.0", 8080))
        s.sendall(b"Hello World")
        data = s.recv(1024)
        print(f"client received: {data.decode()}")

if __name__ == "__main__":
    main()
    exit(0)
