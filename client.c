#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080
#define BUFFER_SIZE 1024



int main(){
    int client_socket;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_address;
    socklen_t server_address_size;

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        perror("socket failed\n");
        exit(1);
    } 
  
    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");


    server_address_size = sizeof(server_address);
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) { 
        perror("Connection Failed\n"); 
        exit(1);
    }
    
    while(1){
        printf("> ");
        memset(buffer, '\0', BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
        
        if (write(client_socket, buffer, strlen(buffer)) < 0) {
            perror("write failed\n");
            exit(1);
        }
    
        memset(buffer, '\0', BUFFER_SIZE);
        read(client_socket, buffer, BUFFER_SIZE);

        printf("%s", buffer);
        printf("\n");
        
    }
    
//     memset(buffer, '\0', BUFFER_SIZE);
//     strcpy(buffer, "Hello server. This is the client speaking!\n");
    
//     if (write(client_socket, buffer, strlen(buffer)) < 0) {
//          perror("write failed\n");
//     }
    
//     memset(buffer, '\0', BUFFER_SIZE);
//     read(client_socket, buffer, BUFFER_SIZE);

//     printf("%s", buffer);

  return 0;
}

