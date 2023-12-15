#include <iostream>
#include <conio.h>
#include <cstring>
#include <iomanip>
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
	friend ostream& operator<<(ostream& os, MyString& target); // 输出内容
	friend istream& operator>>(istream& is, MyString& target); // 读取内容，遇空格、回车停止
	bool operator==(const MyString& matched); // 判断两字符串是否一致
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
	if (target.size != 1) // size!=1，说明已有内容，清空重新输入
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
		if (tmp == ' ' || tmp == '\n') // 遇空格、回车停止
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
/*
	学生信息结点
*/
struct LinkNode_StuInfo { 
	MyString num;
	MyString name;
	bool sex = 0; // 0女1男
	int age = 0;
	MyString category;
	LinkNode_StuInfo* next = NULL;
};
/*
	链表实现管理系统
*/
class ManageSystem {
private:
	int StuNum; // 学生总数
	LinkNode_StuInfo* head; // 记录首个结点
	void init(); // 生成链表
public:
	ManageSystem() :StuNum(0), head(NULL) {};
	void GetInfo(); // 获取初始信息
	int GetChoice(); // 获取操作选项
	void Exit(); // 退出系统
	void Insert(); // 插入信息
	void Delete(); // 删除信息
	void Seek(); // 查找信息
	void Change(); // 更改信息
	void Statistic(); // 统计信息
	void show(); // 展示信息
};

