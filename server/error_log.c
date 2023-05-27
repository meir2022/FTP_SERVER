#ifndef ERROR_LOG_H
#define ERROR_LOG_H

#include "error_log.h"
#include <stdio.h> // problem on recognition library within headet

// function to save the errors to log, got msg to current error to save
void save_errors(char* msg){
    FILE* file = fopen("server_log.txt", "a+");
    fprintf(file,"%s\n",msg);
    fclose(file);
}
// function to end comunication with client
void end_dialog(int clientSocket)
{
    char* throw_msg ="wrong details, Disconnected from server\n";
    send(clientSocket, throw_msg, strlen(throw_msg)+1, 0);
    close(clientSocket);
}

#endif