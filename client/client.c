#include "header.h"
#include "file_handler.h"
#define MAX_USERNAME_SIZE 30
#define MAX_PASSWORD_SIZE 12
#define MAX_FILE_NAME_SIZE 30

enum mode
{
    LIST,
    UPLOAD,
    DOWNLOAD
};

int select_choice()
{
    char choice[10];
    int choice_code = -2;

    while (choice_code == -2)
    {
        puts("SELECT CHOICE [LIST] [UPLOAD] [DOWNLOAD] [QUIT]: ");
        scanf("%s", choice);
        getchar();
        if (!strcmp(choice, "list") || !strcmp(choice, "LIST"))
            choice_code = LIST;
        if (!strcmp(choice, "upload") || !strcmp(choice, "UPLOAD"))
            choice_code = UPLOAD;
        if (!strcmp(choice, "download") || !strcmp(choice, "DOWNLOAD"))
            choice_code = DOWNLOAD;
        if (!strcmp(choice, "quit") || !strcmp(choice, "QUIT"))
            choice_code = -1;
    }
    return choice_code;
}

void main()
{
    while (1)
    {
        char filename[MAX_FILE_NAME_SIZE] = {0};
        char username[MAX_USERNAME_SIZE] = {0};
        char password[MAX_PASSWORD_SIZE] = {0};
        char choice[10] = {0};

        puts("ENTER YOUR NAME: ");
        scanf("%s", username);
        getchar();
        puts("ENTER YOUR PASSWORD: ");
        scanf("%s", password);
        getchar();

        while (1)
        {
            char user_data[MAX_PASSWORD_SIZE + MAX_USERNAME_SIZE + 5] = {0};
            char buffer[MAX_BUFFER_SIZE] = {0};
            int choice_code = select_choice();
            if(choice_code == -1){
                puts("\nbye bye!");
                return;
            }
            sprintf(user_data, "%s:%s %d", username, password, choice_code);

            int new_socket = socket(AF_INET, SOCK_STREAM, 0);
            struct sockaddr_in server_addr;
            server_addr.sin_family = AF_INET;
            server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            server_addr.sin_port = htons(PORT);

            connect(new_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

            strcpy(buffer, user_data);
            send(new_socket, buffer, MAX_BUFFER_SIZE, 0);

            bzero(buffer, sizeof(buffer));
            recv(new_socket, buffer, MAX_BUFFER_SIZE, 0);

            if (strstr(buffer, "wrong "))
            {
                close(new_socket);
                puts("wrong details, try again");
                break;
            }
            if (choice_code == LIST)// no need to continue with file process
            { 
                puts(buffer);
                continue;
            }
            puts("enter file name :");
            scanf("%s", filename);
            send(new_socket, filename, 30, 0);
            
            if(choice_code == UPLOAD)
                send_file(filename,new_socket);

            else if(choice_code == DOWNLOAD)
                recieve_file(filename, new_socket);
        }
    }
}
