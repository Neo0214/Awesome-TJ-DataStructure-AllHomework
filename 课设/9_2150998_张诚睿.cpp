#include <iostream>
using namespace std;
/* 关键活动各边 */
struct EdgeNode {
	int v1, v2;
	int cost;
	EdgeNode() :v1(0), v2(0), cost(0) {};
};

struct Edge {
	int cost;
	int dest;
	Edge* link;
	Edge() :cost(0), dest(-1), link(NULL) {};
};
struct Event {
	int name; //  名字都是数字表示的
	Edge* adj;
	Event() :name(-1), adj(NULL) {};
};

class Graphlnk_Key {
private:
	Event* NodeTable; // 动态申请
	int size; // 顶点总数
	int mission; // 活动总数
	int count; // 关键活动数
	EdgeNode* cp; // 动态申请
public:
	Graphlnk_Key() :NodeTable(NULL), size(0), count(0), cp(NULL), mission(0) {};
	~Graphlnk_Key() { delete NodeTable; };
	void init();
	void Insert(int head, int tail, int cost);
	void CriticalPath();
	int IndNumber(int pos);
	int GetFirstNeighbor(int begin);
	int GetWeight(int now, int visit);
	int GetNextNeighbor(int Tar, int now);
	void Show();
};
int Graphlnk_Key::GetNextNeighbor(int Tar, int now)
{
	if (Tar != -1)
	{
		Edge* tmp = NodeTable[Tar].adj;
		while (tmp != NULL && tmp->dest != now)
		{
			tmp = tmp->link;
		}
		if (tmp != NULL && tmp->link != NULL)
		{
			return tmp->link->dest;
		}
	}
	return -1;
}
int Graphlnk_Key::GetWeight(int now, int visit)
{
	if (now != -1 && visit != -1)
	{
		Edge* tmp = NodeTable[now].adj;
		while (tmp != NULL && tmp->dest != visit)
		{
			tmp = tmp->link;
		}
		if (tmp != NULL)
		{
			return tmp->cost;
		}
	}
	return 0;
}
int Graphlnk_Key::GetFirstNeighbor(int begin)
{
	if (begin == -1)
	{
		return -1;
	}
	if (NodeTable[begin].adj == NULL)
	{
		return -1;
	}
	return NodeTable[begin].adj->dest;
}
int Graphlnk_Key::IndNumber(int pos)
{
	int ind = 0;
	for (int i = 0; i < size; i++)
	{
		Edge* tmp = NodeTable[i].adj;
		while (tmp != NULL)
		{
			if (tmp->dest == pos)
			{
				ind++;
			}
			tmp = tmp->link;
		}
	}
	return ind;
}
void Graphlnk_Key::init()
{
	cout << "请输入交接点数量与子任务数量: ";
	while (true)
	{
		cin >> size;
		if (!cin.good())
		{
			cout << "交接点数量输入有误，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (size <= 0)
		{
			cout << "交接点数量请输入大于零的数，重新输入: " << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
		{
			break;
		}
	}
	while (true)
	{
		cin >> mission;
		if (!cin.good())
		{
			cout << "子任务数量输入有误，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (mission <= 0)
		{
			cout << "子任务数量请输入大于零的数，重新输入: " << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
		{
			break;
		}
	}
	NodeTable = new Event[size];
	if (NodeTable == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "请输入各边信息" << endl;
	for (int i = 0; i < size; i++)
	{
		NodeTable[i].name = i + 1;
	}
	for (int i = 0; i < mission; i++)
	{
		int head = 0, tail = 0, cost = 0;
		cin >> head >> tail >> cost;
		Insert(head - 1, tail - 1, cost); // 添加至邻接表-出表
	}
}
void Graphlnk_Key::Insert(int head, int tail, int cost)
{
	if (NodeTable[head].adj == NULL)
	{
		Edge* tmp = new Edge;
		tmp->cost = cost;
		tmp->dest = tail;
		NodeTable[head].adj = tmp;
		return;
	}
	else
	{
		Edge* tmp = NodeTable[head].adj;
		while (tmp->link != NULL)
		{
			tmp = tmp->link;
		}
		Edge* New = new Edge;
		New->cost = cost;
		New->dest = tail;
		tmp->link = New;
		return;
	}
}
void Graphlnk_Key::CriticalPath()
{
	int top = -1, now, lnk = -1, visit, weigh, ka;
	int* ind = new int[size]; // 入度数组
	for (int i = 0; i < size; i++)
	{
		ind[i] = IndNumber(i);
	}
	// 统计完每个顶点的入度
	int* Ve = new int[size];
	int* V1 = new int[size];
	int* Ae = new int[mission];
	int* A1 = new int[mission];
	// 开辟四个数组存放计算需要的四个量
	for (int i = 0; i < size; i++)
	{
		Ve[i] = 0; // 全部置0
	}
	for (int i = 0; i < size; i++)
	{
		if (!ind[i])
		{
			ind[i] = top;
			top = i;
		}
	}
	while (top!=-1)
	{
		now = top;
		top = ind[top]; // 退栈，并保存顶点
		ind[now] = lnk;
		lnk = now; // 反向拉链
		visit = GetFirstNeighbor(now);
		while (visit != -1)
		{
			weigh = GetWeight(now, visit);
			if (Ve[now] + weigh > Ve[visit])
			{
				Ve[visit] = Ve[now] + weigh;
			}
			if (--ind[visit] == 0)
			{
				ind[visit] = top;
				top = visit;
			}
			visit = GetNextNeighbor(now, visit);
		}
	}
	for (int i = 0; i < size; i++)
	{
		V1[i] = Ve[lnk];
	}
	while (lnk != -1)
	{
		visit = ind[lnk];
		lnk = visit;
		if (lnk == -1)
		{
			break;
		}
		ka = GetFirstNeighbor(visit);
		while (ka != -1)
		{
			weigh = GetWeight(visit, ka);
			if (V1[ka] - weigh < V1[visit])
			{
				V1[visit] = V1[ka] - weigh;
			}
			ka = GetNextNeighbor(visit, ka);
		}
	}
	ka = 0;
	count = 0;
	cp = new EdgeNode[mission];
	for (int i = 0; i < size; i++)
	{
		now = GetFirstNeighbor(i);
		while (now != -1)
		{
			weigh = GetWeight(i, now);
			Ae[ka] = Ve[i];
			A1[ka] = V1[now] - weigh;
			if (Ae[ka] == A1[ka])
			{
				cp[count].cost = weigh;
				cp[count].v1 = i;
				cp[count].v2 = now;
				count++;
			}
			ka++;
			now = GetNextNeighbor(i, now);
		}
	}
	delete[]ind;
	delete[]Ve;
	delete[]V1;
	delete[]Ae;
	delete[]A1;
}
void Graphlnk_Key::Show()
{
	int total = 0;
	for (int i = 0; i < count; i++)
	{
		total += cp[i].cost;
	}
	if (total == 0)
	{
		cout << "无解" << endl;
	}
	else
	{
		cout << "最短时间: " << total << endl;
	}
	for (int i = 0; i < count; i++)
	{
		cout << cp[i].v1+1 << "->" << cp[i].v2+1 << endl;
	}
}

int main()
{
	Graphlnk_Key AOE;
	AOE.init();
	AOE.CriticalPath();
	AOE.Show();
	return 0;
}