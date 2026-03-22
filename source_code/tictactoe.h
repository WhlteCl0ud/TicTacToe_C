#define _CRT_SECURE_NO_WARNINGS
#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

struct data
{
	int i, j;
	int x, y;
	char piece;//两子形状
	int direction;//连子方向
	char target;//第三者形状
	struct data* next;
};

void initialised_chess_board(char* chess_board); //清空棋盘，初始化棋子数
void free_threat_data(struct data** head);//清空判定数据
void make_judge_data_single(struct data** head);//清理重复数据
void print_chess(char*);//打印棋盘
void clear_buffer(void);//清理缓冲区
int user_input(char*);//用户输入判定，如果输入正确则返回输入的值
void change_num_to_COORD(char arr[][3], char*);//把棋盘数据转化成坐标计算

int game_win_judge(const char COORD[][3], struct data** head);
/*判定输赢的函数。从two_chess_judge出发，判定两子能否连成三子。
COORD传递坐标*/

int two_chess_judge(const char COORD[][3], struct data** head);
/*two_chess_judge函数接收棋盘坐标，在坐标内寻找能构成直线的两子。
它找到所有情况后存放在judge_data中。每次调用前初始化judge_data.*/

int two_chess_location_judge(int i, int j, int x, int y);
/*two_chess_judge函数的内置判定函数，用于判定两子构成何种状态。
1为横向；2为纵向；3为左上到右下；4为左下到右上，0为不构成连子*/

int place_chess_judge(const char COORD[][3], struct data** head, int situation, int i, int j, int x, int y);
/*two_chess_judge函数的内置判定函数，用于判定两子是否威胁到AI。
judge_data储存符合情况的数据，situation传递棋子情况，count决定数据组序号，ijxy为坐标，COORD传递棋子形状。*/

int AI_input(const char COORD[][3], struct data** head, int chess_num, int who_go_first);
/*AI根据judge_data决定自己应该进攻，防守还是随机落子*/

int AI_random_chess(const char COORD[][3]);
/*AI随机落子*/

int PvP_mode(void);

int PvE_mode(void);
int Who_First(void);//用户先返回1，AI先返回2

#endif