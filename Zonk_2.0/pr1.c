#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>
#include "CONST.h"
#include <stdbool.h>
#include "GAME_LOGIC.h"

bool checkWin(int);

/*Создаёт массив из 6 элементов, наполняет его рандомными значениями от 1 до 6 и возвращяет*/
int* createRandomDices(int);

void printDices(int*, int);

/*Обрабатывает выбор игрока и возвращает массив с кол-вом костей каждого номинала*/
int* playerMove(int*, int*);

/*Вибирает лучшую комбинацию из возможных и возвращает массив с ней*/
int* botMove(int*, int*);  

void calculateTheSum(int*, int*);

/*Показывает результат хода игрока и обрабатывает решение о продолжении игры*/
int playersRoundResult(int*, int*, int*);

/*Показывает результат хода бота и принимает решение о продолжении игры*/
int botRoundResult(int*, int*, int*);


int main()
{
	int playerResult = 0, playerDecision = 1, selectedDiceCounter = 0, sum = 0, round = 1;
	int botResult = 0, botDecision = 1;

	srand(time(NULL));

	printf("\t\t\t\t\t\tNew game !\n\n");

	while (!checkWin(playerResult) && !checkWin(botResult))
	{
		printf("\t\t\t\t\t\tRound %d\n\n", round);

		printf("\t\t\t\t\t\tPlayer move\n\n");
		while (playerDecision != 0)
		{
			calculateTheSum(playerMove(createRandomDices(6 - selectedDiceCounter), &selectedDiceCounter), &sum);

			playerDecision = playersRoundResult(&sum, &selectedDiceCounter, &playerResult);
		}
		printf("\nThe final result is %d\n\n", playerResult);
		playerDecision = 1;

		if (checkWin(playerResult))
		{
			break;																										
		}

		printf("\t\t\t\t\t\tBot's move\n\n");
		while (botDecision != 0)
		{
			calculateTheSum(botMove(createRandomDices(6 - selectedDiceCounter), &selectedDiceCounter), &sum);
			Sleep (3000);
			
			botDecision = botRoundResult(&sum, &selectedDiceCounter, &botResult);
		}
		printf("\nBot's final result is %d\n\n", botResult);
		botDecision = 1;

		round++;
	}

	if (botResult > playerResult)
	{
		printf("Bot won!");
	}
	else
	{
		printf("Player won!");
	}

	return 0;
}


