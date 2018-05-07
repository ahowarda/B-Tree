#include "funky.h"
#include "BTree.h"

int insertVal() {
  int val;
  std::cout << "Insert degree for BTree: ";
  while(!(std::cin >> val) || val <= 1) {
    std::cin.clear();
    std::cin.ignore(200,'\n');
    std::cout << "Invalid Input, enter again. Degree must be a positive integer greater than 1" << std::endl;
    std::cout << "Insert degree for BTree: ";
  }
  std::cout << std::endl;
  return val;
}
