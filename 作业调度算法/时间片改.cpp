#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct PCB {
	int id;				//���̱�� 
	char name;			//��������
	int arrive;			//����ʱ��
	int serve;			//����ʱ��
	int finish;			//���ʱ��
	//�������Ȳο�����ʱ�䣬����Ƿ���ʱ�� 
	bool operator< (const PCB& t) const {
		if (arrive != t.arrive) return arrive < t.arrive;
		return serve < t.serve;
	};
};
const int N = 10;	//���10������
const int M = 100;	//�100��ʱ�䵥λ 
PCB pcb_list[N];	//�����б�
vector<PCB> table[M];	//����ʱ�̱�
queue<PCB> que;		//���̶���
int n, t, q, sjp;	//���������ܼ�ʱ���̶�ʱ��Ƭ����תʱ��Ƭ
int max_time;	//���ʱ��
void query() {	//��ѯ��ǰ�Ƿ��н��̵���������
	//����ǰʱ�̵����н������
	for (int i = 0; i < table[t].size(); i++)
		que.push(table[t][i]);
}
void run() {
	cout << "��ǰʱ��\t" << "���н���\t" << "ʣ�����ʱ��" << endl;
	PCB cur = pcb_list[0];	//��ʼ����ǰ����
	sjp = q;	//��ʼ��ʱ��Ƭ 
	for (t = 0; t <= max_time; t++) {	//��ʱ�� 
		query();	//��ǰ�Ƿ��н��̵���������
		if (que.empty()) continue;	//������пգ�����
		if (!sjp || !cur.serve) {	//ʱ��Ƭ������ �� ��ǰ�����������ˣ������ 
			sjp = q;	//�ָ�ʱ��Ƭ
			que.pop();	//���׳���
			if (cur.serve) que.push(cur);	//�����ǰ����û�������꣬���Ƶ���β
			else pcb_list[cur.id].finish = t;	//�������ˣ��������ʱ�� 
			if (!que.empty()) cur = que.front();	//ȡ�µĶ���
			else continue;	//�Ѿ����ˣ����� 
		}
		cout << t << "\t\t" << cur.name << "\t\t" << cur.serve << endl;	//�����ǰʱ��״̬ 
		sjp--, cur.serve--;	//ʱ��Ƭ-1����ǰ���̷���ʱ��-1 
	}
}
void set_max_time() {
	for (int i = 0; i < n; i++)
		max_time += pcb_list[i].serve;
	max_time += 5;//���һ�����߽�����
}
int main1() {
	printf("ʱ��Ƭ��ת�����㷨\n\n");
	printf("����������� ʱ��Ƭ\n");
	cin >> n >> q;	//�����������ʱ��Ƭʱ��
	printf("������ÿ�����̵Ľ����� ����ʱ�� ����ʱ��\n");
	for (int i = 0; i < n; i++)
		cin >> pcb_list[i].name >> pcb_list[i].arrive >> pcb_list[i].serve;
	sort(pcb_list, pcb_list + n);	//�Խ��̰�����ʱ������
	for (int i = 0; i < n; i++) {
		pcb_list[i].id = i;	//�����̱�� 
		table[pcb_list[i].arrive].push_back(pcb_list[i]);	//�������͵�ʱ�̱� 
	}
	set_max_time();	//�����������ʱ��
	run();	//��ʼ����
	cout << "��������\t" << "���ʱ��\t" << "��תʱ��\t" << "��Ȩ��תʱ��" << endl;
	for (int i = 0; i < n; i++) {
		int zzsj = pcb_list[i].finish - pcb_list[i].arrive;
		double dqzzsj = (double)zzsj / pcb_list[i].serve;
		printf("%c\t\t%d\t\t%d\t\t%.2lf\n", pcb_list[i].name, pcb_list[i].finish, zzsj, dqzzsj);
	}
	return 0;
}