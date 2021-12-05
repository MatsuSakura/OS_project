#include"stdio.h" 
#include"stdlib.h" 
#include"iostream" 
#define maxsize 100 
using namespace std;
//�����ȷ�������㷨
void FCFS(int array[], int m)
{
	int sum = 0, j, i, now;
	cout << "�����뵱ǰ�Ĵŵ��ţ�";
	cin >> now;
	for (i = 0; i < m; i++)
	{
		cout << array[i] << " ";
	}
	sum += abs(now - array[0]);
	for (i = 0, j = 1; j < m; i++, j++)
	{
		sum += abs(array[j] - array[i]);
	}
	double result = sum;
	cout << "�ƶ����ܵ����� " << sum << endl;
	cout << "���Ѱ��ʱ��Ϊ�� " << result / m << endl;
}
//���Ѱ��ʱ�����ȵ����㷨
void ShortPath(int array[], int m)
{
	int temp;
	int k = 1;
	int now, l, r;
	int i, j, sum = 0;
	for (i = 0; i < m; i++)
		for (j = i + 1; j < m; j++)
		{
			if (array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	for (i = 0; i < m; i++)
	{
		cout << array[i] << " ";
	}/*����*/
	cout << "�����뵱ǰ�Ĵŵ��ţ�";
	cin >> now;
	if (array[m - 1] <= now)
	{
		for (i = m - 1; i >= 0; i--)
			cout << array[i] << " ";
		sum = now - array[0];
	}
	else
		if (array[0] >= now)
		{
			for (i = 0; i < m; i++)
				cout << array[i] << " ";
			sum = array[m - 1] - now;
		}
		else
		{
			while (array[k] < now)
			{
				k++;
			}
			l = k - 1;
			r = k;
			/*ȷ����ǰ�ŵ������ŵ������е�λ�ã�������㷨���õ��ˣ�����ֱ�Ӹ��Ӻ������޸ģ���
		   ʡʱ�䡣*/
			while ((l >= 0) && (r < m))
			{
				if ((now - array[l]) <= (array[r] - now))
				{
					cout << array[l] << " ";
					sum += now - array[l];
					now = array[l];
					l = l - 1;
				}
				else
				{
					cout << array[r] << " ";
					sum += array[r] - now;
					now = array[r];
					r = r + 1;
				}
			}
			if (l = -1)
			{
				for (j = r; j < m; j++)
				{
					cout << array[j] << " ";
				}
				sum += array[m - 1] - array[0];
			}
			else
			{
				for (j = l; j >= 0; j--)
				{
					cout << array[j] << " ";
				}
				sum += array[m - 1] - array[0];
			}
		}
	double result = sum;
	cout << "�ƶ����ܵ����� " << sum << endl;
	cout << "���Ѱ��ʱ��Ϊ�� " << result / m << endl;
}
//���ݵ����㷨
void Elevator(int array[], int m) //��</A>Ҫ������ǰ�ŵ��ź��ƶ��۵��ƶ�����
{
	int temp;
	int k = 1;
	int now, l, r, d;
	int i, j, sum = 0;
	for (i = 0; i < m; i++)
		for (j = i + 1; j < m; j++)
		{
			if (array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	for (i = 0; i < m; i++)
	{
		cout << array[i] << " ";
	}
	cout << "�����뵱ǰ�Ĵŵ��ţ�";
	cin >> now;
	if (array[m - 1] <= now)
	{
		for (i = m - 1; i >= 0; i--)
			cout << array[i] << " ";
		sum = now - array[0];
	}
	else
		if (array[0] >= now)
		{
			for (i = 0; i < m; i++)
				cout << array[i] << " ";
			sum = array[m - 1] - now;
		}
		else
		{
			while (array[k] < now)
			{
				k++;
			}
			l = k - 1;
			r = k;
			cout << "�����뵱ǰ�ƶ��۵��ƶ��ķ��� (1 ��ʾ���� ��0 ��ʾ����) : ";
			cin >> d;
			if (d == 0)
			{
				for (j = l; j >= 0; j--)
				{
					cout << array[j] << " ";
				}
				for (j = r; j < m; j++)
				{
					cout << array[j] << " ";
				}
				sum = -array[0] + array[m - 1]+now-array[0];
			}
			else
			{
				for (j = r; j < m; j++)
				{
					cout << array[j] << " ";
				}
				for (j = l; j >= 0; j--)
				{
					cout << array[j] << " ";
				}

				sum =array[m - 1]-array[0]+array[m-1]-now;
			}
		}
	double result = sum;
	cout << "�ƶ����ܵ����� " << sum << endl;
	cout << "���Ѱ��ʱ��Ϊ�� " << result / m << endl;
}
void CElevator(int array[], int m) {
	int temp;
	int k = 1;
	int now, l, r, d;
	int i, j, sum = 0;
	for (i = 0; i < m; i++)
		for (j = i + 1; j < m; j++) {
			if (array[i] > array[j]) {
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	for (i = 0; i < m; i++) {
		cout << array[i] << " ";
	}
	cout << "�����뵱ǰ�Ĵŵ��ţ� ";
	cin >> now;
	if (array[m - 1] <= now) {
		for (i = m - 1; i >= 0; i--)
			cout << array[i] << " ";
		sum = array[m - 1] - now;
	}
	else {
		while (array[k] < now) {
			k++;
		}
		l = k - 1;
		r = k;
		//cout << l << endl << k << endl;
		cout << "�����뵱ǰ�ƶ��۵��ƶ�����1��ʾ���ڣ�0��ʾ���⣩:";
		cin >> d;
		if (d == 0) {
			for (j = l; j >= 0; j--) {
				cout << array[j] << " ";
			}
			for (j = m - 1; j >= k; j--) {
				cout << array[j] << " ";
			}
			sum = 2*(array[m-1]-array[0])-(array[r]-now);
		}
		else {
			for (j = r; j < m; j++) {
				cout << array[j] << " ";
			}
			for (j = 0; j < k; j++) {
				cout << array[j] << " ";
			}
			cout << array[l]<<endl;
			sum = 2 * (array[m - 1] - array[0]) - (now - array[l]);
		}
	}
	double result = sum;
	cout << "�ƶ����ܵ����� " << sum << endl;
	cout << "���Ѱ��ʱ��Ϊ�� " << result / m << endl;
}

void main()
{
	int c;
	FILE* fp;
	int cidao[maxsize];
	int i = 0, count;
	fp = fopen("cidao.txt", "r+");
	if (fp == NULL)
	{
		cout << "�ļ��򲻿�!" << endl;
		exit(0);
	}
	while (!feof(fp))
	{
		fscanf(fp, "%d", &cidao[i]);
		i++;
	}
	count = i;

	for (i = 0; i < count; i++)
	{
		printf("%5d", cidao[i]);
	}
	cout << endl;
	while (1)
	{
		cout << endl << "ϵͳ�Ĳ˵����£�" << endl;
		printf("1. �����ȷ��� FCFS 2. ���Ѱ��ʱ������ SSTF 3. ���ݵ��� 4.C-SCAN");
		cout << endl;
		printf("5. �˳�");
		cout << endl;
		cout << "��ѡ��";
		cin >> c;
		if (c > 4)
			break;
		switch (c)
		{
		case 1:
			FCFS(cidao, count);
			break;
		case 2:
			ShortPath(cidao, count);
			break;
		case 3:
			Elevator(cidao, count);
			break;
		case 4:
			CElevator(cidao, count);
			break;
		}
	}
}