#include "BTree.h"
#include "funky.h"

int main() {
  srand(time(NULL));
  int n = 100000;
  int k = insertVal();
  BTree b(k);
  double sum = 0;
  int r;
  for (int i = 0; i < n; i++) {
    r = rand() % n + 1;
    auto start = std::chrono::system_clock::now();
    b.insert(r);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    sum += elapsed_seconds.count();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  }

  std::cout << "Average Time for Insert: " << sum/n << "s\n";
  sum = 0;

  for (int i = 0; i < 10; i++) {
    int r = rand() % n + 1;
    BTreeNode* x = b.search(r);
    if (x != NULL) {
      std::cout << "B-TreeNode* Keys: ";
      for (int j = 0; j < x->getNumKeys(); j++) {
        std::cout << x->getKey(j) << " ";
      }
      std::cout << "\n";
    }
  }

  for (int i = 0; i < n/10; i++) {
    r = rand() % n + 1;
    //std::cout << "Searching key: " << r << "...\n";
    auto start = std::chrono::system_clock::now();
    BTreeNode* x = b.search(r);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    sum += elapsed_seconds.count();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  }
  std::cout << "Average Time for Search: " << sum/(n/10) << "s\n";

  for (int i = 0; i < n/10; i++) {
    r = rand() % n + 1;
    //std::cout << "Deleting key: " << r << "...\n";
    auto start = std::chrono::system_clock::now();
    b.remove(r);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    sum += elapsed_seconds.count();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  }
  std::cout << "Average Time for Deletion: " << sum/(n/10) << "s\n";

  return 0;
}
