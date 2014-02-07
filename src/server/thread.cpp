void connection(int fd){
    if (send(fd, "Hello, bite!\n", 13, 0) == -1)
        perror("send");
    sleep(1);
    if (send(fd, "Closing, bye !\n", 15, 0) == -1)
        perror("send");
    close(fd);

}