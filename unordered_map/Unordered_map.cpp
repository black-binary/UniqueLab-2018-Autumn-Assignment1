#include "Unordered_map.hpp"
//#define INIT_SIZE 21788233

//#ifndef TEST_DEBUG
#define INIT_SIZE 52371
using size_type = Unordered_map::size_type;
using key_type = Unordered_map::key_type;
using key_type = Unordered_map::key_type;

size_type Unordered_map::Hash(const key_type &key)
{
	register unsigned int hash= 0;
	for(int i = 0; i < key.size(); i++)
	{
		hash = key[i] + (hash << 6) + (hash << 16) - hash;
	}
	return hash % table_size_;
}

Unordered_map::Unordered_map()
{
	table_ = new list<value_type>*[INIT_SIZE];
	table_size_ = INIT_SIZE;
	size_ = 0;
	for(unsigned i = 0; i < table_size_; i++)
	{
		table_[i] = new list<value_type>;
	}
}

void Unordered_map::clear()
{
	for(unsigned i = 0;i < table_size_; i++)
	{
		table_[i]->clear();
	}
	table_size_ = INIT_SIZE;
	size_ = 0;
}

bool Unordered_map::empty() const
{
	return size_ == 0;
}

size_type Unordered_map::size() const
{
	return size_;
}

void Unordered_map::erase(const key_type &key)
{
	unsigned hash = Hash(key);
	list<value_type> *hash_list = table_[hash];
	for(list<value_type>::iterator it = hash_list->begin(); it != hash_list->end(); it++)
	{
		if(it->first == key)
		{
			hash_list->erase(it);
			size_--;
			break;
		}
	}
}

void Unordered_map::insert(const value_type& value)
{
	unsigned hash = Hash(value.first);
	erase(value.first);
	table_[hash]->insert(table_[hash]->begin(), value);
	size_++;
}

T& Unordered_map::at(const Key& key)
{
	unsigned int hash = Hash(key);
	list<value_type> *hash_list = table_[hash];
	for(list<value_type>::iterator it = hash_list->begin(); it != hash_list->end(); it++)
	{
		if(it->first == key)
		{
			return it->second;
		}
	}
	throw "What the fxxk r u looking for?";
}

size_type Unordered_map::count(const Key &key)
{
	try
	{
		at(key);
	}
	catch(const char* s)
	{
		return 0;
	}
	return 1;
}

Unordered_map::~Unordered_map()
{
	delete[] table_;
}
//#endif
