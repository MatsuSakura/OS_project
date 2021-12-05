//ʱ��Ƭ��ת�㷨
#include<stdlib.h> 
#include"stdio.h" 
#define MAX 5 //��������
#define RR 2 //ʱ��Ƭ��С
#pragma warning(disable:4996)
struct pro
{
	int num;
	int arriveTime;
	int burst;
	int rt; //��¼���̱����еĴ���
	struct pro* next;
};
int TOTALTIME; //��¼���н��̵���ʱ��
//��������
struct pro* creatList();
void insert(struct pro* head, struct pro* s);
struct pro* searchByAT(struct pro* head, int AT);
void del(struct pro* p);
int getCount(struct pro* head, int time);
struct pro* searchEnd(struct pro* head);
void move(struct pro* headF, struct pro* headT, int n);
struct pro* creatList() //�����������ս��̵Ĵﵽʱ�����У���¼���н�����Ϣ
{
	struct pro* head = (struct pro*)malloc(sizeof(struct pro));
	head->next = NULL;
	struct pro* s;
	int i;
	TOTALTIME = 0;
	for (i = 0; i < MAX; i++)
	{
		s = (struct pro*)malloc(sizeof(struct pro));
		printf("�����������:\n");
		scanf("%d", &(s->num));
		printf("������ﵽʱ��\n");
		scanf("%d", &(s->arriveTime));
		printf("����������ʱ��\n");
		scanf("%d", &(s->burst));
		TOTALTIME += s->burst; //������ʱ��
		s->rt = 1; //rt �ĳ�ʼֵΪ 1 
		s->next = NULL;
		insert(head, s);
	}
	return head; //��������еĽ��̰��յ���ʱ����Ⱥ�˳������
}
void insert(struct pro* head, struct pro* s) //����ڵ�
{
	struct pro* p = searchByAT(head, s->arriveTime);
	s->next = p->next;
	p->next = s;
	return;
}
struct pro* searchByAT(struct pro* head, int AT) //���ҵ�һ������ʱ����ڵ��� AT �Ľڵ㣬������ǰһ��ָ��
{
	struct pro* p, * q;
	p = head;
	q = head->next;
	while (q != NULL && q->arriveTime <= AT)
	{
		p = q;
		q = q->next;
	}
	return p;
}
void del(struct pro* p) //ɾ�� p ����һ���ڵ�
{
	struct pro* tmp;
	tmp = p->next;
	p->next = tmp->next;
	free(tmp);
	return;
}
int getCount(struct pro* head, int time) //������ time ֮ǰ���ﵫδ�ƶ������ж��еĽ���
{
	int count = 0;
	struct pro* s, * t;
	s = head;
	t = s->next;
	while (t != NULL && t->arriveTime <= time)
	{
		s = t;
		t = t->next;
		count++; //count ��¼��ǰʱ�̵���Ľ�����
	}
	return count;
}
struct pro* searchEnd(struct pro* head) //���Ҳ�����ѭ�����е�β�ڵ��ǰһ���ڵ�
{
	struct pro* p, * q;
	p = head;
	q = head->next;
	while (q->next != head)
	{
		p = q;
		q = q->next;
	}
	return p;
}
void move(struct pro* headF, struct pro* headT, int n) //�� headF ��� n ���ڵ��ƶ���ѭ������ headT ��
{
	struct pro* r, * s, * t;
	s = headF;
	t = s->next;
	r = t; //r ��¼Ҫ�ƶ��ĵ�һ���ڵ�
	while (n > 1)
	{
		t = t->next;
		n--;
	}
	s->next = t->next; //������ɴ�ԭ������ժ����ؽڵ㣬r��t �ֱ�Ϊ��һ�������һ���ڵ�
	s = searchEnd(headT);
	t->next = s->next;
	s->next = r;
}
void run(struct pro* head)
{
	int time = 0; //��¼��ǰʱ��
	int newarrive;//�µ��������
	struct pro* runhead = (struct pro*)malloc(sizeof(struct pro));
	runhead->next = runhead; //�����µ�ѭ��������ŵ�ǰ���������еĽ���
	struct pro* p, * q;
	p = runhead;
	q = p->next; //q ��¼��ǰӦ�����еĽ���
	while (time <= TOTALTIME)
	{
		newarrive = getCount(head, time);
		if (newarrive > 0)
			move(head, runhead, newarrive); //�� head ��� newarrive ���ڵ��ƶ��� runhead ������
		if (runhead->next == runhead) //����������û�н���
			time++;
		else if (q == runhead)
		{
			p = q;
			q = q->next;
		}
		else
		{
			printf("������%d\n", q->num);
			printf("����ʱ��:%d\n", q->arriveTime);
			if (q->rt == 1)
				printf("��Ӧʱ��:%d\n", time - q->arriveTime);
			else
				printf("��%d �ο�ʼ����ʱ�䣺%d\n", q->rt, time);
			if (q->burst <= RR)
			{
				time += q->burst;
				printf("��%d �����н���ʱ�䣺%d\n", q->rt, time);
				printf("��תʱ��:%d\n", time - q->arriveTime);
				printf("************************************\n");
				struct pro* tmp = q;
				q = q->next;
				p->next = q;
				free(tmp);
			}
			else //q->burst>RR 
			{
				time += RR;
				printf("��%d �����н���ʱ�䣺%d\n", q->rt, time);
				printf("************************************\n");
				q->burst -= RR;
				q->rt++;
				p = q;
				q = q->next;
			}
		}
	}
}
int main2()
{
	struct pro* head = creatList();
	printf("��ǰʱ��Ƭ��СΪ:%d\n", RR);
	run(head);
	system("pause");
	return 0;
}
