//Main function for client.cpp
#include<iostream>
#include<string.h>
#include<sstream>
#include<fstream>
#include<signal.h>
#include<unistd.h>
#include "../inc/client.h"

using namespace std;
//handle the SIGINT signal
int socket_fd;
void sigint_handler(int signum)
{
    send(socket_fd,"bye",strlen("bye"),0);
    close(socket_fd);
    exit(0);
}
int main()
{
    signal(SIGINT,sigint_handler);
    while(1)
    {
        Client client;//oobject of client class
        socket_fd = client.get_sockfd();
        string username, password;
        cout << "username: ";
        getline(cin, username);
        cout << "password: ";
        getline(cin, password);
        client.send_msg(("auth "+username+" "+password).c_str());
        if(string(client.recv_msg()) == "true")
	{
            cout << "login success" << endl;
	    client.send_msg(("send present working directory:"));
	    string pwd = string(client.recv_msg());
	    cout << "your present working directory:" << pwd << endl;
	}

        else
	{        
        	cout << "login failed" << endl;
        	client.close_client();
        	continue;
        }
        while(1)
	{
            string command("");            
            cout << "command: ";
            getline(cin, command);
            stringstream ss(command);
            string filename(""),subcommand("");
            ss >> subcommand >> filename;
            if(subcommand == "bye")//command to exit server
	    {
                client.send_msg(subcommand.c_str());
                client.close_client();
                exit(0);
            }
            else if(subcommand == "full")//command for fullbackup
	    {
                if(filename != "")
		{
                    cout << subcommand+" "+filename << endl;
                    client.send_msg((subcommand+" "+filename).c_str());
                    string response = client.recv_msg();
                    if(response == "received file")
                        client.full_backup(filename);
                    else
                        cout << "server response: " << response << endl;
                }
                else
                    cout << "invalid filename" << endl;
            }
	    else if(subcommand == "ls")//command for ls
            {
		    client.send_msg(subcommand.c_str());
		    string List_of_files = client.recv_msg();
		    int len = strlen(List_of_files.c_str());
		    write(1,List_of_files.c_str(),len);
		    if(len == 0)
		    {
			    write(1,"No files in that directory",26);
		    }
		    else
			    write(1,List_of_files.c_str(),len);
	    }

	   else
                cout << "invalid command" << endl;    
        }
    }
}
