#ifndef BOX_MOVE
#define BOX_MOVE

// ����Ҫ�ظ�ʹ�õĶ���������ŵ�ͷ�ļ���,������Ҫ��ȫ�ֱ����ŵ��궨����(��Ϊ�������Ƕ���ļ��ظ�ʹ��,���Ǳ��ļ�ʹ��)
#define win_row 960
#define win_col 768

#define map_row 9
#define map_col 12
#define box_wid 61 // ���ӿ��

// ��С���ƶ��İ�ȫ�Լ�鶨���һ����,����ߴ���Ŀɶ���
#define checkSecurity(temp) (temp.x >= 0 && temp.x <= map_row && temp.y >= 0 && temp.y <= map_col)

// �����--˵����Ӧ�Ŀ��� -- ��ߴ���Ŀɶ���
#define KEY_UP 'w'  // ���ƶ�
#define KEY_DOWN 's'  // ���ƶ�
#define KEY_LEFT 'a'  // ���ƶ�
#define KEY_RIGHT 'd'  // ���ƶ�
#define QUIT 'q' // �˳�

// ��λƫ�� int py_x = 100, py_y = 150; // ���û������߿��ƫ��ֵ
#define py_x 100
#define py_y 100


// ���ǿ�����д��ôһ���궨�壬��Ȼ�������Ŀɶ��������,��������ܶ�궨���Ƚ�ӷ��,��������ֵ����������(��ȡֵ�̶�)������
// ����ʹ��ö������enum����ʾ(����Ҳ�����������(����֮����Ҫ�޸Ĵ���))
enum goods { WALL, FLOOR, BOX_DEFINATE, MAN, BOX, BOX_IN_TARGET, ALL };


// С�˵�x,y�ڶ�ά����������±�  �ܶ࿪Դ��Ŀ�ṹ������ʹ�� _��ͷ
struct _S_MAN {
	int x;
	int y;
}man;

// ������һ��ö�ٱ�ʾ����Ŀ���(��Ϊ�����������ı�,���ҿ���ʹ�����ֱ�ʾ)
enum direction { UP, DOWN, LEFT, RIGHT };

#endif