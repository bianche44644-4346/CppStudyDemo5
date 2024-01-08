#include <iostream>
#include <Windows.h>
#include <graphics.h>
#include <string>
#include <conio.h>
#include "box_move.h"

//// 在二维数组中,我们使用相应的数字去表示具体的东西，但是可读性很差，我们可以将相应的数字定义成相应的宏
//#define WALL 0
//#define FLOOR 1
//#define BOX_DEFINATE 2 // 箱子目的地
//#define MAN 3
//#define BOX 4
//#define BOX_IN_TARGET 5 // 箱子找到目标
using namespace std;

/*加载物品图片,因为我们很多地方都要使用,所以可以定义一个全局变量*/
IMAGE img_goods[ALL]; // 5个物品， 还有一个表示箱子命中目的地时显示的图片(也是箱子的图片)
IMAGE bg_img;

/*使用二维数组,表示窗口的每一个位置,每个位置放什么东西使用一个数字来表示*/

/*当箱子命中目标时,将目标第设置为5，如果矩阵中没有4了,那就表示箱子都到达了目的地*/
int map[map_row][map_col] = { // 内部数字表示相应的东西
	{WALL, WALL,  WALL,        WALL,           WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,},
	{WALL, FLOOR, WALL,        FLOOR,          FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, WALL, WALL,},
	{WALL, FLOOR, BOX,         FLOOR,          WALL, BOX_DEFINATE, FLOOR, WALL, BOX_DEFINATE, FLOOR, WALL, WALL,},
	{WALL, FLOOR, WALL,        FLOOR,          WALL,FLOOR,WALL,WALL,FLOOR,FLOOR,FLOOR,WALL,},
	{WALL, FLOOR, WALL,        BOX_DEFINATE,   WALL,FLOOR,FLOOR,BOX,FLOOR,FLOOR,FLOOR,WALL,},
	{WALL, FLOOR, FLOOR,FLOOR, WALL, MAN,      FLOOR,FLOOR,FLOOR,BOX,FLOOR,WALL,},
	{WALL, FLOOR, BOX_DEFINATE,FLOOR,FLOOR ,   BOX,  FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,WALL,},
	{WALL, FLOOR, WALL,        WALL, FLOOR,    WALL, FLOOR,FLOOR,WALL,WALL,FLOOR,WALL,},
	{WALL, WALL,  WALL,        WALL, WALL,     WALL, WALL, WALL, WALL,WALL,WALL,WALL,}
};

/***********************************************************
 * 判断游戏结束--如果map中不存在箱子目的地就代表游戏结束了
 * 输入：无
 * 输出： 
 *       true  结束
 *       false 不结束
 ************************************************************/

bool isGameOver() { // 遍历map查找是否存在表示箱子目的地的数(因为我们到了目的地就将其值改为了5),只要不存在就说明都到了目的地了
	                // 就可以结束游戏了
	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			if (map[i][j] == BOX_DEFINATE) return false; // 就表示没有结束游戏
		}
	}

	return true; // 上面代码没有找到目标目的地，说明都到达了位置，那么游戏就可以结束了
}

/***********************************************************
 * 初始化游戏相关属性
 * 输入：无
 * 输出：无
 ************************************************************/

void initGame()
{
	// 导入背景图片
	/*方法一,直接将图片导入到窗口*/
	//loadimage(0, _T("./blackground.bmp"));
	loadimage(&bg_img, _T("./blackground.bmp")); // 将图片导入到图片变量, bg_img中

	putimage(0, 0, &bg_img);  // 在窗口(0,0)处,打印图片

	/*导入物品图片:并设置导入图片的大小*/
	loadimage(&img_goods[WALL], _T("./wall_right.bmp"), box_wid, box_wid);
	loadimage(&img_goods[FLOOR], _T("./floor.bmp"), box_wid, box_wid);
	loadimage(&img_goods[BOX_DEFINATE], _T("./des.bmp"), box_wid, box_wid);
	loadimage(&img_goods[MAN], _T("./man.bmp"), box_wid, box_wid);
	loadimage(&img_goods[BOX], _T("./box.bmp"), box_wid, box_wid);
	loadimage(&img_goods[BOX_IN_TARGET], _T("./box.bmp"), box_wid, box_wid); // 5表示箱子命中了目的地,也是显示箱子的图片


	/*导入图片后,根据地图数组中的数据将图片打印到相应的位置*/
	for (int i = 0; i < map_row; i++)
	{
		for (int j = 0; j < map_col; j++) 
		{
			putimage(py_x +j * box_wid, py_y +i * box_wid, &img_goods[map[i][j]]);
		}
	}

    // 初始化小人的属性 这样写可维护性太差
	//man.x = 5; // 在二维数组的第5行 -- 因为,在窗口打印的位置由二维数组给出
	//man.y = 5; // 在二维数组的第5列
}

