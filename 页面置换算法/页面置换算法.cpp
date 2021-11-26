#include<iostream> 
using namespace std;
void Print(int bc[], int blockCount)
{
	for (int i = 0; i < blockCount; i++)
	{
		cout << bc[i] << " ";
	}
	cout << endl;
}
int Travel(int bc[], int blockCount, int x)
{
	int index = -1;
	int i;
	for (i = 0; i < blockCount; i++)
	{
		if (bc[i] == x)
		{
			index = i;
			break;
		}
	}
	return index;
}
void FIFO(int pc[], int bc[], int pageCount, int blockCount)
{
	cout << "0��FIFO �û��㷨" << endl;
	int i;
	if (pageCount <= blockCount)
	{
		cout << "ȱҳ����Ϊ" << 0 << endl;
		cout << "ȱҳ��Ϊ" << 0 << endl;
	}
	else
	{
		int noPage = 0;
		int p = 0;
		for (i = 0; i < pageCount; i++)
		{
			cout << "����ҳ��" << pc[i] << endl;
			if (Travel(bc, blockCount, pc[i]) == -1) //ҳ�治���ڴ�
			{
				if (i < blockCount) //Ԥ��ҳ
				{
					bc[i] = pc[i];
				}
				else
				{
					�� //ҳ�治���ڴ棬��̭���Ƚ����ҳ��
				}

				noPage++;
				cout << "����������";
				Print(bc, blockCount);
			}
			cout << endl;
		}
		cout << "ȱҳ����Ϊ:" << noPage << endl;
		cout << "ȱҳ��Ϊ:" << (float)noPage / pageCount << endl;
	}
}
int FoundMaxNum(int a[], int n)
{
	int k, j;
	k = a[0];
	j = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] >= k)
		{
			k = a[i];
			j = i;
		}
	}
	return j;
}
void LRU(int pc[], int bc[], int pageCount, int blockCount)
{
	cout << "1��LRU �û��㷨" << endl;
	if (pageCount <= blockCount)
	{
		cout << "ȱҳ����Ϊ" << 0 << endl;
		cout << "ȱҳ��Ϊ" << 0 << endl;
	}
	else
	{
		int noPage = 0;
		int i, j, m;
		int* bc1 = new int[blockCount];
		for (i = 0; i < blockCount; i++)
		{
			bc1[i] = 0;
		}
		for (i = 0; i < pageCount; i++)
		{
			cout << "����ҳ��" << pc[i] << endl;
			if (Travel(bc, blockCount, pc[i]) == -1) //ҳ�治���ڴ�
			{
				if (i < blockCount) //Ԥ��ҳ
				{
					bc[i] = pc[i];
					for (int p = 0; p <= i; p++)
					{
						bc1[p]++;
					}
				}
				else //��̭������δʹ�õ�ҳ��
				{
					for (j = 0; j < blockCount; j++)
					{
						bc1[j]++;
					}
					int k = FoundMaxNum(bc1, blockCount);
					bc[k] = pc[i];
					bc1[k] = 1;
				}
				noPage++;
				cout << "����������";
				Print(bc, blockCount);
			}
			else //ҳ�����ڴ�
			{
				if (i < blockCount)
				{
					for (j = 0; j <= i; j++)
					{
						bc1[j]++;
					}
					for (m = 0; m < i; m++)
					{
						if (bc[m] == pc[i])
						{
							break;
						}
					}
					bc1[m] = 1;
					bc[m] = pc[i];
				}
				else
				{
					for (j = 0; j < blockCount; j++)
					{
						bc1[j]++;
					}
					for (m = 0; m < blockCount; m++)
					{
						if (bc[m] == pc[i])
						{
							break;
						}
					}
					bc1[m] = 1;
					bc[m] = pc[i];
				}
			}
			cout << endl;
		}
		cout << "ȱҳ����Ϊ:" << noPage << endl;
		cout << "ȱҳ��Ϊ:" << (float)noPage / pageCount << endl;
		delete bc1;
	}
}
void Optiomal(int pc[], int bc[], int pageCount, int blockCount)
{
	cout << "2������û��㷨" << endl;
	if (pageCount <= blockCount)
	{
		cout << "ȱҳ����Ϊ" << 0 << endl;
		cout << "ȱҳ��Ϊ" << 0 << endl;
	}
	else
	{
		int noPage = 0;
		int i, j, k;
		for (i = 0; i < pageCount; i++)
		{
			cout << "����ҳ��" << pc[i] << endl;
			if (Travel(bc, blockCount, pc[i]) == -1) //ҳ�治���ڴ�
			{
				if (i < blockCount) //Ԥ��ҳ
				{
					bc[i] = pc[i];
				}
				else //ҳ���û�
				{
					int max = 0;
					int blockIndex;;
					for (j = 0; j < blockCount; j++)
					{
						for (k = i; k < pageCount; k++)
						{
							if (bc[j] == pc[k])
							{
								break;
							}
						}
						if (k >= max)
						{
							max = k;
							blockIndex = j;
						}
					}
					bc[blockIndex] = pc[i];
				}
				noPage++;
				cout << "����������";
				Print(bc, blockCount);
			}
			cout << endl;
		}
		cout << "ȱҳ����Ϊ:" << noPage << endl;
		cout << "ȱҳ��Ϊ:" << (float)noPage / pageCount << endl;
	}
}
void NRU(int pc[], int bc[], int pageCount, int blockCount)
{
	cout << "3��Clock �û��㷨" << endl;
	if (pageCount <= blockCount)
	{
		cout << "ȱҳ����Ϊ" << 0 << endl;
		cout << "ȱҳ��Ϊ" << 0 << endl;
	}
	else
	{
		int noPage = 0;
		int i, j;
		int* bc1 = new int[blockCount];
		for (i = 0; i < blockCount; i++) //����λ��ʼ��
		{
			bc1[i] = 0;
		}
		int replace = 0;
		for (i = 0; i < pageCount; i++)
		{
			cout << "����ҳ��" << pc[i] << endl;
			int index = Travel(bc, blockCount, pc[i]);
			if (index == -1) //ҳ�治���ڴ�
			{
				for (j = 0; j < blockCount; j++) //���ҷ���λΪ 0 ��ҳ��
				{
					if (bc1[replace] == 1)
					{
						bc1[replace] = 0;
						replace = (replace + 1) % blockCount;
					}
					else
					{
						break;
					}
				}
				bc[replace] = pc[i];
				bc1[replace] = 1;
				replace = (replace + 1) % blockCount;
				noPage++;
				cout << "����������";
				Print(bc, blockCount);
				cout << "��־λ�����";
				Print(bc1, blockCount);
			}
			else
			{
				bc1[index] = 1;
				replace = (index + 1) % blockCount;
				cout << "����������";
				Print(bc, blockCount);
				cout << "��־λ�����";
				Print(bc1, blockCount);
			}
			cout << endl;
		}
		cout << "ȱҳ����Ϊ:" << noPage << endl;
		cout << "ȱҳ��Ϊ:" << (float)noPage / pageCount << endl;
		delete bc1;
	}
}
int main()
{
	int pageCount, blockCount, i;
	cout << "����ҳ����" << endl;
	cin >> pageCount;
	int* pc = new int[pageCount];
	cout << "����ҳ������" << endl;
	for (i = 0; i < pageCount; i++)
	{
		cin >> pc[i];
	}
	cout << "�����������" << endl;
	cin >> blockCount;
	cout << "0��FIFO �û��㷨" << endl;
	cout << "1��LRU �û��㷨" << endl;
	cout << "2������û��㷨" << endl;
	cout << "3��Clock �û��㷨" << endl;
	cout << "������ѡ���㷨���" << endl;
	int n;
	while (cin >> n)
	{
		if (n == 0)
		{
			int* bc = new int[blockCount];
			FIFO(pc, bc, pageCount, blockCount);
			delete bc;
		}
		else if (n == 1)
		{
			int* bc = new int[blockCount];
			LRU(pc, bc, pageCount, blockCount);
			delete bc;
		}
		else if (n == 2)
		{
			int* bc = new int[blockCount];
			Optiomal(pc, bc, pageCount, blockCount);
			delete bc;
		}
		else if (n == 3)
		{
			int* bc = new int[blockCount];
			for (i = 0; i < blockCount; i++)
			{
				bc[i] = -1;
			}
			NRU(pc, bc, pageCount, blockCount);
			delete bc;
		}
		else break;
	}
	delete pc;
	return 0;
}