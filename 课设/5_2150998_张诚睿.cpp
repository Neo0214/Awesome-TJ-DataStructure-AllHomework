#include <iostream>
using namespace std;
/**
  * ��ʽ���пͻ����
**/
struct Node {
	int num;
	Node* next;
};
/**
  * ��ʽ���в���˫���ڷ������
**/
class ServiceQueue {
private:
	int TotalNum;
	Node* frontEven, * rearEven; // ż����ͷ��β
	Node* frontOdd, * rearOdd; // ������ͷ��β
	bool EnQueue(int num, Node*& rear, Node*& front); // ���
	bool DeQueue(int& num, Node*& front); // ����
	void makeEmpty();
	bool GetNumber(int& number); // ��ȡ�ͻ����
	bool IsEmpty(Node*& front);
	void EvenOut();
	void OddOut();
public:
	ServiceQueue() :TotalNum(0), frontEven(NULL), rearEven(NULL), frontOdd(NULL), rearOdd(NULL) {};
	~ServiceQueue() { makeEmpty(); };
	bool GetCustom(); // ��ȡ�ͻ���Ϣ
	void Out(); // �������˳����
};
/**
  * �ͻ������������false
  * �ͻ����ż������true
**/
bool ServiceQueue::GetNumber(int& number)
{
	cin >> number;
	if (!cin.good()) // ��������
	{
		cout << "Input Wrong, cut. " << endl;
		cin.clear();
		cin.ignore(65536, '\n');
		number = -1; // ������
		return true;
	}
	return (number % 2);
}
bool ServiceQueue::GetCustom()
{
	// ��ȡ���������������ȷ��
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
	// �������
	for (int i = 0; i < TotalNum; i++)
	{
		int number;
		if (GetNumber(number)) // �����ͻ�
		{
			if (!EnQueue(number, rearOdd, frontOdd))
			{
				return false;
			}
		}
		else // ż���ͻ�
		{
			EnQueue(number, rearEven, frontEven);
		}
	}
	return true;
}
bool ServiceQueue::EnQueue(int num, Node*& rear, Node*& front)
{
	if (num < 0) // ������
	{
		return false;
	}
	// ��ȷ���ʱ�����
	if (front == NULL) // �ն�
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
	else // �ǿն�
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
	if (front == NULL) // �ն�
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
	for (int i = 0; i < 2; i++) // �������
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
	while (!IsEmpty(frontEven) && !IsEmpty(frontOdd)) // ֻҪ�����գ������
	{
		OddOut();
		EvenOut();
	}
	// �пնӣ���һ��ȫ�����
	if (IsEmpty(frontEven)) // ż���ӿ�
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
	else // ż���Ӳ��գ������ӱؿ�
	{
		while (!IsEmpty(frontEven))
		{
			EvenOut();
		}
	}
}
int main()
{
	ServiceQueue Bank; // ���з������
	cout << "��ʼ����˿���Ϣ" << endl;
	while (!Bank.GetCustom())
	{
		cout << "Costom number wrong, reinput from the beginning" << endl;
	}
	cout << "����˳������:" << endl;
	Bank.Out();
	return 0;
}