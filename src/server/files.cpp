#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <iostream>

#define BUFF_SIZE 1024

int readFile(char * fileName, std::string & content){
    char buffer[BUFF_SIZE];
    int read_len = 0;
    int fd = open(fileName, O_RDONLY);
    if (fd){
        do {
            read_len=read(fd, buffer, BUFF_SIZE);
            if(read_len == -1){
                close(fd);
                return -1;
            }
            if(read_len>0){
                content += buffer;
            }
        } while(read_len>0);
    }
    close(fd);
    return 0;
}

int writeFile(char * fileName, std::string & content){
    int write_len = 0;
    int index=0;
    int delta;
    int fd = open(fileName, O_WRONLY, O_CREAT, O_APPEND);
    if (fd){
        do {
            delta = content.size()-index;
            if (delta > BUFF_SIZE){
                delta=BUFF_SIZE;
            }
            const char *buffer = content.substr(index, delta).c_str();
            write_len = write(fd, buffer, content.size());
            if(write_len == -1){
                close(fd);
                perror("Echec écriture : ");
                return -1;
            }
            if(write_len>0){
                index += write_len;
            }
        } while(delta >= BUFF_SIZE);
    }
    return 0;
}