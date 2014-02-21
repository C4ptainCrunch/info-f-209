#ifndef FILES_H
#define FILES_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <iostream>

#define BUFF_SIZE 1024

int readFile(const char * fileName, std::string & content);
int writeFile(const char * fileName, std::string & content);

#endif // FILES_H