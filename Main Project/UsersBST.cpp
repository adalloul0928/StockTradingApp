#include "UsersBST.hpp"

UserTree::UserTree(){
  root = NULL;
}

// helper function for the deconstructor
void deleteTree(UserNode* tmp){
  if (tmp == NULL) return;

  deleteTree(tmp->leftChild);
  deleteTree(tmp->rightChild);

  delete(tmp);
}


UserTree::~UserTree(){
  deleteTree(root);
  root = NULL;
}


UserNode * UserTree::createNewUser(std::string _username, std::string _password){
  UserNode *newUser = new UserNode(_username, _password);
  return newUser;
}


void addHelper(UserNode *root, UserNode *newUser){
  if (root->username > newUser->username){
    if (!root->leftChild){
      root->leftChild = newUser;
    }
    else{
      addHelper(root->leftChild, newUser);
    }
  }
  else{
    if(!root->rightChild){
      root->rightChild = newUser;
    }
    else{
      addHelper(root->rightChild, newUser);
    }
  }
}


void UserTree::addUser(std::string _username, std::string _password){
  UserNode *newUser = createNewUser(_username, _password);
  if (root == NULL){
    root = newUser;
  }
  else{
    addHelper(root, newUser);
  }
}


void UserTree::findUser(){

}


UserNode *UserTree::search(){

}


void printHelper(UserNode *root){
  if (root == NULL) return;

  printHelper(root->leftChild);
  std::cout << root->username << std::endl;
  printHelper(root->rightChild);
}


void UserTree::printUsers(){
  if (root == NULL){
    std::cout << "There are no users" << std::endl;
  }
  else{
    printHelper(root);
  }
}
