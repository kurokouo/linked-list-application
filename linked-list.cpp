#include <iostream>

struct node {
  int data;
  node *next;
};

node *build();

void print_list(node *L) {
  std::cout << " *=> i";
  while (L->next != nullptr) {
    std::cout << L->data << " => ";
    L = L->next;
  }
  std::cout << "NULL" << std::endl;
}

void push_front(node *&H, int value) {
  node node *nn = new node;
  push_front(L, 0);
}
int main() {

  node *L = build();
  print_list(L);
}

node *build() {
  node *n1 = new node;
  n1->data = 1;
  n1->next = nullptr;

  node *n2 = new node;
  n2->data = 1;
  n2->next = nullptr;

  node *n3 = new node;
  n3->data = 1;
  n3->next = nullptr;

  n1->next = n2;
  n2->next = n3;
  return n1;
}
