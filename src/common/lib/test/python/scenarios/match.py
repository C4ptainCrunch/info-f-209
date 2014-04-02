#!/usr/bin/python
# -*- coding: utf-8 -*-

import json
import os
from time import sleep

from lib import sock, send, recv, coroutine, force_login

HOST = 'localhost'
PORT = 5001


def user1():
    with sock(HOST, PORT) as s:
        force_login(s, 'a')
        sleep(0.5)
        send(s, "challenge", {'other_username': 'b'})
        sleep(0.5) # wait to accept
        recv(s) # recieve begin_match


def user2():
    with sock(HOST, PORT) as s:
        force_login(s, 'b')
        r = recv(s) # recieve challenge
        send(s, 'accept_challenge', {'id': r[1]['challenge_id']})
        recv(s) # recieve begin_match


if __name__ == '__main__':
    a = coroutine(user1)
    b = coroutine(user2)

    a.join()
    b.join()
