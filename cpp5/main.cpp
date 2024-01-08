#include <iostream>
#include <Windows.h>
#include <graphics.h>
#include <string>
#include <conio.h>
#include "box_move.h"

//// �ڶ�ά������,����ʹ����Ӧ������ȥ��ʾ����Ķ��������ǿɶ��Ժܲ���ǿ��Խ���Ӧ�����ֶ������Ӧ�ĺ�
//#define WALL 0
//#define FLOOR 1
//#define BOX_DEFINATE 2 // ����Ŀ�ĵ�
//#define MAN 3
//#define BOX 4
//#define BOX_IN_TARGET 5 // �����ҵ�Ŀ��
using namespace std;

/*������ƷͼƬ,��Ϊ���Ǻܶ�ط���Ҫʹ��,���Կ��Զ���һ��ȫ�ֱ���*/
IMAGE img_goods[ALL]; // 5����Ʒ�� ����һ����ʾ��������Ŀ�ĵ�ʱ��ʾ��ͼƬ(Ҳ�����ӵ�ͼƬ)
IMAGE bg_img;

/*ʹ�ö�ά����,��ʾ���ڵ�ÿһ��λ��,ÿ��λ�÷�ʲô����ʹ��һ����������ʾ*/

/*����������Ŀ��ʱ,��Ŀ�������Ϊ5�����������û��4��,�Ǿͱ�ʾ���Ӷ�������Ŀ�ĵ�*/
int map[map_row][map_col] = { // �ڲ����ֱ�ʾ��Ӧ�Ķ���
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
 * �ж���Ϸ����--���map�в���������Ŀ�ĵؾʹ�����Ϸ������
 * ���룺��
 * ����� 
 *       true  ����
 *       false ������
 ************************************************************/

bool isGameOver() { // ����map�����Ƿ���ڱ�ʾ����Ŀ�ĵص���(��Ϊ���ǵ���Ŀ�ĵؾͽ���ֵ��Ϊ��5),ֻҪ�����ھ�˵��������Ŀ�ĵ���
	                // �Ϳ��Խ�����Ϸ��
	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			if (map[i][j] == BOX_DEFINATE) return false; // �ͱ�ʾû�н�����Ϸ
		}
	}

	return true; // �������û���ҵ�Ŀ��Ŀ�ĵأ�˵����������λ�ã���ô��Ϸ�Ϳ��Խ�����
}

/***********************************************************
 * ��ʼ����Ϸ�������
 * ���룺��
 * �������
 ************************************************************/

void initGame()
{
	// ���뱳��ͼƬ
	/*����һ,ֱ�ӽ�ͼƬ���뵽����*/
	//loadimage(0, _T("./blackground.bmp"));
	loadimage(&bg_img, _T("./blackground.bmp")); // ��ͼƬ���뵽ͼƬ����, bg_img��

	putimage(0, 0, &bg_img);  // �ڴ���(0,0)��,��ӡͼƬ

	/*������ƷͼƬ:�����õ���ͼƬ�Ĵ�С*/
	loadimage(&img_goods[WALL], _T("./wall_right.bmp"), box_wid, box_wid);
	loadimage(&img_goods[FLOOR], _T("./floor.bmp"), box_wid, box_wid);
	loadimage(&img_goods[BOX_DEFINATE], _T("./des.bmp"), box_wid, box_wid);
	loadimage(&img_goods[MAN], _T("./man.bmp"), box_wid, box_wid);
	loadimage(&img_goods[BOX], _T("./box.bmp"), box_wid, box_wid);
	loadimage(&img_goods[BOX_IN_TARGET], _T("./box.bmp"), box_wid, box_wid); // 5��ʾ����������Ŀ�ĵ�,Ҳ����ʾ���ӵ�ͼƬ


	/*����ͼƬ��,���ݵ�ͼ�����е����ݽ�ͼƬ��ӡ����Ӧ��λ��*/
	for (int i = 0; i < map_row; i++)
	{
		for (int j = 0; j < map_col; j++) 
		{
			putimage(py_x +j * box_wid, py_y +i * box_wid, &img_goods[map[i][j]]);
		}
	}

    // ��ʼ��С�˵����� ����д��ά����̫��
	//man.x = 5; // �ڶ�ά����ĵ�5�� -- ��Ϊ,�ڴ��ڴ�ӡ��λ���ɶ�ά�������
	//man.y = 5; // �ڶ�ά����ĵ�5��
}

