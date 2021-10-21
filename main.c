#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_LENGTH 70
#define MIN_LENGTH 10
#define MAX_PATH_LENGTH 5

struct PlayerInfo
{
	int numOfLives;
	char playerSymbol;
	int numOfTreasuresFound;
	int counter;
	int history[MAX_LENGTH];
};

struct GameInfo
{
	int maxNumOfMoves;
	int pathLength;
	int bomb[MAX_LENGTH];
	int treasure[MAX_LENGTH];
};

int main(void)
{
	const int maxNumOfLives = 10, minNumOfLives = 1;
	double limitOfMoves = 0.0;
	int round = 0;
	int i;
	int j;
	int move = 0;
	int flag = 1;

	struct PlayerInfo playerInfo = { 0 };
	struct GameInfo gameInfo = { 0 };

	printf("================================\n");
	printf("         Treasure Hunt!         \n");
	printf("================================\n\n");
	printf("PLAYER Configuration\n");
	printf("--------------------\n");
	printf("Enter a single character to represent the player: ");
	scanf("%c", &playerInfo.playerSymbol);
	printf("Set the number of lives: ");
	scanf("%d", &playerInfo.numOfLives);

	while (playerInfo.numOfLives < minNumOfLives || playerInfo.numOfLives > maxNumOfLives)
	{
		printf("     Must be between %d and %d!\n", minNumOfLives, maxNumOfLives);
		printf("Set the number of lives: ");
		scanf("%d", &playerInfo.numOfLives);
	}
	printf("Player configuration set-up is complete\n\n");
	printf("GAME Configuration\n");
	printf("------------------\n");
	printf("Set the path length (a multiple of %d between %d-%d): ", MAX_PATH_LENGTH, MIN_LENGTH, MAX_LENGTH);
	scanf("%d", &gameInfo.pathLength);

	while (gameInfo.pathLength > MAX_LENGTH || gameInfo.pathLength < MIN_LENGTH || gameInfo.pathLength % MAX_PATH_LENGTH != 0)
	{
		printf("     Must be a multiple of 5 and between 10-70!!!\n");
		printf("Set the path length (a multiple of %d between %d-%d): ", MAX_PATH_LENGTH, MIN_LENGTH, MAX_LENGTH);
		scanf("%d", &gameInfo.pathLength);
	}
	for (i = 0; i < gameInfo.pathLength; i++)
		playerInfo.history[i] = '-';

	limitOfMoves = gameInfo.pathLength * 0.75;
	round = (int)(limitOfMoves + 0.5); // rounding to the nearest whole number

	printf("Set the limit for number of moves allowed: ");
	scanf("%d", &gameInfo.maxNumOfMoves);
	while (gameInfo.maxNumOfMoves < playerInfo.numOfLives || gameInfo.maxNumOfMoves > limitOfMoves)
	{
		printf("    Value must be between %d and %d", playerInfo.numOfLives, round);
		printf("\nSet the limit for number of moves allowed: ");
		scanf("%d", &gameInfo.maxNumOfMoves);
	}

	printf("\nBOMB Placement\n");
	printf("--------------\n");
	printf("Enter the bomb positions in sets of %d where a value\nof 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n", MAX_PATH_LENGTH);
	printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", gameInfo.pathLength);

	for (i = 0; i < gameInfo.pathLength; i += MAX_PATH_LENGTH)
	{
		printf("   Positions [%2d-%2d]: ", i + 1, i + MAX_PATH_LENGTH);
		for (j = i; j < MAX_PATH_LENGTH + i; j++)
		{
			scanf("%d", &gameInfo.bomb[j]);
		}
		while (getchar() != '\n');
	}
	printf("BOMB placement set\n");
	printf("\nTREASURE Placement\n");
	printf("------------------\n");
	printf("Enter the treasure placements in sets of %d where a value\nof 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n", MAX_PATH_LENGTH);
	printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", gameInfo.pathLength);
	for (i = 0; i < gameInfo.pathLength; i += MAX_PATH_LENGTH)
	{
		printf("   Positions [%2d-%2d]: ", i + 1, i + MAX_PATH_LENGTH);
		for (j = i; j < MAX_PATH_LENGTH + i; j++)
		{
			scanf("%d", &gameInfo.treasure[j]);
		}
		while (getchar() != '\n');
	}
	printf("TREASURE placement set\n\n");
	printf("GAME configuration set-up is complete...\n\n");
	printf("------------------------------------\n");
	printf("TREASURE HUNT Configuration Settings\n");
	printf("------------------------------------\n");
	printf("Player:\n");
	printf("   Symbol     : %c\n", playerInfo.playerSymbol);
	printf("   Lives      : %d\n", playerInfo.numOfLives);
	printf("   Treasure   : [ready for gameplay]\n");
	printf("   History    : [ready for gameplay]\n");
	printf("\nGame:\n");
	printf("   Path Length: %d", gameInfo.pathLength);
	printf("\n   Bombs      : ");
	for (i = 0; i < gameInfo.pathLength; i++)
	{
		printf("%d", gameInfo.bomb[i]);
	}
	printf("\n   Treasure   : ");
	for (i = 0; i < gameInfo.pathLength; i++)
	{
		printf("%d", gameInfo.treasure[i]);
	}
	printf("\n\n====================================\n");
	printf("~ Get ready to play TREASURE HUNT! ~");
	printf("\n====================================\n\n");

	// part 2

	do
	{
		if (move > 0)
		{
			printf("  ");
			for (i = 1; i <= gameInfo.pathLength; i++)
			{
				if (i == move)
					printf("%c", playerInfo.playerSymbol);
				else
					printf(" ");
			}
			printf("\n");
		}
		else
			printf("\n");



		printf("  ");
		for (i = 0; i < gameInfo.pathLength; i++)
			printf("%c", playerInfo.history[i]);
		printf("\n");



		printf("  ");
		for (i = 1; i <= gameInfo.pathLength; i++)
		{
			if (i % 10 == 0)
				printf("%d", i / 10);
			else
				printf("|");
		}
		printf("\n");



		printf("  ");
		for (i = 1; i <= gameInfo.pathLength; i++)
			printf("%d", i % 10);



		printf("\n+---------------------------------------------------+\n");
		printf("  Lives:  %d  | Treasures:  %d  |  Moves Remaining: %2d\n", playerInfo.numOfLives, playerInfo.counter, gameInfo.maxNumOfMoves);
		printf("+---------------------------------------------------+\n");



		flag = 1;
		do
		{
			printf("Next Move [1-%d]: ", gameInfo.pathLength);
			scanf("%d", &move);
			if (move >= 1 && move <= gameInfo.pathLength)
				flag = 0;
			else
				printf("  Out of Range!!!\n");
		} while (flag);



		if (playerInfo.history[move - 1] == '&' || playerInfo.history[move - 1] == '!' || playerInfo.history[move - 1] == '$' || playerInfo.history[move - 1] == '.')
			printf("\n===============> Dope! You've been here before!\n\n");
		else if (gameInfo.bomb[move - 1] > 0 && gameInfo.treasure[move - 1] > 0)
		{
			printf("\n===============> [&] !!! BOOOOOM !!! [&]\n");
			printf("===============> [&] $$$ Life Insurance Payout!!! [&]\n\n");
			playerInfo.history[move - 1] = '&';
			gameInfo.maxNumOfMoves--;
			playerInfo.numOfLives--;
			playerInfo.counter++;
		}
		else if (gameInfo.bomb[move - 1] > 0)
		{
			printf("\n===============> [!] !!! BOOOOOM !!! [!]\n\n");
			playerInfo.history[move - 1] = '!';
			gameInfo.maxNumOfMoves--;
			playerInfo.numOfLives--;
		}
		else if (gameInfo.treasure[move - 1] > 0)
		{
			printf("\n===============> [$] $$$ Found Treasure! $$$ [$]\n\n");
			playerInfo.history[move - 1] = '$';
			gameInfo.maxNumOfMoves--;
			playerInfo.counter++;
		}
		else
		{
			printf("\n===============> [.] ...Nothing found here... [.]\n\n");
			playerInfo.history[move - 1] = '.';
			gameInfo.maxNumOfMoves--;
		}
	} while (playerInfo.numOfLives > 0 && gameInfo.maxNumOfMoves > 0);



	if (playerInfo.numOfLives == 0)
		printf("No more LIVES remaining!\n\n");
	if (gameInfo.maxNumOfMoves == 0)
		printf("No more MOVES remaining!\n\n");



	printf("  ");
	for (i = 1; i <= gameInfo.pathLength; i++)
	{
		if (i == move)
			printf("%c", playerInfo.playerSymbol);
		else
			printf(" ");
	}
	printf("\n");



	printf("  ");
	for (i = 0; i < gameInfo.pathLength; i++)
		printf("%c", playerInfo.history[i]);
	printf("\n");



	printf("  ");
	for (i = 1; i <= gameInfo.pathLength; i++)
	{
		if (i % 10 == 0)
			printf("%d", i / 10);
		else
			printf("|");
	}
	printf("\n");



	printf("  ");
	for (i = 1; i <= gameInfo.pathLength; i++)
		printf("%d", i % 10);



	printf("\n+---------------------------------------------------+\n");
	printf("  Lives:  %d  | Treasures:  %d  |  Moves Remaining: %2d\n", playerInfo.numOfLives, playerInfo.counter, gameInfo.maxNumOfMoves);
	printf("+---------------------------------------------------+\n");

	printf("\n##################\n");
	printf("#   Game over!   #\n");
	printf("##################\n");
	printf("\nTry again!");
	return 0;
}
