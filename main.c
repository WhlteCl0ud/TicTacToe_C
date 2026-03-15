#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define SIZE 50
#define DATA_SIZE 7

void initialised_chess_board(char* chess_board); //清空棋盘，初始化棋子数
void initialised_judge_data(int judge_data[][DATA_SIZE]);//清空判定数据
void make_judge_data_single(int judge_data[][DATA_SIZE]);//清理重复数据
void print_chess(char*);//打印棋盘
void clear_buffer(void);//清理缓冲区
int user_input(char*);//用户输入判定，如果输入正确则返回输入的值
void change_num_to_COORD(char arr[][3], char*);//把棋盘数据转化成坐标计算

int game_win_judge(const char COORD[][3],int judge_data[][DATA_SIZE]);
/*判定输赢的函数。从two_chess_judge出发，判定两子能否连成三子。
COORD传递坐标*/

int two_chess_judge(const char COORD[][3], int judge_data[][DATA_SIZE]);
/*two_chess_judge函数接收棋盘坐标，在坐标内寻找能构成直线的两子。
它找到所有情况后存放在judge_data中。每次调用前初始化judge_data.*/

int two_chess_location_judge(int i, int j, int x, int y);
/*two_chess_judge函数的内置判定函数，用于判定两子构成何种状态。
1为横向；2为纵向；3为左上到右下；4为左下到右上，0为不构成连子*/

int place_chess_judge(const char COORD[][3], int judge_data[][DATA_SIZE], int situation, int count, int i, int j, int x, int y);
/*two_chess_judge函数的内置判定函数，用于判定两子是否威胁到AI。
judge_data储存符合情况的数据，situation传递棋子情况，count决定数据组序号，ijxy为坐标，COORD传递棋子形状。*/

int AI_input(const char COORD[][3], int judge_data[][DATA_SIZE], int chess_num, int who_go_first);
/*AI根据judge_data决定自己应该进攻，防守还是随机落子*/

int AI_random_chess(const char COORD[][3]);
/*AI随机落子*/

int PvP_mode(void);

int PvE_mode(void);
int Who_First(void);//用户先返回1，AI先返回2