/*****************************************************
 * 传入参数,二维数组中的位置，和该位置放的物品
 * 输入：
 *       line  - 道具在地图数组的行下标
 *       colunm - 道具在地图数组的列下标
 *       good - 道具的类型 (使用枚举类型来表示了)
 * 输出:  none
 *****************************************************/

//void changeMan(int line,int column,enum goods good) {
//	map[line][column] = good; // 将这个位置设置成相应的物品
//	putimage(py_x + column * box_wid, py_y + line * box_wid, &img_goods[good]); // 图片保存在img_goods数组中，good表示具体是什么
//}

// 代码优化 -- 使用指针，减少内存使用
void changeMan(struct _S_MAN* sman, enum goods good) {
	map[sman->x][sman->y] = good; // 将这个位置设置成相应的物品
	putimage(py_x + sman->y * box_wid, py_y + sman->x * box_wid, &img_goods[good]); // 图片保存在img_goods数组中，good表示具体是什么
}

/***********************************************************
 * 控制界面物品运动,根据传入移动位置进行相应的操作
 * 输入：
 *       enum direction direct -- 移动的方向(在枚举中)
 * 输出： 无
 ************************************************************/

void gameControl(enum direction direct)
{
	// 后面我们使用一个结构体来表示，man下一个位置了,所以此处就不需要了
	//int x = man.x;
	//int y = man.y;

	/*对下面代码优化：因为下面的代码相似性很高,我们可以替换成一段代码，提高代码的可读性和可修改性*/
	struct _S_MAN next_man = { man.x,man.y };  // 定义这个结构体,用于记录man下一个位置的坐标
	struct _S_MAN next_box = { man.x,man.y }; // 表示箱子下一个位置,也就是小人的下两个位置

	switch (direct) {
	case UP:
		next_man.x = man.x - 1;
		next_box.x = man.x - 2;
		break;
	case DOWN:
		next_man.x = man.x + 1;
		next_box.x = man.x + 2;
		break;
	case LEFT:
		next_man.y = man.y - 1;
		next_box.y = man.y - 2;
		break;
	case RIGHT:
		next_man.y = man.y + 1;
		next_box.y = man.y + 2;
		break;
	}

	// 优化后的代码 下面是安全性检查,当人移动到边界就不能移动了,因为比较长，可以定义成一个宏,
	// 
	// 这个优化，直接将一堆相似的代码变成了一段代码。 减少了相似代码，又提高了可读性

	/*next_man.x >= 0 && next_man.x <= map_row && next_man.y >= 0 && next_man.y <= map_col*/
	if (checkSecurity(next_man) && map[next_man.x][next_man.y] == FLOOR) {
		//changeMan(next_man.x, next_man.y, MAN); // 将下一个位置换成MAN
		changeMan(&next_man, MAN); // 使用指针传递可以节约内存

		//changeMan(man.x, man.y, FLOOR); // 将原位置换成FLOOR
		changeMan(&man, FLOOR); // 使用指针传递可以节约内存

		man = next_man; // 将man的x,y坐标更新为下一个位置的x,y-->结构体赋值
	}
	else if (checkSecurity(next_man) && map[next_man.x][next_man.y] == BOX) {  // 移动的下一位是箱子
		// 如果前面是是地板
		if (checkSecurity(next_box) && map[next_box.x][next_box.y] == FLOOR) {
			changeMan(&next_man, MAN);
			changeMan(&next_box, BOX);
			changeMan(&man, FLOOR);
            
			man = next_man; // 将man的x,y坐标更新为下一个位置的x,y-->结构体赋值
		}
		else if (checkSecurity(next_box) && map[next_box.x][next_box.y] == BOX_DEFINATE){ // 箱子前面是箱子目的地
			changeMan(&next_man, MAN);
			changeMan(&next_box, BOX_IN_TARGET);
			changeMan(&man, FLOOR);

			man = next_man; // 将man的x,y坐标更新为下一个位置的x,y-->结构体赋值
		}

	}

/*
    // 四个方向的实现
	if (direct == UP) {  
		if ((man.x - 1) >= 0 && map[x-1][y] == FLOOR)// 判断小人是否越界,就是如果没有墙,走到最边界也不能再走了。
		{
			changeMan(x-1,y,MAN);
			changeMan(x, y, FLOOR);
			man.x -= 1;
		}
	}else if (direct == DOWN)
	{
		if ((man.x + 1) <= map_row && map[x + 1][y] == FLOOR) {
			changeMan(x + 1, y, MAN);
			changeMan(x, y, FLOOR);
			man.x += 1;
		}
	}else if (direct == LEFT)
	{
		if ((man.y - 1) >= 0 && map[x][y-1] == FLOOR) {
			changeMan(x, y-1, MAN);
			changeMan(x, y, FLOOR);
			man.y -= 1;
		}
	}else if (direct == RIGHT)
	{
		if ((man.y + 1) <= map_col && map[x][y + 1] == FLOOR) {
			changeMan(x, y + 1, MAN);
			changeMan(x, y, FLOOR);
			man.y += 1;
		}
	}
*/
}

