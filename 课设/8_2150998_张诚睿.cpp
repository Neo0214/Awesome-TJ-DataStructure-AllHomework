#include <iostream>
using namespace std;
/*
	实现不长于10个字符的字符串操作
*/
class MyString {
private:
	char content[10]; // 内容指针
public:
	MyString()
	{
		for (int i = 0; i < 10; i++)
		{
			content[i] = '\0';
		}
	};// 无参
	friend ostream& operator<<(ostream& os, MyString& target); // 输出内容
	friend istream& operator>>(istream& is, MyString& target); // 读取内容，遇空格、回车停止
	bool operator==(const MyString& matched); // 判断两字符串是否一致
	bool operator==(const char* str);
};
istream& operator>>(istream& is, MyString& target)
{
	int Current = 0;
	char tmp;
	while (true)
	{
		tmp = getchar();
		if (tmp == ' ' || tmp == '\n')
		{
			continue;
		}
		else
		{
			target.content[Current++] = tmp;
			break;
		}
	}
	while (Current<10)
	{
		tmp = getchar();
		if (tmp == ' ' || tmp == '\n')
		{
			break;
		}
		else
		{
			target.content[Current++] = tmp;
		}
	}
	return is;
}
ostream& operator<<(ostream& os, MyString& target)
{
	if (target.content == NULL)
	{
		return os;
	}
	os << target.content;
	return os;
}
bool MyString::operator==(const MyString& matched)
{
	for (int i = 0; i < 10; i++)
	{
		if (content[i] != matched.content[i])
		{
			return false;
		}
	}
	return true;
}
bool MyString::operator==(const char* str)
{
	if (strlen(str) != strlen(content))
	{
		return false;
	}
	for (int i = 0; str[i] != '\0' && i < 10; i++)
	{
		if (str[i] != content[i])
		{
			return false;
		}
	}
	return true;
}
/*
 * 边节点
*/
struct Edge {
	int dest; // 边另一个顶点位置
	int cost; // 边权值—花费
	Edge* link = NULL; // 下一条边链指针
};
/*
 * 小区顶点 
*/
struct Quarter {
	MyString name; // 小区名称，不限长度与中英文、符号等
	Edge* adj = NULL;
};
/*
 * 最小生成树的边
*/
struct MSTEdgeNode {
	int head, tail; // 头尾顶点
	MyString headName, tailName;
	int cost; // 权值
};
/*
 * 最小堆
*/
class minHeap {
private:
	MSTEdgeNode* heap;
	int size; // 所有的边的总数，来规定堆的大小
	int last; // 已作为堆使用的数组的最后一位
public:
	minHeap() :heap(NULL), size(0), last(0) {};
	~minHeap() { delete heap; };
	void init(int maxSize);
	void Insert(MSTEdgeNode item); // 添加进最小堆
	bool Remove(MSTEdgeNode& out); // 取出
};

class MinSpanTree {
private:
	MSTEdgeNode* content; // 动态申请结果
	int size; // n-1条边
	int Current; // 当前位置
public:
	MinSpanTree() :content(NULL), size(0), Current(0) {};
	~MinSpanTree() { delete content; };
	void init(int max);
	void Insert(MSTEdgeNode target);
	void Print();
	void clean(); // 清空已有内容，重新初始化
};

class Graphlnk_PowerGrid {
private:
	int size;
	Quarter* NodeTable; // 动态申请顶点表
	MinSpanTree answer;
	int EdgeSize;

	bool NoEdge(int VF, int VS);
	bool SearchName(MyString target, int& Pos);
public:
	Graphlnk_PowerGrid() :size(0), NodeTable(NULL), answer(), EdgeSize(0) {};
	~Graphlnk_PowerGrid() { free(NodeTable); };
	void init();
	void CreateVertex(); // 创建顶点
	void InsertEdge(); // 添加边
	void Prim(); // 构造最小生成树
	void ShowTree(); // 显示最小生成树
	void Insert(int VF_Pos, int VS_Pos, int cost);
};

