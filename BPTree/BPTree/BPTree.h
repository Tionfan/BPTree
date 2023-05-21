#pragma once
#include<queue>
#include<fstream>
#include "Node.h"

class BPTree
{
	Node* root;
	int insert_normal(int x, Node* current);
	void split(int x, Node* parent, Node* current);
	void insert_after_split(int x, Node* current, Node* LLeaf, Node* RLeaf);

public:
	BPTree() :root(NULL) {};
	void insert(int x);
	void search(int x);
	void serializeNode(Node* node, std::ofstream& file);
	void storeToFile(const std::string& filename);
	Node* deserializeNode(std::ifstream& file);
	void loadFromFile(const std::string& filename);
};

