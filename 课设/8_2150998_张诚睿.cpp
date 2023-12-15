#include <iostream>
using namespace std;
/*
	ʵ�ֲ�����10���ַ����ַ�������
*/
class MyString {
private:
	char content[10]; // ����ָ��
public:
	MyString()
	{
		for (int i = 0; i < 10; i++)
		{
			content[i] = '\0';
		}
	};// �޲�
	friend ostream& operator<<(ostream& os, MyString& target); // �������
	friend istream& operator>>(istream& is, MyString& target); // ��ȡ���ݣ����ո񡢻س�ֹͣ
	bool operator==(const MyString& matched); // �ж����ַ����Ƿ�һ��
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
 * �߽ڵ�
*/
struct Edge {
	int dest; // ����һ������λ��
	int cost; // ��Ȩֵ������
	Edge* link = NULL; // ��һ������ָ��
};
/*
 * С������ 
*/
struct Quarter {
	MyString name; // С�����ƣ����޳�������Ӣ�ġ����ŵ�
	Edge* adj = NULL;
};
/*
 * ��С�������ı�
*/
struct MSTEdgeNode {
	int head, tail; // ͷβ����
	MyString headName, tailName;
	int cost; // Ȩֵ
};
/*
 * ��С��
*/
class minHeap {
private:
	MSTEdgeNode* heap;
	int size; // ���еıߵ����������涨�ѵĴ�С
	int last; // ����Ϊ��ʹ�õ���������һλ
public:
	minHeap() :heap(NULL), size(0), last(0) {};
	~minHeap() { delete heap; };
	void init(int maxSize);
	void Insert(MSTEdgeNode item); // ��ӽ���С��
	bool Remove(MSTEdgeNode& out); // ȡ��
};

class MinSpanTree {
private:
	MSTEdgeNode* content; // ��̬������
	int size; // n-1����
	int Current; // ��ǰλ��
public:
	MinSpanTree() :content(NULL), size(0), Current(0) {};
	~MinSpanTree() { delete content; };
	void init(int max);
	void Insert(MSTEdgeNode target);
	void Print();
	void clean(); // ����������ݣ����³�ʼ��
};

class Graphlnk_PowerGrid {
private:
	int size;
	Quarter* NodeTable; // ��̬���붥���
	MinSpanTree answer;
	int EdgeSize;