void minHeap::init(int maxSize)
{
	size = maxSize;
	heap = new MSTEdgeNode[size];
	if (heap == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
}
void minHeap::Insert(MSTEdgeNode item)
{
	/* 有size做规定，一定不会堆满 */
	heap[last++] = item; // 新元素放在最后
	int j = last - 1, i = (j - 1) / 2;
	while (j > 0)
	{
		if (heap[i].cost <= item.cost)
		{
			break;
		}
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (j - 1) / 2;
		}
	}
	heap[j] = item; // 放回
}
bool minHeap::Remove(MSTEdgeNode& out)
{
	if (last <= 0) // 空堆
	{
		return false;
	}
	/* 堆不空，可以取出 */
	out = heap[0]; // 取出堆顶
	heap[0] = heap[--last]; // 最后一个元素放到堆顶
	/* 调整堆 */
	int i = 0, j = i * 2 + 1;
	MSTEdgeNode tmp = heap[0];
	while (j < last)
	{
		if (j<last && heap[j].cost>heap[j + 1].cost)
		{
			j++;
		}
		if (tmp.cost <= heap[j].cost)
		{
			break;
		}
		else
		{
			heap[i] = heap[j];
			i = j;
			j = j * 2 + 1;
		}
	}
	heap[i] = tmp;
	return true;
}

