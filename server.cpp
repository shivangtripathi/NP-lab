#include<unistd.h> /*Access to POSIX operating system APIs */
#include<iostream>
#include<string.h>
#include<sys/socket.h> /* provides socket function and generic socket addr */
#include<netinet/in.h> /* contains definition for IP family*/
#define PORT 8080
#define SIZE 6500

int main(){

    int server_fd,new_socket,val_read;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[100] = {0};

    //creating socket file descriptor
    if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("Socket Failed"); //perror is posix error
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //binding
    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0)
    {
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }

    // puts the server socket in passive mode
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd,
                  (struct sockaddr*)&address,
                  (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
  
    // read string send by client
    valread = read(new_socket, str,
                   sizeof(str));
    int i, j, temp;
    int l = strlen(str);
  
    printf("\nString sent by client:%s\n", str);
  
    // loop to reverse the string
    for (i = 0, j = l - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
  
    // send reversed string to client
    // by send system call
    send(new_socket, str, sizeof(str), 0);
    printf("\nModified string sent to client\n");

    return 0;
}