//Program to define header files for server.h
//Used to avoid mulyiple inclusion
#ifndef SERVER_H
#define SERVER_H

#include<netinet/in.h>
#include<vector>
#include "../inc/user.h"
#define MAX 1024

using namespace std;
//class declaration for server
class Server{
    int sockfd;
    struct sockaddr_in servaddr,clientaddr;
    socklen_t len;
    vector<User> users;
    char buffer[MAX] = "NULL";
    public:

    Server();
    void send_msg(const char *msg,int client_sockfd);
    char *recv_msg(int client_sockfd);
    int accept_client();
    bool authenticateUser(User user);
    void fullbackup(int client_sockfd,string file);
    char *listingfiles(string username);
};

#endif
