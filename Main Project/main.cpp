#include <iostream>
#include <string>
#include <fstream>


void read_users();
void loginMenu();

int main() {
  loginMenu();
  read_users();


  return 0;
}


// function to read in all associated users
void read_users(){
  std::ifstream myfile;
  myfile.open("users.txt");
  if(myfile.is_open()){
    std::string input; // input that stores the next username or passsword
    std::string username; // username that will be stored in a user object (which will be stored in a BST)
    std::string password; // password that will be stored in a user object
    while(getline(myfile, input, ',')){
      username = input;
      std::cout << username << " ";

      getline(myfile, input);
      password = input;
      std::cout << password << std::endl;

    }
  }
  else{
    std::cout << "Error opening file" << std::endl;
  }
}


// login menu for users or to create a new account
void loginMenu(){
  std::string userChoice;
  std::string username;
  std::string password;
  std::cout << "Please login or create a new account" << std::endl;
  std::cout << "1) Login" << std::endl;
  std::cout << "2) Create a new account" << std::endl;
  getline(std::cin, userChoice);
  if (stoi(userChoice) == 1){
    std::cout << "Please enter username: " << std::endl;
    getline(std::cin, username);
    std::cout << "Please enter password: " << std::endl;
    getline(std::cin, password);
    std::cout << "Confirming account" << std::endl;
  }
  else{
    std::cout << "Create a new user" << std::endl;
  }
}
