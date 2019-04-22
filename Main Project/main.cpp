#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "UsersBST.hpp"

// cd github/Final-Project/"Main Project"
// g++ main.cpp UsersBST.cpp -o main

void read_users(UserTree &allUsers, std::vector <std::string> &);
void writeFile(UserTree &allUsers, std::vector <std::string>);
UserNode* loginMenu(UserTree &allUsers, std::vector <std::string> &);
void mainMenu(UserNode &mainUser);
void mainMenuDisplay();

int main() {
  system("python updateTextFile.py");
  UserTree allUsers;
  std::vector <std::string> userList;
  read_users(allUsers, userList);

  UserNode *mainUser;
  mainUser = loginMenu(allUsers, userList);
  mainMenu(*mainUser);

  writeFile(allUsers, userList);

  //allUsers.printUsers();
  //allUsers.printStocks(mainUser->username);
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


// login menu for users or to create a new account
UserNode* loginMenu(UserTree &allUsers, std::vector <std::string> &userList){
  std::string userChoice;
  std::string username;
  std::string password;
  float balance = 1000;
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
        std::cout << "Welcome " << username << std::endl;
        return allUsers.search(username);
      }
    }
  }
  else{
    std::cout << "Please enter preferred username: " << std::endl;
    getline(std::cin, username);
    std::cout << "Please enter preferred password: " << std::endl;
    getline(std::cin, password);

    allUsers.addUser(username, password, balance);
    userList.push_back(username);
    std::cout << "Welcome " << username << std::endl;
    return allUsers.search(username);
  }
}


void writeFile(UserTree &allUsers, std::vector <std::string> userList){
  std::ofstream outfile;
  outfile.open("users.txt");
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
      if (temp->stocks.size()>=1){
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

float getPrice(std::string ticker){
  std::string price;
  system(("python currentStockPrice.py " + ticker).c_str());
  std::ifstream myfile;
  myfile.open("tempFile.txt");
  if(myfile.is_open()){
    getline(myfile, price);
  }
  myfile.close();
  float floatStockPrice = stof(price);
  return floatStockPrice;
}


void mainMenuDisplay(){
  std::cout << "1. Account Details" << std::endl;
  std::cout << "2. Purchase Stock" << std::endl;
  std::cout << "3. Sell Stock" << std::endl;
  std::cout << "4. Stock Lookup" << std::endl;
  std::cout << "5. Logout" << std::endl;
}

void mainMenu(UserNode &mainUser){
  bool flag = true;
  std::string input;
  std::string ticker;
  bool foundStock;
  int numStocks;
  float price;

  while (flag){
    mainMenuDisplay();
    getline(std::cin, input);

    switch(stoi(input)){
      case 1:
        mainUser.displayAccountInfo();
        break;
      case 2:
        std::cout << "Which security would you like to purchase? Enter ticker: ";
        getline(std::cin, ticker);
        price = getPrice(ticker);
        std::cout << "How many shares would you like to purchase? ";
        getline(std::cin, input);
        numStocks = stoi(input);
        if (price*numStocks<mainUser.balance){
          mainUser.balance -= price*numStocks;
          mainUser.addUserStock(ticker, numStocks,price,price);
        }
        else{
          std::cout << "You do not have enough funds" << std::endl;
        }
        break;
      case 3:
        std::cout << "Which security would you like to sell? ";
        getline(std::cin, ticker);
        std::cout << "How many shares would you like to sell? ";
        getline(std::cin, input);
        numStocks = stoi(input);
        foundStock = mainUser.sellStock(ticker, numStocks);
        if (foundStock == false){
          std::cout << "You do not own that security or do not have enough shares" << std::endl;
        }
        break;
      case 4:
        std::cout << "Please enter the security ticker for the current spot price: " << std::endl;
        getline(std::cin, ticker);
        price = getPrice(ticker);
        std::cout << "Current spot price of " << ticker << ": " << price << std::endl;
        break;
      default:
        std::cout << mainUser.username << "has successfully logged out." << std::endl;
        flag = false;
        break;
    }
  }
}
