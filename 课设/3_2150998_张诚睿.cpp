#include <iostream>
using namespace std;
/**
  *  ��ͼ����<1,1>��ʼ������<5,5>
  *  #ǽ0·
**/
const char MAZE_MAP[7][7]{
	'#','#','#','#','#','#','#',
	'#','0','#','0','0','0','#',
	'#','0','#','0','#','#','#',
	'#','0','0','0','#','0','#',
	'#','0','#','0','0','0','#',
	'#','0','#','0','#','0','#',
	'#','#','#','#','#','#','#',
};
#define MAP_ROWS 7
#define MAP_COLS 7
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
class Map {
public:
	void PrintMap()
	{
		cout << "�Թ���ͼ:" << endl;
		cout << "        ";
		for (int i = 0; i < MAP_COLS; i++)
		{
			cout << i << "��     ";
		} // ����
		cout << endl;
		for (int i = 0; i < MAP_ROWS; i++)
		{
			cout << i << "��     ";
			for (int j = 0; j < MAP_COLS; j++)
			{
				cout << MAZE_MAP[i][j] << "       ";
			}
			cout << endl;
		}
	}
};
struct Node{
	char content;
	int PosX, PosY; // ����
	Node* next;
};
class LinkedStack {
protected:
	Node* top; // ͷ���ָ��
	bool Pop(); // ��ջ
	void makeEmpty(); // �ͷ��ڴ�
public:
	LinkedStack() :top(NULL){};
	~LinkedStack() { makeEmpty(); };
	void Push(int Posx, int Posy); // ��ջ
	friend ostream& operator<<(ostream& os, LinkedStack& target);
};
class LinkedStackForMap:public LinkedStack {
public:
	LinkedStackForMap() :LinkedStack() {};
	~LinkedStackForMap();
	void FindPath(); // Ѱ�ҳ���·��
	void PrintPath(); // ��ӡ���
private:
	bool Step(const int direction, const int NowX, const int NowY, bool(*IsDetected)[7]);
};
LinkedStackForMap::~LinkedStackForMap()
{
	makeEmpty();
}
void LinkedStack::Push(int Posx, int Posy)
{
	if (top == NULL) // ��ջ
	{
		top = new(nothrow) Node;
		if (top == NULL)
		{
			cout << "Memory Wrong";
			exit(EXIT_FAILURE);
		}
		top->content = MAZE_MAP[Posy][Posx];
		top->PosX = Posx;
		top->PosY = Posy;
		top->next = NULL;
	}
	else // �ǿ�ջ��ͷ��㴦��ջ
	{
		Node* tmp= new(nothrow) Node;
		if (tmp == NULL)
		{
			cout << "Memory Wrong";
			exit(EXIT_FAILURE);
		}
		tmp->content = MAZE_MAP[Posy][Posx];
		tmp->PosX = Posx;
		tmp->PosY = Posy;
		tmp->next = top;
		top = tmp;
	}
}
bool LinkedStack::Pop()
{
	if (top == NULL) // ��ջ���޷���ջ
	{
		return false;
	}
	else // ��ͷ����ջ
	{
		Node* tmp = top;
		top = top->next;
		delete tmp;
		return true;
	}
	return true;
}
void LinkedStack::makeEmpty()
{
	while (top != NULL)
	{
		Node* tmp = top;
		top = top->next;
		delete tmp;
	}
}
bool LinkedStackForMap::Step(const int direction, const int NowX, const int NowY, bool(*IsDetected)[7])
{
	if (direction == LEFT && MAZE_MAP[NowY][NowX - 1] == '0' && !IsDetected[NowY][NowX - 1])
	{
		IsDetected[NowY][NowX - 1] = true;
		return true;
	}
	else if (direction == RIGHT && MAZE_MAP[NowY][NowX + 1] == '0' && !IsDetected[NowY][NowX + 1])
	{
		IsDetected[NowY][NowX + 1] = true;
		return true;
	}
	else if (direction == UP && MAZE_MAP[NowY-1][NowX] == '0' && !IsDetected[NowY-1][NowX])
	{
		IsDetected[NowY-1][NowX] = true;
		return true;
	}
	else if (direction == DOWN && MAZE_MAP[NowY+1][NowX] == '0' && !IsDetected[NowY+1][NowX])
	{
		IsDetected[NowY+1][NowX] = true;
		return true;
	}
	return false;
}
void LinkedStackForMap::FindPath()
{
	int NowX = 1, NowY = 1; // ��¼��ǰ����
	bool IsDetected[MAP_ROWS][MAP_COLS] = { false }; // ��ʼ��������λ�þ�δ��̽����
	Push(1, 1); // ������ջ
	IsDetected[NowX][NowY] = true; // �����Ϊ��̽��
	while (top!=NULL && (NowX != 5 || NowY != 5))
	{
		NowX = top->PosX;
		NowY = top->PosY;
		if (Step(LEFT, NowX, NowY, IsDetected)) // ������̽��
		{
			NowX -= 1;
			Push(NowX, NowY);
		}
		else if (Step(RIGHT, NowX, NowY, IsDetected)) // ������̽��
		{
			NowX += 1;
			Push(NowX, NowY);
		}
		else if (Step(UP, NowX, NowY, IsDetected)) // ������̽��
		{
			NowY -= 1;
			Push(NowX, NowY);
		}
		else if (Step(DOWN, NowX, NowY, IsDetected)) // ������̽��
		{
			NowY += 1;
			Push(NowX, NowY);
		}
		else // ��·����
		{
			Pop(); // ��ջ������
		}
	}
}
void LinkedStackForMap::PrintPath()
{
	if (top == NULL) // û��·����
	{
		cout << "\nNo Way Out!" << endl;
		return;
	}
	Node* pnode = top;
	LinkedStack output; // �������ջ
	while (pnode != NULL)
	{
		output.Push(pnode->PosX, pnode->PosY);
		pnode = pnode->next;
	}
	cout << "�Թ�·��<�У���>:" << endl;
	cout << output;
}
ostream& operator<<(ostream& os, LinkedStack& target)
{
	Node* pOut = target.top;
	os << "<" << pOut->PosY << "," << pOut->PosX << "> ";
	pOut = pOut->next;
	while (pOut != NULL)
	{
		os << "--> <" << pOut->PosY << "," << pOut->PosX << "> ";
		pOut = pOut->next;
	}
	os << endl;
	return os;
}
int main()
{
	Map mainMap;
	mainMap.PrintMap(); // ��ӡ��ͼ
	LinkedStackForMap MapResult;
	MapResult.FindPath();
	MapResult.PrintPath();
	return 0;
}