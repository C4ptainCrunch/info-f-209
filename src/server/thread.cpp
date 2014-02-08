void connection(const int fd){
    sendTo(fd, "Hello, bite!\n");
    std::string ping = recieveFrom(fd);
    sendTo(fd, ping);
    sendTo(fd, "Bye\n");
    close(fd);

}