int main()
{
	char ch;//菜单控制

	//int judge_data[9][DATA_SIZE];
	/* 0,1,2,3,4,5,6分别对应第一子的两个坐标，第二子的两个坐标，子的形状,子的连线情况，应该落子的地方是空位还是棋子*/

	srand((unsigned int)time(NULL));
	printf("Welcome to our chess game.\n");
	printf("To start pvp, press a. To start pve, press b.\n");
	printf("To quit, press Q.\n");
	while ((ch = getchar()) != 'q')    //控制菜单
	{
		clear_buffer();
		if (ch != 'a' && ch != 'b')
			continue;
		if (ch == 'a')
		{
			printf("Game started.\n");
			PvP_mode();
			printf("To start pvp, press a. To start pve, press b.\n");
			printf("To quit, press Q.\n");
			continue;
		}
		if(ch == 'b')
		{
			printf("Game started.\n");
			PvE_mode();
			printf("To start pvp, press a. To start pve, press b.\n");
			printf("To quit, press Q.\n");
			continue;
		}
		
	}
	printf("Game Quit.\n");
	return 0;
}
void initialised_chess_board(char *chess_board)
{
	int i ;
	for (i = 0; i < 9; i++)
		chess_board[i] = ' ';
}
void initialised_judge_data(int judge_data[][DATA_SIZE])
{
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < DATA_SIZE; j++)
			judge_data[i][j] = -1;
}
void print_chess(char* chess_board)
{
	int i;
	for (i = 1; i <= 9; i++)
	{
		printf("%c", chess_board[i-1]);
		if (i % 3 != 0)
			putchar('|');
		if (i % 3 == 0 && i != 9)
		{
			putchar('\n');
			printf("------\n");
		}
		if (i == 9)
			putchar('\n');
	}
	putchar('\n');
}
int user_input(char* chess_board)
{
	int chess_location_temp;
	int temp;
	temp = scanf("%d", &chess_location_temp);
	clear_buffer();
	while (1)
	{
		if ( temp == 1)
		{
			if (chess_location_temp >= 1 && chess_location_temp <= 9)
			{
				if (chess_board[chess_location_temp - 1] != ' ')
				{
					printf("There's already a chess! Please try again.\n");
					temp = scanf("%d", &chess_location_temp);
					clear_buffer();
				}
					
				else
					break;
			}
			else
			{
				printf("Wrong input! please try again.\n");
				temp = scanf("%d", &chess_location_temp);
				clear_buffer();
			}
		}
		else
		{
			printf("Wrong input! please try again.\n");
			temp = scanf("%d", &chess_location_temp);
			clear_buffer();
		}
	}
	return chess_location_temp;
}
void clear_buffer(void)
{
	while (getchar() != '\n')
		continue;
}
void change_num_to_COORD(char COORD[][3], char* chess_board)
{
	int i, j;
	for (i = 0; i < 3; i++)  
		for (j = 0; j < 3; j++)
			COORD[i][j] = chess_board[3 * i + j];
}
int Who_First(void)
{
	int ch;
	printf("Do You want to go first? Y/N\n");
	while (ch
		= getchar())
	{
		clear_buffer();
		if (ch == 'y' || ch == 'Y')
		{
			printf("OK,you go first.\n");
			return 1;
		}
		else if (ch == 'n' || ch == 'N')
		{
			printf("Ok, me, the AI, will go first.\n");
			return 2;
		}
		else
			continue;
	}
}
int PvE_mode(void)
{
	char chess_board[9];//用户输入1-9表示占据棋盘位置
	char COORD[3][3];//程序处理棋子时需要坐标计算
	int judge_data[SIZE][DATA_SIZE];//存放两子情况
	int chess_num = 0;//控制平局
	int who_go_first = 0;//默认是0
	int result = 0;
	const char chess_symbol[3] = { '0','x' };
	initialised_chess_board(chess_board);
	change_num_to_COORD(COORD, chess_board);
	who_go_first = Who_First();
	while (chess_num < 9)
	{
		if (who_go_first == 1)//用户先
		{
			chess_board[user_input(chess_board) - 1] = chess_symbol[who_go_first - 1];
			print_chess(chess_board);
			change_num_to_COORD(COORD, chess_board);
			result = game_win_judge(COORD, judge_data);
			chess_num++;
			if (chess_num > 2)
				if (result != 0)
					break;
			if (chess_num == 9)
				break;
			chess_board[AI_input(COORD, judge_data, chess_num, who_go_first) - 1] = chess_symbol[who_go_first];
			print_chess(chess_board);
			change_num_to_COORD(COORD, chess_board);
			result = game_win_judge(COORD, judge_data);
			chess_num++;
			if (chess_num > 2)
				if (result != 0)
					break;
			if (chess_num == 9)
				break;
		}
		if (who_go_first == 2)
		{
			chess_board[AI_input(COORD, judge_data, chess_num, who_go_first) - 1] = chess_symbol[who_go_first - 2];
			print_chess(chess_board);
			change_num_to_COORD(COORD, chess_board);
			result = game_win_judge(COORD, judge_data);
			chess_num++;
			if (chess_num > 2)
				if (result != 0)
					break;
			if (chess_num == 9)
				break;

			chess_board[user_input(chess_board) - 1] = chess_symbol[who_go_first - 1];
			print_chess(chess_board);
			change_num_to_COORD(COORD, chess_board);
			result = game_win_judge(COORD, judge_data);
			chess_num++;
			if (chess_num > 2)
				if (result != 0)
					break;
			if (chess_num == 9)
				break;

		}
	}
	if (result == 1)
	{
		if(who_go_first == 1)
			printf("Player  win!\n");
		else
			printf("AI  win!\n");
	}
	else if (result == 2)
	{
		if (who_go_first == 1)
			printf("AI  win!\n");
		else
			printf("Player win!\n");
	}
	else
		printf("No one wins.\n");
	return 0;
}
int PvP_mode(void)
{
	char chess_board[9];//用户输入1-9表示占据棋盘位置
	char COORD[3][3];//程序处理棋子时需要坐标计算
	int judge_data[SIZE][DATA_SIZE];//存放两子情况
	int user_chess_num = 0;//控制平局
	const char chess_symbol[3] = { '0','x' };
	int i, result;

	initialised_chess_board(chess_board);
	change_num_to_COORD(COORD, chess_board);
	while (user_chess_num < 9)
	{
		for (i = 0; i < 2; i++)
		{
			chess_board[user_input(chess_board) - 1] = chess_symbol[i];
			print_chess(chess_board);
			change_num_to_COORD(COORD, chess_board);
			result = game_win_judge(COORD, judge_data);
			user_chess_num++;
			if (user_chess_num > 2)
				if (result != 0)
					break;
			if (user_chess_num == 9)
				break;
		}
		if (user_chess_num > 2)
			if (result != 0)
				break;
	}
	if (result == 1)
		printf("Player with chess 0 win!\n");
	else if (result == 2)
		printf("Player with chess x win!\n");
	else
		printf("No one wins.\n");
	return 0; 
}

