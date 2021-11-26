#include<stdio.h> 
#include<conio.h> 
#include<iostream> 
using namespace std;
typedef struct Max // ��Դ�����������
{
	int m_a;
	int m_b;
	int m_c;
}Max;
typedef struct Allocation //�ѷ������Դ��
{
	int a_a;
	int a_b;
	int a_c;
}Allocation;
typedef struct Need //����Ҫ����Դ��
{
	int n_a;
	int n_b;
	int n_c;
}Need;
struct Available //�����õ���Դ��
{
	int av_a;
	int av_b;
	int av_c;
} q;
struct pr //����һ���ṹ1
{
	char name;
	Max max;
	Allocation allocation;
	Need need;
	int finishflag;
}p[5];
char na[5];
void init() //�����ļ�"input.txt" 
{
	cout << "�����̻���Ҫ����Դ�� NEED��" << endl;
	FILE* fp;
	fp = fopen("input.txt", "r+"); // ���ļ�"input.txt" 
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%c%d%d%d%d%d%d\n", &p[i].name, &p[i].max.m_a, &p[i].max.m_b, &p[i].max.m_c, &p[i].
			allocation.a_a, &p[i].allocation.a_b, &p[i].allocation.a_c);
		p[i].need.n_a = p[i].max.m_a - p[i].allocation.a_a;
		p[i].need.n_b = p[i].max.m_b - p[i].allocation.a_b;
		p[i].need.n_c = p[i].max.m_c - p[i].allocation.a_c;
		cout << p[i].name << ": " << p[i].need.n_a << " " << p[i].need.n_b << " " << p[i].need.n_c << endl;
	}
	fclose(fp); //�ر��ļ�
}
int fenpei() //������Դ
{
	cout << "Available:";
	cout << q.av_a << " " << q.av_b << " " << q.av_c << endl;
	int finishcnt = 0, k = 0, count = 0;
	for (int j = 0; j < 5; j++)
	{
		p[j].finishflag = 0;
	}
	while (finishcnt < 5)
	{
		for (int i = 0; i < 5; i++)
		{
			if (p[i].finishflag == 0 && q.av_a >= p[i].need.n_a && q.av_b >= p[i].need.n_b && q.av_c >= p[i].need.n_c)
			{
				q.av_a += p[i].allocation.a_a;
				q.av_b += p[i].allocation.a_b;
				q.av_c += p[i].allocation.a_c;
				p[i].finishflag = 1;
				finishcnt++;
				na[k++] = p[i].name;
				break;
			}
		}
		count++; //��ֹѭ������
		if (count > 5)
		{
			return 0;
		}
	}
	return 1;
}
int shq() //������Դ
{
	int m = 0, i = 0, j = 0, k = 0; //m Ϊ���̺�; i,j,k Ϊ�����������Դ�� 
	cout << "��������̺ź�������Դ����Ŀ!" << endl;
	cout << "�磺���̺� ��Դ A B C" << endl;
	cout << " 0 2 0 2" << endl;
	cin >> m >> i >> j >> k;
	if (i <= p[m].need.n_a && j <= p[m].need.n_b && k <= p[m].need.n_c)
	{
		if (i <= q.av_a && j <= q.av_b && k <= q.av_c)
		{
			p[m].allocation.a_a += i;
			p[m].allocation.a_b += j;
			p[m].allocation.a_c += k;
			p[m].need.n_a = p[m].max.m_a - p[m].allocation.a_a;
			p[m].need.n_b = p[m].max.m_b - p[m].allocation.a_b;
			p[m].need.n_c = p[m].max.m_c - p[m].allocation.a_c;
			cout << "�����̻���Ҫ����Դ�� NEED:" << '\n';
			for (int w = 0; w < 5; w++)
			{
				cout << p[w].name << ": " << p[w].need.n_a << " " << p[w].need.n_b << " " << p[w].need.n_c << endl;
			}
			return 1;
		}
		else
		{
			cout << "Request>Available �ý���" << m << "�ȴ�......" << endl;
		}
	}
	else
	{
		cout << "Request>Need,�ý���" << m << "�ȴ�......" << endl;
	}
	return 0;
}
void main()
{
	int flag=1;
	char c;
	cout << " /******** �� �� �� �� ��********/ " << endl;
	cout << "ȷ���Ѿ���\"input.txt\"�ĵ�����ȷ��������̵��й���Ϣ�󰴻س���" << endl;
	getch();
	init();
	q.av_a = 10; //������Դ������
	q.av_b = 5;
	q.av_c = 7;
	while (flag)
	{
		for (int i = 0; i < 5; i++)
		{
			q.av_a -= p[i].allocation.a_a;
			q.av_b -= p[i].allocation.a_b;
			q.av_c -= p[i].allocation.a_c;
		}
		if (fenpei())
		{
			cout << "����������Դ�ǰ�ȫ��!" << endl;
			cout << "�䰲ȫ�����ǣ� ";
			for (int k = 0; k < 5; k++)
			{
				cout << "-->" << na[k];
			}
			cout << endl;
			cout << "�н��̷��� Request ����������?(Enter y or Y)" << endl;
			cout << endl;
			c = getch();
			if (c == 'y' || c == 'Y')
			{
				if (shq())
					continue;
				else
					break;
			}
			else
				flag = 0;
		}
		else
		{
			flag = 0;
			cout << "����ȫ!!!" << endl;
		}
	}
}