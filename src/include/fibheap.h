#ifndef FIBHEAP_H
#define FIBHEAP_H

#include <cstdint>

class FibHeapEntry {
 public:
  friend class FibHeap;
  FibHeapEntry(void *value, uint32_t key);
  void *getValue() {
    return value;
  }
  void setKey(uint32_t k) {
    key = k;
  }

 private:
  void insertInList(FibHeapEntry *value) {
    FibHeapEntry *tmp = value->left;

    value->left = this;
    tmp->right = right;

    right->left = tmp;
    right = value;
  }

  void link(FibHeapEntry *nparent) {
    /* Remove y from the rootlist */
    left->right = right;
    right->left = left;
    parent = nparent;

    /* Add y as x's child */
    if (nparent->child == nullptr) {
      nparent->child = this;
      left = this;
      right = this;
    } else {
      right = nparent->child->right;
      left = nparent->child;
      nparent->child->right->left = this;
      nparent->child->right = this;
    }

    /* Increase the degree of x */
    nparent->degree++;

    mark = 0;
  }

  void *value;
  FibHeapEntry *left;
  FibHeapEntry *right;
  FibHeapEntry *parent;
  FibHeapEntry *child;

  uint32_t degree: 31;
  uint32_t mark: 1;
  uint32_t key;
};

class FibHeap {
 public:
  FibHeap();
  ~FibHeap();
  FibHeapEntry *top() {
    return min;
  }
  FibHeapEntry *pop();
  void push(FibHeapEntry *value);
  void decreaseKey(FibHeapEntry *x, uint32_t k);

 private:
  void consolidate();
  void cut(FibHeapEntry *x, FibHeapEntry *y);
  void cascading_cut(FibHeapEntry *x);
  FibHeapEntry *min;
  uint32_t n;
};

#endif
