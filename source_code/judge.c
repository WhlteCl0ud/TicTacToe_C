#define _CRT_SECURE_NO_WARNINGS

#include"tictactoe.h"

int game_win_judge(const char COORD[][3], struct data** head)
{
	struct data* current;
	two_chess_judge(COORD, head);//创建链表
	current = *head;
	while (current != NULL)
	{
		if ((*current).piece == (*current).target)
		{
			if ((*current).piece == '0')
				return 1;
			if ((*current).piece == 'x')
				return 2;
		}
		current = current->next;
	}
	return 0;
}
int two_chess_judge(const char COORD[][3], struct data** head)
{
	free_threat_data(head);
	int i, j, x, y, status;
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
							place_chess_judge(COORD, head, status, i, j, x, y);//由位置判定函数确定是否有空位
						}
					}
				}
			}
		}
	}
	make_judge_data_single(head);
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
int place_chess_judge(const char COORD[][3], struct data** head, int situation, int i, int j, int x, int y)
{
	//坐标通用公式为：((3-x-i+3)%3,(3-j-y+3)%3)
	struct data* current, * previous;
	if (situation == 0)
	{
		return situation;
	}
	current = (struct data*)malloc(sizeof(struct data));
	if (current == NULL)
	{
		printf("Memory allocate failed.\n");
		exit(EXIT_FAILURE);
	}
	//写入数据
	(*current).i = i;
	(*current).j = j;
	(*current).x = x;
	(*current).y = y;
	(*current).piece = COORD[i][j];
	(*current).direction = situation;
	(*current).target = COORD[(3 - x - i + 3) % 3][(3 - j - y + 3) % 3];
	current->next = NULL;
	//判断头指针是否为空
	if (*head == NULL)
	{
		*head = current;
	}
	else
	{
		//找到链表末尾
		previous = *head;
		while (previous->next != NULL)
		{
			previous = previous->next;
		}
		//添加节点
		previous->next = current;
	}
	return situation;
}
void make_judge_data_single(struct data** head)
{
	struct data* anchor, * current, * previous;//current作为删除数据的指针，anchor是第一个锚点,current是第二个锚点,previous记录前节点
	anchor = *head;
	current = NULL;
	while (anchor != NULL)
	{
		previous = anchor;
		current = anchor->next;
		while (current != NULL)
		{
			//judge_data[7] = {i,j,x,y,piece,direction,target}
			if ((*current).piece == (*anchor).piece && (*current).direction == (*anchor).direction && (*current).target == (*anchor).target)
			{
				if ((*current).i == (*anchor).i && (*current).j == (*anchor).j && (*current).x == (*anchor).x && (*current).y == (*anchor).y)
				{
					previous->next = current->next;
					free(current);
					current = previous->next;
					continue;
				}
				if ((*current).i == (*anchor).x && (*current).j == (*anchor).y && (*current).x == (*anchor).i && (*current).y == (*anchor).j)
				{
					previous->next = current->next;
					free(current);
					current = previous->next;
					continue;
				}
			}
			previous = current;
			current = current->next;

		}
		anchor = anchor->next;
	}
}