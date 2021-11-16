#include "server.h"


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        error("ERROR opening socket");
    }

    bzero((char *) &serv_addr , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    serv_addr.sin_port = htons(PORT);
    if(connect(sockfd , (struct sockaddr *) &serv_addr , sizeof(serv_addr))<0)
    {
        error("Connection Failed");
    }

    int num1 , num2 , choice , ans;

    S : bzero(buffer, 256);
        //Read Server String
        n = read(sockfd, buffer, 255);
        if(n < 0)
        {
            error("ERROR reading from socket");
        }
        printf("Server - %s\n", buffer);
        //Enter Number 1
        scanf("%d", &num1);
        //Send Number 1 to Server
        write(sockfd, &num1, sizeof(int));

        bzero(buffer, 256);
        //Read Server String
        n = read(sockfd, buffer, 255);
        if(n < 0)
        {
            error("ERROR reading from socket");
        }
        printf("Server - %s\n", buffer);
        //Enter Number 2
        scanf("%d", &num2);
        //Send Number 2 to Server
        write(sockfd, &num2, sizeof(int));

        bzero(buffer, 256);
        //Read Server String
        n = read(sockfd, buffer, 255);
        if(n < 0)
        {
            error("ERROR reading from socket");
        }
        printf("Server - %s", buffer);
        //Enter choice
        scanf("%d", &choice);
        //Send choice to Server
        write(sockfd, &choice, sizeof(int));

        if(choice == 7)
        {
            goto Q;
        }

        if(choice == 4 && num2 == 0)
        {
            printf("Cannot divide by 0, try again.\n");
            goto S;
        }

        if(choice == 6 && num1 < 0)
        {
            printf("The root of negative numbers is undefined, try again.\n");
            goto S;
        }

        read(sockfd , &ans , sizeof(int));
        printf("Server - The answer is: %d\n", ans);

        if(choice != 7)
        {
            goto S;
        }

    Q :
    printf("Exit Successful.\n");
    close(sockfd);
    return 0;

}
