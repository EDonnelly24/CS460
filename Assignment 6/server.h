/************************************************************************
 * libraries
 ************************************************************************/
// should always be there ...
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// socket/bind/listen/accept
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

// read/write/close
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>

/************************************************************************
 * preprocessor directives
 ************************************************************************/
#define SERVER_ADDR "127.0.0.1" // loopback ip address
#define PORT 23657              // port the server will listen on

// I cannot let go of the old-fashioned way :) - for readability ...
#define FALSE false
#define TRUE !false
