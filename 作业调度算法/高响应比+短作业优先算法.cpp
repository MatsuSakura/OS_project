#include <iostream>
#include <stdlib.h> 
#include<string.h>
using namespace std;
//����һ���ṹ��
struct jcb {
	char name[10]; //��ҵ��
	float arrivetime; //����ʱ��
	float servicetime;//����ʱ��
	float starttime; //��ʼʱ��
	float finishtime;//���ʱ��
	float rtime;//��תʱ��
	float drtime;//��Ȩ��ת
	float Rp;//��Ӧ�� 
}*b;

static int N;//��ҵ���� 

//����һ���ṹ������
jcb a[100];

void input(jcb* a);//���ĵ��������ݵĺ���
void display(jcb* a);//��ʾ��������� 
void Print(jcb* a, int N);//����һ���������
void sort(jcb* a, int N);//������ʱ������
void deal(jcb* a, int N);//���н׶�
void hrrn(jcb* a, int N);
void sjff(jcb* a, int N);

//���ĵ��������ݵĺ���
void input(jcb* a)
{
	int i;

	FILE* fp;
	fp = fopen("input1.txt", "r");
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &N);
	for (i = 0; i < N; i++) {
		fscanf(fp, "%s %f %f", &a[i].name, &a[i].arrivetime, &a[i].servicetime);
	}

}

//��ʾ��������� 
void display(jcb* a)
{
	printf("��������ݣ�\n");
	printf("��������%d\n", N);
	printf("������ ����ʱ�� ����ʱ��\n");
	for (int i = 0; i < N; i++) {
		printf("  %s      %2.2f       %2.2f\n", a[i].name, a[i].arrivetime, a[i].servicetime);
	}
}

//����һ���������
void Print(jcb* p, int N)
{
	int k;

	printf("ִ�е�˳����:");//ִ��˳��
	printf("%s", p[0].name);
	for (k = 1; k < N; k++)
	{
		printf("-->%s", p[k].name);
	}
	printf("\n-----------���------------\n");
	printf("\n====================================================================================\n");
	printf("������   ����ʱ��  ����ʱ��  ��ʼʱ��  ���ʱ��   ��תʱ��   ��Ȩ��תʱ��\n");

	for (k = 0; k <= N - 1; k++)
	{
		printf("%4s  %8.2f  %9.2f  %7.2f  %9.2f  %9.2f %12.2f\n", p[k].name, p[k].arrivetime, p[k].servicetime, p[k].starttime, p[k].finishtime, p[k].rtime, p[k].drtime);
	}

}
//������ʱ������
void sort(jcb* p, int N)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j <= i; j++)
			if (p[i].arrivetime < p[j].arrivetime)
			{
				jcb temp;
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
}

//���н׶�
void deal(jcb* p, int N)
{
	int k;
	for (k = 0; k < N; k++)
	{
		if (k == 0)
		{
			p[k].starttime = p[k].arrivetime;//��һ�����̵Ŀ�ʼʱ��=����ʱ��
			p[k].finishtime = p[k].arrivetime + p[k].servicetime;
		}//���ʱ��=����ʱ��+����ʱ��
		else
		{
			if (p[k - 1].finishtime >= p[k].arrivetime)
			{
				p[k].starttime = p[k - 1].finishtime;
			}
			else
			{
				p[k].starttime = p[k].arrivetime;
			}
			p[k].finishtime = p[k].starttime + p[k].servicetime;
		}
	}

	for (k = 0; k < N; k++)
	{
		p[k].rtime = p[k].finishtime - p[k].arrivetime;//��תʱ��=���ʱ��-����ʱ��
		p[k].drtime = p[k].rtime / p[k].servicetime;//��Ȩ��תʱ��=��תʱ��/����ʱ��

	}
}

