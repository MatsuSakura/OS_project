#include"stdio.h" 
#include"stdlib.h" 
#include"iostream" 
#define maxsize 100 
using namespace std;
//先来先服务调度算法
void FCFS(int array[], int m)
{
	int sum = 0, j, i, now;
	cout << "请输入当前的磁道号：";
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
	cout << "移动的总道数： " << sum << endl;
	cout << "最短寻道时间为： " << result / m << endl;
}
//最短寻道时间优先调度算法
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
	}/*排序*/
	cout << "请输入当前的磁道号：";
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
			/*确定当前磁道在已排的序列中的位置，后面的算法都用到了，可以直接复杂后少量修改，节
		   省时间。*/
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
	cout << "移动的总道数： " << sum << endl;
	cout << "最短寻道时间为： " << result / m << endl;
}
//电梯调度算法
void Elevator(int array[], int m) //先</A>要给出当前磁道号和移动臂的移动方向
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
	cout << "请输入当前的磁道号：";
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
			cout << "请输入当前移动臂的移动的方向 (1 表示向内 ，0 表示向外) : ";
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
	cout << "移动的总道数： " << sum << endl;
	cout << "最短寻道时间为： " << result / m << endl;
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
	cout << "请输入当前的磁道号： ";
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
		cout << "请输入当前移动臂的移动方向（1表示向内，0表示向外）:";
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
	cout << "移动的总道数： " << sum << endl;
	cout << "最短寻道时间为： " << result / m << endl;
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
		cout << "文件打不开!" << endl;
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
		cout << endl << "系统的菜单如下：" << endl;
		printf("1. 先来先服务 FCFS 2. 最短寻道时间优先 SSTF 3. 电梯调度 4.C-SCAN");
		cout << endl;
		printf("5. 退出");
		cout << endl;
		cout << "请选择：";
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