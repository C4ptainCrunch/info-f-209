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
    int fd = open(filename.c_str(), O_WRONLY | O_CREAT, 0600);

    if (fd >= 0) {
        size_t index = 0;
        size_t delta;

        do {
            size_t write_len = 0;

            delta = content.size() - index;
            if (delta > BUFF_SIZE) {
                delta = BUFF_SIZE;
            }

            const char * buffer = content.substr(index, delta).c_str();
            write_len = write(fd, buffer, content.size());
            if (write_len == -1) {
                close(fd);
                return -1;
            }
            if (write_len > 0) {
                index += write_len;
            }
        } while (delta > 0);

        return 0;
    }
    else {
        return fd;
    }
}

bool fileExists(const std::string & filename) {
    access(filename.c_str(), F_OK);
    return errno != ENOENT;
}
