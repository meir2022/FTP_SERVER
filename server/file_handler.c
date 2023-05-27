#include "file_handler.h"

void send_file(char* file_name, int socket)
{
    FILE* file;
    char buffer[MAX_BUFFER_SIZE];
    char dest[MAX_DIR_SIZE] = DEST_STORAGE; // correct the path to the storage
   
    strcat(dest,file_name);
    
    file = fopen(dest,"r");
    if(!file){
        save_errors("error opening file");
        return;
    }
    while (fgets(buffer,  MAX_BUFFER_SIZE, file))  //read file until the end
    {
        send(socket, buffer, MAX_BUFFER_SIZE, 0);
        bzero(buffer, MAX_BUFFER_SIZE);
    }
    fclose(file);
}

void recieve_file(char *file_name, int new_socket)
{
    char buffer[MAX_BUFFER_SIZE];
    FILE *file;
    char dest[MAX_DIR_SIZE] = DEST_STORAGE; // correct the path to the storage
   
    strcat(dest,file_name);

    file = fopen(dest, "w+");
    if(!file){
        save_errors("file open failed");
        return;
    }
    while (recv(new_socket, (void *)buffer, MAX_BUFFER_SIZE, 0) > 0)
    {
        fprintf(file, MAX_BUFFER_SIZE, buffer);
        bzero(buffer, MAX_BUFFER_SIZE);
    }
    fclose(file);
    send(new_socket, "done\n", SHORT_MSG_SIZE, 0);
}

int get_file_size(char *file_name)
{
    char dest[MAX_DIR_SIZE]= DEST_STORAGE; // correct the path to the storage
    strcat(dest,file_name);

    FILE *file = fopen(dest, "r");
    if(!file){
        puts("error opening file");
        return 0;
    }
    int file_size;

    fseek(file, 0, SEEK_END); // move the ptr to end of file
    file_size = ftell(file);
    fclose(file);
    
    return file_size;
}
void send_list(int client_socket)
{
    char buffer[MAX_BUFFER_SIZE] = {0};

    get_list_of_files(buffer);
    send(client_socket, buffer, MAX_BUFFER_SIZE, 0);
  
}
// this fuction got an argument string, and make list of current folder content, and store it in string argument
void get_list_of_files(char *files_list)
{
    struct dirent *file_iterator;
    char dest_dir[MAX_DIR_SIZE];  // local path to concat to destination storage folder 
    DIR *dir;

    getcwd(dest_dir, MAX_DIR_SIZE);        // find current path
    strcat(dest_dir,DEST_STORAGE);
    dir = opendir(dest_dir); 
   
    while ((file_iterator = readdir(dir)) != NULL)
    {                                                                                               // read the folder content until the end
        char dest[MAX_DIR_SIZE] = {0};                                                                             // string destination build
        char full_path[MAX_DIR_SIZE] = {0}; 

        sprintf(full_path,"%s/%s",dest_dir, file_iterator->d_name);                                                                            // string destination build
        sprintf(dest, "%20s\t%d b\n", file_iterator->d_name, get_file_size(full_path)); // current line format

        strcat(files_list, dest);
    }

    closedir(dir);
}
