#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "UsersBST.hpp"

// cd github/Final-Project/"Main Project"
// g++ main.cpp UsersBST.cpp -o main

void read_users(UserTree &allUsers, std::vector <std::string> &);
void writeFile(UserTree &allUsers, std::vector <std::string>);
UserNode* loginMenu(UserTree &allUsers);

int main() {
  UserTree allUsers;
  std::vector <std::string> userList;
  read_users(allUsers, userList);
  //allUsers.printUsers();
  UserNode *mainUser;
  mainUser = loginMenu(allUsers);
  allUsers.printStocks(mainUser->username);
  writeFile(allUsers, userList);
  return 0;
}


// function to read in all associated users
// format of text file username,password,balance,stock1ticker,numStocks owned,purchasePrice,spotprice,
void read_users(UserTree &allUsers, std::vector <std::string> &userList){
  std::ifstream myfile;
  myfile.open("users.txt");
  if(myfile.is_open()){
    std::string line; // input that stores the next username or passsword
    std::string temp; // temp variable to store ints and floats
    std::string username; // username that will be stored in a user object (which will be stored in a BST)
    std::string password; // password that will be stored in a user object
    float balance = 0;
    std::string ticker;
    float numStocks = 0;
    float purchasePrice = 0;
    float spotPrice = 0;
    while(getline(myfile, line)){
      std::stringstream ss(line);
      getline(ss,username,',');
      std::cout << "Username: " << username << std::endl;
      userList.push_back(username);
      getline(ss,password,',');
      std::cout << "Password: " << password << std::endl;
      getline(ss,temp,',');
      balance = stof(temp);
      std::cout << "Balance: " << balance << std::endl;
      allUsers.addUser(username, password, balance);
      while (getline(ss,temp,',')){
        ticker = temp;
        std::cout << "Ticker: " << ticker << std::endl;
        getline(ss,temp,',');
        numStocks = stof(temp);
        std::cout << "Num Shares: " << numStocks << std::endl;
        getline(ss,temp,',');
        purchasePrice = stof(temp);
        std::cout << "Purchase Price: " << purchasePrice << std::endl;
        getline(ss,temp,',');
        spotPrice = stof(temp);
        std::cout << "Spot Price: " << spotPrice << std::endl;
        allUsers.addStock(username, ticker, numStocks, purchasePrice, spotPrice);
      }
      std::cout << std::endl;
    }
    myfile.close();
  }
  else{
    std::cout << "Error opening file" << std::endl;
  }
}


// function to confirm that the user has an account and they have the right password
bool confirmUser(UserTree &allUsers, std::string username, std::string password){
  UserNode *user = allUsers.search(username);
  if (!user){
    std::cout << "That user does not exist in our database. Please try again." << std::endl;
    return false;
  }
  else{
    if (user->password != password){
      std::cout << "That password is incorrect. Please try again." << std::endl;
      return false;
    }
    else{
      std::cout << "Login Successful: " << username << std::endl;
      return true;
    }
  }
}


void createUser(UserTree &allUsers, std::string username, std::string password, float balance){
  std::string addData = username + ',' + password;
  std::ofstream myfile;
  myfile.open("users.txt", std::ios_base::app);
  if(myfile.is_open()){
    myfile << addData;
  }
  myfile.close();

  allUsers.addUser(username, password, balance);
}


// login menu for users or to create a new account
UserNode* loginMenu(UserTree &allUsers){
  std::string userChoice;
  std::string username;
  std::string password;
  bool flag = false; // for confirming their account login info
  std::cout << "Please login or create a new account" << std::endl;
  std::cout << "1) Login" << std::endl;
  std::cout << "2) Create a new account" << std::endl;
  getline(std::cin, userChoice);
  if (stoi(userChoice) == 1){
    while(flag == false){
      std::cout << "Please enter username: " << std::endl;
      getline(std::cin, username);
      std::cout << "Please enter password: " << std::endl;
      getline(std::cin, password);
      flag = confirmUser(allUsers, username, password);
      if (flag){
        return allUsers.search(username);
      }
    }
  }
  else{
    std::cout << "Please enter preferred username: " << std::endl;
    getline(std::cin, username);
    std::cout << "Please enter preferred password: " << std::endl;
    getline(std::cin, password);
    float balance = 1000;
    createUser(allUsers, username, password, balance);
  }
}


void writeFile(UserTree &allUsers, std::vector <std::string> userList){
  std::ofstream outfile;
  outfile.open("outputUsers.txt");
  if(outfile.is_open()){
    std::string line; // input that stores the next username or passsword
    std::string temp; // temp variable to store ints and floats
    std::string username; // username that will be stored in a user object (which will be stored in a BST)
    std::string password; // password that will be stored in a user object
    float balance = 0;
    std::string ticker;
    float numStocks = 0;
    float purchasePrice = 0;
    float spotPrice = 0;
    std::string output;
    for(int x = 0; x < userList.size(); x++){
      output = "";
      UserNode *temp = allUsers.search(userList[x]);
      username = temp->username;
      //std::cout << "Username: " << username << std::endl;
      password = temp->password;
      //std::cout << "Password: " << password << std::endl;
      balance = temp->balance;
      output = username + ',' + password + ',' + std::to_string(balance);
      if (temp->stocks.size()<1){
        output += ',';
      }
      //std::cout << "Balance: " << balance << std::endl;
      //allUsers.addUser(username, password);
      for (int i = 0; i < temp->stocks.size(); i++){
        ticker = temp->stocks[i].ticker;
        //std::cout << "Ticker: " << ticker << std::endl;
        numStocks = temp->stocks[i].numStocks;
        //std::cout << "Num Shares: " << numStocks << std::endl;
        purchasePrice = temp->stocks[i].purchasePrice;
        //std::cout << "Purchase Price: " << purchasePrice << std::endl;
        spotPrice = temp->stocks[i].spotPrice;
        //std::cout << "Spot Price: " << spotPrice << std::endl;
        output += ticker + ',' + std::to_string(numStocks) + ',' + std::to_string(purchasePrice) + ',' + std::to_string(spotPrice);
        if (i != temp->stocks.size()-1){
          output += ',';
        }
      }
      std::cout << "output: " << output << std::endl;
      outfile << output << std::endl;
    }
    outfile.close();
  }
  else{
    std::cout << "Error writing to file" << std::endl;
  }
}
