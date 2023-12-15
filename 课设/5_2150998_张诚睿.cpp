#include <iostream>
using namespace std;
/**
  * 链式队列客户结点
**/
struct Node {
	int num;
	Node* next;
};
/**
  * 链式队列操作双窗口服务队列
**/
class ServiceQueue {
private:
	int TotalNum;
	Node* frontEven, * rearEven; // 偶数队头队尾
	Node* frontOdd, * rearOdd; // 奇数队头队尾
	bool EnQueue(int num, Node*& rear, Node*& front); // 入队
	bool DeQueue(int& num, Node*& front); // 出队
	void makeEmpty();
	bool GetNumber(int& number); // 获取客户编号
	bool IsEmpty(Node*& front);
	void EvenOut();
	void OddOut();
public:
	ServiceQueue() :TotalNum(0), frontEven(NULL), rearEven(NULL), frontOdd(NULL), rearOdd(NULL) {};
	~ServiceQueue() { makeEmpty(); };
	bool GetCustom(); // 获取客户信息
	void Out(); // 输出服务顺序结果
};
/**
  * 客户编号奇数返回false
  * 客户编号偶数返回true
**/
bool ServiceQueue::GetNumber(int& number)
{
	cin >> number;
	if (!cin.good()) // 输入有误
	{
		cout << "Input Wrong, cut. " << endl;
		cin.clear();
		cin.ignore(65536, '\n');
		number = -1; // 错误标记
		return true;
	}
	return (number % 2);
}
bool ServiceQueue::GetCustom()
{
	// 获取总数并检查输入正确性
	cin >> TotalNum;
	while (true)
	{
		if (!cin.good())
		{
			cout << "Input Wrong, please input again" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> TotalNum;
		}
		else if (TotalNum <= 0)
		{
			cout << "Input Wrong, please input again" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> TotalNum;
		}
		else
		{
			break;
		}
	}
	// 放入队列
	for (int i = 0; i < TotalNum; i++)
	{
		int number;
		if (GetNumber(number)) // 奇数客户
		{
			if (!EnQueue(number, rearOdd, frontOdd))
			{
				return false;
			}
		}
		else // 偶数客户
		{
			EnQueue(number, rearEven, frontEven);
		}
	}
	return true;
}
bool ServiceQueue::EnQueue(int num, Node*& rear, Node*& front)
{
	if (num < 0) // 错误编号
	{
		return false;
	}
	// 正确编号时，入队
	if (front == NULL) // 空队
	{
		Node* tmp = new Node;
		if (tmp == NULL)
		{
			cout << "Memory Wrong" << endl;
			exit(EXIT_FAILURE);
		}
		tmp->num = num;
		tmp->next = NULL;
		front = tmp;
		rear = tmp;
	}
	else // 非空队
	{
		Node* tmp = new Node;
		if (tmp == NULL)
		{
			cout << "Memory Wrong" << endl;
			exit(EXIT_FAILURE);
		}
		tmp->num = num;
		tmp->next = NULL;
		rear->next = tmp;
		rear = tmp;
	}
	return true;
}
bool ServiceQueue::DeQueue(int& num, Node*& front)
{
	if (front == NULL) // 空队
	{
		return false;
	}
	else
	{
		num = front->num;
		Node* tmp = front;
		front = front->next;
		delete tmp;
	}
	return true;
}
void ServiceQueue::makeEmpty()
{
	Node* pEven = frontEven;
	Node* pOdd = frontOdd;
	while (pEven != NULL)
	{
		Node* tmp = pEven;
		pEven = pEven->next;
		delete tmp;
	}
	while (pOdd != NULL)
	{
		Node* tmp = pOdd;
		pOdd = pOdd->next;
		delete tmp;
	}
}
bool ServiceQueue::IsEmpty(Node*& front)
{
	if (front == NULL)
		return true;
	return false;
}
void ServiceQueue::OddOut()
{
	int numOut;
	for (int i = 0; i < 2; i++) // 输出两个
	{
		if (DeQueue(numOut, frontOdd))
		{
			cout <<numOut <<" ";
		}
		else
		{
			return;
		}
	}
}
void ServiceQueue::EvenOut()
{
	int numOut;
	if (DeQueue(numOut, frontEven))
	{
		cout << numOut << " ";
	}
}
void ServiceQueue::Out()
{
	while (!IsEmpty(frontEven) && !IsEmpty(frontOdd)) // 只要都不空，就输出
	{
		OddOut();
		EvenOut();
	}
	// 有空队，另一队全部输出
	if (IsEmpty(frontEven)) // 偶数队空
	{
		if (IsEmpty(frontOdd))
		{
			return;
		}
		else
		{
			while (!IsEmpty(frontOdd))
			{
				OddOut();
			}
		}
	}
	else // 偶数队不空，奇数队必空
	{
		while (!IsEmpty(frontEven))
		{
			EvenOut();
		}
	}
}
int main()
{
	ServiceQueue Bank; // 银行服务队列
	cout << "开始输入顾客信息" << endl;
	while (!Bank.GetCustom())
	{
		cout << "Costom number wrong, reinput from the beginning" << endl;
	}
	cout << "处理顺序如下:" << endl;
	Bank.Out();
	return 0;
}