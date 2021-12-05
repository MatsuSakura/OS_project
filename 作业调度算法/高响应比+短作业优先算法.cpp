#include <iostream>
#include <stdlib.h> 
#include<string.h>
using namespace std;
//定义一个结构体
struct jcb {
	char name[10]; //作业名
	float arrivetime; //到达时间
	float servicetime;//服务时间
	float starttime; //开始时间
	float finishtime;//完成时间
	float rtime;//周转时间
	float drtime;//带权周转
	float Rp;//响应比 
}*b;

static int N;//作业个数 

//定义一个结构体数组
jcb a[100];

void input(jcb* a);//向文档读入数据的函数
void display(jcb* a);//显示输入的数据 
void Print(jcb* a, int N);//定义一个输出函数
void sort(jcb* a, int N);//按到达时间排序
void deal(jcb* a, int N);//运行阶段
void hrrn(jcb* a, int N);
void sjff(jcb* a, int N);

//向文档读入数据的函数
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

//显示输入的数据 
void display(jcb* a)
{
	printf("输入的数据：\n");
	printf("进程数：%d\n", N);
	printf("进程名 到达时间 服务时间\n");
	for (int i = 0; i < N; i++) {
		printf("  %s      %2.2f       %2.2f\n", a[i].name, a[i].arrivetime, a[i].servicetime);
	}
}

//定义一个输出函数
void Print(jcb* p, int N)
{
	int k;

	printf("执行的顺序是:");//执行顺序
	printf("%s", p[0].name);
	for (k = 1; k < N; k++)
	{
		printf("-->%s", p[k].name);
	}
	printf("\n-----------结果------------\n");
	printf("\n====================================================================================\n");
	printf("进程名   到达时间  服务时间  开始时间  完成时间   周转时间   带权周转时间\n");

	for (k = 0; k <= N - 1; k++)
	{
		printf("%4s  %8.2f  %9.2f  %7.2f  %9.2f  %9.2f %12.2f\n", p[k].name, p[k].arrivetime, p[k].servicetime, p[k].starttime, p[k].finishtime, p[k].rtime, p[k].drtime);
	}

}
//按到达时间排序
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

//运行阶段
void deal(jcb* p, int N)
{
	int k;
	for (k = 0; k < N; k++)
	{
		if (k == 0)
		{
			p[k].starttime = p[k].arrivetime;//第一个进程的开始时间=到达时间
			p[k].finishtime = p[k].arrivetime + p[k].servicetime;
		}//完成时间=到达时间+服务时间
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
		p[k].rtime = p[k].finishtime - p[k].arrivetime;//周转时间=完成时间-到达时间
		p[k].drtime = p[k].rtime / p[k].servicetime;//带权周转时间=周转时间/服务时间

	}
}

//高响应比优先调度算法
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
			if (p[n].arrivetime <= p[m].finishtime)//按到达时间排序之后，有i个的后面的作业比m完成前到来 
				i++;
		}


		//按高响应比排序
		p[m + 1].Rp = (p[m].finishtime - p[m + 1].arrivetime + p[m + 1].servicetime) / p[m + 1].servicetime; //Rp=上一个(m)完成时间-这个到达时间 
//检测代码 
		printf("第%d次调度\n", num++);
		printf("进程名   到达时间  服务时间  开始时间  完成时间   周转时间   带权周转时间   优先权\n");
		//        printf("m+1个的计算Rp的过程：(%.2f - %.2f + %.2f)/%.2f = %.2f\n",p[m].finishtime,p[m+1].arrivetime,p[m+1].servicetime,p[m+1].servicetime,p[m+1].Rp);
		printf("%4s  %8.2f  %9.2f  %7.2f  %9.2f  %9.2f %12.2f %12.2f\n", p[m + 1].name, p[m + 1].arrivetime, p[m + 1].servicetime, p[m + 1].starttime, p[m + 1].finishtime, p[m + 1].rtime, p[m + 1].drtime, p[m + 1].Rp);
		float max = p[m + 1].Rp;
		int next = m + 1;//m+1=n
		for (int k = m + 1; k < m + i; k++)
		{
			p[k + 1].Rp = (p[m].finishtime - p[k + 1].arrivetime + p[k + 1].servicetime) / p[k + 1].servicetime;
			//检测代码 
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


//短作业优先调度算法

void sjff(jcb* p, int N)
{
	display(p);
	float arrivetime = 0, servicetime = 0, starttime = 0, finishtime = 0, rtime = 0, drtime = 0;


	sort(p, N);//调用sort函数


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
		for (int n = m + 1; n < N; n++)//n在m后 
		{
			if (p[n].arrivetime <= p[m].finishtime)//按到达时间排序之后，有i个的后面的作业比m完成前到来 
				i++;
		}
		//按服务时间排序（也不是说排序吧，就是确定了m+1是谁而已，把它调出来
		float min = p[m + 1].servicetime;
		int next = m + 1;//m+1=n
		for (int k = m + 1; k < m + i; k++)//为什么没有 = ，因为数组从0开始的 
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
	printf("作业调度算法：1.SJF 2.HRRN 3.quit\n");
	scanf("%d", &aa);

	while (aa != 3) {

		switch (aa) {
		case 1:
			input(a);
			b = a;
			sjff(a, N);//调用sjff函数

			break;

		case 2:

			input(a);
			b = a;
			hrrn(a, N);
			break;

		default:
			break;
		}

		printf("作业调度算法：1.SJF 2.HRRN 3.quit\n");
		scanf("%d", &aa);
	}
	printf("end.\n");

	return 0;
}