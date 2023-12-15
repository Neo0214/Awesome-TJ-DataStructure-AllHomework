#include <iostream>
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
	MyString(MyString& target); // ���
	friend ostream& operator<<(ostream& os, MyString& target); // �������
	friend istream& operator>>(istream& is, MyString& target); // ��ȡ���ݣ����ո񡢻س�ֹͣ
	bool operator==(const MyString& matched); // �ж����ַ����Ƿ�һ��
	MyString& operator=(const MyString target);
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
	if (target.size!=1) // size!=1��˵���������ݣ������������
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
		if (tmp == ' ' || tmp=='\n') // ���ո񡢻س�ֹͣ
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
  *  �����Ա���
*/
struct NodeMember {
	MyString name;
	NodeMember* firstchild;
	NodeMember* nextSibling;
	NodeMember* prev;
	NodeMember(MyString _name) :name(_name), firstchild(NULL), nextSibling(NULL), prev(NULL) {};
};
/*
  *  ���׹���ϵͳ
*/
class FamilyTree {
private:
	NodeMember* root; // ���ڵ�
public:
	FamilyTree() :root(NULL) {};
	~FamilyTree() { MakeEmpty(root); };

	void MakeEmpty(NodeMember* start); // �����startΪ����������
	bool IsEmpty() { return !bool(root); }; // �ж��Ƿ�Ϊ����
	void NewFamilyMember(NodeMember* Parent, NodeMember* child); // ����³�Ա����
	void InitTree(); // ��ʼ��������ȡroot�����Ϣ
	void ManageTree(); // �������
	void GetChoice(char& chocie);
	void Perfect(); // ���Ƽ���
	void New(); // ��ӳ�Աָ��
	void Break(); // ��ɢ��ͥ
	void ChangeName(); // ��������
	void FindName(MyString& target, NodeMember* now, NodeMember*& Addr); // �ҵ�ָ������
	void ShowChild(NodeMember* parent); // ��ӡĳһ��Ա�ĵ�һ������
};
void FamilyTree::ShowChild(NodeMember* parent)
{
	cout << parent->name << "�ĵ�һ��������:";
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
	if (Parent->firstchild == NULL) // ������
	{
		Parent->firstchild = child;
		child->prev = Parent;
	}
	else
	{
		// tmp�ҵ����һ������
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
	cout << "**         ���׹���ϵͳ         **" << endl;
	cout << "==================================" << endl;
	cout << "**      ��ѡ��Ҫִ�еĲ���      **" << endl;
	cout << "**         A--���Ƽ���          **" << endl;
	cout << "**         B--��Ӽ�ͥ��Ա      **" << endl;
	cout << "**         C--��ɢ�ֲ���ͥ      **" << endl;
	cout << "**         D--���ļ�ͥ��Ա����  **" << endl;
	cout << "**         E--�˳�����          **" << endl;
	cout << "==================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�����:" << endl;
	MyString RootName;
	cin >> RootName;
	root = new NodeMember(RootName);
	cout << "�˼��׵�������:" << RootName << endl;
}
void FamilyTree::ManageTree()
{
	char choice;
	while (true)
	{
		GetChoice(choice); // ��ȡָ��
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
	cout << "\n��ѡ��Ҫִ�еĲ���: ";
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
	cin.ignore(1024, '\n'); // ��ջ�����������MyString��ȡ����
}
void FamilyTree::Perfect()
{
	cout << "������Ҫ������ͥ���˵�����: ";
	MyString ParentName;
	// �ҵ�ָ������
	NodeMember* Parent = NULL;
	while (true)
	{
		cin >> ParentName; // ��ȡ��������
		Parent = NULL;
		FindName(ParentName, root, Parent); // Ѱ��ָ������
		if (Parent == NULL) // δ�ҵ�����
		{
			cout << "���޴���! ����������: ";
		}
		else if (Parent->firstchild != NULL)
		{
			cout << "�������м�ͥ����Ҫ��Ӻ�����ѡ��Bָ��" << endl;
			return;
		}
		else
		{
			break;
		}
	}
	cout << "������" << ParentName << "�Ķ�Ů����: ";
	int Num;
	while (true)
	{
		cin >> Num;
		if (!cin.good())
		{
			cout << "������������������";
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (Num <= 0)
		{
			cout << "���벻���������������¼�ͥ" << endl;
			return;
		}
		else // ������Ч��׼�������¼�ͥ
		{
			break;
		}
	}
	cout << "����������" << ParentName << "�Ķ�Ů������: ";
	int Count = 0;
	while (Count < Num)
	{
		MyString ChildName;
		cin >> ChildName;
		NodeMember* check = NULL; // �������������������
		FindName(ChildName, root, check);
		if (check != NULL) // ˵��������
		{
			cout << "��" << Count + 1 << "�������������������������Ӵ˴�������������β" << endl;
		}
		else // �������������
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
	cout << "������Ҫ��ɢ��ͥ���˵�����: ";
	MyString ParentName;
	NodeMember* Parent = NULL;
	/* find address*/
	while (true)
	{
		cin >> ParentName; // ��ȡ����
		Parent = NULL;
		FindName(ParentName, root, Parent); // Ѱ��ָ������
		if (Parent == NULL) // δ�ҵ�����
		{
			cout << "���޴���! ����������: ";
		}
		else
		{
			cout << "Ҫ��ɢ��ͥ������: " << ParentName << endl;
			break;
		}
	}
	if (ParentName == root->name)
	{
		cout << "������û������" << endl;
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
	cout << "������Ҫ�����������˵�Ŀǰ����: ";
	MyString ParentName;
	NodeMember* Parent;
	/* find address*/
	while (true)
	{
		cin >> ParentName; // ��ȡ����
		Parent = NULL;
		FindName(ParentName, root, Parent); // Ѱ��ָ������
		if (Parent == NULL) // δ�ҵ�����
		{
			cout << "���޴���! ����������: ";
		}
		else
		{
			cout << "Ҫ��������������: " << ParentName << endl;
			break;
		}
	}
	cout << "��������ĺ������: ";
	MyString newName;
	NodeMember* check;
	while (true)
	{
		cin >> newName;
		check = NULL;
		FindName(newName, root, check);
		if (check == NULL) // ������
		{
			Parent->name = newName;
			cout << ParentName << "�Ѹ���Ϊ" << newName << endl;
			break;
		}
		else
		{
			cout << "���������������������������������" << endl;
		}
	}
}
void FamilyTree::New()
{
	cout << "������Ҫ��ӵĶ���(��Ů��)���˵�����: ";
	MyString ParentName;
	NodeMember* Parent;
	while (true)
	{
		cin >> ParentName; // ��ȡ����
		Parent = NULL;
		FindName(ParentName, root, Parent); // Ѱ��ָ������
		if (Parent == NULL) // δ�ҵ�����
		{
			cout << "���޴���! ����������: ";
		}
		else
		{
			break;
		}
	}
	cout << "������" << ParentName << "����ӵĶ���(��Ů��)������: ";
	MyString childName;
	NodeMember* child;
	while (true)
	{
		cin >> childName;
		child = NULL;
		FindName(childName, root, child);
		if (child == NULL) // ������
		{
			child = new NodeMember(childName);
			NewFamilyMember(Parent, child);
			break;
		}
		else
		{
			cout << "���������������������������������" << endl;
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