/*****************************************************
 * �������,��ά�����е�λ�ã��͸�λ�÷ŵ���Ʒ
 * ���룺
 *       line  - �����ڵ�ͼ��������±�
 *       colunm - �����ڵ�ͼ��������±�
 *       good - ���ߵ����� (ʹ��ö����������ʾ��)
 * ���:  none
 *****************************************************/

//void changeMan(int line,int column,enum goods good) {
//	map[line][column] = good; // �����λ�����ó���Ӧ����Ʒ
//	putimage(py_x + column * box_wid, py_y + line * box_wid, &img_goods[good]); // ͼƬ������img_goods�����У�good��ʾ������ʲô
//}

// �����Ż� -- ʹ��ָ�룬�����ڴ�ʹ��
void changeMan(struct _S_MAN* sman, enum goods good) {
	map[sman->x][sman->y] = good; // �����λ�����ó���Ӧ����Ʒ
	putimage(py_x + sman->y * box_wid, py_y + sman->x * box_wid, &img_goods[good]); // ͼƬ������img_goods�����У�good��ʾ������ʲô
}

/***********************************************************
 * ���ƽ�����Ʒ�˶�,���ݴ����ƶ�λ�ý�����Ӧ�Ĳ���
 * ���룺
 *       enum direction direct -- �ƶ��ķ���(��ö����)
 * ����� ��
 ************************************************************/

