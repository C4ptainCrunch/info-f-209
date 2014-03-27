#!/usr/bin/python
# -*- coding: utf-8 -*-

import json
import os
from time import sleep

from lib import sock, send, recv, coroutine

HOST = 'localhost'
PORT = 5001


def user1():
    with sock(HOST, PORT) as s:
        send(s, "login", {'username': 'a', 'password': 'a'})
        r = recv(s)
        if not r[1]['success']:
            send(s, "register", {'username': 'a', 'password': 'a', 'name': 'aa'})
            recv(s)
        sleep(0.5)
        send(s, "challenge", {'other_username': 'fail'})
        recv(s)
        send(s, "challenge", {'other_username': 'b'})
        sleep(0.5)
        recv(s)


def user2():
    with sock(HOST, PORT) as s:
        send(s, "login", {'username': 'b', 'password': 'b'})
        r = recv(s)
        if not r[1]['success']:
            send(s, "register", {'username': 'b', 'password': 'b', 'name': 'bb'})
            recv(s)
        #send(s, 'userlist', None)
        r = recv(s)

        send(s, 'accept_challenge', {'id': 10000})
        recv(s)

        send(s, 'accept_challenge', {'id': r[1]['challenge_id']})
        recv(s)


if __name__ == '__main__':
    a = coroutine(user1)
    b = coroutine(user2)

    a.join()
    b.join()
