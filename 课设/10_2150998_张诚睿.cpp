#include <iostream>
#include <time.h>
using namespace std;
class Rank {
private:
	int length; // ��������
	int* data; // ����������
	long long int times;
	time_t begin, end;
public:
	Rank() :data(NULL), length(0), begin(0), end(0), times(0) { srand(unsigned int(time(NULL))); };
	~Rank() { delete[]data; };
	void StartTime();
	void EndTime();
	void Choose();
	void InitData();
	void Ranking();
	void BubbleSort();
	void SelectSort();
	void InsertionSort();
	void ShellSort();
	void QuickSort(); // �ܺ���
	void QuickSort(int startPos, int endPos); // ʵ�ֺ���
	void HeapSort();
	void MergeSort();
	void RadixSort();
	void out();
	void initHeap(int* content);
	void siftUp(int start, int* content); // �ϻ�����
	void siftDown(int start, int end, int* content); // �»�����
	void Merge(int* L1, int* L2, int left, int right);
	void MergeCalc(int* L1, int* L2, int left, int mid, int right);
	void Radix(int* List, int left, int right, int Weigh);
	int Digit(int num, int Weigh);
};
void Rank::StartTime()
{
	time(&begin);
}
void Rank::EndTime()
{
	time(&end);
}
void Rank::Choose()
{
	system("cls");
	cout << "**      �����㷨�Ƚ�      **" << endl;
	cout << "============================" << endl;
	cout << "**      1--ð������       **" << endl;
	cout << "**      2--ѡ������       **" << endl;
	cout << "**      3--ֱ�Ӳ�������   **" << endl;
	cout << "**      4--ϣ������       **" << endl;
	cout << "**      5--��������       **" << endl;
	cout << "**      6--������         **" << endl;
	cout << "**      7--�鲢����       **" << endl;
	cout << "**      8--��������       **" << endl;
	cout << "**      9--�˳�����       **" << endl;
	cout << "============================" << endl;
	// ��ȡ��ȷ��lengthֵ
	cout << "\n������Ҫ������������ĸ���: " << endl;
	cin >> length;
	while (true)
	{
		if (!cin.good())
		{
			cout << "input number please" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> length;
		}
		else if (length == 100 || length == 1000 || length == 10000 || length == 100000)
		{
			break;
		}
		else
		{
			cout << "only 100/1000/10000/100000 is available" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			cin >> length;
		}
	}
}
void Rank::InitData()
{
	data = new int[length];
	if (data == NULL)
	{
		cout << "Memory Wrong" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < length; i++)
	{
		data[i] = rand() % 1000; // ���0 ~ 999
	}
}
void Rank::Ranking()
{
	int choice = 0;
	while (true)
	{
		cout << "��ѡ�������㷨: ";
		cin >> choice;
		while (true)
		{
			if (!cin.good())
			{
				cout << "Wrong input, please input again" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				cin >> choice;
			}
			else if (choice <= 0 || choice > 9)
			{
				cout << "Wrong input, please input again" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
				cin >> choice;
			}
			else
			{
				break;
			}
		}
		InitData(); // ÿ�λ����򷽷�ǰ�����������
		switch (choice)
		{
		case 1:
			BubbleSort();
			break;
		case 2:
			SelectSort();
			break;
		case 3:
			InsertionSort();
			break;
		case 4:
			ShellSort();
			break;
		case 5:
			QuickSort();
			break;
		case 6:
			HeapSort();
			break;
		case 7:
			MergeSort();
			break;
		case 8:
			RadixSort();
			break;
		case 9:
			return;
		default:
			return;
		}
	}	
}
void Rank::BubbleSort()
{
	times = 0;
	StartTime();
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length - 1 - i; j++)
		{
			if (data[j] > data[j + 1])
			{
				times++;
				int tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}
	EndTime();
	out();
}
void Rank::SelectSort()
{
	times = 0;
	StartTime();
	for (int i = 0; i < length - 1; i++)
	{
		int minAddress = i; // ��ǰ����λ��Ϊ��Сֵ
		for (int j = i + 1; j < length; j++)
		{
			if (data[j] < data[minAddress])
			{
				minAddress = j;
			}
		}
		if (minAddress != i) // ��Ҫ����
		{
			times++;
			int tmp = data[i];
			data[i] = data[minAddress];
			data[minAddress] = tmp;
		}
	}
	EndTime();
	out();
}
void Rank::InsertionSort()
{
	times = 0;
	StartTime();
	for (int i = 1; i < length; i++)
	{ // ��һ��Ԫ��Ĭ�������򣬴ӵڶ���Ԫ�ؿ�ʼ����
		int j = i - 1;
		int tmp = data[i];
		for (; j >= 0; j--)
		{
			if (data[j] > tmp)
			{ // ������ǰ�ң�ԭλ�����Ų
				times++;
				data[j + 1] = data[j];
			}
			else
			{
				break;
			}
		}
		times++;
		data[j + 1] = tmp;
	}
	EndTime();
	out();
}
void Rank::ShellSort()
{
	times = 0;
	StartTime();
	// step���鲽��
	for (int step = length / 2; step > 0; step /= 2)
	{
		for (int i = step; i < length; i += step)
		{
			int j = i - step;
			int tmp = data[i];
			for (; j >= 0; j-=step)
			{
				if (data[j] > tmp)
				{ // ������ǰ�ң�ԭλ�����Ų
					data[j + step] = data[j];
					times++;
				}
				else
				{
					break;
				}
			}
			times++;
			data[j + step] = tmp;
		}
	}
	EndTime();
	out();
}
void Rank::QuickSort()
{
	times = 0;
	StartTime();
	QuickSort(0, length - 1);
	EndTime();
	out();
}
void Rank::QuickSort(int startPos, int endPos)
{
	if (startPos >= endPos)
	{
		return;
	}
	int key = data[startPos]; // ѡȡ��һ��Ԫ��Ϊ��׼ֵ
	int keyPos = startPos; // ��¼��׼ֵ����λ��
	int left = startPos + 1, right = endPos; // ��¼������������λ��
	while (left <= right)
	{
		if (right>keyPos && data[right] >= key) // ˳����ȷ������
		{
			right--;
		}
		else if (right>keyPos) // С����ǰ������
		{
			times++;
			data[keyPos] = data[right];
			keyPos = right;
			right--;
		}
		if (left < keyPos && data[left] <= key)
		{
			left++;
		}
		else if (left<keyPos)
		{
			times++;
			data[keyPos] = data[left];
			keyPos = left;
			left++;
		}
	}
	data[keyPos] = key;
	QuickSort(startPos, keyPos - 1); // ����������
	QuickSort(keyPos + 1, endPos); // ����������
}
void Rank::HeapSort()
{
	times = 0;
	StartTime();
	int* heap = new int[length]; // �½�������
	initHeap(heap); // ��������
	for (int i = length - 1; i > 0;)
	{
		times++;
		int tmp = heap[0];
		heap[0] = heap[i];
		heap[i--] = tmp;
		// ����ͷβ
		siftDown(0, i, heap); // ���µ���Ϊ����
	}
	EndTime();
	for (int i = 0; i < length; i++)
	{
		data[i] = heap[i];
	}
	delete[]heap;
	out();
}
void Rank::MergeSort()
{
	times = 0;
	StartTime();
	/* �ݹ���� */
	int* L2 = new int[length];
	Merge(data, L2, 0, length-1);
	EndTime();
	delete[]L2;
	out();
}
void Rank::RadixSort()
{
	times = 0;
	StartTime();
	/* �ݹ���� */
	Radix(data, 0, length - 1, 0);
	EndTime();
	out();
}
void Rank::out()
{
	cout << "��ʱ: " << end - begin << endl;
	cout << "��������: " << times << endl;
	cout << endl;
}
void Rank::initHeap(int* content)
{
	for (int i = 0; i < length; i++)
	{ // ��������
		content[i] = data[i]; // ���ݷ������
		siftUp(i, content);
	}
}
void Rank::siftUp(int start, int* content)
{
	int j = start, i = (j - 1) / 2, tmp = content[j];
	while (j > 0)
	{
		if (content[i] >= tmp)
		{
			break;
		}
		else
		{
			times++;
			content[j] = content[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	content[j] = tmp;
}
void Rank::siftDown(int start, int end, int* content)
{
	int i = start, j = 2 * i + 1;
	int tmp = content[i];
	while (j <= end)
	{
		if (j < end && content[j] < content[j + 1])
		{
			j++; // ָ���Һ���
		}
		if (tmp >= content[j])
		{
			break;
		}
		else
		{
			times++;
			content[i] = content[j];
			i = j;
			j = i * 2 + 1;
		}
	}
	content[i] = tmp;
}
void Rank::Merge(int* L1, int* L2, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	Merge(L1, L2, left, mid);
	Merge(L1, L2, mid + 1, right);
	MergeCalc(L1, L2, left, mid, right);
}
void Rank::MergeCalc(int* L1, int* L2, int left, int mid, int right)
{
	for (int i = left; i <= right; i++)
	{
		L2[i] = L1[i]; // ���ƽ�L2
	}
	int s1 = left, s2 = mid + 1, tmp = left;
	while (s1 <= mid && s2 <= right) // ˫ָ��
	{
		times++;
		if (L2[s1] <= L2[s2])
		{
			L1[tmp++] = L2[s1++];
		}
		else
		{
			L1[tmp++] = L2[s2++];
		}
	}
	/* ʣ�ಿ�� */
	while (s1 <= mid)
	{
		times++;
		L1[tmp++] = L2[s1++];
	}
	while (s2 <= right)
	{
		times++;
		L1[tmp++] = L2[s2++];
	}
}
void Rank::Radix(int* List, int left, int right, int Weigh)
{
	if (left >= right || Weigh > 2)
	{
		return;
	}
	int* auxArray = new int[right - left + 1];
	int count[10];
	for (int i = 0; i < 10; i++)
	{
		count[i] = 0;
	}
	for (int i = left; i <= right; i++)
	{
		count[Digit(List[i], Weigh)]++;
	}
	/* ����Ͱ�ĵ�ַ */
	int posit[10];
	posit[0] = 0;
	for (int i = 1; i < 10; i++)
	{
		posit[i] = count[i - 1] + posit[i - 1];
	}
	for (int i = left; i <= right; i++)
	{
		int j = Digit(List[i], Weigh);
		auxArray[posit[j]++] = List[i]; // �ŵ�Ͱ��
	}
	for (int i = left, j = 0; i <= right; i++, j++)
	{
		List[i] = auxArray[j];
	}
	delete[]auxArray;
	int pos1 = left;
	for (int i = 0; i < 10; i++)
	{
		int pos2 = pos1 + count[i] - 1;
		Radix(List, pos1, pos2, Weigh + 1);
		pos1 = pos2 + 1;
	}
}
int Rank::Digit(int num, int Weigh)
{
	int prev = 0;
	for (int i = 0, div = 100; i <= Weigh; i++)
	{
		prev = num / div;
		num = num - prev * div;
		div /= 10;
	}
	return prev;
}
int main()
{
	Rank TimeTest;
	TimeTest.Choose();
	TimeTest.Ranking();
	return 0;
}