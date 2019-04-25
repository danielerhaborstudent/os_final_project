#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "list.h"
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAXARGLEN 1024

typedef enum command_type{
    GET,
    PUT,
    DUMP,
    QUIT,
    ERROR
} command_t;

typedef struct cmd_tokens{
  char* arg1;
  char* arg2;
  int arg_count;
  command_t cmd_type;
} cmd_tokens_t;



void Tokenize(char* cmd, cmd_tokens_t* tokens);
int ParseCommand(char* cmd, char* argv[]);
void ProcessCommands(cmd_tokens_t* tokens, char* buffer);

list_t* map;


int main(){
    int server_socket, client_socket;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_size;
    map = list_alloc();

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        perror("socket failed");
        exit(1);
    } 

    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ( bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0){
        perror("bind failed");
        exit(1);
    }

    if( listen(server_socket,5) < 0){
      perror("listen failed"); 
      exit(1);
    }
    else{
      printf("Listening.\n");
    }

    client_address_size = sizeof (client_address);
    if ( (client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_address_size)) < 0) {
        perror("accept failed");
        exit(1);
    }
    
    while(1){
       
        memset(buffer, '\0', BUFFER_SIZE);
        read(client_socket, buffer, BUFFER_SIZE);
        
//         printf("Raw command: %s\n", buffer );
        cmd_tokens_t tokens;
        Tokenize(buffer, &tokens);
        
        

        memset(buffer, '\0', BUFFER_SIZE);
//         strcpy(buffer, "Hello client. I got your message!");
        ProcessCommands(&tokens, buffer);

        if (write(client_socket, buffer, strlen(buffer)) < 0) {
            perror("write failed\n");
            exit(1);
        }
    }
    

    
    close(client_socket);
    close(server_socket);

    return 0;
}

void Tokenize(char* cmd, cmd_tokens_t* tokens){
	int init_size = strlen(cmd);
	char delim[] = " \n";

    char* argv[MAXARGLEN];
    int curr_num_args = 0;
    int arg_length;
    arg_length = ParseCommand(cmd, argv);
//     printf("Arg length after parse: %d\n", arg_length);

    
//     for (int i = 0; i < arg_length; ++i){
//         printf("Args: %s\n", argv[i]);
//     }

    if (strcmp(argv[0], "GET") == 0){
        tokens->cmd_type = GET;
    }
    else if (strcmp(argv[0], "PUT") == 0){
        tokens->cmd_type = PUT;
    }
    else if (strcmp(argv[0], "DUMP") == 0){
        tokens->cmd_type = DUMP;
    }
    else if (strcmp(argv[0], "QUIT") == 0){
        tokens->cmd_type = QUIT;
    }
    else {
        printf("Will handle errors here\n");
    }
    
    if (tokens->cmd_type == GET && arg_length == 2){
        tokens->arg1 = argv[1];
    }
    else if (tokens->cmd_type == PUT && arg_length == 3){
        tokens->arg1 = argv[1];
        tokens->arg2 = argv[2];
    }
    
    // Maybe some error handling for DUMP, QUIT and actual ERROR
}

int ParseCommand(char* cmd, char* argv[]){
	char delim[] = " \n";
    char* cmd_copy = malloc(strlen(cmd));
    strcpy(cmd_copy, cmd);
	char *ptr = strtok(cmd_copy, delim);

    int curr_num_args = 0;
    
    while(ptr != NULL){
        argv[curr_num_args] = ptr;

//         printf("Arg %d: %s\n", curr_num_args, argv[curr_num_args]);
        ptr = strtok(NULL, delim);
        ++curr_num_args;
	}
    
    return curr_num_args;
    
}

void ProcessCommands(cmd_tokens_t* tokens, char* buffer){
    if (tokens->cmd_type == PUT){
        
        list_put(map, tokens->arg1, tokens->arg2);
        sprintf(buffer, "%s, %s", tokens->arg1, tokens->arg2);
    }
    else if (tokens->cmd_type == GET){
//         sprintf(buffer, list_get_value_of_key(map, tokens->arg1));
        strcpy(buffer, list_get_value_of_key(map, tokens->arg1);
    
    }
    else if (tokens->cmd_type == DUMP){
        list_print(map, buffer);
    }
    
    printf("Do nothing\n");
}