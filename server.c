#include "server.h"


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char **argv)
{
    int sockfd, newsockfd, n;
    char buffer[255];

    struct sockaddr_in serv_addr , cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        error("Error opening socket.");
    }

    bzero((char *) &serv_addr , sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd , (struct sockaddr *) &serv_addr , sizeof(serv_addr)) < 0)
    {
        error("Binding Failed.");
    }

    listen(sockfd , 7);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd , (struct sockaddr *) &cli_addr , &clilen);

    if(newsockfd < 0)
    {
        error("Error on Accept");
    }

    int num1 , num2 , ans , choice;

    //Ask for Number 1
S : n = write(newsockfd,"Enter Number 1: ", strlen("Enter Number 1"));
    if (n < 0)
    {
        error("ERROR writing to socket");
    }
    //Read Number 1
    read(newsockfd, &num1, sizeof(int));
    printf("Client - Number 1 is: %d\n", num1);

    //Ask for Number 2
    n = write(newsockfd,"Enter Number 2: ", strlen("Enter Number 2"));
    if (n < 0)
    {
        error("ERROR writing to socket");
    }
    //Read Number 2
    read(newsockfd, &num2, sizeof(int));
    printf("Client - Number 2 is: %d\n", num2);

    //Ask for choice
    n = write(newsockfd, "Enter your choice : \n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exponentiation\n6.Root\n7.Exit\n",
    strlen("Enter your choice : \n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exponentiation\n6.Root\n7.Exit\n"));
    if (n < 0)
    {
        error("ERROR writing to socker");
    }
    //Read choice
    read(newsockfd, &choice, sizeof(int));
    printf("Client - Choice is : %d\n" , choice);

    switch(choice)
    {
        case 1:
            ans = num1 + num2;
            break;
        case 2:
            ans = num1 - num2;
            break;
        case 3:
            ans = num1 * num2;
            break;
        case 4:
            if(num2 == 0)
            {
                break;
            }
            ans = num1 / num2;
            break;
        case 5:
            ans = pow(num1, num2);
            break;
        case 6:
            if(num1 < 0)
            {
                break;
            }
            ans = pow(num1, (1.0/num2));
            break;
        case 7:
            goto Q;
            break;
    }

    write(newsockfd , &ans , sizeof(int));
    if(choice != 7)
    {
        goto S;
    }

Q : close(newsockfd);
    close(sockfd);
    return 0;

}
