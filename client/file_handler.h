#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "header.h"
#include <dirent.h>
#define MAX_BUFFER_SIZE 1024
#define MAX_DIR_SIZE    300
#define SHORT_MSG_SIZE  10
#define DEST_STORAGE ""

void send_list(int client_socket);

void send_file(char *file_name, int new_socket);

void recieve_file(char* file_name, int new_socket);

int get_file_size(char* file_name);

void get_list_of_files(char* files_list);

#endif