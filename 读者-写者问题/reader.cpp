#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<io.h>
#include<string.h>
#include <iostream>
using namespace std;
#define READER 'R'   //����
#define WRITER 'W'   //д��
#define INTE_PER_SEC 1000 //ÿ��ʱ���жϵ���Ŀ
#define MAX_THREAD_NUM 64  //����߳���
#define MAX_FILE_NUM 32  //����ļ���Ŀ
#define MAX_STR_LEN 32  //�ַ����ĳ���
int readcount = 0;
int writecount = 0;
CRITICAL_SECTION RP_Write;//������Ŀ
CRITICAL_SECTION cs_Write;//д����Ŀ
CRITICAL_SECTION cs_Read; //�ٽ���Դ
struct ThreadInfo {
	int serial;//�߳����
	char entity;//�߳�����ж��Ƕ��߻���д�߽��̣�
	double delay;//�߳��ӳ�ʱ��
	double persist;//�̶߳�д����ʱ��
};
//��������-�����߳�
//P:�����߳���Ϣ
void RP_ReaderThread(void* p) {
	HANDLE h_Mutex;//�������
	h_Mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "mutex_for_readcount");
	DWORD wait_for_mutex; //�ȴ��������������Ȩ 
	DWORD m_delay; //�ӳ�ʱ��
	DWORD m_persist;//���ļ�����ʱ��
	int m_serial;
	//�Ӳ����л����Ϣ
	m_serial = ((ThreadInfo*)(p))->serial;
	m_delay = (DWORD)(((ThreadInfo*)(p))->delay * INTE_PER_SEC);
	m_persist = (DWORD)(((ThreadInfo*)(p))->persist * INTE_PER_SEC);
	Sleep(m_delay);  //�ӳٵȴ�
	printf("���߳� %d ����������.\n", m_serial);
	//�ȴ������źţ���֤��ReadCount�ķ��ʣ��޸Ļ���
	wait_for_mutex = WaitForSingleObject(h_Mutex, -1);
	//������Ŀ����
	readcount++;
	if (readcount == 1) {
		//��һ�����ߣ��ȴ���Դ
		EnterCriticalSection(&RP_Write);//����ȷ��ͬһʱ��ֻ��һ���̲߳��������������ݵĲ�������
	}
	ReleaseMutex(h_Mutex);
	//���ļ�
	printf("���߳� %d ��ʼ���ļ�.\n", m_serial);
	Sleep(m_persist);
	//�˳��߳�
	printf("���߳� %d �������ļ�.\n", m_serial);
	//�ȴ������źţ���֤��ReadCount�ķ��ʣ��޸Ļ���
	wait_for_mutex = WaitForSingleObject(h_Mutex, -1);
	//������Ŀ����
	readcount--;
	if (readcount == 0) {
		LeaveCriticalSection(&RP_Write);
	}
	ReleaseMutex(h_Mutex);
}
//��������--д�߽���
//P:д���߳���Ϣ
void RP_WriterThread(void* p) {
	DWORD m_delay;//�ӳ�ʱ��  
	DWORD m_persist;  //д�ļ�����ʱ��
	int m_serial; //�߳����
	//�Ӳ����л�ȡ��Ϣ
	m_serial = ((ThreadInfo*)(p))->serial;
	m_delay = (DWORD)(((ThreadInfo*)(p))->delay * INTE_PER_SEC);
	m_persist = (DWORD)(((ThreadInfo*)(p))->persist * INTE_PER_SEC);
	Sleep(m_delay);
	printf("д�߳�%d����д����***.\n", m_serial);
	//�ȴ���Դ
	EnterCriticalSection(&RP_Write);
	//д�ļ�
	printf("д�߳�%d��ʼд�ļ�.\n", m_serial);
	Sleep(m_persist);
	//�˳��߳�
	printf("д�߳�%d����д�ļ�.\n", m_serial);
	//�ͷ���Դ
	LeaveCriticalSection(&RP_Write);
}
//�������ȴ�����
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
		printf("���ļ�\"%os\"ʧ��!�뽫\"%s\"�ų���Ŀ¼�¡�\n", file, file);
		return;
	}
	printf("�������ȣ�\n\n");
	while (inFile) {
		inFile >> thread_info[n_thread].serial;
		inFile >> thread_info[n_thread].entity;
		inFile >> thread_info[n_thread].delay;
		inFile >> thread_info[n_thread++].persist;
		inFile.get();
	}
	for (int i = 0; i < (int)(n_thread); i++) {
		if (thread_info[i].entity == READER || thread_info[i].entity == 'r') {
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(RP_ReaderThread), &thread_info[i], 0, &thread_ID);//�������߽���
		}
		else {
			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(RP_WriterThread), &thread_info[i], 0, &thread_ID);//����д�߽���
		}
	}
	//�ȴ����е��߳̽���
	wait_for_all = WaitForMultipleObjects(n_thread, h_Thread, TRUE, -1);
	printf("���еĶ�д�߳̽�������.\n");
}
int main(int argc, const char* argv[]) {
	ReaderPriority("input.txt");
	printf("\n�������������");
	system("pause");
	return 0;
}