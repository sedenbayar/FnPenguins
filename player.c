#include "penguin.h"
#include "player.h"
#include "handling.h"
#include "algorithm.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER_OF_PENGUINS 4

playerType* player_container(int number_of_players)
{
	playerType *players = (playerType*)malloc(number_of_players * sizeof(struct playerType));
	return players;
}
void free_memory_1(playerType *players)
{
	free(players);	
}
playerType add_player(char identifier)
{
	int i;
	playerType player;
	for (i = 0; i < NUMBER_OF_PENGUINS; i++)
	{
		player.penguins[i].x = -1;
		player.penguins[i].y = -1;
	}
	player.points = 0;
	player.is_dead = 0;
	player.identifier = identifier;
	return player;
}
playerType add_new_players_penguin(playerType player, int x, int y)
{
	int i;
	for (i = 0; i < NUMBER_OF_PENGUINS; i++)
	{
		if ((player.penguins[i].x == -1) && (player.penguins[i].y == -1))
		{
			player.penguins[i] = add_penguin(x, y);
			break;
		}
	}
	return player;
}
playerType moving_switch(char **board, playerType player, int direction, int how_far, int which_penguin, int size_of_the_board)		/* made by Dominik*/
{
	int i;
	for (i = 0; i < how_far; i++)
	{
		switch (direction)
		{
		case 0:	/* moving right */
		{	
			if (player_will_be_on_the_board_right(player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
			{
				if (field_have_fishes_right(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
				{
					player.penguins[which_penguin].x += 0;
					player.penguins[which_penguin].y += 1;
				}
			}
		break;
		}
		case 1: /* moving bottom right */
		{
			if (player_will_be_on_the_board_bottom_right(player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
			{
				if (player.penguins[which_penguin].x % 2 == 0)
				{
					if (field_have_fishes_bottom_right(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
					{
						player.penguins[which_penguin].x += 1;
						player.penguins[which_penguin].y += 1;
					}
				}
				else
				{
					if (field_have_fishes_bottom_right(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
					{
						player.penguins[which_penguin].x += 1;
						player.penguins[which_penguin].y += 0;
					};
				}
			}
			break;
		}
		case 2: /* moving bottom left */
		{
			if (player_will_be_on_the_board_bottom_left(player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
			{
				if (player.penguins[which_penguin].x % 2 == 0)
				{
					if (field_have_fishes_bottom_left(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
					{
						player.penguins[which_penguin].x += 1;
						player.penguins[which_penguin].y += 0;
					}
				}
				else
				{
					if (field_have_fishes_bottom_left(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
					{
						player.penguins[which_penguin].x += 1;
						player.penguins[which_penguin].y -= 1;
					}
				}
			}
			break;
		}
		case 3: /* moving left */
		{
			if (player_will_be_on_the_board_left(player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
			{
				if (field_have_fishes_left(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
				{
					player.penguins[which_penguin].x += 0;
					player.penguins[which_penguin].y -= 1;
				}
			}
		break;
		}
		case 4: /* moving top left */
		{
			if (player_will_be_on_the_board_top_left(player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
			{
				if (player.penguins[which_penguin].x % 2 == 0)
				{
					if (field_have_fishes_top_left(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
					{
						player.penguins[which_penguin].x -= 1;
						player.penguins[which_penguin].y += 0;
					}
				}
				else
				{
					if (field_have_fishes_top_left(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
					{
						player.penguins[which_penguin].x -= 1;
						player.penguins[which_penguin].y -= 1;
					}
				}
			}
			break;
		}
		case 5: /* moving top right */
		{
			if (player_will_be_on_the_board_top_right(player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
			{
				if (player.penguins[which_penguin].x % 2 == 0)
				{
					if (field_have_fishes_top_right(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
					{
						player.penguins[which_penguin].x -= 1;
						player.penguins[which_penguin].y += 1;
					}
				}
				else
				{
					if (field_have_fishes_top_right(board, player.penguins[which_penguin].x, player.penguins[which_penguin].y, size_of_the_board))
					{
						player.penguins[which_penguin].x -= 1;
						player.penguins[which_penguin].y += 0;
					}
				}
			}
			break;
		}
		}
		player.penguins[which_penguin].is_dead = is_penguin_dead(board, player, size_of_the_board, which_penguin);
		if (player.penguins[which_penguin].is_dead == 1)
		{
			printf("PENGUIN IS DEAD");
			return player;
		}
	}
	return player;
}
playerType player_move(char **board, playerType player, int direction, int how_far, int size_of_the_board, int which_penguin) /* 0 - right, 1 - bottom right, 2 - bottom left, 3 - left, 4 - top left, 5 - top right. coordinates - position of the player*/
{
	if (player.penguins[which_penguin].is_dead != 1)
	{
		if (player.penguins[which_penguin].points == 0)
		{
			player.penguins[which_penguin].points += board[player.penguins[which_penguin].x][player.penguins[which_penguin].y];
			board[player.penguins[which_penguin].x][player.penguins[which_penguin].y] = 0;
		}
		player = moving_switch(board, player, direction, how_far, which_penguin, size_of_the_board);
		player.penguins[which_penguin].points += board[player.penguins[which_penguin].x][player.penguins[which_penguin].y];
		board[player.penguins[which_penguin].x][player.penguins[which_penguin].y] = 0;
	}
	flag_player++;
	return player;
}
void save_the_player(playerType player, int argc, char** argv, unsigned int player_number)	/* It is saving the player to the file */
{
	int error_checker = argc - player_number;									/* Error exception */
	if (error_checker <= 0)
	{
		printf("\nInvalid player_number in read_the_player");
		exit(1);
	}
	int i;
	FILE *fp; /* For C File I/O you need to use a FILE pointer, which will let the program keep track of the file being accessed. 
			  (You can think of it as the memory address of the file or the location of the file). */
	if ((fp = fopen(argv[player_number], "w")) == NULL)
	{
		printf("Cannot open file!\n");
		exit(1);
	}
	fprintf(fp, "Name: %s", player.name);
	fprintf(fp, "\nPoints: %d", player.points);
	fprintf(fp, "\nIs dead: %d", player.is_dead);
	for (i = 0; i < NUMBER_OF_PENGUINS; i++)
	{
		if (player.penguins[i].x == -1 && player.penguins[i].y == -1)
			break;
		fprintf(fp, "\n\nPenguin: %d", i);
		fprintf(fp, "\nCoordinate x: %d", player.penguins[i].x);
		fprintf(fp, " | Coordinate y: %d", player.penguins[i].y);
		fprintf(fp, " | Points: %d", player.penguins[i].points);
		fprintf(fp, " | Is dead: %d", player.penguins[i].is_dead);
	}
	fclose(fp);
	return;
}
playerType read_the_player(int argc, char** argv, unsigned int player_number, int* num_of_penguins, int size_of_the_board)	//It is reading the player from the file 
{
	int error_checker = argc - player_number;									/* Error exception */
	if (error_checker <= 0)
	{
		printf("\nInvalid player_number in read_the_player");
		exit(1);
	}
	int i;
	int file_format_checking_name, file_format_checking_points, file_format_checking_isdead, file_format_checking_penguins, file_format_checking_coordinates;
	file_format_checking_name = file_format_checking_points = file_format_checking_isdead = file_format_checking_penguins = file_format_checking_coordinates = 1;
	char *name = malloc(sizeof(char) * 21);
	playerType player;
	for (i = 0; i < NUMBER_OF_PENGUINS; i++)
	{
		player.penguins[i].x = -1;
		player.penguins[i].y = -1;
	}
	FILE *fp;
	fp = fopen(argv[player_number], "r");
	if(fscanf(fp, "Name: %s\n", name) != 1)
		file_format_checking_name = 0;
	player.name = name;
	player.identifier = player.name[0];
	if(fscanf(fp, "Points: %d\n", &player.points) != 1)
		file_format_checking_points = 0;
	if(fscanf(fp, "Is dead: %d\n", &player.is_dead) != 1)
		file_format_checking_isdead = 0;
	for (i = 0; i < NUMBER_OF_PENGUINS; i++)
	{
		if (fscanf(fp, "\n\nPenguin: %d\n", &i) == 1)
		{
			if (fscanf(fp, "Coordinate x: %d | Coordinate y: %d | Points: %d | Is dead: %d", &player.penguins[i].x, &player.penguins[i].y, &player.penguins[i].points, &player.penguins[i].is_dead) != 4)
				file_format_checking_coordinates = 0;
			if (player.penguins[i].x > size_of_the_board)
				player.penguins[i].x = size_of_the_board - 1;					//Check position of penguins so if there is biger x and y in file you than board size penguins get max right down position		
			if (player.penguins[i].y > size_of_the_board)
				player.penguins[i].y = size_of_the_board - 1;
			(*num_of_penguins)++;
		}
		else
		{
			if (i == 0)
				file_format_checking_penguins = 0;
			break;
		}
	}
	fclose(fp);
	if (!file_format_checking_name || !file_format_checking_points || !file_format_checking_isdead || !file_format_checking_penguins || !file_format_checking_coordinates)
	{
		printf("There is something wrong with your %s.txt file.\n", argv[player_number]);
		printf("Please check if the following parts of the file are correct: \n");
		if (!file_format_checking_name)
			printf("-Name of the player\n");
		if (!file_format_checking_points)
			printf("-Points of the player\n");
		if (!file_format_checking_isdead)
			printf("-Is dead value\n");
		if (!file_format_checking_penguins)
			printf("-Penguins\n");
		if (!file_format_checking_coordinates)
			printf("-Penguins values\n");
		exit(1);
	}
	printf("%d", *num_of_penguins);
	delay(100);
	return player;
}