bool checkWin(int result)
{
	if (result > WINNING_RESULT - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int* createRandomDices(int diceCount)
{
	int i, *dices = (int*)malloc(diceCount * sizeof(int));

	for (i = 0; i < diceCount; i++)
	{
		*(dices + i) = rand() % 5 + 1;
	}

	printDices(dices, diceCount);

	return dices;
}


void printDices(int* dices, int diceCount)
{
	int i;

	for (i = 0; i < diceCount; i++)
	{
		printf("|%d|  ", *(dices + i));
	}
}


int* botMove(int* dices, int* selectedDicesCounter)
{
	int  i;
	static int	amountDices[6];

	for (i = 0; i < 6; i++)
	{
		amountDices[i] = 0;
	}

	/*Запись в массив количества костей каждого номинала*/
	for (i = 0; i < 6; ++i)
	{
		switch (*(dices + i))
		{
		case 1:
			amountDices[0]++;
			break;
		case 2:
			amountDices[1]++;
			break;
		case 3:
			amountDices[2]++;
			break;
		case 4:
			amountDices[3]++;
			break;
		case 5:
			amountDices[4]++;
			break;
		case 6:
			amountDices[5]++;
			break;
		}
	}

	/*Удаление не приносящих очки значений*/
	for (i = 0; i < 6; i++)
	{
		if ((i != 0 && i != 4) && amountDices[i] < 3)
		{
			amountDices[i] = 0;
		}
		*selectedDicesCounter = *selectedDicesCounter + amountDices[i];
	}

	free(dices);

	return amountDices;
}


int* playerMove(int* dices, int* selectedDicesCounter)
{
	int i, d = -1, diceNumbers[6] = { 0 };
	static int amountDices[6] = {0};

	printf("\n\nEnter bone numbers (enter 0 to finish)\n");
	for (i = 0; i < 6 && d != 0; ++i)
	{
		scanf_s("%d", &d);
		diceNumbers[i] = d;

		/*Счётчик не должен защитывать символ завершения ввода*/
		if (d != 0)
		{
			(*selectedDicesCounter)++;
		}
	}

	for (i = 0; i < 6; i++)
	{
		amountDices[i] = 0;
	}

	/*Запись в массив количества костей каждого номинала*/
	for (i = 0; diceNumbers[i] != 0 && i < 6; ++i)
	{
		switch (*(dices + diceNumbers[i] - 1))
		{
		case 1:
			amountDices[0]++;
			break;
		case 2:
			amountDices[1]++;
			break;
		case 3:
			amountDices[2]++;
			break;
		case 4:
			amountDices[3]++;
			break;
		case 5:
			amountDices[4]++;
			break;
		case 6:
			amountDices[5]++;
			break;
		}
	}

	free(dices);

	return amountDices;
}


void calculateTheSum(int* amountDices, int* sum)
{
	int i, dicesCounter = 0;

	/*Для 1 и 5 действуют отдельные правила подсчёта суммы*/
	for (i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			switch (*amountDices)
			{
			case 1:
				*sum = *sum + HUNDRED;
				break;
			case 2:
				*sum = *sum + 2 * HUNDRED;
				break;
			case 3:
				*sum = *sum + THOUSAND;
				break;
			case 4:
				*sum = *sum + 2 * THOUSAND;
				break;
			case 5:
				*sum = *sum + 4 * THOUSAND;
				break;
			case 6:
				*sum = *sum + 8 * THOUSAND;
				break;
			}
		}
		else if (i == 4)
		{
			switch (*(amountDices + 4))
			{
			case 1:
				*sum = *sum + FIFTY;
				break;
			case 2:
				*sum = *sum + 2 * FIFTY;
				break;
			case 3:
				*sum = *sum + FIVE_HUNDRED;
				break;
			case 4:
				*sum = *sum + 2 * FIVE_HUNDRED;
				break;
			case 5:
				*sum = *sum + 4 * FIVE_HUNDRED;
				break;
			case 6:
				*sum = *sum + 8 * FIVE_HUNDRED;
				break;
			}
		}
		else
		{
			if (*(amountDices + i) > 2)
			{
				switch (*(amountDices + i))
				{
				case 3:
					*sum = *sum + (i + 1) * HUNDRED;
					break;
				case 4:
					*sum = *sum + (i + 1) * 2 * HUNDRED;
					break;
				case 5:
					*sum = *sum + (i + 1) * 4 * HUNDRED;
					break;
				case 6:
					*sum = *sum + (i + 1) * 8 * HUNDRED;
					break;
				}
			}

			/*Обнуление суммы в том случае, если была выбрана одна*/
			/*или две кости со значением 2,3,4,6*/
			else if (*(amountDices + i) != 0)
			{
				*sum = -1;
				break;
			}
		}
		dicesCounter = dicesCounter + *(amountDices + i);
	}

	/*Обнуление суммы в том случае, если не выбрали ни одну кость*/
	if (dicesCounter == 0)
	{
		*sum = -1;
	}
}


int playersRoundResult(int* sum, int* selectedBonesCounter, int* playerResult)
{
	int playerDecision;

	/*Игрок выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
	if (*sum == -1)
	{
		printf("\nThe current result is 0\n\n");
		*sum = 0;
		*selectedBonesCounter = 0;
		return 0;
	}

	/*Игрок выбирает 6 костей*/
	else if (*selectedBonesCounter == 6)
	{
		printf("\nThe current result is %d\nEnter 0 to save the result, or enter 1 to continue\n", *sum);
		scanf_s("%d", &playerDecision);

		if (playerDecision == 0)
		{
			*playerResult = *playerResult + *sum;
			*sum = 0;
			*selectedBonesCounter = 0;
		}
		else
		{
			*selectedBonesCounter = 0;
		}
		return playerDecision;
	}

	/*Игрок выбирает меньше 6 костей*/
	else
	{
		printf("\nThe current result is %d\nEnter 0 to save the result, or enter 1 to continue\n", *sum);
		scanf_s("%d", &playerDecision);

		if (playerDecision == 0)
		{
			*playerResult = *playerResult + *sum;
			*sum = 0;
			*selectedBonesCounter = 0;
		}
		return playerDecision;
	}
}


int botRoundResult(int* sum, int* selectedBonesCounter, int* botResult)
{
	/*Бот выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
	if (*sum == -1)
	{
		printf("\nBot's current result is 0\n\n");
		*sum = 0;
		*selectedBonesCounter = 0;
		return 0;
	}

	/*Бот выбирает 6 костей*/
	else if (*selectedBonesCounter == 6)
	{
		printf("\nBot's current result is %d\n\n", *sum);
		*selectedBonesCounter = 0;
		return 1;
	}

	/*Бот выбирает меньше 6 костей*/
	else
	{
		printf("\nBot's current result is %d\n\n", *sum);

		/*Условие окончания хода*/
		if (*selectedBonesCounter > 3 || (*sum > 300 && *selectedBonesCounter > 2))
		{
			*botResult = *botResult + *sum;
			*sum = 0;
			*selectedBonesCounter = 0;
			return 0;
		}
		else
		{
			return 1;
		}
	}
}