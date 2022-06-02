#ifndef CLIENT_H
#define CLIENT_H

#include<netinet/in.h>
#include<string>
#define MAX 1024
using namespace std;
class Client{
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAX] = "NULL";
    public:
    Client();
    void send_msg(const char* msg);
    char *recv_msg();
    void close_client();
    void full_backup(string file);
    int get_sockfd();
};

#endif


