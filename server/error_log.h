#ifndef ERROR_LOG_H
#define ERROR_LOG_H

#include "server.h"

// this function save the errors to log file
void save_errors(char* msg);
void end_dialog(int clientSocket);

#endif