/************************************
 * 游戏运行过程中游戏数据的更新
 * 输入： 无
 * 输出： 无
 ************************************/

 /************************************
  * 游戏通过后显示相关界面
  * 输入： 
  *        IMAGE *bg -- 显示的界面图片
  * 输出： 无
  ************************************/
void gameOver(IMAGE *bg) {
	putimage(0, 0, bg);
	settextcolor(WHITE);
	RECT rect = { 0,0,win_row,win_col }; // 表示从(0,0)到(win_row,win_col)定义一个矩形
	settextstyle(20, 0, _T("宋体"));

	// 在矩形中输出相应格式的文字
	drawtext(_T("成功过关"),&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);  // 后面三个参数 水平居中 垂直居中 文字显示单行
}

void dataUpdate()
{
	// 小人位置更新,使用for循环进行判断,比较map数组中的每个位置的值是否为3，如果等于，那么这个位置的值就是小人的位置，可是实现
    // 动态修改，小人的位置。然后我们就可以在任何时候得到小人的位置(最新);
	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			if (map[i][j] == MAN) {
				man.x = i;
				man.y = j;
			}
		}
	}

	// 游戏环节
	bool quit = false;

	// 因为我们可能随时按键，所以需要不断的判断--使用循环
	do {
		// 是否有键盘敲击--有的话返回true
		if (_kbhit())
		{
			char ch = _getch(); // 获取敲击的元素 c++中使用getch要加_
			if (ch == KEY_UP){
				gameControl(UP);
			}
			else if (ch == KEY_DOWN){
				gameControl(DOWN);
			}
			else if (ch == KEY_LEFT){
				gameControl(LEFT);
			}
			else if (ch == KEY_RIGHT){
				gameControl(RIGHT);
			}
			else if (ch == QUIT){
				quit = true; // 将quit设置为ture就退出循环了
			}
          // 在有按键信息的时候判断是否结束(因为没按键肯定不会结束，接不需要判断了)
			if (isGameOver())
			{
				gameOver(&bg_img);
				quit = true;  // 将退出循环条件修改
			}
		}

		//Sleep(1000); // 休眠1秒,因为代码中没有任何处理,如果太快，我们来不及输入，就会白循环那么多次(休眠之后我们按下q就退出了)
	} while (quit == false);  // !quit

}

int main(void)
{
	initgraph(win_row,win_col);

	initGame();

	dataUpdate();

	system("pause");

	closegraph(); // 游戏结束释放资源，初始化的窗口,也占内存,(因为是程序的一部分)，使用结束之后应该释放资源

	return 0;
}