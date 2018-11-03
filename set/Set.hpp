#ifndef _SET_HPP
#define _SET_HPP

#include <functional>
using T = double;
using Compare = std::less<T>;

class Set {
public:
  typedef T                 key_type;
  typedef key_type&         reference;
  typedef const key_type&   const_reference;
  typedef size_t            size_type;
  typedef Compare           key_compare;

public:
  bool empty() const;
  size_type size() const;
  void clear();
  void insert(const key_type& key);
  size_type erase(const key_type& key);
  size_type count(const key_type& key);
  Set();
  ~Set();
  struct Node;

private:
  Node *root_;
  bool flag_;
  size_type size_;
  Node* RotateLeft(Node *h);
  Node* RotateRight(Node *h);
  Node* Insert(Node *h, const key_type key);
  Node* NewNode(const key_type key);
  Node *Search(const key_type key);
  Node *FixUp(Node *h);
  Node *MoveRedLeft(Node *h);
  Node *DeleteMin(Node *h);
  Node *FindMin(Node *h);
  Node *Delete(Node *h, const key_type &key);
  void DeleteAll(Node *h);
  void ColorFlip(Node *h);
  bool IsRed(Node *h);
};

#endif
