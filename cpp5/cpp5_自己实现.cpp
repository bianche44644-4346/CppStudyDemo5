#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>   // 提供_kbhit()函数和_getch()函数的函数原型
#include "cpp5_self.h"

locate man;   // 小人当前的位置

IMAGE goods_img[ALL];  

// 将窗口看作一个二维数组,每一个位置对应一个物品(墙,小人,箱子,箱子目的地,地板等)
int map[MAP_ROW][MAP_COL] = {
	{WALL, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL},
	{WALL, FLOOR, WALL,  FLOOR, FLOOR, FLOOR, FLOOR, FLOOR, WALL},
	{WALL, FLOOR, BOX,   FLOOR, WALL,  DEF,   FLOOR, FLOOR, WALL},
	{WALL, FLOOR, WALL,  FLOOR, WALL,  FLOOR, FLOOR, FLOOR, WALL},
	{WALL, FLOOR, WALL,  DEF,   WALL,  FLOOR, BOX,   FLOOR, WALL},
	{WALL, FLOOR, FLOOR, FLOOR, WALL,  MAN,   FLOOR, FLOOR, WALL},
	{WALL, FLOOR, DEF,   FLOOR, FLOOR, BOX,   FLOOR, FLOOR, WALL},
	{WALL, FLOOR, WALL,  WALL,  FLOOR, WALL,  FLOOR, FLOOR, WALL},
	{WALL, WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL,  WALL}
};

int main(void) {
   
	initGame();

	manMove();

	system("pause");

	// 释放游戏资源---我们在绘图的过程中,其实也是占有内存的，所以当我们游戏结束的时候就将这片资源释放
	closegraph();

	return 0;
}

/********************************
* 初始化游戏中需要使用的数据,包括界面创建,数据初始化,加载图片等
* 输入:   无
* 输出:   无
*********************************/
void initGame() {
	initgraph(WIN_ROW, WIN_COL);  // 也是申请了这片资源使用完之后需要释放

    loadimage(&goods_img[BG_IMAGE], _T("blackground.bmp"));
	putimage(0, 0, &goods_img[BG_IMAGE]);

	steps(0);  // 输出步数

	loadimage(&goods_img[WALL], _T("wall_right.bmp"));
	loadimage(&goods_img[FLOOR], _T("floor.bmp"));
	loadimage(&goods_img[DEF], _T("des.bmp"));
	loadimage(&goods_img[BOX], _T("box.bmp"));
	loadimage(&goods_img[MAN], _T("man.bmp"));
	loadimage(&goods_img[BOX_DEF], _T("box.bmp"));  // 箱子到达目的地时,还是渲染箱子，所以此处还是存放箱子

	for (int i = 0; i < MAP_ROW; i++){
		for (int j = 0; j < MAP_COL; j++) {
			putimage(PY_y+BOX_WID*j, PY_x+BOX_WID*i, &goods_img[map[i][j]]);

			// 初始化小人的位置(在二维数组中的行列位置)
			if (map[i][j] == MAN) {
				man.x = i;
				man.y = j;
			}
		}
	}
}


/********************************
* 实现角色上下左右移动 -- 按下'w': 向上,按下's': 向下,按下'd': 向右,按下'a': 向左  
* 输入:   无
* 输出:   无
*********************************/
void manMove() {
	char ch;
	static int step = 0;

	while (1) {
		if (_kbhit()) {
			ch = _getch(); // 获取键盘按下信息

			if (ch == KEY_UP) {
				moveControl(UP);
				steps(++step);
			}
			else if (ch == KEY_DOWN) {
				moveControl(DOWN);
				steps(++step);
			}
			else if (ch == KEY_LEFT) {
				moveControl(LEFT);
				steps(++step);
			}
			else if (ch == KEY_RIGHT) {
				moveControl(RIGHT);
				steps(++step);
			}
			else if (ch == QUIT) {  // 游戏结束
				return;
			}
			// Sleep(50); // 延迟0.5秒因为人不可能那么快反应,因为人的反应速度不可能太快,如果一直循环不延迟,会一直
		               // 损耗cpu
			if (isGameOver()) {
				GameOver(); // 可以结束游戏时，调用游戏结束函数
			}
		}
	}
}

