#include <iostream>
#include <Windows.h>
#include <string.h>
#include <string>
#include <fstream>
#include <errno.h>

using namespace std;

#define fileBallAcount 33  // 文件中球标号的数量
#define linesCount 7 // 一行有七个数据

bool calculate(const char* fileName, int* cout,int len);

/*跟上老师的思路*/
int main(void)
{
	/*定义文件名,文件打开以及相关操作都在函数中封装,我们只需要传入文件名字和存放结果的数组即可*/
	string fileName;
	int count[fileBallAcount] = { 0 };/*文件中总共有33个数据进行计算*/

	cout << "请输入文件名" << endl;
	cin >> fileName;

	/*安全检测-- 是否输入成功*/
	if (cin.fail())
	{
		cerr << "文件名输入失败" << endl; /*cerr和C语言的stderr类似,将错误信息输出到标准错误输出*/
		exit(1); /*结束输入*/
	}

	/*输入成功则调用函数,返回true则计算成功,相反计算失败*/
	if (calculate(fileName.c_str(), count, fileBallAcount))
	{
		// 如果操作成功，输出count中的数据
		for (int i = 1; i < fileBallAcount; i++)
		{
			cout << i << "出现了" << count[i] << "次" << endl;
		}
	}
	else
	{
		cout << "操作失败" << endl;
	}


	system("pause");

	return 0;
}

/*传入const char*fileName 是因为打开文件的open函数需要使用C语言的字符串,所以在此处和它封装的相同*/
bool calculate(const char* fileName, int* count,int len) /*数组作为函数参数,就需要将其长度传入*/
{
	int ballData[linesCount] = {0}; // 记录读取的一行的数据数据
	int i = 0;

	/*错误检测--传入的文件名非空*/
	if (!strcmp(fileName,"")) // 如果为空则返回0
	{
		cerr << "传入文件名为空" << endl;

		return false;
	}

	/*文件名正常打开文件*/
	ifstream file;  // 定义文件类对象

	file.open(fileName);

	/*错误检测--文件是否打开成功*/
	if (file.fail())
	{
		cerr << "文件打开失败，原因：" << strerror(errno) << endl;

		file.close();
		return false;  // 文件打开失败返回false
	}

	/*打开成功,读取文件中的数据，一个反复读取的过程，使用循环*/
	
	while (!file.eof()) // 到了文件结尾,那就停止循环，读到文件结束符号返回ture
	{
		int line = 0;
		/*读取一行数据也是一个循环的过程,使用循环*/
		for (i = 0; i < linesCount; i++)
		{
			file >> ballData[i];
		}
		line++;

		/*如果一行的数据不满足7个那就不进行统计*/
		if (i >= 7)
		{
			i = 0;
			/*使用指针对count的每一个元素进行++*/
			/*错误验证--文件中的值可能出错(此处是给指针初始位置+一定值,所以应该在范围内的同时,保证数据大于0)*/
			if (ballData[i] > 0 && ballData[i] <= 33)
				(*(count + ballData[i++]))++;
			else
				file.close();
				return false;
			continue;
		}
		else 
		{
			cout << "第" << line << "行数据不够7个，希望是7个" << endl;
			continue;
		}
	}

	file.close();
	return true;
}