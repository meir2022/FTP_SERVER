#include "authenticate_client.h"
#include "error_log.h"

bool authenticate_client(char *username, char *password)
{
    char line[MAX_BUFFER_SIZE];
    FILE *users_file = fopen(USERS_FILE, "r");

    if (!users_file){
        save_errors("can't open users file");
        return false;
    }

    while (fgets(line, MAX_BUFFER_SIZE, users_file) != NULL)
    {
        char stored_username[MAX_USERNAME_SIZE + 1];
        char stored_password[MAX_PASSWORD_SIZE + 1];
        sscanf(line, "%s , %s", stored_username, stored_password);
        if (!strcmp(username, stored_username) && !strcmp(password, stored_password))
        {
            printf("in authenticate_client user = %s , password = %s\n", stored_username, stored_password);
            fclose(users_file);
            return true;
        }
    }
    fclose(users_file);
    return false;
}