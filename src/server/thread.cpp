void connection(const int fd){
    sendTo(fd, "Hello, bite!\n");
    std::string ping = recieveFrom(fd);
    sendTo(fd, ping.c_str());
    sendTo(fd, "Bye\n");
    close(fd);

}