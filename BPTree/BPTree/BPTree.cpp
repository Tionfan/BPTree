#include "BPTree.h"


void BPTree::insert(int x)
{
	//Ϊ����ʱ
	if (root == NULL)
	{
		root = new Node;
		root->IS_LEAF = true;
		root->key[0] = x;
		root->parent = NULL;
		root->size = 1;
		return;
	}

	Node* current = root;
	Node* parent = nullptr;

	//��������Ѱ�Ҳ����Ҷ�ӽڵ�
	while (current->IS_LEAF == false)
	{
		for (int i = 0; i < current->size; i++)
		{
			if (x < current->key[i])
			{
				parent = current;
				current = current->ptr[i];
				break;
			}

			if (i == current->size - 1)
			{
				parent = current;
				current = current->ptr[i + 1];
				break;
			}
		}
	}

	//Ҷ�ӽڵ�δ��
	if (current->size < MAX)
	{
		//��������
		insert_normal(x, current);

		//ָ����һƬҶ�ӵ�ָ����ptr�е�sizeλ
		current->ptr[current->size] = current->ptr[current->size - 1];
		current->ptr[current->size - 1] = nullptr;
	}
	else
	{
		split(x, parent, current);
	}
}

int BPTree::insert_normal(int x, Node* current)
{
	int i = 0;

	//�ҵ�����λ��
	for (i; i < current->size; i++)
	{
		if (x < current->key[i]) 
			break;
	}

	//ѭ�����ƺ����
	for (int j = current->size; j > i; j--)
	{
		current->key[j] = current->key[j - 1];
	}
	current->key[i] = x;
	current->size++;
	return i;
}

void BPTree::split(int x, Node* parent, Node* current)
{
	//ģ������Ϊ���ѵ�״��
	insert_normal(x, current);

	//���Ѻ������Ҷ�ӵĳ�ʼ��
	Node* LLeaf = new Node;
	Node* RLeaf = new Node;
	RLeaf->IS_LEAF = LLeaf->IS_LEAF = true;
	LLeaf->size = (MAX + 1) / 2;
	RLeaf->size = MAX + 1 - (MAX + 1) / 2;

	//��������Ҷ�ӵ�����
	for (int i = 0; i < LLeaf->size; i++)
	{
		LLeaf->key[i] = current->key[i];
	}
	for (int i = 0, j = LLeaf->size; i < RLeaf->size; i++, j++)
	{
		RLeaf->key[i] = current->key[j];
	}

	//���Ҷ�ӵ�ָ��
	LLeaf->ptr[LLeaf->size] = RLeaf;
	RLeaf->ptr[RLeaf->size] = current->ptr[current->size - 1];

	//Ҷ�ӽڵ�Ϊ���ڵ�ʱ
	if (current == root)
	{
		//�����µĸ��ڵ�
		Node* newroot = new Node;
		newroot->key[0] = RLeaf->key[0];
		newroot->IS_LEAF = false;
		newroot->ptr[0] = LLeaf;
		newroot->ptr[1] = RLeaf;
		newroot->size = 1;
		root = newroot;

		//Ҷ�ӽڵ�ĸ�ָ�븳ֵ
		LLeaf->parent = RLeaf->parent = root;
	}
	else
	{
		insert_after_split(RLeaf->key[0], parent, LLeaf, RLeaf);
	}

}

