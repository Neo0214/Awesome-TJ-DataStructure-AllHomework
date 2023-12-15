#include <iostream>
using namespace std;
/*
	仿制string类，实现变长度存储字符
*/
class MyString {
private:
	MyString& operator+=(char ch); // 末尾添加一个字符
	int size; // 字符串长度
	char* content; // 内容指针
public:
	MyString(const char* str);
	MyString() :size(1) {
		content = new char;
		if (content == NULL) {
			cout << "No Memory" << endl;
			exit(EXIT_FAILURE);
		}
		*content = '\0';
	};// 无参
	~MyString();
	MyString(MyString& target); // 深拷贝
	friend ostream& operator<<(ostream& os, MyString& target); // 输出内容
	friend istream& operator>>(istream& is, MyString& target); // 读取内容，遇空格、回车停止
	bool operator==(const MyString& matched); // 判断两字符串是否一致
	MyString& operator=(const MyString target);
};
MyString& MyString::operator+=(char ch)
{
	this->size++;
	char* tmp = new char[size]; // 重新申请一个数组
	if (tmp == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size - 1; i++)
	{
		tmp[i] = this->content[i];
	}
	tmp[size - 2] = ch;
	tmp[size - 1] = '\0';
	delete this->content;
	this->content = tmp;
	return *this;
}
istream& operator>>(istream& is, MyString& target)
{
	if (target.size!=1) // size!=1，说明已有内容，清空重新输入
	{
		delete[]target.content;
		target.content = new char;
		if (target.content == NULL) {
			cout << "No Memory" << endl;
			exit(EXIT_FAILURE);
		}
		*target.content = '\0';
		target.size = 1;
	}
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
			target += tmp;
			break;
		}
	}
	while (true)
	{
		tmp = getchar(); // 每次读入一个字符
		if (tmp == ' ' || tmp=='\n') // 遇空格、回车停止
		{
			break;
		}
		else
		{
			target += tmp;
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
	if (this->size != matched.size)
	{
		return false; // 长度不一样，直接判不同
	}
	// 依次比较字符，有不同直接返回false
	for (int i = 0; i < size; i++)
	{
		if (this->content[i] != matched.content[i])
		{
			return false;
		}
	}
	return true;
}
MyString& MyString::operator=(const MyString target)
{
	size = target.size;
	delete content;
	content = new char[target.size];
	for (int i = 0; i < size; i++)
	{
		content[i] = target.content[i];
	}
	return *this;
}
MyString::MyString(const char* str)
{
	MyString::size = strlen(str) + 1; // 将\0纳入
	content = new char[MyString::size];
	if (content == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	// 依次读入，再放尾零
	for (int i = 0; i < size; i++)
	{
		content[i] = str[i];
	}
	content[size - 1] = '\0';
}
MyString::~MyString()
{
	delete content;
}
MyString::MyString(MyString& target)
{
	this->content = new char[target.size];
	size = target.size;
	if (content == NULL)
	{
		cout << "Memory Wrong" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < target.size; i++)
	{
		content[i] = target.content[i];
	}
}
/*
  *  家族成员结点
*/
struct NodeMember {
	MyString name;
	NodeMember* firstchild;
	NodeMember* nextSibling;
	NodeMember* prev;
	NodeMember(MyString _name) :name(_name), firstchild(NULL), nextSibling(NULL), prev(NULL) {};
};
/*
  *  家谱管理系统
*/
class FamilyTree {
private:
	NodeMember* root; // 根节点
public:
	FamilyTree() :root(NULL) {};
	~FamilyTree() { MakeEmpty(root); };

	void MakeEmpty(NodeMember* start); // 清空以start为根的整棵树
	bool IsEmpty() { return !bool(root); }; // 判断是否为空树
	void NewFamilyMember(NodeMember* Parent, NodeMember* child); // 添加新成员操作
	void InitTree(); // 初始化树，获取root结点信息
	void ManageTree(); // 管理家谱
	void GetChoice(char& chocie);
	void Perfect(); // 完善家谱
	void New(); // 添加成员指令
	void Break(); // 解散家庭
	void ChangeName(); // 更改姓名
	void FindName(MyString& target, NodeMember* now, NodeMember*& Addr); // 找到指定姓名
	void ShowChild(NodeMember* parent); // 打印某一成员的第一代子孙
};
void FamilyTree::ShowChild(NodeMember* parent)
{
	cout << parent->name << "的第一代子孙是:";
	NodeMember* out = parent->firstchild;
	while (out != NULL)
	{
		cout << " " << out->name;
		out = out->nextSibling;
	}
	cout << endl;
}
void FamilyTree::MakeEmpty(NodeMember* start)
{
	if (start->firstchild != NULL)
	{
		MakeEmpty(start->firstchild);
	}
	if (start->nextSibling != NULL)
	{
		MakeEmpty(start->nextSibling);
	}
	delete start;
	return;

}
void FamilyTree::NewFamilyMember(NodeMember* Parent, NodeMember* child)
{
	if (Parent->firstchild == NULL) // 无子孙
	{
		Parent->firstchild = child;
		child->prev = Parent;
	}
	else
	{
		// tmp找到最后一个孩子
		NodeMember* tmp = Parent->firstchild;
		while (tmp->nextSibling != NULL)
		{
			tmp = tmp->nextSibling;
		}
		tmp->nextSibling = child;
		child->prev = tmp;
	}
	
}
void FamilyTree::InitTree()
{
	cout << "**         家谱管理系统         **" << endl;
	cout << "==================================" << endl;
	cout << "**      请选择要执行的操作      **" << endl;
	cout << "**         A--完善家谱          **" << endl;
	cout << "**         B--添加家庭成员      **" << endl;
	cout << "**         C--解散局部家庭      **" << endl;
	cout << "**         D--更改家庭成员姓名  **" << endl;
	cout << "**         E--退出程序          **" << endl;
	cout << "==================================" << endl;
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名:" << endl;
	MyString RootName;
	cin >> RootName;
	root = new NodeMember(RootName);
	cout << "此家谱的祖先是:" << RootName << endl;
}
void FamilyTree::ManageTree()
{
	char choice;
	while (true)
	{
		GetChoice(choice); // 获取指令
		switch (choice)
		{
		case'A':
			Perfect();
			break;
		case'B':
			New();
			break;
		case'C':
			Break();
			break;
		case'D':
			ChangeName();
			break;
		default:
			return;
		}
	}
}
void FamilyTree::GetChoice(char& choice)
{
	cout << "\n请选择要执行的操作: ";
	cin >> choice;
	while (true)
	{
		if (!cin.good())
		{
			cout << "Wrong Input, input again please" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> choice;
		}
		else if (choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D' || choice == 'E')
		{
			break;
		}
		else
		{
			cout << "Wrong Input, input again please" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> choice;
		}
	}
	cin.ignore(1024, '\n'); // 清空缓冲区，避免MyString读取问题
}
void FamilyTree::Perfect()
{
	cout << "请输入要建立家庭的人的姓名: ";
	MyString ParentName;
	// 找到指定姓名
	NodeMember* Parent = NULL;
	while (true)
	{
		cin >> ParentName; // 获取祖先姓名
		Parent = NULL;
		FindName(ParentName, root, Parent); // 寻找指定姓名
		if (Parent == NULL) // 未找到名字
		{
			cout << "查无此人! 请重新输入: ";
		}
		else if (Parent->firstchild != NULL)
		{
			cout << "此人已有家庭，若要添加孩子请选择B指令" << endl;
			return;
		}
		else
		{
			break;
		}
	}
	cout << "请输入" << ParentName << "的儿女人数: ";
	int Num;
	while (true)
	{
		cin >> Num;
		if (!cin.good())
		{
			cout << "输入有误，请重新输入";
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (Num <= 0)
		{
			cout << "输入不是正数，不建立新家庭" << endl;
			return;
		}
		else // 输入有效，准备建立新家庭
		{
			break;
		}
	}
	cout << "请依次输入" << ParentName << "的儿女的姓名: ";
	int Count = 0;
	while (Count < Num)
	{
		MyString ChildName;
		cin >> ChildName;
		NodeMember* check = NULL; // 检查重名，不允许重名
		FindName(ChildName, root, check);
		if (check != NULL) // 说明有重名
		{
			cout << "第" << Count + 1 << "个名字与家谱已有人重名，请从此处重新输入至结尾" << endl;
		}
		else // 无重名，可添加
		{
			Count++;
			NodeMember* child = new NodeMember(ChildName);
			NewFamilyMember(Parent, child);
		}
	}
	ShowChild(Parent);
}
void FamilyTree::Break()
{
	cout << "请输入要解散家庭的人的姓名: ";
	MyString ParentName;
	NodeMember* Parent = NULL;
	/* find address*/
	while (true)
	{
		cin >> ParentName; // 获取姓名
		Parent = NULL;
		FindName(ParentName, root, Parent); // 寻找指定姓名
		if (Parent == NULL) // 未找到名字
		{
			cout << "查无此人! 请重新输入: ";
		}
		else
		{
			cout << "要解散家庭的人是: " << ParentName << endl;
			break;
		}
	}
	if (ParentName == root->name)
	{
		cout << "家谱里没有人了" << endl;
		MakeEmpty(root);
		exit(EXIT_SUCCESS);
	}
	/* show children */
	ShowChild(Parent);
	/* delete tree */
	if (Parent->prev != NULL)
	{
		if (Parent->prev->nextSibling == Parent)
		{
			Parent->prev->nextSibling = Parent->nextSibling;
		}
		else
		{
			Parent->prev->firstchild = Parent->nextSibling;
		}
	}
	MakeEmpty(Parent->firstchild);
	delete Parent;
}
void FamilyTree::ChangeName()
{
	cout << "请输入要更改姓名的人的目前姓名: ";
	MyString ParentName;
	NodeMember* Parent;
	/* find address*/
	while (true)
	{
		cin >> ParentName; // 获取姓名
		Parent = NULL;
		FindName(ParentName, root, Parent); // 寻找指定姓名
		if (Parent == NULL) // 未找到名字
		{
			cout << "查无此人! 请重新输入: ";
		}
		else
		{
			cout << "要更改姓名的人是: " << ParentName << endl;
			break;
		}
	}
	cout << "请输入更改后的姓名: ";
	MyString newName;
	NodeMember* check;
	while (true)
	{
		cin >> newName;
		check = NULL;
		FindName(newName, root, check);
		if (check == NULL) // 无重名
		{
			Parent->name = newName;
			cout << ParentName << "已更名为" << newName << endl;
			break;
		}
		else
		{
			cout << "新名字与家谱已有人重名，请重新输入" << endl;
		}
	}
}
void FamilyTree::New()
{
	cout << "请输入要添加的儿子(或女儿)的人的姓名: ";
	MyString ParentName;
	NodeMember* Parent;
	while (true)
	{
		cin >> ParentName; // 获取姓名
		Parent = NULL;
		FindName(ParentName, root, Parent); // 寻找指定姓名
		if (Parent == NULL) // 未找到名字
		{
			cout << "查无此人! 请重新输入: ";
		}
		else
		{
			break;
		}
	}
	cout << "请输入" << ParentName << "新添加的儿子(或女儿)的姓名: ";
	MyString childName;
	NodeMember* child;
	while (true)
	{
		cin >> childName;
		child = NULL;
		FindName(childName, root, child);
		if (child == NULL) // 无重名
		{
			child = new NodeMember(childName);
			NewFamilyMember(Parent, child);
			break;
		}
		else
		{
			cout << "新名字与家谱已有人重名，请重新输入" << endl;
		}
	}
	ShowChild(Parent);
}
void FamilyTree::FindName(MyString& target, NodeMember* now, NodeMember*& Addr)
{
	if (target == now->name)
	{
		Addr = now;
	}
	if (now->firstchild != NULL)
	{
		FindName(target, now->firstchild, Addr);
	}
	if (now->nextSibling != NULL)
	{
		FindName(target, now->nextSibling, Addr);
	}
	return;
}
int main()
{
	FamilyTree Family;
	Family.InitTree();
	Family.ManageTree();
	return 0;
}