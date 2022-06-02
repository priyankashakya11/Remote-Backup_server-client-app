//Main funnction for TCP server
#include<iostream>
#include<string.h>
#include<sstream>
#include<fstream>
#include<unistd.h>
#include<signal.h>
#include "../inc/server.h"
#include "../inc/user.h"

using namespace std;

int main()
{
    Server server;//Creating server class object
    while(1){
        int client_sockfd = server.accept_client();
	//Child process
        pid_t pid = fork();

        if(pid ==0){
            while(1){
                string request = server.recv_msg(client_sockfd);
                cout << "request received : " << request << endl;
                stringstream ss(request);
                string name,passwd,command,filename("");
                ss >> command;//Taking command from user
                User* current_user;
		//If authenticated user then login success
                if(command == "auth")
		{
                    ss >> name >> passwd;
                    User user = User(name,passwd);
                    current_user = &user;
                    if(server.authenticateUser(user))
		    {
                        cout << "login success" << endl;
                        server.send_msg("true",client_sockfd);
			server.recv_msg(client_sockfd);
			server.send_msg(("/home/cguser26/may25/mabhujani/data/"+current_user->getUsername()).c_str(),client_sockfd);
                    }
		    //If user is not authenticated
                    else
		    {
                        server.send_msg("false",client_sockfd);
                        close(client_sockfd);
                        break;
                    }
                }
		//Full backup
                else if(command == "full")
		{
                    ss >> filename;
		    filename = filename.substr(filename.find_last_of('/')+1);
                        server.send_msg("received file",client_sockfd);
                        server.fullbackup(client_sockfd,current_user->getDirectory()+filename);
                }
		//Listing the files in the directory
		else if(command =="ls")
		{
			string listbuffer = server.listingfiles(current_user->getUsername());
			server.send_msg(listbuffer.c_str(),client_sockfd);
		}

		//Quit from server
                else if(command == "bye"){
                    close(client_sockfd);
                    break;
                }
                ss.clear();
	
            }
        }
        else{
            signal(SIGCHLD,SIG_IGN);
            close(client_sockfd);//close client connection
        }
    }
}