void gameControl(enum direction direct)
{
	// ��������ʹ��һ���ṹ������ʾ��man��һ��λ����,���Դ˴��Ͳ���Ҫ��
	//int x = man.x;
	//int y = man.y;

	/*����������Ż�����Ϊ����Ĵ��������Ժܸ�,���ǿ����滻��һ�δ��룬��ߴ���Ŀɶ��ԺͿ��޸���*/
	struct _S_MAN next_man = { man.x,man.y };  // ��������ṹ��,���ڼ�¼man��һ��λ�õ�����
	struct _S_MAN next_box = { man.x,man.y }; // ��ʾ������һ��λ��,Ҳ����С�˵�������λ��

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

	// �Ż���Ĵ��� �����ǰ�ȫ�Լ��,�����ƶ����߽�Ͳ����ƶ���,��Ϊ�Ƚϳ������Զ����һ����,
	// 
	// ����Ż���ֱ�ӽ�һ�����ƵĴ�������һ�δ��롣 ���������ƴ��룬������˿ɶ���

	/*next_man.x >= 0 && next_man.x <= map_row && next_man.y >= 0 && next_man.y <= map_col*/
	if (checkSecurity(next_man) && map[next_man.x][next_man.y] == FLOOR) {
		//changeMan(next_man.x, next_man.y, MAN); // ����һ��λ�û���MAN
		changeMan(&next_man, MAN); // ʹ��ָ�봫�ݿ��Խ�Լ�ڴ�

		//changeMan(man.x, man.y, FLOOR); // ��ԭλ�û���FLOOR
		changeMan(&man, FLOOR); // ʹ��ָ�봫�ݿ��Խ�Լ�ڴ�

		man = next_man; // ��man��x,y�������Ϊ��һ��λ�õ�x,y-->�ṹ�帳ֵ
	}
	else if (checkSecurity(next_man) && map[next_man.x][next_man.y] == BOX) {  // �ƶ�����һλ������
		// ���ǰ�����ǵذ�
		if (checkSecurity(next_box) && map[next_box.x][next_box.y] == FLOOR) {
			changeMan(&next_man, MAN);
			changeMan(&next_box, BOX);
			changeMan(&man, FLOOR);
            
			man = next_man; // ��man��x,y�������Ϊ��һ��λ�õ�x,y-->�ṹ�帳ֵ
		}
		else if (checkSecurity(next_box) && map[next_box.x][next_box.y] == BOX_DEFINATE){ // ����ǰ��������Ŀ�ĵ�
			changeMan(&next_man, MAN);
			changeMan(&next_box, BOX_IN_TARGET);
			changeMan(&man, FLOOR);

			man = next_man; // ��man��x,y�������Ϊ��һ��λ�õ�x,y-->�ṹ�帳ֵ
		}

	}

/*
    // �ĸ������ʵ��
	if (direct == UP) {  
		if ((man.x - 1) >= 0 && map[x-1][y] == FLOOR)// �ж�С���Ƿ�Խ��,�������û��ǽ,�ߵ���߽�Ҳ���������ˡ�
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
 * ��Ϸ���й�������Ϸ���ݵĸ���
 * ���룺 ��
 * ����� ��
 ************************************/

 /************************************
  * ��Ϸͨ������ʾ��ؽ���
  * ���룺 
  *        IMAGE *bg -- ��ʾ�Ľ���ͼƬ
  * ����� ��
  ************************************/
void gameOver(IMAGE *bg) {
	putimage(0, 0, bg);
	settextcolor(WHITE);
	RECT rect = { 0,0,win_row,win_col }; // ��ʾ��(0,0)��(win_row,win_col)����һ������
	settextstyle(20, 0, _T("����"));

	// �ھ����������Ӧ��ʽ������
	drawtext(_T("�ɹ�����"),&rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);  // ������������ ˮƽ���� ��ֱ���� ������ʾ����
}

void dataUpdate()
{
	// С��λ�ø���,ʹ��forѭ�������ж�,�Ƚ�map�����е�ÿ��λ�õ�ֵ�Ƿ�Ϊ3��������ڣ���ô���λ�õ�ֵ����С�˵�λ�ã�����ʵ��
    // ��̬�޸ģ�С�˵�λ�á�Ȼ�����ǾͿ������κ�ʱ��õ�С�˵�λ��(����);
	for (int i = 0; i < map_row; i++) {
		for (int j = 0; j < map_col; j++) {
			if (map[i][j] == MAN) {
				man.x = i;
				man.y = j;
			}
		}
	}

	// ��Ϸ����
	bool quit = false;

	// ��Ϊ���ǿ�����ʱ������������Ҫ���ϵ��ж�--ʹ��ѭ��
	do {
		// �Ƿ��м����û�--�еĻ�����true
		if (_kbhit())
		{
			char ch = _getch(); // ��ȡ�û���Ԫ�� c++��ʹ��getchҪ��_
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
				quit = true; // ��quit����Ϊture���˳�ѭ����
			}
          // ���а�����Ϣ��ʱ���ж��Ƿ����(��Ϊû�����϶�����������Ӳ���Ҫ�ж���)
			if (isGameOver())
			{
				gameOver(&bg_img);
				quit = true;  // ���˳�ѭ�������޸�
			}
		}

		//Sleep(1000); // ����1��,��Ϊ������û���κδ���,���̫�죬�������������룬�ͻ��ѭ����ô���(����֮�����ǰ���q���˳���)
	} while (quit == false);  // !quit

}

int main(void)
{
	initgraph(win_row,win_col);

	initGame();

	dataUpdate();

	system("pause");

	closegraph(); // ��Ϸ�����ͷ���Դ����ʼ���Ĵ���,Ҳռ�ڴ�,(��Ϊ�ǳ����һ����)��ʹ�ý���֮��Ӧ���ͷ���Դ

	return 0;
}