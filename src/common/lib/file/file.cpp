#include "file.h"

using namespace std;

int readFile(const string & filename, string & content) {
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd >= 0) {
        char buffer[BUFF_SIZE];
        size_t read_len = 0;
        do {
            read_len = read(fd, buffer, BUFF_SIZE);
            if (read_len == -1) {
                close(fd);
                return -1;
            }
            if (read_len > 0) {
                content += string(buffer, read_len);
            }
        } while (read_len > 0);
        close(fd);
        return 0;
    }
    else {
        return fd;
    }
}

int writeFile(const string & filename, string & content) {
    int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0600);

    if(fd >= 0){
        int pos = 0;

        while(pos < content.length()){
            const char* buffer = content.c_str();
            int len = content.length();

            int size =  write(fd, buffer, len);
            if(size == -1){
                return -1;
            }
            pos += size;
        }
        close(fd);
        return 0;
    }
    return fd;

}

bool fileExists(const std::string & filename) {
    access(filename.c_str(), F_OK);
    return errno != ENOENT;
}
