//Program to define function of TCP client
#include "../inc/client.h"
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<fstream>
#include<sstream>
#include<string.h>
#include<iostream>
using namespace std;
#define PORT 8101
#define SERVER_IP "127.0.0.1"
//constructor for client class
Client::Client()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    //set the server address in one line 
    servaddr = {AF_INET, htons(PORT), inet_addr(SERVER_IP)};
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }
}

//function to get socket fd
int Client::get_sockfd()
{
    return sockfd;
}
//function to send message
void Client::send_msg(const char* msg)
{
    if(send(sockfd, msg, strlen(msg), 0) == -1)
    {
        perror("send");
        exit(1);
    }
}
//function to recv message
char* Client::recv_msg(){
    memset(buffer, 0, sizeof(buffer));
    if(recv(sockfd, buffer, sizeof(buffer), 0) == -1)
    {
        perror("recv");
        exit(1);
    }
    return buffer;
}
//function to close client
void Client::close_client()
{
    close(sockfd);
}
//function to send full backup to server
void Client::full_backup(string file)
{
   
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    int mlen = 0;
     int fp = open(file.c_str(), O_RDONLY);
     while(mlen = read(fp,buff,sizeof(buff)))
     {
         write(sockfd, buff,mlen);
         memset(buff, 0, sizeof(buff));
     }
	write(sockfd,buff,1024);
    close(fp);
}
