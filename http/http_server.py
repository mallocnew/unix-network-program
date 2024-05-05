#!/usr/bin/env python3
#
# Author : easytojoin@163.com (Jok)
# Date   : Sun May 05 21:00:34 CST 2024
#

import socket
import threading

def client_handle(c:socket, addr):
    print(addr, "connected.")
    with c:
        req = c.recv(1024)
        req = req.decode()
        print(req)
        headers = req.split("\r\n")
        print(f"headers: {headers}")
        method, path, version = headers[0].split()[0], headers[0].split()[1], headers[0].split()[2]
        print(f"method: {method}, path: {path}, version: {version}")
        if path == "/":
            res = version + " 200 OK\r\n\r\n" + "Hello world!"
        else:
            res = version + " 404 NOT FOUND\r\n\r\n" + "File not found"
        c.sendall(res.encode())
        print(f"send {res.encode()}")

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind(("127.0.0.1", 8080))
        s.listen()
        while True:
            c,addr = s.accept()
            t = threading.Thread(target=client_handle, args=(c, addr))
            t.start()

if __name__ == "__main__":
    main()
    exit(0)
