#define RCV_SIZE 2

char *get_ip_str(const struct sockaddr *sa, char *s, size_t maxlen=128)
{
    switch(sa->sa_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr),
                    s, maxlen);
            break;

        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr),
                    s, maxlen);
            break;

        default:
            strncpy(s, "Unknown AF", maxlen);
            return NULL;
    }

    return s;
}

char * addrinfo_to_ip(const addrinfo info, char * ip){
    get_ip_str((struct sockaddr *)info.ai_addr, ip);
    return ip;
}

void *get_in_addr(const sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void sendTo(const int sock, std::string message) {
    const char * msg = message.c_str();
    int len = strlen(msg);
    int bytes_sent = 0;
    while(len > 0){
        bytes_sent = send(sock, msg, len, 0);
        len -= bytes_sent;
        msg = msg + bytes_sent;
    }
}

std::string recieveFrom(const int sock){
    std::string message;
    char buf[RCV_SIZE];
    int len = RCV_SIZE;

    while(len >= RCV_SIZE || len == 0){
        if((len = recv(sock,buf, RCV_SIZE, 0)) == 0)
            printf("Listen failed : %s\n", strerror(errno));
        else {
            buf[len] = '\0';
            message += buf;
        }
    }
    return message;
}
