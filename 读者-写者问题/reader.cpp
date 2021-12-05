#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<io.h>
#include<string.h>
#include <iostream>
using namespace std;
#define READER 'R'   //读者
#define WRITER 'W'   //写者
#define INTE_PER_SEC 1000 //每秒时钟中断的数目
#define MAX_THREAD_NUM 64  //最大线程数
#define MAX_FILE_NUM 32  //最大文件数目
#define MAX_STR_LEN 32  //字符串的长度
int readcount = 0;
int writecount = 0;
CRITICAL_SECTION RP_Write;//读者数目
CRITICAL_SECTION cs_Write;//写者数目
CRITICAL_SECTION cs_Read; //临界资源
struct ThreadInfo {
	int serial;//线程序号
	char entity;//线程类别（判断是读者还是写者进程）
	double delay;//线程延迟时间
	double persist;//线程读写操作时间
};
//读者优先-读者线程
//P:读者线程信息
void RP_ReaderThread(void* p) {
	HANDLE h_Mutex;//互斥变量
	h_Mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "mutex_for_readcount");
	DWORD wait_for_mutex; //等待互斥变量的所有权 
	DWORD m_delay; //延迟时间
	DWORD m_persist;//读文件持续时间
	int m_serial;
	//从参数中获得信息
	m_serial = ((ThreadInfo*)(p))->serial;
	m_delay = (DWORD)(((ThreadInfo*)(p))->delay * INTE_PER_SEC);
	m_persist = (DWORD)(((ThreadInfo*)(p))->persist * INTE_PER_SEC);
	Sleep(m_delay);  //延迟等待
	printf("读线程 %d 发出读请求.\n", m_serial);
	//等待互斥信号，保证对ReadCount的访问，修改互斥
	wait_for_mutex = WaitForSingleObject(h_Mutex, -1);
	//读者数目增加
	readcount++;
	if (readcount == 1) {
		//第一个读者，等待资源
		EnterCriticalSection(&RP_Write);//用来确保同一时刻只有一个线程操作被保护的数据的操作函数
	}
	ReleaseMutex(h_Mutex);
	//读文件
	printf("读线程 %d 开始读文件.\n", m_serial);
	Sleep(m_persist);
	//退出线程
	printf("读线程 %d 结束读文件.\n", m_serial);
	//等待互斥信号，保证对ReadCount的访问，修改互斥
	wait_for_mutex = WaitForSingleObject(h_Mutex, -1);
	//读者数目减少
	readcount--;
	if (readcount == 0) {
		LeaveCriticalSection(&RP_Write);
	}
	ReleaseMutex(h_Mutex);
}
//读者优先--写者进程
//P:写者线程信息
void RP_WriterThread(void* p) {
	DWORD m_delay;//延迟时间  
	DWORD m_persist;  //写文件持续时间
	int m_serial; //线程序号
	//从参数中获取信息
	m_serial = ((ThreadInfo*)(p))->serial;
	m_delay = (DWORD)(((ThreadInfo*)(p))->delay * INTE_PER_SEC);
	m_persist = (DWORD)(((ThreadInfo*)(p))->persist * INTE_PER_SEC);
	Sleep(m_delay);
	printf("写线程%d发出写请求***.\n", m_serial);
	//等待资源
	EnterCriticalSection(&RP_Write);
	//写文件
	printf("写线程%d开始写文件.\n", m_serial);
	Sleep(m_persist);
	//退出线程
	printf("写线程%d结束写文件.\n", m_serial);
	//释放资源
	LeaveCriticalSection(&RP_Write);
}
//读者优先处理函数
void ReaderPriority(const char* file) {
	DWORD n_thread = 0;
	DWORD thread_ID;
	DWORD wait_for_all;
	HANDLE h_Mutex;
	h_Mutex = CreateMutex(NULL, FALSE, "mutex_for_readcount");
	HANDLE h_Thread[MAX_THREAD_NUM];
	ThreadInfo thread_info[MAX_THREAD_NUM];
	readcount = 0;
	InitializeCriticalSection(&RP_Write);
	ifstream inFile;
	inFile.open(file);
	if (inFile.rdstate() == ios::failbit) {
		printf("打开文件\"%os\"失败!请将\"%s\"放程序目录下。\n", file, file);
		return;
	}
	printf("读者优先：\n\n");
	while (inFile) {
		inFile >> thread_info[n_thread].serial;
		inFile >> thread_info[n_thread].entity;
		inFile >> thread_info[n_thread].delay;
		inFile >> thread_info[n_thread++].persist;
		inFile.get();
	}
	for (int i = 0; i < (int)(n_thread); i++) {
		if (thread_info[i].entity == READER || thread_info[i].entity == 'r') {
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(RP_ReaderThread), &thread_info[i], 0, &thread_ID);//创建读者进程
		}
		else {
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(RP_WriterThread), &thread_info[i], 0, &thread_ID);//创建写者进程
		}
	}
	//等待所有的线程结束
	wait_for_all = WaitForMultipleObjects(n_thread, h_Thread, TRUE, -1);
	printf("所有的读写线程结束操作.\n");
}
int main(int argc, const char* argv[]) {
	ReaderPriority("input.txt");
	printf("\n按任意键结束：");
	system("pause");
	return 0;
}