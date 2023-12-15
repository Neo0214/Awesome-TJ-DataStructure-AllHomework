#include <iostream>
using namespace std;

struct Node {
	int length;
	Node* next;
};
class PriorityWoodSolution {
private:
	Node* head; // 含有首元结点
	int cost;
	int Num; // 木头数量
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
	cout << "请输入木头总数: ";
	/* 输入错误处理 */
	while (true)
	{
		cin >> Num;
		if (!cin.good())
		{
			cout << "输入有误，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (Num <= 0)
		{
			cout << "请输入正整数，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (Num <= 2)
		{
			cout << "两块木头以内不需要电脑计算，请输入大于2的总数" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
		{
			break;
		}
	}
	int* LengthTmp = new(nothrow) int[Num]; // 申请一段临时变量方便错误处理
	if (LengthTmp == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "请输入每块木头长度" << endl;
	for (int i = 0; i < Num;)
	{
		cin >> LengthTmp[i];
		if (!cin.good())
		{
			cout << "输入有误，请从第"<<i+1<<"块木头长度重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (Num <= 0)
		{
			cout << "请输入正整数，请从第" << i + 1 << "块木头长度重新输入" << endl;
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
{ // 有Num规定数组长度，故不必担心越界
	Node* now = new Node;
	if (now == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	head = now;
	now->length = -1; // 不影响优先级排序
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
			tmp = tmp->next; // 新节点比当前节点大，就往后找，直到找到结尾或者比当前节点小于等于
		}
		/* 插入在tmp后 */
		now->next = tmp->next;
		tmp->next = now;
	}
}
void PriorityWoodSolution::Solve()
{
	int NodeNum = Num; // 记下有用结点个数
	while (NodeNum > 2)
	{
		cost += head->next->length;
		cost += head->next->next->length;
		// 计算好价格
		Node* New = new Node;
		New->length = head->next->length + head->next->next->length; 
		// 两块最小的木头合到一起
		Node* tmp = head->next; // 记录第一个节点
		// 去除前两个节点
		head->next = head->next->next->next; 
		delete tmp->next;
		delete tmp;
		tmp = head;
		while (tmp->next != NULL && New->length > tmp->next->length)
		{
			tmp = tmp->next; // 新节点比当前节点大，就往后找，直到找到结尾或者比当前节点小于等于
		}
		/* 插入在tmp后 */
		New->next = tmp->next;
		tmp->next = New;
		NodeNum--;
	}
	cost += head->next->length;
	cost += head->next->next->length;
	cout << "总价为:" << cost << endl;
}
int main()
{
	PriorityWoodSolution Woods;
	Woods.Init();
	Woods.Solve();
	return 0;
}