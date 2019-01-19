//
// Created by Kevin on 10-4-2018.
//

#include "Server.h"

/**
* @brief Server Constructor
* @returns none
* @author Kevin Jansen
*/
Server::Server(int port, char *ip_addr) {
    _port = port;
    //Saferead the IP
    _ip_addr = (char *) malloc(sizeof(char) * 15);
    cpString(ip_addr, _ip_addr);
}

/**
* @brief starts the server
* @returns none
* @author Kevin Jansen
*/
void Server::startup() {

    _listen_fd = (int) socket(AF_INET, SOCK_STREAM, 0);

    _serveraddr.sin_family = AF_INET;
    _serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    _serveraddr.sin_port = htons(_port);

    bind( _listen_fd, (struct sockaddr *) &_serveraddr, sizeof(_serveraddr));

    listen( _listen_fd, 10);
}

/**
* @brief connects the server
* @returns none
* @author Kevin Jansen
*/
void Server::connect(){
    _comm_fd = (int) accept( _listen_fd, (struct sockaddr *) NULL, NULL);

    printf("Connected\n");
}

/**
* @brief Gets the data send by the client/module
* @returns The data revieved
* @author Kevin Jansen
*/
char* Server::getData() {
    zeroTarget(data);
    printf("Zeroed Data\n");
    printf("Listening\n");

    read(_comm_fd, data, 100);

    return data;
}

/**
* @brief Sends the data to the client/module
* @returns none
* @author Kevin Jansen
*/
void Server::sendData(char* data) {
    printf("Got Data\n");
    printf("Echoing back - %s\n", data);
    write(_comm_fd, data, (unsigned int) (strlen(data) + 1));
}

/**
* @brief disconnects the connection
* @returns none
* @author Kevin Jansen
*/
void Server::disconnect(){
    shutdown(_comm_fd, 2);

    printf("Closed connection\n");
}

/**
* @brief Gets the ip address
* @returns The ip address
* @author Kevin Jansen
*/
char *Server::toString() {
    char *string = (char *) malloc(sizeof(_ip_addr));
    cpString(_ip_addr, string);
    return string;
}

/**
* @brief Copies a byte array from one place to another, used for strings
* @returns none 
* @author Kevin Jansen
*/
void Server::cpString(char *source, char *dest) {
    zeroTarget(dest);
    int size = sizeof(source) + 1;
    for (int i = 0; i <= size; i++) {
        *dest = *source;
        dest++;
        source++;
    }
    source -= size;
    dest -= size;
}

/**
* @brief Zeroes the targeted byte array.
* @returns none 
* @author Kevin Jansen
*/
void Server::zeroTarget(char *target) {
    int size = sizeof(target);
    for (int i = 0; i <= size; i++) {
        *target = 0;
        target++;
    }
    target -= size;
}
