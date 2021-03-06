//Program to define user
#include<iostream>
#include "../inc/user.h"

User::User(string name, string password){//constructor
    this->name = name;
    this->password = password;
    this->directory = "../data/" + name + "/";
}

bool User::operator==(const User &user){
    return this->name == user.name && this->password == user.password;
}

string User::getDirectory(){
    return this->directory;
}
string User::getUsername(){
	return this->name;
}