int AI_input(const char COORD[][3], int judge_data[][DATA_SIZE], int chess_num, int who_go_first)
{
	int time = 0;
	int chess_x, chess_y;
	chess_x = chess_y = -1;
	char AI_symbol = ((who_go_first == 1) ? 'x' : '0');
	char user_symbol = ((who_go_first == 1) ? '0' : 'x');
	two_chess_judge(COORD, judge_data);
	if(chess_num == 0)
		return AI_random_chess(COORD);
	while (time < SIZE)
	{
		if (judge_data[time][0] == -1 || judge_data[time][6] != ' ')//未连成两子
		{
			time++;
			continue;
		}
		if (judge_data[time][4] == AI_symbol && judge_data[time][6] == ' ')//首先判定AI能不能一击必杀
		{
			chess_x = (3 - judge_data[time][0] - judge_data[time][2] + 3) % 3;
			chess_y = (3 - judge_data[time][1] - judge_data[time][3] + 3) % 3;
			return (chess_x * 3 + chess_y + 1);
		}
		if (judge_data[time][4] == user_symbol && judge_data[time][6] == ' ')//再判定AI需不需要防守，只需一组坐标，因为如果有两组则必输
		{
			chess_x = (3 - judge_data[time][0] - judge_data[time][2] + 3) % 3;
			chess_y = (3 - judge_data[time][1] - judge_data[time][3] + 3) % 3;
			time++;
			continue;
		}
	}
	if (chess_x != -1)
		return (chess_x * 3 + chess_y + 1);
	return AI_random_chess(COORD);//默认情况
}
int AI_random_chess(const char COORD[][3])
{
	int chess_place_random;
	while (1)
	{
		chess_place_random = rand() % 9;
		if (COORD[chess_place_random / 3][chess_place_random % 3] == ' ')
			return (chess_place_random + 1);
	}
}

int game_win_judge(const char COORD[][3], int judge_data[][DATA_SIZE])
{
	two_chess_judge(COORD, judge_data);
	int count = 0;
	while (count < SIZE)
	{
		if (judge_data[count][0] == -1)
		{
			count++;
			continue;
		}
		if (judge_data[count][4] == judge_data[count][6])
		{
			if (judge_data[count][4] == '0')
				return 1;
			if (judge_data[count][4] == 'x')
				return 2;
		}
		count++;
	}
	return 0;
}
int two_chess_judge(const char COORD[][3], int judge_data[][DATA_SIZE])
{
	int i, j, x, y, status;
	int count = 0;
	initialised_judge_data(judge_data);
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (COORD[i][j] != ' ')
			{
				for (x = i - 2; x <= i + 2; x++)
				{
					if (x < 0 || x > 2)
					{
						continue;//排除x不合法的情况
					}
					for (y = j - 2; y <= j + 2; y++)
					{
						if (y < 0 || y > 2)
							continue;//排除有不合法的情况
						if (x == i && y == j)
							continue;//排除重合情况
						if (COORD[x][y] == COORD[i][j])//两子相同时
						{
							status = two_chess_location_judge(i, j, x, y);//由构成判定函数确定构型
							place_chess_judge(COORD, judge_data, status, count, i, j, x, y);//由位置判定函数确定是否有空位
							make_judge_data_single(judge_data);
							count++;//下一次循环
							if (count >= SIZE)
							{
								printf("Error:judge_data overflow!\n");
								exit(EXIT_FAILURE);
							}
						}
					}       
				}
			}
		}
	}
	return 0;
}
int two_chess_location_judge(int i, int j, int x, int y)
{
	if (x == i)
		return 1;//横向
	else if (y == j)
		return 2;//纵向
	else if (i == j && x == y)
		return 3;//左上到右下
	else if (i + j == 2 && x + y == 2)
		return 4;//左下到右上
	else
		return 0;
}
int place_chess_judge(const char COORD[][3], int judge_data[][DATA_SIZE], int situation, int count, int i, int j, int x, int y )
{
	//坐标通用公式为：((3-x-i+3)%3,(3-j-y+3)%3)
	if (situation == 0)
	{
		return situation;
	}
	judge_data[count][0] = i;
	judge_data[count][1] = j;
	judge_data[count][2] = x;
	judge_data[count][3] = y;
	judge_data[count][4] = COORD[i][j];
	judge_data[count][5] = situation;
	judge_data[count][6] = COORD[(3 - x - i + 3) % 3][(3 - j - y + 3) % 3];
	return situation;
}
void make_judge_data_single(int judge_data[][DATA_SIZE])
{
	int m, n;
	for (m = 0; m < SIZE-1; m++)
	{
		for (n = m +1; n < SIZE; n++)
		{
			if (judge_data[n][5] != -1 && judge_data[m][5] != -1 && (judge_data[n][4] == judge_data[m][4]) && (judge_data[n][5] == judge_data[m][5]) && (judge_data[n][6] == judge_data[m][6]))
			{
				if ((judge_data[n][0] == judge_data[m][2]) && (judge_data[n][1] == judge_data[m][3]) && (judge_data[n][2] == judge_data[m][0]) && (judge_data[n][3] == judge_data[m][1]))
				{
					for (int q = 0; q < DATA_SIZE; q ++ )
						judge_data[n][q] = -1;
				}
				if ((judge_data[n][0] == judge_data[m][0]) && (judge_data[n][1] == judge_data[m][1]) && (judge_data[n][2] == judge_data[m][2]) && (judge_data[n][3] == judge_data[m][3]))
				{
					for (int q = 0; q < DATA_SIZE; q++)
						judge_data[n][q] = -1;
				}
			}
		}
	}
} 
