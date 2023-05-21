#include"BPTree.h"
#include"test.h"
#include<random>
#include<set>
#include<vector>
#include<algorithm>

 const int totalNumbers = 1000000;
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_int_distribution<int> distribution(0, totalNumbers-1);

std::set<int> generatedNumbers;

void main()
{
	int x,y;
	BPTree* bptree=new BPTree;
	int randomNumber;

	std::cout << "��������Ҫ����ʲô����" << std::endl;
	std::cout << "1.�ӱ��ض�ȡ����    2.�����������    3.˳���������" << std::endl;
	while (true)
	{
		std::cin >> y;
		if (y == 1)
		{
			//��data.txt�ж�ȡ����������
			bptree->loadFromFile("data.txt");
			std::cout << "��ȡ�������" << std::endl;
			break;
		}
		else if (y == 2)
		{
			std::vector<int> numbers(totalNumbers);
			for (int i = 0; i < totalNumbers; i++)
			{
				numbers[i] = i ;
			}

			//ϴ���㷨����һ����������飬֮���������
			for (int i = totalNumbers-1; i >= 0; i--)
			{
				randomNumber = distribution(generator);
				std::swap(numbers[i], numbers[randomNumber]);
			}
			for (int number : numbers)
			{
				bptree->insert(number);
			}
			std::cout << "B+���������" << std::endl;
			break;
		}
		else if (y == 3)
		{
			//˳���������
			for (int i = 0; i < totalNumbers; i++)
			{
				bptree->insert(i);
			}
			std::cout << "B+���������" << std::endl;
			break;
		}
		else
		{
			//���������
			std::cout << "������1����2" << std::endl;
		}
	}
	
	// ��ѯ����
	while (y != 0)
	{
		std::cout << "������Ҫ��ѯ����" << std::endl;
		std::cin >> x;
		bptree->search(x);
		std::cout << "��Ҫ������ѯ��" << std::endl;
		std::cout << "1.YES    0.NO" << std::endl;
		std::cin >> y;
	}


	std::cout << "��Ҫ�洢����������" << std::endl;
	std::cout << "1.YES    0.NO" << std::endl;
	std::cin >> y;
	if(y==1)
	{ 
		//�洢����
		bptree->storeToFile("data.txt");
		std::cout << "�洢���ݳɹ�" << std::endl;
	}
	system("pause");
}