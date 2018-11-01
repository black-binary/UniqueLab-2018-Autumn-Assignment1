#ifdef TEST_DEBUG
#define _UNORDERD_MAP_HPP
#include <unordered_map>
#include <string>
typedef typename std::unordered_map<std::string, double> Unordered_map;
#endif // DEBUG

#ifndef _UNORDERD_MAP_HPP
#define _UNORDERD_MAP_HPP

#include <string>
#include <vector>

using Key = std::string;
using T = double;

class Unordered_map {

public:
  typedef Key             key_type;
  typedef T               mapped_type;
  typedef key_type&       reference;
  typedef const key_type& const_reference;
  typedef std::pair<const key_type, mapped_type> value_type;
  typedef size_t          size_type;

public:
  bool empty() const;
  size_type size() const;
  void clear();
  void insert(const value_type& value);
  void erase(const key_type& key);
  T& at(const Key& key);
  size_type count(const Key& key);
  Unordered_map();

private:
  struct Element;
  struct Header;
  size_type Hash(const key_type& key);
  void CheckAndExpand();
  void Insert(Element *elements);

private:
  Header *table_;
  size_type table_size_;
  unsigned int size_;
};
#endif
