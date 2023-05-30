#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


#include "../include/team.hpp"



class User{
    protected:
        std::string userName;
        std::string password;



    
    public:
        User(std::string _userName,std::string _passWord);
        virtual std::string getUserName();
        virtual std::string getPassWord();



};

class Admin : public User {
    public:
        Admin();  
        virtual bool isAdmin();
    private:

};

class RegularUser : public User {
    public:
        RegularUser(std::string _userName,std::string _passWord);  

    private:
        Team* fantasyTeam;
};

#endif