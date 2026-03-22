#define _CRT_SECURE_NO_WARNINGS

#include"tictactoe.h"

void initialised_chess_board(char* chess_board)
{
	int i;
	for (i = 0; i < 9; i++)
		chess_board[i] = ' ';
}
void free_threat_data(struct data** head)
{
	struct data* current;
	current = *head;
	while (current != NULL)
	{
		*head = (*head)->next;
		free(current);
		current = *head;
	}
}
void print_chess(char* chess_board)
{
	int i;
	for (i = 1; i <= 9; i++)
	{
		printf("%c", chess_board[i - 1]);
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
		if (temp == 1)
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