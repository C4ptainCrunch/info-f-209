#ifndef FILES_H
#define FILES_H

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <errno.h>

#define BUFF_SIZE 1024

int readFile(const std::string & filename, std::string & content);
int writeFile(const std::string & filename, std::string & content);

bool fileExists(const std::string & filename);

bool createDir(std::string dirname);

#endif // FILES_H
