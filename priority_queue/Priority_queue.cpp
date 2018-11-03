#include "Priority_queue.hpp"
#include <algorithm>

using std::swap;
using std::max;
using value_type = Priority_queue::value_type;
using size_type = Priority_queue::size_type;
using const_reference = Priority_queue::const_reference;

bool Priority_queue::empty() const
{
	return heap_.empty();
}

size_type Priority_queue::size() const
{
	return heap_.size();
}

const_reference Priority_queue::top() const
{
	if(size() == 0)
	{
		throw "It's Empty, you fool";
	}
	return heap_[0];
}

size_type Priority_queue::CheckIndex(size_type index)
{
	return index >= size() ? index : -1;
}

bool Priority_queue::IsExist(size_type index)
{
	return index < size();
}

size_type Priority_queue::LeftChild(size_type index)
{
	return index * 2 + 1;
}

size_type Priority_queue::RightChild(size_type index)
{
	return index * 2 + 2;
}

size_type Priority_queue::Parent(size_type index)
{
	return (index - 1) / 2;
}

value_type& Priority_queue::GetValue(size_type index)
{
	return heap_[index];
}

void Priority_queue::PercolateUp(size_type index)
{
	value_type parent = Parent(index);
	value_type current = index;
	while(IsExist(parent) && GetValue(parent) < GetValue(current))
	{
		swap(GetValue(parent), GetValue(current));
		current = parent;
		parent = Parent(current);
	}
}

void Priority_queue::PercolateDown(size_type index)
{
	size_type left, right, current;
	current = index;
	while(1)
	{
		left = LeftChild(current);
		right = RightChild(current);
		if(IsExist(left) && IsExist(right))
		{
			size_type bigger = GetValue(left) > GetValue(right) ? left : right;
			if(GetValue(bigger) > GetValue(current))
			{
				swap(GetValue(bigger), GetValue(current));
				current = bigger;
			}
			else
			{
				break;
			}
		}
		else if(IsExist(left))
		{
			if(GetValue(left) > GetValue(current))
			{
				swap(GetValue(left), GetValue(current));
			}
			current = left;
		}
		else
		{
			break;
		}
	}
}

void Priority_queue::push(const value_type& value)
{
	heap_.push_back(value);
	PercolateUp(size() - 1);
}

void Priority_queue::pop()
{
	if(empty())
	{
		throw "It's Empty, you fool";
	}
	value_type last = GetValue(size() - 1);
	GetValue(0) = last;
	heap_.pop_back();
	PercolateDown(0);
}