/********************************
* 找出物体移动的下个位置,并且判断是否可以移动
* 输入:   
*         mov -- 一个枚举类型的变量,用来表示移动的方向。
* 输出:   无
*********************************/
void moveControl(move mov) {
	// 获得下一个位置的行和列

	// 定义到达目标位置的标志
	static bool def_flag = false;  // 设置为静态,是为了防止每次调用函数都初始化为false会影响后面的判断
	static bool box_flag = false;

	locate next_man = man;
	locate next_box = man; // 当人推箱子的时候,箱子移动到箱子的下一个位置,所以定义一个变量,来存储箱子的下一个位置
	                       // 因为，只有人推到箱子才需要判断箱子的下个位置,所以箱子的下个位置，就是人的下两个位置

	switch (mov) {
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

	// 渲染图片,在指定位置渲染相应图片,实现移动效果。(移动就是两个位置的图片互换一下),下一个移动的位置已经封装好了(next_man,上面
	// 已经得出来了)，所以现在还需要有替换的东西,这一堆比较多我们可以封装成一个函数

	if (def_flag && map[next_man.x][next_man.y] == FLOOR) {
			def_flag = false; // 离开目的地之后,就设置为false,否则执行不了下面的语句了
			changeLocate(&next_man, MAN);
			changeLocate(&man, DEF);
			man = next_man;
	}
	else if (map[next_man.x][next_man.y] == FLOOR) { /*如果移动的下一个位置是地板或者是地板目的地才可以移动,否则不会移动*/
		// 封装位移函数
		changeLocate(&next_man,MAN);
		changeLocate(&man,FLOOR);
		man = next_man;
	}
	else if (map[next_man.x][next_man.y] == DEF) {
		def_flag = true;
		changeLocate(&next_man, MAN);
		changeLocate(&man, FLOOR);
		man = next_man;
	}
	else if (map[next_man.x][next_man.y] == BOX) {
		if (map[next_box.x][next_box.y] == FLOOR) {
			if (def_flag) {
				def_flag = false; // 离开目的地之后,就设置为false,否则执行不了下面的语句了
				changeLocate(&next_man, MAN);
				changeLocate(&man, DEF);
				changeLocate(&next_box, BOX);
				man = next_man;
			}
			else {
				changeLocate(&next_man, MAN);
				changeLocate(&man, FLOOR);
				changeLocate(&next_box, BOX);
				man = next_man;
			}
		}
		else if (map[next_box.x][next_box.y] == DEF) {
			changeLocate(&next_man, MAN);
			changeLocate(&man, FLOOR);
			changeLocate(&next_box, BOX_DEF);
			man = next_man;
		}
	}
	else if (map[next_man.x][next_man.y] == BOX_DEF && map[next_box.x][next_box.y] == FLOOR) {
		def_flag = true;
		changeLocate(&next_man, MAN);
		changeLocate(&man, FLOOR);
		changeLocate(&next_box, BOX);
		man = next_man;
	}
}

/********************************
* 根据传入参数,将图片在相应位置渲染出来,实现移动效果
* 输入:
*         x -- 要打印的位置在第几行
*         y -- 要打印的位置在第几列
*         good -- 要在此位置打印的图片是什么
* 输出:   无
*********************************/
void changeLocate(locate *addr, goods good) {
	map[addr->x][addr->y] = good;

	putimage(PY_y+BOX_WID * addr->y, PY_x+BOX_WID * addr->x, &goods_img[good]);
}

/********************************
* 判断是否可以游戏结束 -- 如果map数组中没有目的地了.只有命中目的地时，那就说明可以结束游戏了
* 输入:   无
* 输出:   
*         true -- 可以结束
*         false -- 不会结束
*********************************/
bool isGameOver() {
	for (int i = 0; i < MAP_ROW; i++) {
		for (int j = 0; j < MAP_COL; j++) {
			if (map[i][j] == DEF) return false;  // 如果有等于DEF的,就说明,还有箱子没有到目的地,不需要结束游戏
		}
	}

	return true;
}

/********************************
* 游戏结束,打印游戏结束的文字
* 输入:   无
* 输出:   无
*********************************/
void GameOver() {
	putimage(0, 0, &goods_img[BG_IMAGE]);
	settextcolor(RED);
	
	// 在屏幕中心输出文字,具体查看文档的示例
	RECT rect = { 0,0,WIN_ROW,WIN_COL }; // 在整个窗口画一个矩形
	drawtext(_T("恭喜通关"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void steps(int step) {
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	char temp[100];

	sprintf(temp,"最多%d步",STEPS);

	// 在屏幕中心输出文字,具体查看文档的示例
	RECT rect = { 0,0,WIN_ROW,WIN_COL }; // 在整个窗口画一个矩形
	drawtext(temp, &rect, DT_CENTER | DT_TOP);

	if (step > STEPS) {
		putimage(0, 0, &goods_img[BG_IMAGE]);
		settextcolor(RED);

		// 在屏幕中心输出文字,具体查看文档的示例
		RECT rect = { 0,0,WIN_ROW,WIN_COL }; // 在整个窗口画一个矩形
		drawtext(_T("步数使用完了"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}