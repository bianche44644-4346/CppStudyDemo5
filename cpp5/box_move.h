#ifndef BOX_MOVE
#define BOX_MOVE

// 将需要重复使用的定义和声明放到头文件中,尽量不要将全局变量放到宏定义中(因为它并不是多个文件重复使用,而是本文件使用)
#define win_row 960
#define win_col 768

#define map_row 9
#define map_col 12
#define box_wid 61 // 箱子宽度

// 将小人移动的安全性检查定义成一个宏,以提高代码的可读性
#define checkSecurity(temp) (temp.x >= 0 && temp.x <= map_row && temp.y >= 0 && temp.y <= map_col)

// 定义宏--说明相应的控制 -- 提高代码的可读性
#define KEY_UP 'w'  // 上移动
#define KEY_DOWN 's'  // 下移动
#define KEY_LEFT 'a'  // 左移动
#define KEY_RIGHT 'd'  // 右移动
#define QUIT 'q' // 退出

// 首位偏移 int py_x = 100, py_y = 150; // 设置画面距离边框的偏移值
#define py_x 100
#define py_y 100


// 我们看上面写这么一串宏定义，虽然下面代码的可读性提高了,但是如果很多宏定义会比较臃肿,而且这块的值都是连续的(且取值固定)，所以
// 可以使用枚举类型enum来表示(并且也方便后面增加(增加之后不需要修改代码))
enum goods { WALL, FLOOR, BOX_DEFINATE, MAN, BOX, BOX_IN_TARGET, ALL };


// 小人的x,y在二维数组的行列下标  很多开源项目结构体名称使用 _开头
struct _S_MAN {
	int x;
	int y;
}man;

// 定义了一个枚举表示方向的控制(因为方向基本不会改变,而且可以使用数字表示)
enum direction { UP, DOWN, LEFT, RIGHT };

#endif