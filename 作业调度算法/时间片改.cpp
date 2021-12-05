#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct PCB {
	int id;				//进程编号 
	char name;			//进程名字
	int arrive;			//到达时间
	int serve;			//服务时间
	int finish;			//完成时刻
	//排序优先参考到达时间，其次是服务时间 
	bool operator< (const PCB& t) const {
		if (arrive != t.arrive) return arrive < t.arrive;
		return serve < t.serve;
	};
};
const int N = 10;	//最多10个进程
const int M = 100;	//最长100个时间单位 
PCB pcb_list[N];	//进程列表
vector<PCB> table[M];	//进程时刻表
queue<PCB> que;		//进程队列
int n, t, q, sjp;	//进程数，总计时，固定时间片，运转时间片
int max_time;	//最大时间
void query() {	//查询当前是否有进程到达，有则入队
	//将当前时刻的所有进程入队
	for (int i = 0; i < table[t].size(); i++)
		que.push(table[t][i]);
}
void run() {
	cout << "当前时刻\t" << "运行进程\t" << "剩余服务时间" << endl;
	PCB cur = pcb_list[0];	//初始化当前进程
	sjp = q;	//初始化时间片 
	for (t = 0; t <= max_time; t++) {	//跑时间 
		query();	//当前是否有进程到达，有则入队
		if (que.empty()) continue;	//如果队列空，跳过
		if (!sjp || !cur.serve) {	//时间片用完了 或 当前进程运行完了，则调度 
			sjp = q;	//恢复时间片
			que.pop();	//队首出队
			if (cur.serve) que.push(cur);	//如果当前进程没有运行完，则移到队尾
			else pcb_list[cur.id].finish = t;	//运行完了，设置完成时刻 
			if (!que.empty()) cur = que.front();	//取新的队首
			else continue;	//已经空了，跳过 
		}
		cout << t << "\t\t" << cur.name << "\t\t" << cur.serve << endl;	//输出当前时刻状态 
		sjp--, cur.serve--;	//时间片-1，当前进程服务时间-1 
	}
}
void set_max_time() {
	for (int i = 0; i < n; i++)
		max_time += pcb_list[i].serve;
	max_time += 5;//多加一点避免边界问题
}
int main1() {
	printf("时间片轮转调度算法\n\n");
	printf("请输入进程数 时间片\n");
	cin >> n >> q;	//输入进程数和时间片时长
	printf("请输入每个进程的进程名 到达时间 服务时间\n");
	for (int i = 0; i < n; i++)
		cin >> pcb_list[i].name >> pcb_list[i].arrive >> pcb_list[i].serve;
	sort(pcb_list, pcb_list + n);	//对进程按到达时间排序
	for (int i = 0; i < n; i++) {
		pcb_list[i].id = i;	//给进程编号 
		table[pcb_list[i].arrive].push_back(pcb_list[i]);	//将进程送到时刻表 
	}
	set_max_time();	//设置最大运行时间
	run();	//开始运行
	cout << "进程名字\t" << "完成时间\t" << "周转时间\t" << "带权周转时间" << endl;
	for (int i = 0; i < n; i++) {
		int zzsj = pcb_list[i].finish - pcb_list[i].arrive;
		double dqzzsj = (double)zzsj / pcb_list[i].serve;
		printf("%c\t\t%d\t\t%d\t\t%.2lf\n", pcb_list[i].name, pcb_list[i].finish, zzsj, dqzzsj);
	}
	return 0;
}