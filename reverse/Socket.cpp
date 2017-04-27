#include <arpa/inet.h>
#include <zconf.h>
#include "Socket.h"


Socket::Socket()
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);

    }

    my_addr.sin_family = AF_INET; /* host byte order */
    my_addr.sin_port = htons(MYPORT); /* short, network byte order */
    my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
    bzero(&(my_addr.sin_zero),sizeof(my_addr.sin_zero)); /* zero the rest of the struct */


    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
}

void Socket::initial() {

    sin_size = sizeof(struct sockaddr_in);

    if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size)) == -1) {
        perror("accept");
        exit(0);
    }
}

int Socket::mysend(std::string)
{
    printf("server: got connection from %s\n", \

    inet_ntoa(their_addr.sin_addr));

    if(send(new_fd, "Hello, world!\n", 14, 0) == -1)
        perror("send");
}

Socket::~Socket()
{
    close(new_fd);
}
