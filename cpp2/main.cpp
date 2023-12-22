#include <iostream>
#include <fstream> // 对文件流进行操作
#include <Windows.h>
#include <string>

using namespace std;
#define X 64
#define Y 64

bool isPeak(int map[X][Y], int x,int y); // 判断是否是峰值的函数,传入需要判断值的行和列

int main(void)
{
	/*定义行和列*/
	int rows, cols;
	int map[X][Y]; /*因为c之前是不支持变长数组定义,所以我们在定义数组时,就定义一个最大情况(就是实际
	                   一般不会这么大)*/
	string fileName; /*存放文件名*/
	ifstream file; /*定义读取文件流的对象*/

	cout << "请输入文件名:" << endl;
	cin >> fileName;

	/*打开文件*/
	file.open(fileName.c_str());

	/*判断文件是否打开成功*/
	if (file.fail())  /*使用这个函数,打开失败返回真,打开成功返回假*/
	{
		cout << "文件打开失败" << endl;
		exit(1); /*参数为1,异常结束,参数为0,正常结束*/
	}

	file >> rows >> cols; /*从文件中输入行数和列数*/

	/*检测实际得到的行列数,超过我们预计的大小了,进行防御性检测*/
	if (rows > X || cols > Y) //数组存不下就放弃
	{
		cout << "数组放不下了" << endl;
		exit(1);
	}

	/*从数据文件中读取数据到二维数组*/
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) 
		{
			file >> map[i][j]; // 输入数据
		}
	}

	/*判断并打印峰值*/
	for (int i = 1; i < rows-1; i++)
	{
		for (int j = 1; j < cols-1; j++)
		{
			if (isPeak(map,i,j))
			{
				//cout << "峰值:" << map[i][j] << ' ';
				cout << "峰值出现在行" << i << " 列" << j << endl;
			}
		}
	}

	system("pause");

	/*一定要记得关闭文件*/
	file.close();

	return 0;
}
bool isPeak(int map[X][Y], int x, int y)
{
	if ((map[x-1][y] < map[x][y])  && (map[x + 1][y] < map[x][y])
		&& (map[x][y-1] < map[x][y]) && (map[x][y + 1] < map[x][y]))
	{
		return true;  // 符合四个条件就代表是一个峰值
	}

	return false; // 走到这里的一定不是峰值,因为在上面符合条件就直接退出了
}