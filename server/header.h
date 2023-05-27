#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_PASSWORD_SIZE 12
#define MAX_USERNAME_SIZE 20
#define MAX_USER_DATA_SIZE 70
#define MAX_FILE_NAME_SIZE 30
#define MAX_DIR_SIZE 100
#define USER_OPTION_SIZE 10
#define SHORT_MSG_SIZE 10
#define USERS_FILE "users.txt"
#define PORT 5555

#endif