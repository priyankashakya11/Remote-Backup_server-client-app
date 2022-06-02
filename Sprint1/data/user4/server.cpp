//Program to create TCP server and function defination for server.h
#include<iostream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include<exception>
#include <experimental/filesystem>
#include<sys/types.h>
#include"../inc/server.h"
#include"../inc/user.h"

#define PORT 8101
#define SERVER_IP "0.0.0.0"
using namespace std::experimental::filesystem;

//Creating server socket 
Server::Server(){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Error while creating socket");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));//setting server address to 0 

    //set the server address in one line 
    servaddr = {AF_INET, htons(PORT), inet_addr(SERVER_IP)};

    //Binding server socket
    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        perror("Error while binding");
        exit(1);
    }

    //Listening to client
    if(listen(sock
fd, 10) == -1){
        perror("Error while listen to client");
      	exit(1);
    }

    //populate the users.dat file into the vector
    try
    {
    	ifstream file("../data/users.dat");
    	if(file.is_open()){
    	    string line;
    	    while(getline(file, line))
	    {
    	        stringstream ss(line);
    	        string name, password, dir;
    	        ss >> name >> password >> dir;
    	        User user(name,password);
        	    users.push_back(user);
            }
    	}	
    	else 
    	{
	    throw "Error opening file!";
    	}
    	file.close();
    }
    catch (const std::exception &e)
    {
    	cout << e.what() <<endl;
    	exit(1);
    }
    
    //show the status of the server
    cout << "Server is running on port " << PORT << endl;
}

//Function to send message to 
void Server::send_msg(const char *msg,int client_sockfd){
    if(send(client_sockfd, msg, strlen(msg), 0) == -1){
        perror("Error while sending message to client");
        exit(1);
    }
}
//Funtion to receve
 message from server
char* Server::recv_msg(int client_sockfd){
    memset(buffer, 0, sizeof(buffer));//setting buffer to zero
    if(recv(client_sockfd, buffer, sizeof(buffer), 0) == -1){
        perror("Error while recieving message from client");
        exit(1);
    }
    return buffer;
}

//Accepting client connection
int Server::accept_client(){
    len = sizeof(clientaddr);//capturing length into variable
    int clientfd = accept(sockfd, (struct sockaddr *)&clientaddr, &len);
    if(clientfd == -1){
        perror("Error while accepting client");
        exit(1);
    }
    return clientfd;
}

//Funtion to authenticate user
bool Server::authenticateUser(User auth_user){
    for(auto user : users){
        if(auth_user == user)
        return true;
    }
    return false;
}

//Function to provide full backup
void Server::fullbackup(int client_sockfd,string file){
    //create a file with the name of the file received 
    	ofstream backup_file(file);
    	if(backup_file.is_open())
	{
    	bool isNotEof 
= true;
        	// //read the file from the client and write it to the file
        	while(isNotEof)
		{
            		memset(buffer, 0, sizeof(buffer));
            		if(recv(client_sockfd, buffer, sizeof(buffer), 0) == -1)
			{
                		perror("recv");
                		exit(1);
            		}
            		isNotEof = buffer[0];
            		backup_file << buffer << endl;
        	}
        	cout << "file created" << endl;
        	backup_file.close();
    	}
	else{
		perror("Error while backup_file");
		exit(1);
	}
}
char* Server::listingfiles(string username)
{
	string path = "../data/" + username + "/";
	memset(buffer,0,sizeof(buffer));
	string contents;
	for(const directory_entry& entry : recursive_directory_iterator(path))
		contents += entry.path().string() + "\n";
	strcpy(buffer,contents.c_str());
	return buffer;
}



