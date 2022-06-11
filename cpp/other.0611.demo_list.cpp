
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Node {
  Node(int v) : val(v), next(nullptr) {}
  int val;
  Node* next;
};

void PrintList(Node* root) {
  while (root) {
    cout << root->val << " ";
    root = root->next;
  }
}

int main(int argc, char* argv[]) {
  Node *a = new Node(0), *b = new Node(1), *c = new Node(2);
  a->next = b;
  b->next = c;
  PrintList(a);

  delete a;
  delete b;
  delete c;
  cout << endl;
  return 0;
}

