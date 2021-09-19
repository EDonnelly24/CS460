#include "server.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int main() {

    // declarations
    int time_server_socket;                  // time client side socket
    struct sockaddr_in time_server_address;  // time client socket naming struct
    char* time_server_ip;
    char buffer[1024] = {0};
    char OTM = '*';
    

    // getting the string of the ip of server, given SERVER_ADDR
    time_server_ip = inet_ntoa(*(struct in_addr*)(gethostbyname(SERVER_ADDR)->h_addr_list[0])); // DNS lookup, grab first IP
    
    // create an unnamed socket, and then name it
    time_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // create addr struct
    time_server_address.sin_family = AF_INET;
    time_server_address.sin_addr.s_addr = inet_addr(time_server_ip);
    time_server_address.sin_port = htons(PORT);

    printf("Echo client\n");

    // connect to server socket
    if (connect(time_server_socket, (struct sockaddr *)&time_server_address, sizeof(time_server_address)) == -1) {
        perror("Error connecting to server!\n");
        exit(EXIT_FAILURE);
    }

    // get the result up until OTM
    read(time_server_socket, buffer, sizeof(buffer));
    int index = 0;
    while(buffer[index] != OTM) {
        printf("%c", buffer[index]);
        index++;
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}
