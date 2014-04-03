#!/usr/bin/python
# -*- coding: utf-8 -*-

# Some code from voorloop@gmail.com under the IDC(I Don't Care) license.
# Modified by Nikita Marchant

import socket
import select
import time
import sys

BUFFER_LEN = 4096 * 10
WAIT = 0.0001


class Forward:
    def __init__(self):
        self.forward = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def start(self, destination):
        try:
            self.forward.connect(destination)
            return self.forward
        except Exception, e:
            print e
            return False


class Proxy:

    def __init__(self, listen, forward):
        forward = socket.gethostbyname(forward[0]), forward[1]
        print 'Listening on {0[0]}:{0[1]}.\nForwarding to {1[0]}:{1[1]}.'.format(listen, forward)
        self.input_list = []
        self.channel = {}

        self.forward = forward

        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        self.server.bind(listen)
        self.server.listen(200)

    def main_loop(self):
        self.input_list.append(self.server)
        while 1:
            time.sleep(WAIT)
            ss = select.select
            inputready, outputready, exceptready = ss(self.input_list, [], [])
            for self.s in inputready:
                if self.s == self.server:
                    self.on_accept()
                    break

                self.data = self.s.recv(BUFFER_LEN)
                if len(self.data) == 0:
                    self.on_close()
                else:
                    self.on_recv()

    def on_accept(self):
        forward = Forward().start(self.forward)
        clientsock, clientaddr = self.server.accept()
        if forward:
            self.input_list.append(clientsock)
            self.input_list.append(forward)
            self.channel[clientsock] = forward
            self.channel[forward] = clientsock
            print "{0[0]}:{0[1]} has connected".format(clientaddr)
        else:
            print "Can't establish connection with remote server.",
            print "Closing connection with client side {0[0]}:{0[1]}".format(clientaddr)
            clientsock.close()

    def on_close(self):
        print "{0[0]}:{0[1]} has disconnected".format(self.s.getpeername())

        self.input_list.remove(self.s)
        self.input_list.remove(self.channel[self.s])
        out = self.channel[self.s]
        self.channel[out].close()
        self.channel[self.s].close()

        del self.channel[out]
        del self.channel[self.s]

    def on_recv(self):
        data = self.data.replace('\r\n', '\n')
        if self.s.getpeername() == self.forward:
            sign, color = '↓', '\x1b[31;1m'
        else:
            sign, color = '↑', '\x1b[32;1m'
        print '{}{}\x1b[0m {}'.format(color, sign, repr(data))
        self.channel[self.s].send(data)

if __name__ == '__main__':
    if not len(sys.argv) == 3:
        print 'Bad parameters\nUsage: {} listen:port target:port' .format(sys.argv[0])
        sys.exit(0)
    listen = sys.argv[1].split(':')
    forward = sys.argv[2].split(':')
    listen[1], forward[1] = int(listen[1]), int(forward[1])
    proxy = Proxy(listen=tuple(listen), forward=tuple(forward))
    try:
        proxy.main_loop()
    except KeyboardInterrupt:
        print "\nStopping proxy..."
        sys.exit(1)
