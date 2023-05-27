#include "save_user_log.h"

void save_users_log(char* user_data){
    FILE* user_log_file = fopen("users_log.txt","a+");
    fprintf(user_log_file,"%s\n",user_data);
    fclose(user_log_file);
}