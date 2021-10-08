#include "server.h"
/************************************************************************
 * MAIN
 ************************************************************************/
//global variable for lock
pthread_mutex_t lock;

int main(int argc, char** argv) {
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket
    int client_socket;
    pthread_t pthread;

    // sent when ,client disconnected
    signal(SIGPIPE, SIG_IGN);

    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
    server_address.sin_port        = htonl(PORT);       // port to listen on

    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) == -1) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    // server loop
    while (TRUE) {

        // accept connection to client
        if ((client_socket = accept(server_socket, NULL, NULL)) == -1) {
            perror("Error accepting client");
        } else {
            printf("\nAccepted client\n");
            pthread_create(&pthread,NULL,handle_client,(void *)&client_socket);
            printf("\nCreated pthread\n");
        }

        pthread_mutex_lock(&lock);

        printf("\n Detatching pthread");
        pthread_detach(pthread);

        pthread_mutex_unlock(&lock);
    }
}

int three_a_plus_one(int input)
{
    int counter = 0;
    int current = input;

    while (current != 1)
    {
        counter++;
        if (current % 2) {
            current = (current*3) + 1;
        }
        else {
            current >>= 1;
        }
    }
    return counter;
}
/************************************************************************
 * handle client
 ************************************************************************/

void *handle_client(void *client_socket) {
    int input;
    int keep_going = TRUE;
    // int client_socket = (int *)client_socket;

    while (keep_going) {
        // read int from client
        printf("%c", input);

        // check if we terminate
        if (input == 'q') {
            keep_going = FALSE;
        }

        // send result back to client
        write(client_socket, &input, sizeof(int));

    }

    // cleanup
    if (close(client_socket) == -1) {
        perror("Error closing socket");
        exit(EXIT_FAILURE);
    } else {
        printf("\nClosed socket to client, exit");
    }
}
