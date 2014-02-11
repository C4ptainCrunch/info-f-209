#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include <string>

#define RCV_SIZE 2

char * get_ip_str(const struct sockaddr *sa, char *s, size_t maxlen);


char * addrinfo_to_ip(const addrinfo info, char * ip);

void *get_in_addr(const sockaddr *sa);
void sendTo(const int sock, std::string message);

std::string recieveFrom(const int sock, char * buffer);

#endif // HELPERS_H
