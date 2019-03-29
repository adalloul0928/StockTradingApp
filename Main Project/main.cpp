#include <iostream>
#include <string>
#include <fstream>
#include "UsersBST.hpp"


void read_users(UserTree &allUsers);
void printUsers();
void loginMenu(UserTree &allUsers);

int main() {
  UserTree allUsers;
  read_users(allUsers);
  allUsers.printUsers();
  loginMenu(allUsers);


  return 0;
}


// function to read in all associated users
void read_users(UserTree &allUsers){
  std::ifstream myfile;
  myfile.open("users.txt");
  if(myfile.is_open()){
    std::string input; // input that stores the next username or passsword
    std::string username; // username that will be stored in a user object (which will be stored in a BST)
    std::string password; // password that will be stored in a user object
    while(getline(myfile, input, ',')){
      username = input;
      //std::cout << username << " ";

      getline(myfile, input);
      password = input;
      //std::cout << password << std::endl;
      allUsers.addUser(username, password);
    }
    myfile.close();
  }
  else{
    std::cout << "Error opening file" << std::endl;
  }
}


// function to confirm that the user has an account and they have the right password
bool confirmUser(UserTree &allUsers, std::string username, std::string password){
  
}


// login menu for users or to create a new account
void loginMenu(UserTree &allUsers){
  std::string userChoice;
  std::string username;
  std::string password;
  std::bool flag = true; // for confirming their account login info
  std::cout << "Please login or create a new account" << std::endl;
  std::cout << "1) Login" << std::endl;
  std::cout << "2) Create a new account" << std::endl;
  getline(std::cin, userChoice);
  if (stoi(userChoice) == 1){
    while(flag){
      std::cout << "Please enter username: " << std::endl;
      getline(std::cin, username);
      std::cout << "Please enter password: " << std::endl;
      getline(std::cin, password);
      confirmUser(allUsers, username, password);
    }
  }
  else{
    std::cout << "Create a new user" << std::endl;
  }
}
