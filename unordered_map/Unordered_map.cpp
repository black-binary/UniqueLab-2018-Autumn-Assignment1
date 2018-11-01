#include "Unordered_map.hpp"

using size_type = Unordered_map::size_type;
using key_type = Unordered_map::key_type;
using key_type = Unordered_map::key_type;

struct Unordered_map::Element
{
	Element* next_ = NULL;
	value_type item_;
	Element(const value_type &value):item_(value){}
};

struct Unordered_map::Header
{
	Element *list_ = NULL;
};

size_type Unordered_map::Hash(const key_type &key)
{
	register unsigned int hash_value = 0;
	for(int i = 0; i < key.size(); i++)
	{
		hash_value = hash_value * 65599 + key[i];
	}
	return hash_value % table_size_;
}

Unordered_map::Unordered_map()
{
	table_ = new Header[233]();
	table_size_ = 233;
	size_ = 0;
}

bool Unordered_map::empty() const
{
	return size() == 0;
}

size_type Unordered_map::size() const
{
	return size_;
}

void Unordered_map::insert(const value_type& value)
{
	CheckAndExpand();
	unsigned int hash = Hash(value.first);
	Element *element = new Element(value);
	erase(value.first);
	Insert(element);
	/*
	Element *current = table_[hash].list_;
	Element *prev = NULL;
	while(current)
	{
		if(current->item_.first == value.first)
		{
			current->item_.second = value.second;
			return;
		}
		prev = current;
		current = current->next_;
	}
	if(prev)
	{
		prev->next_ = current;
	}
	else
	{
		table_[hash].list_ = element;
	}
	size_++;
	*/
}

void Unordered_map::Insert(Element *element) //insert into the empty table
{
	unsigned int hash = Hash(element->item_.first);
	element->next_ = NULL;
	Element *current = table_[hash].list_;
	table_[hash].list_=element;
	if(current)
	{
		element->next_ = current;
	}
}

T& Unordered_map::at(const Key& key)
{
	unsigned int hash = Hash(key);
	Element *current = table_[hash].list_;
	while(current)
	{
		if(current->item_.first == key)
		{
			return current->item_.second;
		}
		current = current->next_;
	}
	throw "Nothing here, what the fxxk r u doing??";
}

void Unordered_map::erase(const key_type &key)
{
	unsigned int hash = Hash(key);
	Element *current = table_[hash].list_;
	Element *prev = NULL;
	while(current)
	{
		if(current->item_.first == key)
		{
			if(prev)
			{
				prev->next_ = current->next_;
			}
			delete current;
			return;
		}
		prev = current;
		current = current->next_;
	}
	//throw "Nothing here, what the fxxk r u doing??";
}

void Unordered_map::CheckAndExpand()
{
	if(table_size_ < size() * 2)
	{
		std::vector<Element*> elements;
		for(unsigned int i = 0;i < table_size_; i++)
		{
			Element *current = table_[i].list_;
			while(current)
			{
				elements.push_back(current);
				current = current->next_;
			}
		}
		delete[] table_;
		table_size_ *= 2;
		table_ = new Header[table_size_];
		for(int i = 0; i < elements.size(); i++)
		{
			Insert(elements[i]);
		}
	}
}