//����Ӧ�����ȵ����㷨
void hrrn(jcb* p, int N)
{
	display(p);
	float arrivetime = 0, servicetime = 0, starttime = 0, finishtime = 0, rtime = 0, drtime = 0, Rp = 0;
	int num = 1;

	sort(p, N);

	for (int m = 0; m < N - 1; m++)
	{
		if (m == 0)
			p[m].finishtime = p[m].arrivetime + p[m].servicetime;
		else
		{
			if (p[m - 1].finishtime >= p[m].arrivetime)
			{
				p[m].starttime = p[m - 1].finishtime;
			}
			else
			{
				p[m].starttime = p[m].arrivetime;
			}
			p[m].finishtime = p[m].starttime + p[m].servicetime;
		}

		int i = 0;
		for (int n = m + 1; n < N; n++)
		{
			if (p[n].arrivetime <= p[m].finishtime)//������ʱ������֮����i���ĺ������ҵ��m���ǰ���� 
				i++;
		}


		//������Ӧ������
		p[m + 1].Rp = (p[m].finishtime - p[m + 1].arrivetime + p[m + 1].servicetime) / p[m + 1].servicetime; //Rp=��һ��(m)���ʱ��-�������ʱ�� 
//������ 
		printf("��%d�ε���\n", num++);
		printf("������   ����ʱ��  ����ʱ��  ��ʼʱ��  ���ʱ��   ��תʱ��   ��Ȩ��תʱ��   ����Ȩ\n");
		//        printf("m+1���ļ���Rp�Ĺ��̣�(%.2f - %.2f + %.2f)/%.2f = %.2f\n",p[m].finishtime,p[m+1].arrivetime,p[m+1].servicetime,p[m+1].servicetime,p[m+1].Rp);
		printf("%4s  %8.2f  %9.2f  %7.2f  %9.2f  %9.2f %12.2f %12.2f\n", p[m + 1].name, p[m + 1].arrivetime, p[m + 1].servicetime, p[m + 1].starttime, p[m + 1].finishtime, p[m + 1].rtime, p[m + 1].drtime, p[m + 1].Rp);
		float max = p[m + 1].Rp;
		int next = m + 1;//m+1=n
		for (int k = m + 1; k < m + i; k++)
		{
			p[k + 1].Rp = (p[m].finishtime - p[k + 1].arrivetime + p[k + 1].servicetime) / p[k + 1].servicetime;
			//������ 
			printf("%4s  %8.2f  %9.2f  %7.2f  %9.2f  %9.2f %12.2f %12.2f\n", p[k + 1].name, p[k + 1].arrivetime, p[k + 1].servicetime, p[k + 1].starttime, p[k + 1].finishtime, p[k + 1].rtime, p[k + 1].drtime, p[k + 1].Rp);

			if (p[k + 1].Rp > max)
			{
				max = p[k + 1].Rp;
				next = k + 1;
			}

		}
		jcb temp;
		temp = p[m + 1];
		p[m + 1] = p[next];
		p[next] = temp;
	}
	deal(p, N);

	Print(p, N);
}


//����ҵ���ȵ����㷨

void sjff(jcb* p, int N)
{
	display(p);
	float arrivetime = 0, servicetime = 0, starttime = 0, finishtime = 0, rtime = 0, drtime = 0;


	sort(p, N);//����sort����


	for (int m = 0; m < N - 1; m++)
	{
		if (m == 0)
			p[m].finishtime = p[m].arrivetime + p[m].servicetime;
		else
		{
			if (p[m - 1].finishtime >= p[m].arrivetime)
			{
				p[m].starttime = p[m - 1].finishtime;
			}
			else
			{
				p[m].starttime = p[m].arrivetime;
			}
			p[m].finishtime = p[m].starttime + p[m].servicetime;
		}

		int i = 0;
		for (int n = m + 1; n < N; n++)//n��m�� 
		{
			if (p[n].arrivetime <= p[m].finishtime)//������ʱ������֮����i���ĺ������ҵ��m���ǰ���� 
				i++;
		}
		//������ʱ������Ҳ����˵����ɣ�����ȷ����m+1��˭���ѣ�����������
		float min = p[m + 1].servicetime;
		int next = m + 1;//m+1=n
		for (int k = m + 1; k < m + i; k++)//Ϊʲôû�� = ����Ϊ�����0��ʼ�� 
		{
			if (p[k + 1].servicetime < min)
			{
				min = p[k + 1].servicetime;
				next = k + 1;
			}

		}
		jcb temp;
		temp = p[m + 1];
		p[m + 1] = p[next];
		p[next] = temp;
	}

	deal(p, N);

	Print(p, N);
}

int main3()
{
	int aa;
	printf("��ҵ�����㷨��1.SJF 2.HRRN 3.quit\n");
	scanf("%d", &aa);

	while (aa != 3) {

		switch (aa) {
		case 1:
			input(a);
			b = a;
			sjff(a, N);//����sjff����

			break;

		case 2:

			input(a);
			b = a;
			hrrn(a, N);
			break;

		default:
			break;
		}

		printf("��ҵ�����㷨��1.SJF 2.HRRN 3.quit\n");
		scanf("%d", &aa);
	}
	printf("end.\n");

	return 0;
}