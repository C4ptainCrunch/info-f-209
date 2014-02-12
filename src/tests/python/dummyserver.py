#!/usr/bin/python
# -*- coding: utf-8 -*-

PORT = 50007

# Echo server program
import socket
import sys
import json

HOST = None               # Symbolic name meaning all available interfaces


def bindto(host, port):
    s = None

    for res in socket.getaddrinfo(host, port, socket.AF_UNSPEC, socket.SOCK_STREAM, 0, socket.AI_PASSIVE):
        af, socktype, proto, canonname, sa = res
        try:
            s = socket.socket(af, socktype, proto)
        except socket.error as msg:
            s = None
            continue
        try:
            s.bind(sa)
            s.listen(1)
        except socket.error as msg:
            s.close()
            s = None
            continue
        break

    if s is None:
        print 'could not open socket'
        return False, False

    conn, addr = s.accept()
    return conn, addr


def listen(so):
    left = ''
    while 1:
        data, left = recieve(so, left)
        if not data:
            break
        send(so, data)


def recieve(so, before=''):
    msg = before
    while '\r\n' * 2 not in msg:
        msg += so.recv(1024)
    index = msg.find('\r\n' * 2)
    m = json.loads(msg[:index])
    l = msg[index + 2:] if msg[index + 2:] != '\r\n' else ""
    return m, l


def send(so, j):
    so.send(json.dumps(j) + '\n\n')

if __name__ == '__main__':
    so, ip = bindto(HOST, PORT)
    if not so:
        so, ip = bindto(HOST, PORT + 1)
        print PORT + 1
    print 'Connected by', ip
    send(so, {'hostname': 'ulb.ac.be'})
    listen(so)
    so.close()
