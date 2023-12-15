#include <iostream>
using namespace std;

struct Node {
	int length;
	Node* next;
};
class PriorityWoodSolution {
private:
	Node* head; // ������Ԫ���
	int cost;
	int Num; // ľͷ����
	void MakeEmpty();
	void InitQueue(int* LengthTmp);
	bool IsEmpty() { return !bool(head); };
public:
	PriorityWoodSolution() :head(NULL), cost(0), Num(0) {};
	~PriorityWoodSolution() { MakeEmpty(); };
	void Init();
	
	void Solve();
};
void PriorityWoodSolution::MakeEmpty()
{
	Node* pwork = head, *prev = head;
	while (pwork != NULL)
	{
		prev = pwork;
		pwork = pwork->next;
		delete prev;
	}
}
void PriorityWoodSolution::Init()
{
	cout << "������ľͷ����: ";
	/* ��������� */
	while (true)
	{
		cin >> Num;
		if (!cin.good())
		{
			cout << "������������������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (Num <= 0)
		{
			cout << "������������������������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (Num <= 2)
		{
			cout << "����ľͷ���ڲ���Ҫ���Լ��㣬���������2������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
		{
			break;
		}
	}
	int* LengthTmp = new(nothrow) int[Num]; // ����һ����ʱ�������������
	if (LengthTmp == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "������ÿ��ľͷ����" << endl;
	for (int i = 0; i < Num;)
	{
		cin >> LengthTmp[i];
		if (!cin.good())
		{
			cout << "����������ӵ�"<<i+1<<"��ľͷ������������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (Num <= 0)
		{
			cout << "����������������ӵ�" << i + 1 << "��ľͷ������������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
		{
			i++;
		}
	}
	InitQueue(LengthTmp);
}
void PriorityWoodSolution::InitQueue(int* LengthTmp)
{ // ��Num�涨���鳤�ȣ��ʲ��ص���Խ��
	Node* now = new Node;
	if (now == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	head = now;
	now->length = -1; // ��Ӱ�����ȼ�����
	now->next = NULL;
	for (int i = 0; i < Num; i++) // 
	{
		now = new Node;
		if (now == NULL)
		{
			cout << "No Memory" << endl;
			exit(EXIT_FAILURE);
		}
		now->length = LengthTmp[i];
		now->next = NULL;
		Node* tmp = head;
		while (tmp->next != NULL && now->length > tmp->next->length)
		{
			tmp = tmp->next; // �½ڵ�ȵ�ǰ�ڵ�󣬾������ң�ֱ���ҵ���β���߱ȵ�ǰ�ڵ�С�ڵ���
		}
		/* ������tmp�� */
		now->next = tmp->next;
		tmp->next = now;
	}
}
void PriorityWoodSolution::Solve()
{
	int NodeNum = Num; // �������ý�����
	while (NodeNum > 2)
	{
		cost += head->next->length;
		cost += head->next->next->length;
		// ����ü۸�
		Node* New = new Node;
		New->length = head->next->length + head->next->next->length; 
		// ������С��ľͷ�ϵ�һ��
		Node* tmp = head->next; // ��¼��һ���ڵ�
		// ȥ��ǰ�����ڵ�
		head->next = head->next->next->next; 
		delete tmp->next;
		delete tmp;
		tmp = head;
		while (tmp->next != NULL && New->length > tmp->next->length)
		{
			tmp = tmp->next; // �½ڵ�ȵ�ǰ�ڵ�󣬾������ң�ֱ���ҵ���β���߱ȵ�ǰ�ڵ�С�ڵ���
		}
		/* ������tmp�� */
		New->next = tmp->next;
		tmp->next = New;
		NodeNum--;
	}
	cost += head->next->length;
	cost += head->next->next->length;
	cout << "�ܼ�Ϊ:" << cost << endl;
}
int main()
{
	PriorityWoodSolution Woods;
	Woods.Init();
	Woods.Solve();
	return 0;
}