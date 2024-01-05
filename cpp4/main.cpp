#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <errno.h>
#include <cmath>  // c++中的数学库

#define FZ 1.5 // 定义使用到的阈值

using namespace std;

/*短窗口是长窗口的最右侧对应的与顿窗口数量相同的窗口*/

/*函数用于计算，短/长时间窗口的能量数据的采样值, 所以返回一个double值*/
double judgementEarthquake(double arr[], int length, int n);  // 参数： 1. 数据 2. 长窗口大小 3. 当前计算窗口大小

int main(void)
{
	string fileName;
	ifstream file; 
	int nub = 0, short_time = 0, long_time = 0; // account
	double timer_up = 0.0,*sensor = NULL; // time-up gap   sensor points to dynamic memory
	double short_power = 0.0, long_power = 0.0;// 短时间窗口的采样值和长时间窗口的采样值
	double radio; // 比例

	cout << "Input file name:" << endl;
	cin >> fileName;

	/*Is input success or fail?*/
	if (cin.fail())
	{
		cerr << "Input fail!!!" << endl;
		exit(1); // error exit
	}

	/*open file stream*/
	file.open(fileName.c_str());

	/*judgement: Is file open fail?*/
	if (file.fail())
	{
		cerr << "file open fail, because: " << strerror(errno) << endl;
		exit(1); // error exit
	}
	else  // file open success, reading file data
	{
		file >> nub >> timer_up;

		// legal judgement
		if(nub >=0)
		{
			// legal : dynamic request memory 
			sensor = new double[nub];

			// Gradually read data
			for (int i = 0; i < nub; i++)
			{
				file >> sensor[i];
			}
		}

		cout << "Enter long window data:" << endl;
		cin >> long_time;
		cout << "Enter short window data:" << endl;
		cin >> short_time;

		//分析能量数据找出地震时间
		for (int i = long_time-1; i < nub; i++)
		{ // 函数的定义，应该具有通用性，同类型的需求，都可以调用函数，所以只需要封装相同处理的代码就行,不需要再代码中进行特殊处理。各自的特点通过函数的参数
		  // 传递
			short_power = judgementEarthquake(sensor, i, short_time);
			long_power = judgementEarthquake(sensor, i, long_time);

			radio = short_power / long_power;

			if (radio > FZ)
			{
				cout << "poosible event at" << i * timer_up << endl;
			}
		}

		// final : release file pointer!!!  put there the cause of only file open success, just need to close it
		file.close();

		delete[] sensor; // 释放动态分配的内存空间
	}


	system("pause");

	return 0;
}

double judgementEarthquake(double arr[], int length, int n)
{
	double square = 0.0; // 得到的平均值

	for (int i = 0; i < n; i++)
	{
		square += pow(arr[length - i], 2); // 从最长窗口后往前找对应窗口数的值然后求平方和
	}

	return square / n; // 将计算到的平方和除以对应窗口值,得到对应窗口的数据
}
