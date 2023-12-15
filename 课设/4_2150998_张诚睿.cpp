#include <iostream>
using namespace std;


struct Node {
	char content[21];
	Node* next;
};

/**
 *  按要求除空格外不超过20个字符，长度可控，用char[]存储即可
 *  
**/
class LinkedStackForTrans {
private:
	Node* top; // 头指针
	char* Origin; // 原中缀表达式
	char* Output; // 结果后缀表达式 
	int ptrOrigin; // 记录当前处理Origin的位置
	int OriginLength, OutputLength; // 字符串长度

	void Push(char* in); // 进栈
	bool Pop(char* out); // 出栈
	void makeEmpty(); // 释放内存
	char* GetTop();
	bool GetOriginElement(char* ch);
	int Isp(const char ch);
	int Icp(const char ch);
	void WriteIn(char* str);
public:
	LinkedStackForTrans() :top(NULL), Origin(NULL),Output(NULL), ptrOrigin(0), OriginLength(0), OutputLength(0) 
	{
		Output = new char[42];
		if (Output == NULL)
		{
			cout << "Memory Wrong" << endl;
			exit(EXIT_FAILURE);
		}
		memset(Output, 0, 42); // 全部置\0
	};
	~LinkedStackForTrans() { makeEmpty(); };
	void Transform(); // 中缀换后缀
	friend istream& operator>>(istream& is, LinkedStackForTrans& target);
	friend ostream& operator<<(ostream& os, LinkedStackForTrans& target);
};

istream& operator>>(istream& is, LinkedStackForTrans& target)
{
	target.Origin = new char[42]; // 肯定不超过该长度
	if (target.Origin == NULL)
	{
		cout << "Memory Wrong" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 40; i++)
	{
		char ch = getchar();
		if (ch == '\n')
		{
			target.Origin[i] = ' ';
			target.Origin[i + 1] = '#';
			target.Origin[i + 2] = '\0';
			break;
		}
		target.Origin[i] = ch;
	}
	target.OriginLength = strlen(target.Origin) + 1;
	return is;
}

ostream& operator<<(ostream& os, LinkedStackForTrans& target)
{
	os << target.Output; 
	return os;
}

void LinkedStackForTrans::makeEmpty()
{
	while (top != NULL)
	{
		Node* tmp = top;
		top = top->next;
		delete tmp;
	}
}

void LinkedStackForTrans::Push(char* in)
{
	if (top == NULL) // 空栈
	{
		top = new Node;
		if (top == NULL)
		{
			cout << "Memory Wrong";
			exit(EXIT_FAILURE);
		}
		strcpy_s(top->content, in);
		top->next = NULL;
	}
	else // 非空栈
	{
		Node* tmp = new Node;
		if (tmp == NULL)
		{
			cout << "Memory Wrong";
			exit(EXIT_FAILURE);
		}
		strcpy_s(tmp->content, in);
		tmp->next = top;
		top = tmp;
	}
}

bool LinkedStackForTrans::Pop(char* out)
{
	if (top == NULL)
	{
		return false;
	}
	else
	{
		out[0] = top->content[0];
		Node* tmp = top;
		top = top->next;
		delete tmp;
		return true;
	}
	return false;
}

char* LinkedStackForTrans::GetTop()
{
	if (top == NULL) // 空栈
	{
		return NULL;
	}
	else // 非空栈
	{
		return top->content;
	}
}
int LinkedStackForTrans::Isp(const char ch)
{
	if (ch == '#')
	{
		return 0;
	}
	else if (ch == '(')
	{
		return 1;
	}
	else if (ch == '*' || ch == '%' || ch == '/')
	{
		return 5;
	}
	else if (ch == '+' || ch == '-')
	{
		return 3;
	}
	else if (ch == ')')
	{
		return 6;
	}
	return 0;
}
int LinkedStackForTrans::Icp(const char ch)
{
	if (ch == '#')
	{
		return 0;
	}
	else if (ch == '(')
	{
		return 6;
	}
	else if (ch == '*' || ch == '%' || ch == '/')
	{
		return 4;
	}
	else if (ch == '+' || ch == '-')
	{
		return 2;
	}
	else if (ch == ')')
	{
		return 1;
	}
	return 0;
}
void LinkedStackForTrans::WriteIn(char* str)
{
	int pos = 0;
	while (pos < 42 && Output[pos] != '\0')
	{
		pos++;
	} // 寻找有效内容的尾巴
	if (pos != 0) // 不是第一个有效内容
	{
		Output[pos++] = ' ';
	}
	int strPos = 0;
	if (str[0] == '+' && str[1] != '\0')
	{
		strPos++;
	}
	for (; strPos < int(strlen(str) + 1) && str[strPos] != '\0'; strPos++, pos++)
	{
		Output[pos] = str[strPos];
	} // 答案写进output里
}
bool LinkedStackForTrans::GetOriginElement(char* ch)
{
	memset(ch, 0, 21);
	int place = 0;
	while (ptrOrigin < OriginLength && Origin[ptrOrigin]!=' ')
	{
		ch[place] = Origin[ptrOrigin];
		place++;
		ptrOrigin++;
	}
	ptrOrigin++; // 跳过中间的空格
	if (place == 0)
	{
		return false;
	}
	return true;
}
void LinkedStackForTrans::Transform()
{
	char ch[21] = { "#" };
	char out[2] = { '\0' };
	char op[2] = { '\0' };
	Push(ch); // 结束符入栈
	if (!GetOriginElement(ch)) // 取出第一个元素
	{
		return;
	}
	do
	{
		if ((ch[0] >= '1' && ch[0] <= '9') || ((ch[0] == '-' || ch[0] == '+') && ch[1] >= '1' && ch[1] <= '9')) // 是操作数
		{
			WriteIn(ch);
			if (!GetOriginElement(ch))
			{
				break;
			}
		}
		else // 是操作符
		{
			op[0] = top->content[0];
			if (Icp(ch[0]) > Isp(op[0]))
			{
				Push(ch); // 应当进栈
				if (!GetOriginElement(ch))
				{
					break;
				}
			}
			else if (Icp(ch[0]) < Isp(op[0]))
			{
				Pop(out); // 应当出栈并输出
				WriteIn(out);
			}
			else
			{
				Pop(out); // 退栈但不输出
				if (!GetOriginElement(ch))
				{
					break;
				}
			}
		}
	} while (!(ch[0] == '#' && !strcmp(GetTop(), "#")));
}
int main()
{
	LinkedStackForTrans Expression; 
	cout << "请输入中缀表达式" << endl;
	cin >> Expression;
	Expression.Transform(); // 生成结果
	cout << "后缀表达式为:" << endl;
	cout << Expression;
	return 0;
}