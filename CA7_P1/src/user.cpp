#include "../include/user.hpp"

User::User(std::string _userName,std::string _passWord){
    userName = _userName;
    password = _passWord;
}

std::string User::getUserName(){
    return userName;
}

std::string User::getPassWord(){
    return password;
}

Admin::Admin() : User("admin","12345"){

}


bool Admin::isAdmin(){
    return true;
}

RegularUser::RegularUser(std::string _userName,std::string _passWord):User(_userName, _passWord){
    
} 