#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Stock{
  Stock(){};
  Stock(std::string _ticker, int _numStocks, float _purchasePrice, float _spotPrice){
    ticker = _ticker;
    numStocks = _numStocks;
    purchasePrice = _purchasePrice;
    spotPrice = _spotPrice;
  }
  std::string ticker;
  int numStocks;
  float purchasePrice;
  float spotPrice;
};

struct UserNode{
  UserNode(){}; // default constructor
  UserNode(std::string _username, std::string _password, float _balance):username(_username),
     password(_password), balance(_balance){}; // parameterized constructor

   std::string username;
   std::string password;
   float balance = 0;
   std::vector <Stock> stocks;

   UserNode *parent = nullptr;
   UserNode *leftChild = nullptr;
   UserNode *rightChild = nullptr;

   void displayAccountInfo();
   void addUserStock(std::string, int, float, float);
   bool sellStock(std::string, int);

};

class UserTree{
  public:
    UserTree();
    ~UserTree();
    void addUser(std::string, std::string, float);
    void printUsers();
    void printStocks(std::string user);
    void addStock(std::string, std::string, int, float, float); // username, ticker, number of particular stock, purchase price, spot price
    UserNode *search(std::string);

  private:
    UserNode *createNewUser(std::string, std::string, float);
    // pointer to the root node
    UserNode *root;
};
