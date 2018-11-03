#include "Set.hpp"
#include <assert.h>

#define RED true
#define BLACK false

using key_type = Set::key_type;
using size_type = Set::size_type;
using Node = Set::Node;

struct Set::Node
{
	Node *left_, *right_;
	bool color_;
	key_type key_;
	Node(key_type key, bool color):left_(NULL), right_(NULL)
	{
		color_ = color;
		key_ = key;
	}
};

Node *Set::RotateLeft(Node *h)
{
	Node *x = h->right_;
	h->right_ = x->left_;
	x->left_ = h;
	x->color_ = h->color_;
	h->color_ = RED;
	return x;
}

Node *Set::RotateRight(Node *h)
{
	Node *x = h->left_;
	h->left_ = x->right_;
	x->right_ = h;
	x->color_ = h->color_;
	h->color_ = RED;
	return x;
}

void Set::ColorFlip(Node *h)
{
	h->color_ = !h->color_;
	if(h->left_)
	{
		h->left_->color_ = !h->left_->color_;
	}
	if(h->right_)
	{
		h->right_->color_ = !h->right_->color_;
	}
}

bool Set::IsRed(Node *h)
{
	if(h)
	{
		return h->color_ == RED;
	}
	return false;
}

Node* Set::NewNode(const key_type key)
{
	return new Node(key, RED);
}

Node* Set::Insert(Node *h, const key_type key)
{
	if(h == NULL)
	{
		return NewNode(key);
	}
	if(IsRed(h->left_) && IsRed(h->right_))
	{
		ColorFlip(h);
	}

	if(key == h->key_)
	{
		flag_ = false;
	}
	else if(key < h->key_)
	{
		h->left_ = Insert(h->left_, key);
	}
	else// if(key > h->key_)
	{
		h->right_ = Insert(h->right_, key);
	}
	/*
	if(IsRed(h->right_))
	{
		h = RotateLeft(h);
	}
	if(IsRed(h->left_) && h->left_ && IsRed(h->left_->left_))
	{
		h = RotateRight(h);
	}
	if(IsRed(h->left_) && IsRed(h->right_))
	{
		ColorFlip(h);
	}
	*/
	return FixUp(h);
}

Node *Set::Search(const key_type key)
{
	Node *current = root_;
	while(current)
	{
		if(key == current->key_)
		{
			return current;
		}
		else if(key < current->key_)
		{
			current = current->left_;
		}
		else// if(key > current->key_)
		{
			current = current->right_;
		}
	}
	return NULL;
}

Node *Set::FixUp(Node *h)
{
	if(IsRed(h->right_))
	{
		h = RotateLeft(h);
	}
	if(IsRed(h->left_) && h->left_ && IsRed(h->left_->left_))
	{
		h = RotateRight(h);
	}
	if(IsRed(h->left_) && IsRed(h->right_))
	{
		ColorFlip(h);
	}
	return h;
}

Node *Set::MoveRedLeft(Node *h)
{
	ColorFlip(h);
	if(h->right_ && IsRed(h->right_->left_))
	{
		h->right_ = RotateRight(h->right_);
		h = RotateLeft(h);
		ColorFlip(h);
	}
	return h;
}

Node *Set::DeleteMin(Node *h)
{
	if(h->left_ == NULL)
	{
		delete h;
		return NULL;
	}
	if(!IsRed(h->left_) && h->left_ && !IsRed(h->left_->left_))
	{
		h = MoveRedLeft(h);
	}
	h->left_ = DeleteMin(h->left_);
	return FixUp(h);
}

Node *Set::FindMin(Node *h)
{
	if(h == NULL)
	{
		return NULL;
	}
	while(h->left_)
	{
		h = h->left_;
	}
	return h;
}

Node *Set::Delete(Node *h, const key_type &key)
{
	if(h == NULL)
	{
		flag_ = false;
		return NULL;
	}
	if(key < h->key_)
	{
		if(h->left_ == NULL)
		{
			flag_ = false;
			return h;
		}
		if(!IsRed(h->left_) && h->left_ && !IsRed(h->left_->left_))
		{
			h = MoveRedLeft(h);
		}
		h->left_ = Delete(h->left_, key);
	}
	else
	{
		if(IsRed(h->left_))
		{
			h = RotateRight(h);
		}
		/*
		if(key == h->key_)
		{
			Node *right_min = FindMin(h->right_);
			if(right_min)
			{
				h->key_ = right_min->key_;
				h->right_ = DeleteMin(h->right_);
			}
			else
			{
				delete h;
				return NULL;
			}
		}
		else
		{
			if(!IsRed(h->right_) && h->right_ && !IsRed(h->right_->left_))
			{
				MoveRedLeft(h);
			}
			h->right_ = Delete(h->right_, key);
		}*/
		if(key == h->key_ && h->right_ == NULL)
		{
			delete h;
			return NULL;
		}
		if(!IsRed(h->right_) && h->right_ && !IsRed(h->right_->left_))
		{
			MoveRedLeft(h);
		}
		if(key == h->key_)
		{
			Node *right_min = FindMin(h->right_);
			if(right_min)
			{
				h->key_ = right_min->key_;
				h->right_ = DeleteMin(h->right_);
			}
			else
			{
				delete h;
				return NULL;
			}
		}
		else
		{
			h->right_ = Delete(h->right_, key);
		}
	}
	return FixUp(h);
}

void Set::DeleteAll(Node *h)
{
	if(h == NULL)
	{
		return;
	}
	DeleteAll(h->left_);
	DeleteAll(h->right_);
	delete h;
}

bool Set::empty() const
{
	return size_ == 0;
}

size_type Set::size() const
{
	return size_;
}

void Set::clear()
{
	DeleteAll(root_);
	root_ = NULL;
	size_ = 0;
}

void Set::insert(const key_type &key)
{
	flag_ = true;
	root_ = Insert(root_, key);
	if(root_)
	{
		root_->color_ = BLACK;
	}
	if(flag_)
	{
		size_++;
	}
}

size_type Set::erase(const key_type &key)
{
	flag_ = true;
	root_ = Delete(root_, key);
	if(root_)
	{
		root_->color_ = BLACK;
	}
	if(flag_)
	{
		size_--;
	}
	return flag_? 1 : 0;
}

size_type Set::count(const key_type &key)
{
	return Search(key) ? 1 : 0;
}

Set::Set()
{
	root_ = NULL;
	size_ = 0;
}

Set::~Set()
{
	DeleteAll(root_);
}


#undef RED
#undef BLACK

