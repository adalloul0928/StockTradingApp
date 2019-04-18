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


UserNode * UserTree::createNewUser(std::string _username, std::string _password, float _balance){
  UserNode *newUser = new UserNode(_username, _password, _balance);
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


void UserTree::addUser(std::string _username, std::string _password, float _balance){
  UserNode *newUser = createNewUser(_username, _password, _balance);
  if (root == NULL){
    root = newUser;
  }
  else{
    addHelper(root, newUser);
  }
}


UserNode* findUser(UserNode *root, std::string _username){
  if (!root) return NULL;
  if (root->username == _username){
    return root;
  }
  else if (root->username > _username){
    return findUser(root->leftChild, _username);
  }
  else{
    return findUser(root->rightChild, _username);
  }
}


UserNode *UserTree::search(std::string _username){
  if (!root) return NULL;
  UserNode *user = findUser(root, _username);
  return user;
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


void UserTree::addStock(std::string username, std::string ticker, int numStocks, float purchasePrice, float spotPrice){
  UserNode *tempUser = search(username);
  Stock tempStock(ticker, numStocks, purchasePrice, spotPrice);
  tempUser->stocks.push_back(tempStock);
}


void UserTree::printStocks(std::string user){
  UserNode *tempUser = search(user);
  Stock tempStock;
  std::cout << "---------------------USER SUMMARY---------------------" << std::endl << std::endl;
  for (int x = 0; x < tempUser->stocks.size(); x++){
    tempStock = tempUser->stocks[x];
    std::cout << "Ticker: " << tempStock.ticker << std::endl;
    std::cout << "Number of Stock: " << tempStock.numStocks << std::endl;
    std::cout << "Purchase Price: " << tempStock.purchasePrice << std::endl;
    std::cout << "Spot Price: " << tempStock.spotPrice << std::endl << std::endl;
  }
}
