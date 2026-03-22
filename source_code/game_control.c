#define _CRT_SECURE_NO_WARNINGS

#include"tictactoe.h"

int main()
{
	char ch;//菜单控制

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

int PvE_mode(void)
{
	char chess_board[9];//用户输入1-9表示占据棋盘位置
	char COORD[3][3];//程序处理棋子时需要坐标计算
	struct data* head = NULL;
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
			result = game_win_judge(COORD, &head);
			chess_num++;
			if (chess_num > 2)
				if (result != 0)
					break;
			if (chess_num == 9)
				break;
			chess_board[AI_input(COORD, &head, chess_num, who_go_first) - 1] = chess_symbol[who_go_first];
			print_chess(chess_board);
			change_num_to_COORD(COORD, chess_board);
			result = game_win_judge(COORD, &head);
			chess_num++;
			if (chess_num > 2)
				if (result != 0)
					break;
			if (chess_num == 9)
				break;
		}
		if (who_go_first == 2)
		{
			chess_board[AI_input(COORD, &head, chess_num, who_go_first) - 1] = chess_symbol[who_go_first - 2];
			print_chess(chess_board);
			change_num_to_COORD(COORD, chess_board);
			result = game_win_judge(COORD, &head);
			chess_num++;
			if (chess_num > 2)
				if (result != 0)
					break;
			if (chess_num == 9)
				break;

			chess_board[user_input(chess_board) - 1] = chess_symbol[who_go_first - 1];
			print_chess(chess_board);
			change_num_to_COORD(COORD, chess_board);
			result = game_win_judge(COORD, &head);
			chess_num++;
			if (chess_num > 2)
				if (result != 0)
					break;
			if (chess_num == 9)
				break;

		}
	}
	free_threat_data(&head);
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
	struct data* head = NULL;//头指针
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
			result = game_win_judge(COORD, &head);
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
	free_threat_data(&head);
	if (result == 1)
		printf("Player with chess 0 win!\n");
	else if (result == 2)
		printf("Player with chess x win!\n");
	else
		printf("No one wins.\n");
	return 0; 
}