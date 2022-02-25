#include "FingerTree.h"
#include <ctime>
#include <iostream>
#include <random>

using namespace luke36;

int main() {
  FingerTree<int> t1;

  auto s = clock();
  for (int i = 0; i < 1000000; i++)
    t1.push_front(i);
  for (int i = 0; i < 1000000; i++)
    t1.pop_front();
  std::cout << static_cast<double>(clock() - s) / CLOCKS_PER_SEC;
  std::cout << "" << std::endl;
  return 0;
}
