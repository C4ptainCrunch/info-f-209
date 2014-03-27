import socket
from contextlib import contextmanager
import json
from multiprocessing import Process


@contextmanager
def sock(host, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    yield s
    s.close()


def send(s, topic, message):
    if not isinstance(message, str):
        message = json.dumps(message)
    s.sendall("{}:{}\n\n".format(topic, message))


def recv(s):
    data = s.recv(10240)
    t = data.split(':')
    return t[0], json.loads((":".join(t[1:]))[:-2])


def coroutine(f):
    p = Process(target=f)
    p.start()

    return p
