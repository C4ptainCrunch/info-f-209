#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8000
#define BUFFERSIZE 200

/*defaultRecv et defaultSend sont des raccourcis pour ne pas préciser les para csts.*/
int defaultRecv(int sockFd, void *buf);
int defaultSend(int sockFd, void *buf);


int main(int argc, char** argv)
{
    int sockFd, run = 1, loggedIn = 0;
    char buffer[BUFFERSIZE];
    struct sockaddr_in theirAddr;
    struct hostent *he;
    socklen_t addrSize = sizeof(struct sockaddr);


    if (argc != 2)
    {
        fprintf(stderr, "Donnez le nom de la machine distante en argument.\n");
        return EXIT_FAILURE;
    }

    if ((he=gethostbyname(argv[1])) == NULL)
    {
        perror("Client: gethostbyname ");
        return EXIT_FAILURE;
    }

    if ((sockFd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Client: socket ");
        return EXIT_FAILURE;
    }

    theirAddr.sin_family = AF_INET;
    theirAddr.sin_port = htons(PORT);
    theirAddr.sin_addr = *((struct in_addr*)he->h_addr);
    memset(&(theirAddr.sin_zero), '\0', 8);

    if (connect(sockFd, (struct sockaddr *)&theirAddr, addrSize) == -1)
    {
        perror("Client: connect ");
        return EXIT_FAILURE;
    }

    printf("Connecté au serveur.");

    while (run == 1)
    {
        int boolSend = 1; /*Ce "bool" représente "faut-il envoyer un message au serveur"*/

        printf("\n>>> ");
        fgets(buffer, BUFFERSIZE, stdin);

        if ((strncmp("Q", buffer, 1) == 0) || (strncmp("q", buffer, 1) == 0))
        {
            printf("Fin de la connection.\n");
            run = 0;
            mySend(sockFd, buffer);
        }
    }

    close(sockFd);
    return EXIT_SUCCESS;
}

int defaultRecv(int sockFd, void *buf)
{
    int numbytes;

    if ((numbytes = recv(sockFd, buf, len, flags)) == -1)
    {
        char errorText[50];
        sprintf(errorText, "Client : recv ");
        perror(errorText);
        exit(EXIT_FAILURE);
    }

    return numbytes;
}

int defaultSend(int sockFd, void *buf)
{
    int res;

    if ((res = send(sockFd, buf, len, flags)) == -1)
    {
        char errorText[50];
        sprintf(errorText, "Client : send ");
        perror(errorText);
        exit(EXIT_FAILURE);
    }

    return res;
}
