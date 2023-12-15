#include <iostream>
using namespace std;


struct Node {
	char content[21];
	Node* next;
};

/**
 *  ��Ҫ����ո��ⲻ����20���ַ������ȿɿأ���char[]�洢����
 *  
**/
class LinkedStackForTrans {
private:
	Node* top; // ͷָ��
	char* Origin; // ԭ��׺���ʽ
	char* Output; // �����׺���ʽ 
	int ptrOrigin; // ��¼��ǰ����Origin��λ��
	int OriginLength, OutputLength; // �ַ�������

	void Push(char* in); // ��ջ
	bool Pop(char* out); // ��ջ
	void makeEmpty(); // �ͷ��ڴ�
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
		memset(Output, 0, 42); // ȫ����\0
	};
	~LinkedStackForTrans() { makeEmpty(); };
	void Transform(); // ��׺����׺
	friend istream& operator>>(istream& is, LinkedStackForTrans& target);
	friend ostream& operator<<(ostream& os, LinkedStackForTrans& target);
};

istream& operator>>(istream& is, LinkedStackForTrans& target)
{
	target.Origin = new char[42]; // �϶��������ó���
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
	if (top == NULL) // ��ջ
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
	else // �ǿ�ջ
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
	if (top == NULL) // ��ջ
	{
		return NULL;
	}
	else // �ǿ�ջ
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
	} // Ѱ����Ч���ݵ�β��
	if (pos != 0) // ���ǵ�һ����Ч����
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
	} // ��д��output��
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
	ptrOrigin++; // �����м�Ŀո�
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
	Push(ch); // ��������ջ
	if (!GetOriginElement(ch)) // ȡ����һ��Ԫ��
	{
		return;
	}
	do
	{
		if ((ch[0] >= '1' && ch[0] <= '9') || ((ch[0] == '-' || ch[0] == '+') && ch[1] >= '1' && ch[1] <= '9')) // �ǲ�����
		{
			WriteIn(ch);
			if (!GetOriginElement(ch))
			{
				break;
			}
		}
		else // �ǲ�����
		{
			op[0] = top->content[0];
			if (Icp(ch[0]) > Isp(op[0]))
			{
				Push(ch); // Ӧ����ջ
				if (!GetOriginElement(ch))
				{
					break;
				}
			}
			else if (Icp(ch[0]) < Isp(op[0]))
			{
				Pop(out); // Ӧ����ջ�����
				WriteIn(out);
			}
			else
			{
				Pop(out); // ��ջ�������
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
	cout << "��������׺���ʽ" << endl;
	cin >> Expression;
	Expression.Transform(); // ���ɽ��
	cout << "��׺���ʽΪ:" << endl;
	cout << Expression;
	return 0;
}