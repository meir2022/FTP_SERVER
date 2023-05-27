#ifndef SERVER_H
#define SERVER_H

#include "header.h"
#include "authenticate_client.h"
#include "save_user_log.h"
#include "error_log.h"
#include "file_handler.h"

void start_server();

// this function run on different thread, for multitask client handling
void* handle_client(void* ptr_client_socket);

// function to close port safety when ctrl+c
void handle_interrupt_signal(int signum);

#endif