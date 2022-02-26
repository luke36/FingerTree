#include "FingerTree.h"
#include <ctime>
#include <iostream>
#include <random>

using namespace luke36;

int main() {
  FingerTree<int> t1;
  FingerTree<int> t2;

  auto s = clock();
  for (int i = 0; i < 100000; i++) {
    t2.push_back(i);
    t1.push_front(i);
  }
  t1.append(t2);
  for (int i = 0; i < 5000; i++) {
    t1.pop_back();
    t1.pop_front();
  }
  for (int i = 0; i < 80000; i++)
    std::cout << t1[i] << std::endl;
  std::cout << static_cast<double>(clock() - s) / CLOCKS_PER_SEC << std::endl;
}