void MinSpanTree::init(int max)
{
	size = max;
	content = new MSTEdgeNode[size];
	if (content == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
}
void MinSpanTree::Insert(MSTEdgeNode target)
{
	content[Current++] = target;
}
void MinSpanTree::Print()
{
	for (int i = 0; i < size; i++)
	{
		cout << "  " << content[i].headName << "-<" << content[i].cost << ">->" << content[i].tailName;
	}
	cout << endl;
}
void MinSpanTree::clean()
{
	delete content;
	size = 0;
	Current = 0;
	content = NULL;
}

bool Graphlnk_PowerGrid::NoEdge(int VS, int VF)
{
	if (NodeTable[VS].adj == NULL)
	{
		return true;
	}
	else
	{
		Edge* tmp = NodeTable[VS].adj;
		while (tmp != NULL)
		{
			if (tmp->dest == VF)
			{
				return false;
			}
			tmp = tmp->link;
		}
	}
	return true;
}
bool Graphlnk_PowerGrid::SearchName(MyString target, int& Pos)
{
	for (int i = 0; i < size; i++)
	{
		if (NodeTable[i].name == target)
		{
			Pos = i;
			return true;
		}
	}
	return false;
}
void Graphlnk_PowerGrid::Insert(int VF_Pos, int VS_Pos, int cost)
{
	Quarter* tmp = &NodeTable[VF_Pos]; // 指向起点的指针
	if (tmp->adj == NULL) // 无边
	{
		Edge* NewEdge = new Edge;
		if (NewEdge == NULL)
		{
			cout << "No Memory" << endl;
			exit(EXIT_FAILURE);
		}
		tmp->adj = NewEdge;
		NewEdge->cost = cost;
		NewEdge->dest = VS_Pos;
	}
	else // 已经有边
	{
		Edge* check = tmp->adj;
		while (check->link != NULL)
		{
			check = check->link;
		}
		Edge* NewEdge = new Edge;
		if (NewEdge == NULL)
		{
			cout << "No Memory" << endl;
			exit(EXIT_FAILURE);
		}
		check->link = NewEdge;
		NewEdge->cost = cost;
		NewEdge->dest = VS_Pos;
	}
	
}
void Graphlnk_PowerGrid::init()
{
	cout << "**        电网造价模拟系统        **" << endl;
	cout << "====================================" << endl;
	cout << "**        A--创建电网顶点        **" << endl;
	cout << "**        B--添加电网的边        **" << endl;
	cout << "**        C--构造最小生成树      **" << endl;
	cout << "**        D--显示最小生成树      **" << endl;
	cout << "**        E--退出  程序          **" << endl;
	cout << "====================================" << endl;
	cout << "还没有任何顶点，已为您自动选择A指令" << endl;
	CreateVertex();
}
void Graphlnk_PowerGrid::CreateVertex()
{
	if (size != 0)
	{
		cout << "已经创建过电网顶点，请选择其他指令" << endl;
		return;
	}
	cout << "请输入顶点的个数: ";
	// 输入错误处理
	while (true)
	{
		cin >> size;
		if (!cin.good())
		{
			cout << "输入有误，请重新输入!" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (size <= 2)
		{
			cout << "输入数字对求解电网没有意义，请至少大于2" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
		{
			break;
		}
	}
	NodeTable = new Quarter[size];
	if (NodeTable==NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "请依次输入各顶点的名称:" << endl;
	for (int i = 0; i < size; i++)
	{
		if (NodeTable[i].name == "\0") // 只输入新顶点名字
		{
			cin >> NodeTable[i].name;
		}
	}
}
void Graphlnk_PowerGrid::InsertEdge()
{
	while (true)
	{
		cout << "请输入两个顶点及边权值: " << endl;
		MyString VertexF, VertexS;
		int cost,VF_Pos=0,VS_Pos=0;
		cin >> VertexF >> VertexS >> cost;
		if (!cin.good() || cost < 0)
		{
			cout << "输入有误，请重新输入" << endl;
			continue;
		}
		if (SearchName(VertexF,VF_Pos) && SearchName(VertexS,VS_Pos) && NoEdge(VF_Pos,VS_Pos)) // 名字都存在，且无边
		{ 
			/* 无向图，来回添加一遍 */
			Insert(VF_Pos, VS_Pos, cost);
			Insert(VS_Pos, VF_Pos, cost);
			EdgeSize++;
		}
		else
		{
			cout << "有名字不是已经存在的顶点名，或已经有边了。已自动退出该指令操作" << endl;
			return;
		}
	}
}
void Graphlnk_PowerGrid::Prim()
{
	for (int i = 0; i < size; i++)
	{
		if (NodeTable[i].adj == NULL)
		{
			cout << "有的顶点未被连接在一起，请添加新的边" << endl;
			return;
		}
	}
	answer.clean();
	cout << "请输入起始顶点" << endl;
	MyString start;
	int startPos = 0;
	while (true)
	{
		cin >> start;
		if (!SearchName(start, startPos))
		{
			cout << "名字不存在，请重新输入: ";
		}
		else
		{
			break;
		}
	}
	/* 用获取的起点和其数组内地址startPos开始计算最小生成树 */
	bool* Vmst = new bool[size];
	for (int i = 0; i < size; i++)
	{
		Vmst[i] = false;
	}
	answer.init(size - 1); // 初始化最小生成树
	minHeap Heap;
	Heap.init(EdgeSize); // 初始化最小堆
	Vmst[startPos] = true; // 起始点置为已放入
	int count = 1;
	while (count <= size - 1)
	{
		Edge* tmp = NodeTable[startPos].adj;
		/* 把startPos的所以边加入到堆中 */
		while (tmp != NULL)
		{
			if (!Vmst[tmp->dest])
			{
				MSTEdgeNode ReadyToHeap;
				ReadyToHeap.cost = tmp->cost;
				ReadyToHeap.head = startPos;
				ReadyToHeap.tail = tmp->dest;
				ReadyToHeap.headName = NodeTable[startPos].name;
				ReadyToHeap.tailName = NodeTable[tmp->dest].name;
				Heap.Insert(ReadyToHeap);
			}
			tmp = tmp->link;
		}
		/* 从堆中取出堆顶，取出的边加入结果中 */
		MSTEdgeNode out;
		while (Heap.Remove(out))
		{
			/* 取出的元素需要判断是否可以加入结果 */
			if (Vmst[out.head] && !Vmst[out.tail])
			{ // 可以加入结果
				answer.Insert(out);
				Vmst[out.tail] = true;
				count++;
				startPos = out.tail;
				break;
			}
		}
	}
	delete[] Vmst;
	cout << "已生成Prim最小生成树!" << endl;
}
void Graphlnk_PowerGrid::ShowTree()
{
	answer.Print();
}
int main()
{
	Graphlnk_PowerGrid QuarterGrid;
	QuarterGrid.init(); // 初始化
	while (true)
	{
		char choice;
		cout << "请选择操作: ";
		cin >> choice;
		cin.clear();
		cin.ignore(1024, '\n');
		if (choice >= 'A' && choice <= 'E')
		{
			switch (choice)
			{
			case 'A':
				QuarterGrid.CreateVertex();
				break;
			case 'B':
				QuarterGrid.InsertEdge();
				break;
			case 'C':
				QuarterGrid.Prim();
				break;
			case 'D':
				QuarterGrid.ShowTree();
				break;
			default:
				cout << "已成功退出!" << endl;
				return 0;
			}
		}
		else
		{
			cout << "非法指令，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	return 0;
}