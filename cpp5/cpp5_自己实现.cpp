#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>   // �ṩ_kbhit()������_getch()�����ĺ���ԭ��
#include "cpp5_self.h"

locate man;   // С�˵�ǰ��λ��

IMAGE goods_img[ALL];  

// �����ڿ���һ����ά����,ÿһ��λ�ö�Ӧһ����Ʒ(ǽ,С��,����,����Ŀ�ĵ�,�ذ��)
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

	// �ͷ���Ϸ��Դ---�����ڻ�ͼ�Ĺ�����,��ʵҲ��ռ���ڴ�ģ����Ե�������Ϸ������ʱ��ͽ���Ƭ��Դ�ͷ�
	closegraph();

	return 0;
}

/********************************
* ��ʼ����Ϸ����Ҫʹ�õ�����,�������洴��,���ݳ�ʼ��,����ͼƬ��
* ����:   ��
* ���:   ��
*********************************/
void initGame() {
	initgraph(WIN_ROW, WIN_COL);  // Ҳ����������Ƭ��Դʹ����֮����Ҫ�ͷ�

    loadimage(&goods_img[BG_IMAGE], _T("blackground.bmp"));
	putimage(0, 0, &goods_img[BG_IMAGE]);

	steps(0);  // �������

	loadimage(&goods_img[WALL], _T("wall_right.bmp"));
	loadimage(&goods_img[FLOOR], _T("floor.bmp"));
	loadimage(&goods_img[DEF], _T("des.bmp"));
	loadimage(&goods_img[BOX], _T("box.bmp"));
	loadimage(&goods_img[MAN], _T("man.bmp"));
	loadimage(&goods_img[BOX_DEF], _T("box.bmp"));  // ���ӵ���Ŀ�ĵ�ʱ,������Ⱦ���ӣ����Դ˴����Ǵ������

	for (int i = 0; i < MAP_ROW; i++){
		for (int j = 0; j < MAP_COL; j++) {
			putimage(PY_y+BOX_WID*j, PY_x+BOX_WID*i, &goods_img[map[i][j]]);

			// ��ʼ��С�˵�λ��(�ڶ�ά�����е�����λ��)
			if (map[i][j] == MAN) {
				man.x = i;
				man.y = j;
			}
		}
	}
}


/********************************
* ʵ�ֽ�ɫ���������ƶ� -- ����'w': ����,����'s': ����,����'d': ����,����'a': ����  
* ����:   ��
* ���:   ��
*********************************/
void manMove() {
	char ch;
	static int step = 0;

	while (1) {
		if (_kbhit()) {
			ch = _getch(); // ��ȡ���̰�����Ϣ

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
			else if (ch == QUIT) {  // ��Ϸ����
				return;
			}
			// Sleep(50); // �ӳ�0.5����Ϊ�˲�������ô�췴Ӧ,��Ϊ�˵ķ�Ӧ�ٶȲ�����̫��,���һֱѭ�����ӳ�,��һֱ
		               // ���cpu
			if (isGameOver()) {
				GameOver(); // ���Խ�����Ϸʱ��������Ϸ��������
			}
		}
	}
}

/********************************
* �ҳ������ƶ����¸�λ��,�����ж��Ƿ�����ƶ�
* ����:   
*         mov -- һ��ö�����͵ı���,������ʾ�ƶ��ķ���
* ���:   ��
*********************************/
void moveControl(move mov) {
	// �����һ��λ�õ��к���

	// ���嵽��Ŀ��λ�õı�־
	static bool def_flag = false;  // ����Ϊ��̬,��Ϊ�˷�ֹÿ�ε��ú�������ʼ��Ϊfalse��Ӱ�������ж�
	static bool box_flag = false;

	locate next_man = man;
	locate next_box = man; // ���������ӵ�ʱ��,�����ƶ������ӵ���һ��λ��,���Զ���һ������,���洢���ӵ���һ��λ��
	                       // ��Ϊ��ֻ�����Ƶ����Ӳ���Ҫ�ж����ӵ��¸�λ��,�������ӵ��¸�λ�ã������˵�������λ��

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

	// ��ȾͼƬ,��ָ��λ����Ⱦ��ӦͼƬ,ʵ���ƶ�Ч����(�ƶ���������λ�õ�ͼƬ����һ��),��һ���ƶ���λ���Ѿ���װ����(next_man,����
	// �Ѿ��ó�����)���������ڻ���Ҫ���滻�Ķ���,��һ�ѱȽ϶����ǿ��Է�װ��һ������

	if (def_flag && map[next_man.x][next_man.y] == FLOOR) {
			def_flag = false; // �뿪Ŀ�ĵ�֮��,������Ϊfalse,����ִ�в�������������
			changeLocate(&next_man, MAN);
			changeLocate(&man, DEF);
			man = next_man;
	}
	else if (map[next_man.x][next_man.y] == FLOOR) { /*����ƶ�����һ��λ���ǵذ�����ǵذ�Ŀ�ĵزſ����ƶ�,���򲻻��ƶ�*/
		// ��װλ�ƺ���
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
				def_flag = false; // �뿪Ŀ�ĵ�֮��,������Ϊfalse,����ִ�в�������������
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
* ���ݴ������,��ͼƬ����Ӧλ����Ⱦ����,ʵ���ƶ�Ч��
* ����:
*         x -- Ҫ��ӡ��λ���ڵڼ���
*         y -- Ҫ��ӡ��λ���ڵڼ���
*         good -- Ҫ�ڴ�λ�ô�ӡ��ͼƬ��ʲô
* ���:   ��
*********************************/
void changeLocate(locate *addr, goods good) {
	map[addr->x][addr->y] = good;

	putimage(PY_y+BOX_WID * addr->y, PY_x+BOX_WID * addr->x, &goods_img[good]);
}

/********************************
* �ж��Ƿ������Ϸ���� -- ���map������û��Ŀ�ĵ���.ֻ������Ŀ�ĵ�ʱ���Ǿ�˵�����Խ�����Ϸ��
* ����:   ��
* ���:   
*         true -- ���Խ���
*         false -- �������
*********************************/
bool isGameOver() {
	for (int i = 0; i < MAP_ROW; i++) {
		for (int j = 0; j < MAP_COL; j++) {
			if (map[i][j] == DEF) return false;  // ����е���DEF��,��˵��,��������û�е�Ŀ�ĵ�,����Ҫ������Ϸ
		}
	}

	return true;
}

/********************************
* ��Ϸ����,��ӡ��Ϸ����������
* ����:   ��
* ���:   ��
*********************************/
void GameOver() {
	putimage(0, 0, &goods_img[BG_IMAGE]);
	settextcolor(RED);
	
	// ����Ļ�����������,����鿴�ĵ���ʾ��
	RECT rect = { 0,0,WIN_ROW,WIN_COL }; // ���������ڻ�һ������
	drawtext(_T("��ϲͨ��"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void steps(int step) {
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	char temp[100];

	sprintf(temp,"���%d��",STEPS);

	// ����Ļ�����������,����鿴�ĵ���ʾ��
	RECT rect = { 0,0,WIN_ROW,WIN_COL }; // ���������ڻ�һ������
	drawtext(temp, &rect, DT_CENTER | DT_TOP);

	if (step > STEPS) {
		putimage(0, 0, &goods_img[BG_IMAGE]);
		settextcolor(RED);

		// ����Ļ�����������,����鿴�ĵ���ʾ��
		RECT rect = { 0,0,WIN_ROW,WIN_COL }; // ���������ڻ�һ������
		drawtext(_T("����ʹ������"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}