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
* WALL : 表示墙
* FLOOR : 表示地板
* MAN : 表示小人
* DEF : 表示箱子目的地
* BOX : 表示箱子
* ALL : 表示共有几个物品
**********************************/
typedef enum _GOODS { BG_IMAGE, WALL, FLOOR, MAN, DEF, BOX, BOX_DEF, ALL }goods; // 最后一个ALL表示总共有多少个数据

typedef enum _MOVE { UP, DOWN, LEFT, RIGHT }move;

typedef struct _LOCATE {  // 存放物品的相应位置(包括人)
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
