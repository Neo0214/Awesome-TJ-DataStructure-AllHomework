#include <iostream>
#include <conio.h>
#include <cstring>
#include <iomanip>
using namespace std;
 
/*
	����string�࣬ʵ�ֱ䳤�ȴ洢�ַ�
*/
class MyString {
private:
	MyString& operator+=(char ch); // ĩβ���һ���ַ�
	int size; // �ַ�������
	char* content; // ����ָ��
public:
	MyString(const char* str);
	MyString() :size(1) {
		content = new char;
		if (content == NULL) {
			cout << "No Memory" << endl;
			exit(EXIT_FAILURE);
		}
		*content = '\0';
	};// �޲�
	~MyString();
	friend ostream& operator<<(ostream& os, MyString& target); // �������
	friend istream& operator>>(istream& is, MyString& target); // ��ȡ���ݣ����ո񡢻س�ֹͣ
	bool operator==(const MyString& matched); // �ж����ַ����Ƿ�һ��
};
MyString& MyString::operator+=(char ch)
{
	this->size++;
	char* tmp = new char[size]; // ��������һ������
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
	if (target.size != 1) // size!=1��˵���������ݣ������������
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
		tmp = getchar(); // ÿ�ζ���һ���ַ�
		if (tmp == ' ' || tmp == '\n') // ���ո񡢻س�ֹͣ
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
		return false; // ���Ȳ�һ����ֱ���в�ͬ
	}
	// ���αȽ��ַ����в�ֱͬ�ӷ���false
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
	MyString::size = strlen(str) + 1; // ��\0����
	content = new char[MyString::size];
	if (content == NULL)
	{
		cout << "No Memory" << endl;
		exit(EXIT_FAILURE);
	}
	// ���ζ��룬�ٷ�β��
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
	ѧ����Ϣ���
