#pragma once

#include <iostream>
#include <string>

struct UserNode{
  std::string username;
  std::string password;

  UserNode *parent = nullptr;
  UserNode *leftChild = nullptr;
  UserNode *rightChild = nullptr;

  UserNode(){}; // default constructor
  UserNode(std::string _username, std::string _password){:username(_username),
     password(_password)}; // parameterized constructor
};

class UserTree{
  public:
    UserTree();
    ~UserTree();
    void addUser();
    void findUser();

  private:
    UserNode *search();
    // pointer to the root node
    UserNode *root;
}