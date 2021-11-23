#include "server.h"


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
	struct sockaddr_in serv_addr = {0};
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int len = sendto(sockfd, (const char *)hello, strlen(hello),
		0, (const struct sockaddr_in *)&serv_addr, sizeof(serv_addr));
	if(len ==-1)
	{
		perror("failed to send");
	}
	close(sockfd);

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