*/
struct LinkNode_StuInfo { 
	MyString num;
	MyString name;
	bool sex = 0; // 0Ů1��
	int age = 0;
	MyString category;
	LinkNode_StuInfo* next = NULL;
};
/*
	����ʵ�ֹ���ϵͳ
*/
class ManageSystem {
private:
	int StuNum; // ѧ������
	LinkNode_StuInfo* head; // ��¼�׸����
	void init(); // ��������
public:
	ManageSystem() :StuNum(0), head(NULL) {};
	void GetInfo(); // ��ȡ��ʼ��Ϣ
	int GetChoice(); // ��ȡ����ѡ��
	void Exit(); // �˳�ϵͳ
	void Insert(); // ������Ϣ
	void Delete(); // ɾ����Ϣ
	void Seek(); // ������Ϣ
	void Change(); // ������Ϣ
	void Statistic(); // ͳ����Ϣ
	void show(); // չʾ��Ϣ
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
		if (i == 0) // ��¼ͷ���
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
				cout << "�Ա�����(��1Ů0)����ӵ�" << i + 1 << "��ѧ����ʼ��������������Ϣ" << endl;
			}
		}
		if (i != 0)// ������һ���
		{ 
			p_Record->next = p_Work;
		}
		p_Record = p_Work;
	}
	if (p_Work != NULL) // �˾�Ϊȡ��intelligence Warning C6011
	{
		p_Work->next = NULL;
	}
	show();
}
void ManageSystem::GetInfo()
{
	cout << "�����뽨��������Ϣϵͳ!\n�����뿼������:";
	while (true)
	{ // ���������
		cin >> StuNum;
		if (!cin.good()) 
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "������������������!" << endl;
		}
		else if (StuNum <= 0)
		{
			cout << "����������������������" << endl;
		}
		else
			break;
	}
	cout << "���������뿼���Ŀ���,����,�Ա�,���估�������!" << endl;
	init();
}
void ManageSystem::Change()
{
	cout << "������Ҫ�޸ĵĿ����Ŀ���:";
	MyString query;
	cin >> query;
	// ����
	LinkNode_StuInfo* p_Work = head;
	while (p_Work != NULL)
	{
		if (p_Work->num == query) 
		{
			break;
		} // ���ҳɹ�
		p_Work = p_Work->next;
	}
	if (p_Work == NULL) 
	{ // ����ʧ��
		cout << "���޴���!" << endl;
	}
	else
	{ // ���ҳɹ�
		cout << "����������Ҫ�޸ĵĿ����Ŀ���,����,�Ա�,���估�������!" << endl;
		cin >> p_Work->num >> p_Work->name >> p_Work->sex >> p_Work->age >> p_Work->category;
		// ��ȡ�޸ĺ�����
	}
}
void ManageSystem::Delete()
{
	cout << "������Ҫɾ���Ŀ����Ŀ���:";
	MyString Delete_Query;
	cin >> Delete_Query;
	// ɾ��
	LinkNode_StuInfo* p_Work = head; // ����ָ��
	if (p_Work->num == Delete_Query)
	{ // ���ΪĿ��
		head = p_Work->next;
		delete p_Work;
		cout << "�ѳɹ�ɾ���ÿ�����Ϣ" << endl;
		StuNum--;
		if (StuNum == 0)
		{
			cout << "���޿����������Զ��˳�" << endl;
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
			} // ���ҳɹ���λ��Ϊp->next
			p_Work = p_Work->next;
		}
	}

	if (p_Work->next == NULL)
	{ // ����ʧ��
		cout << "���޴���!" << endl;
	}
	else 
	{ // ���ҳɹ��Ҳ�Ϊ����
		LinkNode_StuInfo* p_Record = p_Work->next;
		p_Work->next = p_Record->next;
		delete p_Record;
		cout << "�ѳɹ�ɾ���ÿ�����Ϣ" << endl;
		StuNum--;
	}
	if (StuNum == 0)
	{
		cout << "���޿����������Զ��˳�" << endl;
		exit(EXIT_SUCCESS);
	}
}
void ManageSystem::Exit()
{
	cout << "����ѡ���˳�ϵͳ,�밴�س��뿪";
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
	cout << "��ѡ����Ҫ���еĲ���(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������)" << endl;
	cout << "\n��ѡ����Ҫ���еĲ���:";
	int choice;
	cin >> choice;
	while (true) 
	{
		if (!cin.good()) 
		{
			cout << "����Ƿ�������������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> choice;
		}
		else if (choice < 0 || choice > 5) 
		{
			cout << "������������������";
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
	cout << "��������Ҫ����Ŀ���λ��:";
	int address = 0;
	cin >> address;
	// ���������
	while (true)
	{
		if (!cin.good())
		{
			cout << "����Ƿ�������������!" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> address;
		}
		else if (address <= 0 || address > StuNum + 1) 
		{
			cout << "����Ƿ�������������!" << endl;
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
	cout << "����������Ҫ����Ŀ����Ŀ���,����,�Ա�,���估�������!" << endl;
	cin >> NewMember->num >> NewMember->name >> NewMember->sex >> NewMember->age >> NewMember->category;
	// ��ȡ�³�Ա����
	LinkNode_StuInfo* p_Work = head; // ����ָ��
	for (int i = 0; i < address - 2; i++) 
	{
		p_Work = p_Work->next;
	}
	if (p_Work == head) 
	{ // �ڿ�ͷ����
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
	cout << "������Ҫ���ҵĿ����Ŀ���:";
	MyString query;
	cin >> query;
	// ����
	LinkNode_StuInfo* p_Work = head;
	while (p_Work != NULL)
	{
		if (p_Work->num == query)
		{
			break;
		} // ���ҳɹ�
		p_Work = p_Work->next;
	}
	if (p_Work == NULL)
	{ // ����ʧ��
		cout << "���޴���!" << endl;
	}
	else 
	{ // ���ҳɹ�
		cout << endl;
		cout << setiosflags(ios::left); // �Ҷ���ģʽ
		cout << "����      ����          �Ա�    ����    ��������" << endl;
		cout << setfill(' ') << setw(10) << p_Work->num <<
			setw(14) << p_Work->name <<
			setw(8) << (p_Work->sex ? "��" : "Ů") <<
			setw(8) << p_Work->age <<
			p_Work->category << endl;
	}
}
void ManageSystem::Statistic()
{
	cout << "ȫԱ��Ϣͳ������" << endl;
	ManageSystem::show();
}
void ManageSystem::show()
{
	cout << endl;
	cout << setiosflags(ios::left); // �Ҷ���ģʽ
	cout << "����      ����          �Ա�    ����    ��������" << endl;
	LinkNode_StuInfo* p = head;
	while (p != NULL)
	{
		cout <<setfill(' ')<<setw(10)<<p->num <<
			setw(14) << p->name <<
			setw(8) << (p->sex ? "��" : "Ů") <<
			setw(8) << p->age <<
			p->category << endl;
		p = p->next;
	}
}

int main()
{
	ManageSystem ExamRegister;
	ExamRegister.GetInfo(); // ��ȡ��ʼ��Ϣ
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