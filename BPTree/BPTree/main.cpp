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

	std::cout << "请问您需要进行什么操作" << std::endl;
	std::cout << "1.从本地读取数据    2.随机插入数据    3.顺序插入数据" << std::endl;
	while (true)
	{
		std::cin >> y;
		if (y == 1)
		{
			//从data.txt中读取二进制数据
			bptree->loadFromFile("data.txt");
			std::cout << "读取数据完成" << std::endl;
			break;
		}
		else if (y == 2)
		{
			std::vector<int> numbers(totalNumbers);
			for (int i = 0; i < totalNumbers; i++)
			{
				numbers[i] = i ;
			}

			//洗牌算法生成一个随机的数组，之后插入数据
			for (int i = totalNumbers-1; i >= 0; i--)
			{
				randomNumber = distribution(generator);
				std::swap(numbers[i], numbers[randomNumber]);
			}
			for (int number : numbers)
			{
				bptree->insert(number);
			}
			std::cout << "B+树构建完成" << std::endl;
			break;
		}
		else if (y == 3)
		{
			//顺序插入数据
			for (int i = 0; i < totalNumbers; i++)
			{
				bptree->insert(i);
			}
			std::cout << "B+树构建完成" << std::endl;
			break;
		}
		else
		{
			//输入错误检测
			std::cout << "请输入1或者2" << std::endl;
		}
	}
	
	// 查询数据
	while (y != 0)
	{
		std::cout << "请输入要查询的数" << std::endl;
		std::cin >> x;
		bptree->search(x);
		std::cout << "还要继续查询吗" << std::endl;
		std::cout << "1.YES    0.NO" << std::endl;
		std::cin >> y;
	}


	std::cout << "需要存储本次数据吗" << std::endl;
	std::cout << "1.YES    0.NO" << std::endl;
	std::cin >> y;
	if(y==1)
	{ 
		//存储数据
		bptree->storeToFile("data.txt");
		std::cout << "存储数据成功" << std::endl;
	}
	system("pause");
}