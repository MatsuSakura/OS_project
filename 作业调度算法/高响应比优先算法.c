#include"string.h" 
#include <stdio.h>
#define n 10 //�ٶ�ϵͳ�����ɵ���ҵ����Ϊ N 
#pragma warning(disable:4996)
typedef struct jcb
{
	char name[4]; //��ҵ��
	int length; //��ҵ���ȣ������ڴ��С
	int printer; //��ҵִ������Ĵ�ӡ������
	int tape; //��ҵִ������ĴŴ�������
	int runtime; //��ҵ��������ʱ��
	int waittime; //��ҵ��ϵͳ�еĵȴ�ʱ��
	int next; //ָ����һ����ҵ���ƿ��ָ��
}JCB;
int head;
int tape, printer;
long memory;
JCB jobtable[n]; //��ҵ��
int jobcount = 0; //ϵͳ��������ҵ����
void shedule()
{
	float xk, k;
	int p, q, s, t;
	do
	{
		p = head;
		q = s = -1;
		k = 0;
		while (p != -1)
		{
			//ϵͳ������Դ���Ƿ�������ҵ����
			if (jobtable[p].length <= memory && jobtable[p].tape <= tape && jobtable[p].printer <= printer)
			{
				xk = (float)(jobtable[p].waittime + jobtable[p].runtime) / jobtable[p].runtime;
				if (q == 0 || xk > k)
					//���������ĵ�һ����ҵ������ҵ q ����Ӧ��С����ҵ P ����Ӧ��
				{
					k = xk;
					q = p;
					t = s;
				}
			}
			s = p;
			p = jobtable[p].next; //ָ�����
		}
		if (q != -1)
		{
			if (t == -1) //����ҵ���еĵ�һ��
				head = jobtable[head].next;
			else
				jobtable[t].next = jobtable[q].next;
			memory = memory - jobtable[q].length; //Ϊ��ҵ�����ڴ�ռ�
			tape = tape - jobtable[q].tape; //Ϊ��ҵ����Ŵ���
			printer = printer - jobtable[q].printer; //Ϊ��ҵ�����ӡ��
			printf("ѡ�е���ҵ����ҵ����%s\n", jobtable[q].name);
		}
	} while (q != -1);
}
void main()
{
	char name[4];
	int size, tcount, pcount, wtime, rtime;
	int p;
	memory = 65536; //ϵͳ���ݳ�ʼ��
	tape = 4;
	printer = 2;
	head = -1;
	printf("��������ҵ������ݣ�����ҵ��СΪ����ֹͣ���룩��\n"); //�������ݣ���������
	printf("������ҵ�� ��ҵ��С �Ŵ����� ��ӡ���� �ȴ�ʱ�� ��������ʱ��\n");
	scanf("%s%d%d %d %d %d", name, &size, &tcount, &pcount, &wtime, &rtime);
	while (size != -1)
	{ //���� JCB 
		if (jobcount < n)
			p = jobcount;
		else
		{
			printf("�޷��ڴ�����ҵ\n");
			break;
		}
		jobcount++;
		strcpy(jobtable[p].name, name); //��д��ҵ����
		jobtable[p].length = size;
		jobtable[p].printer = pcount;
		jobtable[p].tape = tcount;
		jobtable[p].runtime = rtime;
		jobtable[p].waittime = wtime;
		jobtable[p].next = head; //������ҵ�Ӷ���
		head = p;
		printf("������ҵ�� ��ҵ��С �Ŵ����� ��ӡ���� �ȴ�ʱ�� ��������ʱ��\n"); //��������
		scanf("%s%d%d %d %d %d", name, &size, &tcount, &pcount, &wtime, &rtime);
	}
	shedule(); //������ҵ����
	return;
}