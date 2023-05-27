#include "server.h"

int server_socket;
enum mode
{
    LIST,
    UPLOAD,
    DOWNLOAD
};
// function to shutdown the server safetly
void handle_interrupt_signal(int signum)
{
    printf("\nshutting down the server\n");
    close(server_socket);
    exit(signum);
}
void start_server()
{
    int client_addrress_length, client_socket, check;
    pthread_t thread_id;
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
        save_errors("failed create socket");

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    check = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (check < 0)
    {
        save_errors("failed binding socket");
        puts("failed binding socket"); 
    }

    check = listen(server_socket, 5);
    if(check < 0)
        save_errors("the port isn't available");
        printf("listening port %d\n",PORT); 

    while (1)
    {
        char buffer[MAX_BUFFER_SIZE] = {0};
        struct sockaddr_in client_addrress;

        client_addrress_length = sizeof(client_addrress);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addrress, &client_addrress_length);
        puts("accepted"); 
        pthread_create(&thread_id, 0 , handle_client,(void *) &client_socket);
    }
}
void* handle_client(void* ptr_client_socket)
{
    int client_socket = *(int*)ptr_client_socket;
    char buffer[MAX_BUFFER_SIZE];
    char username[MAX_USERNAME_SIZE] = {0};
    char password[MAX_PASSWORD_SIZE] = {0};
    char user_option[USER_OPTION_SIZE] = {0};
    char user_data[MAX_USER_DATA_SIZE] = {0};
    char file_name[MAX_FILE_NAME_SIZE] = {0};

    int option, input_params;

    recv(client_socket, buffer, sizeof(buffer), 0);
    input_params = sscanf(buffer, "%[^:]:%s %s%s", username, password, user_option);

    if (input_params < 3)
    {
        end_dialog(client_socket);
        pthread_exit(1);
    }
    sprintf(user_data,"%s, %s, %s ", username, password, user_option); // build user data for saving in users log

    if (!authenticate_client(username, password))
    {
        end_dialog(client_socket);
        pthread_exit(1);
    }
    option = atoi(user_option);
printf("option %d\n", option); //----------------------------------------------------------------------
    if (option != LIST) 
    {
        char *success_msg = "connected, send file name:\n";
        send(client_socket, success_msg, strlen(success_msg) + 1, 0);
        recv(client_socket, file_name, sizeof(file_name), 0);
        strcat(user_data, file_name); // build user data for saving in users log
    }
    save_users_log(user_data); // save the client details in users log

    switch (option)
    {
        case LIST:
            send_list(client_socket);
            break;

        case UPLOAD:
            FILE *file = fopen(file_name, "r+");
            if (file) { // if mode 'r' opened file its already exist
                char* exist_msg = "file already exist";
                send(client_socket, exist_msg, strlen(exist_msg)+1, 0);
                fclose(file);
            }
            else
                recieve_file(file_name, client_socket);
            break;

        case DOWNLOAD:
            send_file(file_name, client_socket);
            break;
    }
    close(client_socket);
    pthread_exit(1);
}