	bool NoEdge(int VF, int VS);
	bool SearchName(MyString target, int& Pos);
public:
	Graphlnk_PowerGrid() :size(0), NodeTable(NULL), answer(), EdgeSize(0) {};
	~Graphlnk_PowerGrid() { free(NodeTable); };
	void init();
	void CreateVertex(); // ��������
	void InsertEdge(); // ��ӱ�
	void Prim(); // ������С������
	void ShowTree(); // ��ʾ��С������
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
	/* ��size���涨��һ��������� */
	heap[last++] = item; // ��Ԫ�ط������
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
	heap[j] = item; // �Ż�
}
bool minHeap::Remove(MSTEdgeNode& out)
{
	if (last <= 0) // �ն�
	{
		return false;
	}
	/* �Ѳ��գ�����ȡ�� */
	out = heap[0]; // ȡ���Ѷ�
	heap[0] = heap[--last]; // ���һ��Ԫ�طŵ��Ѷ�
	/* ������ */
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
	Quarter* tmp = &NodeTable[VF_Pos]; // ָ������ָ��
	if (tmp->adj == NULL) // �ޱ�
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
	else // �Ѿ��б�
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
	cout << "**        �������ģ��ϵͳ        **" << endl;
	cout << "====================================" << endl;
	cout << "**        A--������������        **" << endl;
	cout << "**        B--��ӵ����ı�        **" << endl;
	cout << "**        C--������С������      **" << endl;
	cout << "**        D--��ʾ��С������      **" << endl;
	cout << "**        E--�˳�  ����          **" << endl;
	cout << "====================================" << endl;
	cout << "��û���κζ��㣬��Ϊ���Զ�ѡ��Aָ��" << endl;
	CreateVertex();
}
void Graphlnk_PowerGrid::CreateVertex()
{
	if (size != 0)
	{
		cout << "�Ѿ��������������㣬��ѡ������ָ��" << endl;
		return;
	}
	cout << "�����붥��ĸ���: ";
	// ���������
	while (true)
	{
		cin >> size;
		if (!cin.good())
		{
			cout << "������������������!" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (size <= 2)
		{
			cout << "�������ֶ�������û�����壬�����ٴ���2" << endl;
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
	cout << "��������������������:" << endl;
	for (int i = 0; i < size; i++)
	{
		if (NodeTable[i].name == "\0") // ֻ�����¶�������
		{
			cin >> NodeTable[i].name;
		}
	}
}
void Graphlnk_PowerGrid::InsertEdge()
{
	while (true)
	{
		cout << "�������������㼰��Ȩֵ: " << endl;
		MyString VertexF, VertexS;
		int cost,VF_Pos=0,VS_Pos=0;
		cin >> VertexF >> VertexS >> cost;
		if (!cin.good() || cost < 0)
		{
			cout << "������������������" << endl;
			continue;
		}
		if (SearchName(VertexF,VF_Pos) && SearchName(VertexS,VS_Pos) && NoEdge(VF_Pos,VS_Pos)) // ���ֶ����ڣ����ޱ�
		{ 
			/* ����ͼ���������һ�� */
			Insert(VF_Pos, VS_Pos, cost);
			Insert(VS_Pos, VF_Pos, cost);
			EdgeSize++;
		}
		else
		{
			cout << "�����ֲ����Ѿ����ڵĶ����������Ѿ��б��ˡ����Զ��˳���ָ�����" << endl;
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
			cout << "�еĶ���δ��������һ��������µı�" << endl;
			return;
		}
	}
	answer.clean();
	cout << "��������ʼ����" << endl;
	MyString start;
	int startPos = 0;
	while (true)
	{
		cin >> start;
		if (!SearchName(start, startPos))
		{
			cout << "���ֲ����ڣ�����������: ";
		}
		else
		{
			break;
		}
	}
	/* �û�ȡ�������������ڵ�ַstartPos��ʼ������С������ */
	bool* Vmst = new bool[size];
	for (int i = 0; i < size; i++)
	{
		Vmst[i] = false;
	}
	answer.init(size - 1); // ��ʼ����С������
	minHeap Heap;
	Heap.init(EdgeSize); // ��ʼ����С��
	Vmst[startPos] = true; // ��ʼ����Ϊ�ѷ���
	int count = 1;
	while (count <= size - 1)
	{
		Edge* tmp = NodeTable[startPos].adj;
		/* ��startPos�����Ա߼��뵽���� */
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
		/* �Ӷ���ȡ���Ѷ���ȡ���ı߼������� */
		MSTEdgeNode out;
		while (Heap.Remove(out))
		{
			/* ȡ����Ԫ����Ҫ�ж��Ƿ���Լ����� */
			if (Vmst[out.head] && !Vmst[out.tail])
			{ // ���Լ�����
				answer.Insert(out);
				Vmst[out.tail] = true;
				count++;
				startPos = out.tail;
				break;
			}
		}
	}
	delete[] Vmst;
	cout << "������Prim��С������!" << endl;
}
void Graphlnk_PowerGrid::ShowTree()
{
	answer.Print();
}
int main()
{
	Graphlnk_PowerGrid QuarterGrid;
	QuarterGrid.init(); // ��ʼ��
	while (true)
	{
		char choice;
		cout << "��ѡ�����: ";
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
				cout << "�ѳɹ��˳�!" << endl;
				return 0;
			}
		}
		else
		{
			cout << "�Ƿ�ָ�����������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	return 0;
}