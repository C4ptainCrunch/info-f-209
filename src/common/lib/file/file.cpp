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

    if (fd >= 0) {
        int pos = 0;

        while (pos < content.length()) {
            const char * buffer = content.c_str();
            int len = content.length();

            int size =  write(fd, buffer, len);
            if (size == -1) {
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


bool createDir(string dirname) {
    size_t start = 0, pos;
    std::string dir;
    int ret;
    if (dirname[dirname.size() - 1] != '/') {
        dirname += '/'; // add a trailing / if not present
    }

    while ((pos = dirname.find_first_of('/', start)) != std::string::npos) {
        dir = dirname.substr(0, pos);
        start = pos + 1;
        if (dir.size() == 0) {
            continue;                 // if leading / first time is 0 length
        }
        ret = mkdir(dir.c_str(), 0700);
        if ((ret != 0) && (errno != EEXIST)) {
            return false;
        }
    }
    return ret == 0 || errno == EEXIST;
}