void BPTree::insert_after_split(int x, Node* current, Node* LLeaf, Node* RLeaf)
{
	//�ڵ�δ�������
	if (current->size < MAX)
	{
		//�Ȳ����ֵ,֮�����ָ��
		int i = insert_normal(x, current);
		for (int j = current->size; j > i+1; j--)
		{
			current->ptr[j] = current->ptr[j - 1];
		}
		current->ptr[i] = LLeaf;
		current->ptr[i + 1] = RLeaf;
		LLeaf->parent = RLeaf->parent = current;
		return;
	}

	Node* newLNode = new Node;
	Node* newRNode = new Node;
	Node* tempNode[MAX + 2];

	//ģ������δ���ѵĽڵ�ָ��ͼ�ֵ����,�㷨�ͽڵ�δ��ʱһ��
	int i=insert_normal(x, current);
	for (int j = 0; j < MAX + 1; j++)
	{
		tempNode[j] = current->ptr[j];
	}
	for (int j = MAX + 1; j > i + 1; j--)
	{
		tempNode[j] = tempNode[j - 1];
	}
	tempNode[i] = LLeaf;
	tempNode[i + 1] = RLeaf;

	//��ʼ�����Ѻ�����ҽڵ���Ϣ
	newLNode->IS_LEAF = newRNode->IS_LEAF = false;
	newLNode->size = (MAX + 1) / 2;
	newRNode->size = MAX - (MAX + 1) / 2;

	//�����ֵ��ָ��
	for (int i = 0; i < newLNode->size; i++)
	{
		newLNode->key[i] = current->key[i];
	}
	for (int i = 0, j = newLNode->size + 1; i < newRNode->size; i++, j++)
	{
		newRNode->key[i] = current->key[j];
	}
	
	for (int i = 0; i < newLNode->size + 1; i++)
	{
		newLNode->ptr[i] = tempNode[i];
		tempNode[i]->parent = newLNode;
	}
	for (int i = 0, j = newLNode->size + 1; i < newRNode->size + 1; i++, j++)
	{
		newRNode->ptr[i] = tempNode[j];
		tempNode[j]->parent = newRNode;
	}

	//��ǰΪ���ڵ�����
	if (current == root)
	{
		//�����¸��ڵ�
		Node* newroot = new Node;
		newroot->IS_LEAF = false;
		newroot->size = 1;
		newroot->key[0] = current->key[newLNode->size];
		newroot->ptr[0] = newLNode;
		newroot->ptr[1] = newRNode;
		root = newroot;

		newLNode->parent = newRNode->parent = newroot;
	}
	else
	{
		insert_after_split(current->key[newLNode->size], current->parent, newLNode, newRNode);
	}
}

void BPTree::search(int x)
{
	Node* current = root;
	while (current->IS_LEAF == false)
	{
		for (int i = 0; i < current->size; i++)
		{
			if (x < current->key[i])
			{
				std::cout << current->key[i] << std::endl;
				current = current->ptr[i];
				break;
			}

			if (i == current->size - 1)
			{
				std::cout << current->key[i] << std::endl;
				current = current->ptr[i + 1];
				break;
			}
		}
	}
}

void BPTree::serializeNode(Node* node, std::ofstream& file)
{
	//���ڵ�ĸ�����Ա��Ϣд���ļ�
	file.write(reinterpret_cast<char*>(&node->IS_LEAF), sizeof(bool));
	file.write(reinterpret_cast<char*>(&node->size), sizeof(int));
	file.write(reinterpret_cast<char*>(node->key), sizeof(int) * node->size);

	//�ݹ�����ӽڵ�
	if (!node->IS_LEAF)
	{
		for (int i = 0; i < node->size + 1; i++)
		{
			serializeNode(node->ptr[i], file);
		}
	}
}

void BPTree::storeToFile(const std::string& filename)
{
	std::ofstream file(filename, std::ios::binary);
	if (!file)
	{
		return;
	}

	//�ݹ����л��ڵ����Ϣ
	serializeNode(root, file);

	file.close();
}

Node* BPTree::deserializeNode(std::ifstream& file)
{
	Node* node=new Node;
	//�������ڵ�ĳ�Ա��Ϣ�����ڴ�
	file.read(reinterpret_cast<char*>(&node->IS_LEAF), sizeof(bool));
	file.read(reinterpret_cast<char*>(&node->size), sizeof(int));
	file.read(reinterpret_cast<char*>(node->key), sizeof(int) * node->size);

	//�ݹ鷴���л��ڵ���Ϣ
	if (!node->IS_LEAF)
	{
		for (int i = 0; i < node->size + 1; i++)
		{
			node->ptr[i] = deserializeNode(file);
		}

	}

	return node;
}

void BPTree::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file)
	{
		return;
	}

	//�ݹ鷴���л��ڵ����Ϣ
	root = deserializeNode(file);

	file.close();
}
