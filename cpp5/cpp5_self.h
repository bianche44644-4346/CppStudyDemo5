#ifndef SELF_CPP5
#define SELF_CPP5

#define WIN_ROW 700
#define WIN_COL 600

#define MAP_ROW  9
#define MAP_COL  9

#define BOX_WID 61
#define PY_x 25
#define PY_y 70

#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define QUIT 'q'

#define STEPS 30

/*********************************
* WALL : ��ʾǽ
* FLOOR : ��ʾ�ذ�
* MAN : ��ʾС��
* DEF : ��ʾ����Ŀ�ĵ�
* BOX : ��ʾ����
* ALL : ��ʾ���м�����Ʒ
**********************************/
typedef enum _GOODS { BG_IMAGE, WALL, FLOOR, MAN, DEF, BOX, BOX_DEF, ALL }goods; // ���һ��ALL��ʾ�ܹ��ж��ٸ�����

typedef enum _MOVE { UP, DOWN, LEFT, RIGHT }move;

typedef struct _LOCATE {  // �����Ʒ����Ӧλ��(������)
	int x;
	int y;
}locate;

void initGame();
void moveControl(move mov);
void manMove();
void changeLocate(locate* addr, goods good);
bool isGameOver();
void GameOver();
void steps(int step);

#endif
