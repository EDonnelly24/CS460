#include "server.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int main() {
    int client_socket;                  // client side socket
    struct sockaddr_in client_address;  // client socket naming struct
    char buffer[1024] = {0};
    char OTM = '*';
    
    printf("Echo client\n");
    
    // create an unnamed socket, and then name it
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // create addr struct
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    client_address.sin_port = htons(PORT);
    
    // connect to server socket
    if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
        perror("Error connecting to server!\n");
        exit(EXIT_FAILURE);
    }

    // get the result up until OTM
    read(client_socket, buffer, sizeof(buffer));
    int index = 0;
    while(buffer[index] != OTM) {
        printf("%c", buffer[index]);
        index++;
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}