void ManageSystem::init()
{
	struct LinkNode_StuInfo* p_Work = NULL, * p_Record = NULL;
	int sextmp;
	for (int i = 0; i < StuNum; i++)
	{
		p_Work = new LinkNode_StuInfo;
		if (p_Work == NULL)
		{
			cout << "Memory Wrong" << endl;
			exit(EXIT_FAILURE);
		}
		if (i == 0) // 记录头结点
		{ 
			head = p_Work;
		}
		while (true)
		{
			cin >> p_Work->num >> p_Work->name >> sextmp >> p_Work->age >> p_Work->category;
			if (sextmp == 0 || sextmp == 1)
			{
				p_Work->sex = sextmp;
				break;
			}
			else 
			{
				cout << "性别有误(男1女0)，请从第" << i + 1 << "个学生开始重新输入所有信息" << endl;
			}
		}
		if (i != 0)// 连接下一结点
		{ 
			p_Record->next = p_Work;
		}
		p_Record = p_Work;
	}
	if (p_Work != NULL) // 此句为取消intelligence Warning C6011
	{
		p_Work->next = NULL;
	}
	show();
}
void ManageSystem::GetInfo()
{
	cout << "首先请建立考生信息系统!\n请输入考生人数:";
	while (true)
	{ // 输入错误处理
		cin >> StuNum;
		if (!cin.good()) 
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入有误，请重新输入!" << endl;
		}
		else if (StuNum <= 0)
		{
			cout << "请输入正数！请重新输入" << endl;
		}
		else
			break;
	}
	cout << "请依次输入考生的考号,姓名,性别,年龄及报考类别!" << endl;
	init();
}
void ManageSystem::Change()
{
	cout << "请输入要修改的考生的考号:";
	MyString query;
	cin >> query;
	// 查找
	LinkNode_StuInfo* p_Work = head;
	while (p_Work != NULL)
	{
		if (p_Work->num == query) 
		{
			break;
		} // 查找成功
		p_Work = p_Work->next;
	}
	if (p_Work == NULL) 
	{ // 查找失败
		cout << "查无此人!" << endl;
	}
	else
	{ // 查找成功
		cout << "请依次输入要修改的考生的考号,姓名,性别,年龄及报考类别!" << endl;
		cin >> p_Work->num >> p_Work->name >> p_Work->sex >> p_Work->age >> p_Work->category;
		// 获取修改后数据
	}
}
void ManageSystem::Delete()
{
	cout << "请输入要删除的考生的考号:";
	MyString Delete_Query;
	cin >> Delete_Query;
	// 删除
	LinkNode_StuInfo* p_Work = head; // 工作指针
	if (p_Work->num == Delete_Query)
	{ // 首项即为目标
		head = p_Work->next;
		delete p_Work;
		cout << "已成功删除该考生信息" << endl;
		StuNum--;
		if (StuNum == 0)
		{
			cout << "已无考生待处理，自动退出" << endl;
			exit(EXIT_SUCCESS);
		}
		return; 
	}
	else 
	{
		while (p_Work->next != NULL)
		{
			if (p_Work->next->num == Delete_Query) 
			{
				break;
			} // 查找成功，位置为p->next
			p_Work = p_Work->next;
		}
	}

	if (p_Work->next == NULL)
	{ // 查找失败
		cout << "查无此人!" << endl;
	}
	else 
	{ // 查找成功且不为首项
		LinkNode_StuInfo* p_Record = p_Work->next;
		p_Work->next = p_Record->next;
		delete p_Record;
		cout << "已成功删除该考生信息" << endl;
		StuNum--;
	}
	if (StuNum == 0)
	{
		cout << "已无考生待处理，自动退出" << endl;
		exit(EXIT_SUCCESS);
	}
}
void ManageSystem::Exit()
{
	cout << "您已选择退出系统,请按回车离开";
	char ch = '\0';
	while (true)
	{
		ch = _getch();
		if (ch == '\r')
			break;
	}
}
int ManageSystem::GetChoice()
{
	cout << "请选择您要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)" << endl;
	cout << "\n请选择您要进行的操作:";
	int choice;
	cin >> choice;
	while (true) 
	{
		if (!cin.good()) 
		{
			cout << "输入非法，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> choice;
		}
		else if (choice < 0 || choice > 5) 
		{
			cout << "数字有误，请重新输入";
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> choice;
		}
		else
		{
			break;
		}
	}
	return choice;
}
void ManageSystem::Insert()
{
	cout << "请输入你要插入的考生位置:";
	int address = 0;
	cin >> address;
	// 输入错误处理
	while (true)
	{
		if (!cin.good())
		{
			cout << "输入非法，请重新输入!" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> address;
		}
		else if (address <= 0 || address > StuNum + 1) 
		{
			cout << "输入非法，请重新输入!" << endl;
			cin >> address;
		}
		else
		{
			break;
		}
	}
	LinkNode_StuInfo* NewMember = NULL;
	NewMember = new LinkNode_StuInfo;
	if (NewMember == NULL)
	{
		cout << "Memory Wrong!" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "请依次输入要插入的考生的考号,姓名,性别,年龄及报考类别!" << endl;
	cin >> NewMember->num >> NewMember->name >> NewMember->sex >> NewMember->age >> NewMember->category;
	// 获取新成员数据
	LinkNode_StuInfo* p_Work = head; // 工作指针
	for (int i = 0; i < address - 2; i++) 
	{
		p_Work = p_Work->next;
	}
	if (p_Work == head) 
	{ // 在开头插入
		head = NewMember;
		NewMember->next = p_Work;
	}
	else 
	{
		NewMember->next = p_Work->next;
		p_Work->next = NewMember;
	}
	StuNum++;
}
void ManageSystem::Seek()
{
	cout << "请输入要查找的考生的考号:";
	MyString query;
	cin >> query;
	// 查找
	LinkNode_StuInfo* p_Work = head;
	while (p_Work != NULL)
	{
		if (p_Work->num == query)
		{
			break;
		} // 查找成功
		p_Work = p_Work->next;
	}
	if (p_Work == NULL)
	{ // 查找失败
		cout << "查无此人!" << endl;
	}
	else 
	{ // 查找成功
		cout << endl;
		cout << setiosflags(ios::left); // 右对齐模式
		cout << "考号      姓名          性别    年龄    报考类型" << endl;
		cout << setfill(' ') << setw(10) << p_Work->num <<
			setw(14) << p_Work->name <<
			setw(8) << (p_Work->sex ? "男" : "女") <<
			setw(8) << p_Work->age <<
			p_Work->category << endl;
	}
}
void ManageSystem::Statistic()
{
	cout << "全员信息统计如下" << endl;
	ManageSystem::show();
}
void ManageSystem::show()
{
	cout << endl;
	cout << setiosflags(ios::left); // 右对齐模式
	cout << "考号      姓名          性别    年龄    报考类型" << endl;
	LinkNode_StuInfo* p = head;
	while (p != NULL)
	{
		cout <<setfill(' ')<<setw(10)<<p->num <<
			setw(14) << p->name <<
			setw(8) << (p->sex ? "男" : "女") <<
			setw(8) << p->age <<
			p->category << endl;
		p = p->next;
	}
}

int main()
{
	ManageSystem ExamRegister;
	ExamRegister.GetInfo(); // 获取初始信息
	int choice = 0;
	while (choice = ExamRegister.GetChoice())
	{
		switch (choice){
		case 1:
			ExamRegister.Insert();
			break;
		case 2:
			ExamRegister.Delete();
			break;
		case 3:
			ExamRegister.Seek();
			break;
		case 4:
			ExamRegister.Change();
			break;
		case 5:
			ExamRegister.Statistic();
			break;
		}
	}
	ExamRegister.Exit();
	return 0;
}