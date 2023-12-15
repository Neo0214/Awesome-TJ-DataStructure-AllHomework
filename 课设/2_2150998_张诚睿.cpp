#include <iostream>
using namespace std;

/*
����������
*/
struct NumNode {
	int Num;
	NumNode* next;
};
/*
���ֽ���������
*/
class Union {
private:
	NumNode* Ahead;
	NumNode* Bhead;
	NumNode* Output;

public:
	Union();
	~Union();
	void init(NumNode*& head);
	void output();
};
Union::Union()
{
	Ahead = NULL;
	Bhead = NULL;
	Output = NULL;
	cout << "������A��������ݣ���-1��β" << endl;
	init(Ahead);
	cout << "������B��������ݣ���-1��β" << endl;
	init(Bhead);
}
Union::~Union()
{
	NumNode* tmp = Ahead, * prev = tmp;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		delete prev;
		prev = tmp;
	}
	tmp = Bhead;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		delete prev;
		prev = tmp;
	}
	tmp = Output;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		delete prev;
		prev = tmp;
	}
}
void Union::init(NumNode*& head)
{
	NumNode* pointer = NULL; // ����ָ��
	NumNode* pointerRecord = NULL; // �ݴ�ָ��
	for (int i = 0;; i++) 
	{
		int tmp = 0;
		cin >> tmp;
		if (tmp == -1) 
		{
			break;
		}
		else 
		{
			pointer = new(nothrow) NumNode;
			if (pointer == NULL) 
			{
				cout << "No Memory" << endl;
				exit(EXIT_FAILURE);
			}
			pointer->Num = tmp;
			pointer->next = NULL;
		}
		if (i == 0) 
		{
			head = pointer;
			pointerRecord = pointer;
		}
		if (i != 0) 
		{
			pointerRecord->next = pointer;
			pointerRecord = pointer;
		}
	}
}
void Union::output()
{
	NumNode* p_A = Ahead, *p_B = Bhead; // ����ָ��
	int tmp = -1; // ��¼��һ�����ֵ,������ͬ
	Output = new(nothrow) NumNode;
	if (Output == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	Output->Num = -1;
	Output->next = NULL;
	NumNode* p_Out = Output;
	cout << "�󽻼����Ϊ:" << endl;
	if (p_A == NULL || p_B == NULL)
	{
		cout << "NULL" << endl;
		return;
	}
	while (p_A != NULL && p_B != NULL)
	{
		if (p_A->Num == p_B->Num)
		{
			if (tmp != p_A->Num)
			{
				NumNode* ans = new(nothrow) NumNode;
				if (ans == NULL)
				{
					cout << "No Memory" << endl;
					exit(EXIT_FAILURE);
				}
				ans->Num = p_A->Num;
				ans->next = NULL;
				p_Out->next = ans;
				p_Out = p_Out->next;
			}
			tmp = p_A->Num;
			p_A = p_A->next;
			p_B = p_B->next;
		}
		else if (p_A->Num > p_B->Num)
		{
			p_B = p_B->next;
		}
		else if (p_A->Num < p_B->Num)
		{
			p_A = p_A->next;
		}
	}
	p_Out = Output->next;
	if (p_Out == NULL)
	{ // ˵��δ�н���
		cout << "NULL" << endl;
		return;
	}
	else
	{
		cout << p_Out->Num;
		p_Out = p_Out->next;
	}
	while (p_Out != NULL)
	{
		cout << " " << p_Out->Num;
		p_Out = p_Out->next;
	}
}
int main()
{
	Union Intersection;
	Intersection.output();
	return 0;
}