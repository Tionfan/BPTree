#pragma once
#include <iostream>
#define MAX 499
class Node
{
	bool IS_LEAF;
	int* key;
	int size;
	Node* parent;
	Node* ptr[MAX + 1];
	friend class BPTree;

public:
	Node() :key(new int[MAX+1]), size(0), parent(nullptr)
	{
		for (int i = 0; i < MAX + 1; i++)
		{
			ptr[i] = NULL;
		}
	}
};


