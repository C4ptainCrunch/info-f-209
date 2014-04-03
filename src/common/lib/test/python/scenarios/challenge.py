#!/usr/bin/python
# -*- coding: utf-8 -*-

import json
import os
from time import sleep

from lib import sock, send, recv, coroutine, force_login

HOST = 'localhost'
PORT = 9001


def user1():
    with sock(HOST, PORT) as s:
        force_login(s, 'a')
        sleep(0.2) # wait for the other user to conect
        send(s, "challenge", {'other_username': 'fail'})
        recv(s) # recive fail response
        send(s, "challenge", {'other_username': 'b'})
        recv(s) # challenge refused
        send(s, "challenge", {'other_username': 'b'})
        recv(s) # match_begin


def user2():
    with sock(HOST, PORT) as s:
        force_login(s, 'b')
        r = recv(s) # recieve challenge

        send(s, 'accept_challenge', {'id': 10000}) # accept fake challenge
        recv(s) # recive fail response

        send(s, 'refuse_challenge', {'id': r[1]['challenge_id']}) # refuse real challenge

        r = recv(s) # recieve challenge
        send(s, 'accept_challenge', {'id': r[1]['challenge_id']}) # refuse real challenge

        recv(s) # match_begin


if __name__ == '__main__':
    a = coroutine(user1)
    b = coroutine(user2)

    a.join()
    b.join()
