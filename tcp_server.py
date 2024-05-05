#!/usr/bin/env python3
#
# Author : easytojoin@163.com (Jok)
# Date   : Sun May 05 21:00:34 CST 2024
#

import socket
import threading

def client_handle(c, addr):
    print(addr, "connected.")
    while True:
        data = c.recv(1024)
        if not data:
            break
        c.sendall(data)


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind(("0.0.0.0", 8080))
        s.listen()
        while True:
            c,addr = s.accept()
            t = threading.Thread(target=client_handle, args=(c, addr))
            t.start()

if __name__ == "__main__":
    main()
    exit(0)
