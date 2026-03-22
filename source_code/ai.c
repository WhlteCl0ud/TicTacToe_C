#define _CRT_SECURE_NO_WARNINGS

#include"tictactoe.h"

int AI_input(const char COORD[][3], struct data** head, int chess_num, int who_go_first)
{
	int chess_x, chess_y;
	chess_x = chess_y = -1;
	char AI_symbol = ((who_go_first == 1) ? 'x' : '0');
	char user_symbol = ((who_go_first == 1) ? '0' : 'x');
	struct data* current;
	two_chess_judge(COORD, head);//创建链表
	current = *head;
	if (chess_num == 0)
		return AI_random_chess(COORD);
	while (current != NULL)
	{
		if ((*current).piece == AI_symbol && (*current).target == ' ')//首先判定AI能不能一击必杀
		{
			chess_x = (3 - (*current).i - (*current).x + 3) % 3;
			chess_y = (3 - (*current).j - (*current).y + 3) % 3;
			return (chess_x * 3 + chess_y + 1);
		}
		if ((*current).piece == user_symbol && (*current).target == ' ')//再判定AI需不需要防守，只需一组坐标，因为如果有两组则必输
		{
			chess_x = (3 - (*current).i - (*current).x + 3) % 3;
			chess_y = (3 - (*current).j - (*current).y + 3) % 3;
			current = current->next;
			continue;
		}
		current = current->next;
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