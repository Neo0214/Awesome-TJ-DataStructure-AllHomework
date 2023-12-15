#include <iostream>
using namespace std;
/**
  *  地图，从<1,1>开始，出口<5,5>
  *  #墙0路
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
		cout << "迷宫地图:" << endl;
		cout << "        ";
		for (int i = 0; i < MAP_COLS; i++)
		{
			cout << i << "列     ";
		} // 首行
		cout << endl;
		for (int i = 0; i < MAP_ROWS; i++)
		{
			cout << i << "行     ";
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
	int PosX, PosY; // 坐标
	Node* next;
};
class LinkedStack {
protected:
	Node* top; // 头结点指针
	bool Pop(); // 出栈
	void makeEmpty(); // 释放内存
public:
	LinkedStack() :top(NULL){};
	~LinkedStack() { makeEmpty(); };
	void Push(int Posx, int Posy); // 进栈
	friend ostream& operator<<(ostream& os, LinkedStack& target);
};
class LinkedStackForMap:public LinkedStack {
public:
	LinkedStackForMap() :LinkedStack() {};
	~LinkedStackForMap();
	void FindPath(); // 寻找出口路径
	void PrintPath(); // 打印结果
private:
	bool Step(const int direction, const int NowX, const int NowY, bool(*IsDetected)[7]);
};
LinkedStackForMap::~LinkedStackForMap()
{
	makeEmpty();
}
void LinkedStack::Push(int Posx, int Posy)
{
	if (top == NULL) // 空栈
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
	else // 非空栈，头结点处进栈
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
	if (top == NULL) // 空栈，无法出栈
	{
		return false;
	}
	else // 从头结点出栈
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
	int NowX = 1, NowY = 1; // 记录当前坐标
	bool IsDetected[MAP_ROWS][MAP_COLS] = { false }; // 初始设置所有位置均未被探索过
	Push(1, 1); // 将起点进栈
	IsDetected[NowX][NowY] = true; // 起点置为已探索
	while (top!=NULL && (NowX != 5 || NowY != 5))
	{
		NowX = top->PosX;
		NowY = top->PosY;
		if (Step(LEFT, NowX, NowY, IsDetected)) // 可向左探索
		{
			NowX -= 1;
			Push(NowX, NowY);
		}
		else if (Step(RIGHT, NowX, NowY, IsDetected)) // 可向右探索
		{
			NowX += 1;
			Push(NowX, NowY);
		}
		else if (Step(UP, NowX, NowY, IsDetected)) // 可向上探索
		{
			NowY -= 1;
			Push(NowX, NowY);
		}
		else if (Step(DOWN, NowX, NowY, IsDetected)) // 可向下探索
		{
			NowY += 1;
			Push(NowX, NowY);
		}
		else // 无路可走
		{
			Pop(); // 出栈，回溯
		}
	}
}
void LinkedStackForMap::PrintPath()
{
	if (top == NULL) // 没有路可走
	{
		cout << "\nNo Way Out!" << endl;
		return;
	}
	Node* pnode = top;
	LinkedStack output; // 倒序输出栈
	while (pnode != NULL)
	{
		output.Push(pnode->PosX, pnode->PosY);
		pnode = pnode->next;
	}
	cout << "迷宫路径<行，列>:" << endl;
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
	mainMap.PrintMap(); // 打印地图
	LinkedStackForMap MapResult;
	MapResult.FindPath();
	MapResult.PrintPath();
	return 0;
}