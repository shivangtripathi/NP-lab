#include<unistd.h> /*Access to POSIX operating system APIs */
#include<iostream>
#include<string.h>
#include<sys/socket.h> /* provides socket function and generic socket addr */
#include<netinet/in.h> /* contains definition for IP family*/
#define PORT 8080

int main(){

    int sock = 0,valread;
    struct sockaddr_in serv_addr;
    char str[100];
    printf("\nEnter your string : ");
    scanf("%[^\n]s",str);
    char buffer[1024] = {0};
    if((sock = socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("Failed creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr,'0',sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //connect the socket
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
    {
        printf("Connection Failed");
        return -1;
    }
    int l = strlen(str);

    //send
    send(sock,str,sizeof(str),0);

    //read string by server
    valread  = read(sock,str,l);
    printf("\n %s",str);
    return 0;
}