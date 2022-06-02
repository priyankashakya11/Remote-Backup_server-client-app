//program to define header file for user.cpp
#ifndef USER_H
#define USER_H

#include<string>

using namespace std;
//class declaration for user
class User{
    string name;
    string password;
    string directory;

    public:
    //copy constructor
    User(string name, string password);
    bool operator==(const User &user);
    string getDirectory();
    string getUsername();
};
#endif
