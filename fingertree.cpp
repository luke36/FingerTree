#include <ctime>
#include <iostream>

template <typename T> class FingerTree {
private:
  struct node {
    node(T *val) : val(val) {}
    node(int n) : nchild(n) {}
    int nchild;
    node *child[3];
    T *val;
  };

  struct level {
    level(int n1, int n2)
        : next(nullptr), root(nullptr), ndigitl(n1), ndigitr(n2) {}
    level *next;
    node *root;
    node *digitl[4];
    int ndigitl;
    node *digitr[4];
    int ndigitr;
  };

  level *bottom;

  void push_front_aux(level *l, node *n) {
    if (l->root != nullptr) {
      l->next = new level(0, 0);
      l->digitl[0] = n;
      l->digitr[0] = l->root;
      l->ndigitl = l->ndigitr = 1;
      l->root = nullptr;
    } else if (l->next == nullptr)
      l->root = n;
    else if (l->ndigitl == 4) {
      node *nn = new node(3);
      nn->child[0] = l->digitl[2];
      nn->child[1] = l->digitl[1];
      nn->child[2] = l->digitl[0];
      l->digitl[0] = l->digitl[3];
      l->digitl[1] = n;
      l->ndigitl = 2;
      push_front_aux(l->next, nn);
    } else {
      l->digitl[l->ndigitl++] = n;
    }
  }

  void push_back_aux(level *l, node *n) {
    if (l->root != nullptr) {
      l->next = new level(0, 0);
      l->digitl[0] = l->root;
      l->digitr[0] = n;
      l->ndigitl = l->ndigitr = 1;
      l->root = nullptr;
    } else if (l->next == nullptr)
      l->root = n;
    else if (l->ndigitr == 4) {
      node *nn = new node(3);
      nn->child[0] = l->digitr[0];
      nn->child[1] = l->digitr[1];
      nn->child[2] = l->digitr[2];
      l->digitr[0] = l->digitr[3];
      l->digitr[1] = n;
      l->ndigitr = 2;
      push_back_aux(l->next, nn);
    } else {
      l->digitr[l->ndigitr++] = n;
    }
  }

  node *front_aux(level *l) {
    if (l->root != nullptr)
      return l->root;
    else
      return l->digitl[l->ndigitl - 1];
  }

  void deepl(level *l) {
    if (l->ndigitl == 0) {
      if (l->next->next == nullptr && l->next->root == nullptr) {
        l->next = nullptr;
        int n = l->ndigitr;
        l->ndigitr = 0;
        node *temp[4];
        for (int i = 0; i < n; i++)
          temp[i] = l->digitr[i];
        for (int i = n - 1; i >= 0; i--)
          push_front_aux(l, temp[i]);
      } else {
        node *p = pop_front_aux(l->next);
        for (int i = p->nchild - 1; i >= 0; i--) {
          l->digitl[l->ndigitl++] = p->child[i];
        }
      }
    }
  }

  node *pop_front_aux(level *l) {
    node *p = front_aux(l);
    if (l->root != nullptr) {
      l->root = nullptr;
    } else {
      l->ndigitl--;
      deepl(l);
    }
    return p;
  }

public:
  FingerTree() : bottom(new level(0, 0)) {}

  void push_front(T &val) {
    T *p = new T(val);
    node *n = new node(p);
    push_front_aux(bottom, n);
  }

  void push_back(T &val) {
    T *p = new T(val);
    node *n = new node(p);
    push_back_aux(bottom, n);
  }

  T &front() { return *(front_aux(bottom)->val); }

  void pop_front() { pop_front_aux(bottom); }
};

int main() {
  FingerTree<int> t;

  auto s = clock();
  for (int i = 0; i < 1000000; i++)
    t.push_front(i);
  for (int i = 0; i < 1000000; i++)
    t.push_back(i);
  for (int i = 0; i < 1000000; i++)
    t.pop_front();
  for (int i = 0; i < 1000000; i++)
    t.push_front(i);
  for (int i = 0; i < 1000000; i++)
    t.push_back(i);
  for (int i = 0; i < 1000000; i++)
    t.pop_front();
  std::cout << static_cast<double>(clock() - s) / CLOCKS_PER_SEC << std::endl;
}
