#include<iostream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include<sys/types.h>
#include"../include/server.h"
#include"../include/user.h"

#define PORT 8888
#define SERVER_IP "0.0.0.0"
Server::Server(){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("socket");
        exit(1);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    //set the server address in one line 
    servaddr = {AF_INET, htons(PORT), inet_addr(SERVER_IP)};
    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        perror("bind");
        exit(1);
    }
    if(listen(sockfd, 10) == -1){
        perror("listen");
        exit(1);
    }
    //populate the users.dat file into the vector
    ifstream file("../data/users.dat");
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            stringstream ss(line);
            string name, password, dir;
  
          ss >> name >> password >> dir;
            User user(name,password);
            users.push_back(user);
        }
        file.close();
    }
    //show the status of the server
    cout << "Server is running on port " << PORT << endl;
}

void Server::send_msg(const char *msg,int client_sockfd){
    if(send(client_sockfd, msg, strlen(msg), 0) == -1){
        perror("send");
        exit(1);
    }
}

char* Server::recv_msg(int client_sockfd){
    memset(buffer, 0, sizeof(buffer));
    if(recv(client_sockfd, buffer, sizeof(buffer), 0) == -1){
        perror("recv");
        exit(1);
    }
    return buffer;
}

int Server::accept_client(){
    len = sizeof(clientaddr);
    int clientfd = accept(sockfd, (struct sockaddr *)&clientaddr, &len);
    if(clientfd == -1){
        perror("accept");
        exit(1);
    }
    return clientfd;
}

bool Server::authenticateUser(User auth_user){
    for(auto user : users){
        if(auth_user == user)
        return true;
    }
    return false;
}

void Server::ful
lbackup(int client_sockfd,string file){
    //create a file with the name of the file received 
    bool isNotEof = true;
    ofstream backup_file(file);
    if(backup_file.is_open()){
        // //read the file from the client and write it to the file
        while(isNotEof){
            memset(buffer, 0, sizeof(buffer));
            if(recv(client_sockfd, buffer, sizeof(buffer), 0) == -1){
                perror("recv");
                exit(1);
            }
            isNotEof = buffer[0];
            backup_file << buffer << endl;
        }
        cout << "file created" << endl;
        backup_file.close();
    //     int len = 0;
    // bool isNotEnd = true;
    // char buffer[1024];
    // while(isNotEnd){
    //     //receive data from server
    //     memset(buffer, 0, sizeof(buffer));
    //     len = recv(sockfd, buffer, sizeof(buffer), 0);
    //     isNotEnd = buffer[0];
    //     //write data to file
    //     backup_file << buffer << endl;
    // }
    // backup_file.close();
    // std::c
out << "\nFile received successfully" << std::endl;
    }
    else{
        perror("backup_file");
        exit(1);
    }
}


