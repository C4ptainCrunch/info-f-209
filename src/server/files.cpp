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
    int fd = open(fileName, O_WRONLY, O_CREAT, O_APPEND);
    std::cout<<"write 1"<<std::endl;
    if (fd){
        std::cout<<"write 2"<<std::endl;
        do {
            const char *buffer = content.substr(index, BUFF_SIZE).c_str();
            std::cout<<"write 3"<<std::endl;
            write_len = write(fd, buffer, BUFF_SIZE);
            if(write_len == -1){
                close(fd);
                return -1;
            }
            if(write_len>0){
                index += write_len;
                std::cout<<"write 4"<<std::endl;
            }
        } while(write_len>0);
    }
    return 0;
}

int main(int argc, char * argv[]){
    if(argc <= 1){
        std::cout<<"Invalid parameters"<<std::endl;
        exit(0);
    }
    std::string lol;
    char * file = argv[1];
    int state = readFile(file, lol);
    if (state == -1){
        std::cout<<"Erreur en lecture "<<std::endl;
        exit(1);
    }
    std::cout<<lol<<std::endl;
    state = writeFile("lol.txt", lol);
    if (state == -1){
        std::cout<<"Erreur en écriture "<<std::endl;
        exit(1);
    }
    std::cout<<"Success"<<std::endl;
    return 0;    // TO DO : vérifier si EXIT_SUCCESS à return
}