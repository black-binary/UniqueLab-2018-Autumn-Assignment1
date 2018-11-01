#ifdef TEST_DEBUG
#define _PRIORITY_QUEUE_HPP
#include <queue>
#include <vector>
typedef typename std::priority_queue<double, std::vector<double>> Priority_queue;
#endif // DEBUG

#ifndef _PRIORITY_QUEUE_HPP
#define _PRIORITY_QUEUE_HPP

#include <vector>
#include <functional>

//#define private: public:
using T = double;
using Container = std::vector<T>;
using Compare = std::less<T>;

class Priority_queue {
public:
  typedef Container     container_type;
  typedef typename      container_type::value_type value_type;
  typedef typename      container_type::reference reference;
  typedef typename      container_type::const_reference const_reference;
  typedef typename      container_type::size_type size_type;

public:
  const_reference top() const;
  bool empty() const;
  size_type size() const;
  void push(const value_type& value);
  void pop();

private:
  container_type heap_;
  void PercolateUp(size_type index);
  void PercolateDown(size_type index);
  size_type LeftChild(size_type index);
  size_type RightChild(size_type index);
  size_type Parent(size_type index);
  size_type CheckIndex(size_type index);
  bool IsExist(size_type index);
  value_type& GetValue(size_type index);
};

#endif
