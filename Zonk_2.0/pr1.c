#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>
#include "CONST.h"

int* createRandomDices(int);                    /*Создаёт массив из 6 элементов, наполняет его рандомными значениями от 1 до 6 и возвращяет*/
int* selectionOfDices(int*, int*);              /*Обрабатывает выбор игрока и возвращает массив с этим выбором*/
void calculateTheSum(int*, int*);               /*Подсчитывает сумму костей*/
int* botMove(int*, int*);                       /*Вибирает лучшую комбинацию из возможных и возвращает массив с ней*/
void printDices(int*, int);

int main()
{
	int playerResult = 0, botResult = 0, sum = 0, i = 1, playerDecision = 1, botDecision = 1,selectedBonesCounter = 0;

	srand(time(NULL));

	printf("\t\t\t\t\t\tNew game !\n\n");

	while (playerResult < WINNING_RESULT && botResult < WINNING_RESULT)                                                 /*Условие победы*/
	{
		printf("\t\t\t\t\t\tRound %d\n\n", i);

		printf("\t\t\t\t\t\tPlayer move\n\n");
		while (playerDecision != 0)
		{
			calculateTheSum(selectionOfDices(createRandomDices(6 - selectedBonesCounter), &selectedBonesCounter), &sum);

			if (sum == -1)                                                                                              /*Игрок выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
			{
				printf("\nThe current result is 0\n\n");
				printf("\nThe final result is %d\n\n", playerResult);
				sum = 0;
				selectedBonesCounter = 0;
				playerDecision = 0;
				break;
			}
			else if (selectedBonesCounter == 6)
			{
				printf("\nThe current result is %d\nEnter 0 to save the result, or enter 1 to continue\n", sum);        /*Игрок выбирает 6 костей*/
				scanf_s("%d", &playerDecision);
				selectedBonesCounter = 0;
			}
			else                                                                                                        /*Игрок выбирает меньше 6 костей*/
			{
				printf("\nThe current result is %d\nEnter 0 to save the result, or enter 1 to continue\n", sum);
				scanf_s("%d", &playerDecision);

				if (playerDecision == 0)
				{
					playerResult = playerResult + sum;
					sum = 0;
					selectedBonesCounter = 0;
					printf("\nThe final result is %d\n\n", playerResult);
				}
			}
		}
		playerDecision = 1;
		if (playerResult >= WINNING_RESULT)
		{
			printf("Player won!");
			break;																										
		}

		printf("\t\t\t\t\t\tBot's move\n\n");
		while (botDecision != 0)
		{
			calculateTheSum(botMove(createRandomDices(6 - selectedBonesCounter), &selectedBonesCounter), &sum);
			Sleep (3000);

			if (sum == -1)                                                                                              /*Бот выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
			{
				printf("\nBot's current result is 0\n\n");
				printf("\nBot's final result is %d\n\n", botResult);
				sum = 0;
				selectedBonesCounter = 0;
				botDecision = 0;
				break;
			}
			else if (selectedBonesCounter == 6)                                                                         /*Бот выбирает 6 костей*/
			{
				printf("\nBot's current result is %d\n\n", sum);														
				selectedBonesCounter = 0;
			}
			else                                                                                                        /*Бот выбирает меньше 6 костей*/
			{
				printf("\nBot's current result is %d\n\n", sum);

				if (selectedBonesCounter >= 4 || (sum > 300 && selectedBonesCounter >= 3))                              /*Условие окончания хода*/
				{
					botResult = botResult + sum;
					sum = 0;
					selectedBonesCounter = 0;
					botDecision = 0;
					printf("\nBot's final result is %d\n\n", botResult);
				}
			}
		}
		botDecision = 1;
		if (botResult >= WINNING_RESULT)
		{
			printf("Bot won!");
		}

		i++;
	}

	return 0;
}


int* createRandomDices(int diceCount)                                               /*Бросок n костей*/
{
	int i, *dices = (int*)malloc(diceCount * sizeof(int));                          /*Выделение памяти под n элемернтов типа int */

	for (i = 0; i <= diceCount - 1; i++)                                            /*Заполняет n элементов случайными числами от 1 до 6*/
	{
		*(dices + i) = rand() % 5 + 1;
	}

	printDices(dices, diceCount);

	return dices;
}


void printDices(int* dicesPtr, int diceCount)
{
	int i;

	for (i = 0; i <= diceCount - 1; i++)
	{
		printf("|%d|  ", *(dicesPtr + i));
	}
}


int* botMove(int* dicesPtr, int* selectedDicesCounterPtr)
{
	int  i;
	static int	amountDices[6];

	for (i = 0; i <= 5; i++)                                                        /*Обнуление массива*/
	{
		amountDices[i] = 0;
	}

	for (i = 0; i <= 5; ++i)                                                        /*Запись в массив количества костей каждого номинала*/
	{
		switch (*(dicesPtr + i))
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

	for (i = 0; i <= 5; i++)                                                        /*Удаление не приносящих очки значений*/
	{
		if ((i != 0 && i != 4) && amountDices[i] <= 2)
		{
			amountDices[i] = 0;
		}
		*selectedDicesCounterPtr = *selectedDicesCounterPtr + amountDices[i];       /*Подсчёт количества выбранных костей*/
	}

	free(dicesPtr);

	return amountDices;
}


int* selectionOfDices(int* dicesPtr, int* selectedDicesCounterPtr)
{
	int i, d = -1, diceNumbers[6] = { 0 };
	static int amountDices[6] = {0};

	printf("\n\nEnter bone numbers (enter 0 to finish)\n");
	for (i = 0; i <= 5 && d != 0; ++i)                                              /*Игрок выбирает кости и вводи их номера*/
	{
		scanf_s("%d", &d);
		diceNumbers[i] = d;
		if (d != 0)                                                                 /*Счётчик не должен защитывать символ завершения ввода*/
		{
			(*selectedDicesCounterPtr)++;                                           /*Считает количество выбранных костей*/
		}
	}

	for (i = 0; i <= 5; i++)                                                        /*Обнуление массива*/
	{
		amountDices[i] = 0;
	}

	for (i = 0; diceNumbers[i] != 0 && i <= 5; ++i)                                 /*Запись в массив количества костей каждого номинала*/
	{
		switch (*(dicesPtr + diceNumbers[i] - 1))
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

	free(dicesPtr);

	return amountDices;
}


void calculateTheSum(int* amountDicesPtr, int* sumPtr)
{
	int i, dicesCounter = 0;

	for (i = 0; i <= 5; i++)                                        /*Подсчёт результата*/
	{
		if (i == 0)                                                 /*Для 1 и 5 действуют отдельные правила подсчёта суммы*/
		{
			switch (*amountDicesPtr)
			{
			case 1:
				*sumPtr = *sumPtr + HUNDRED;
				break;
			case 2:
				*sumPtr = *sumPtr + 2 * HUNDRED;
				break;
			case 3:
				*sumPtr = *sumPtr + THOUSAND;
				break;
			case 4:
				*sumPtr = *sumPtr + 2 * THOUSAND;
				break;
			case 5:
				*sumPtr = *sumPtr + 4 * THOUSAND;
				break;
			case 6:
				*sumPtr = *sumPtr + 8 * THOUSAND;
				break;
			}
		}
		else if (i == 4)
		{
			switch (*(amountDicesPtr + 4))
			{
			case 1:
				*sumPtr = *sumPtr + FIFTY;
				break;
			case 2:
				*sumPtr = *sumPtr + 2 * FIFTY;
				break;
			case 3:
				*sumPtr = *sumPtr + FIVE_HUNDRED;
				break;
			case 4:
				*sumPtr = *sumPtr + 2 * FIVE_HUNDRED;
				break;
			case 5:
				*sumPtr = *sumPtr + 4 * FIVE_HUNDRED;
				break;
			case 6:
				*sumPtr = *sumPtr + 8 * FIVE_HUNDRED;
				break;
			}
		}
		else
		{
			if (*(amountDicesPtr + i) >= 3)
			{
				switch (*(amountDicesPtr + i))
				{
				case 3:
					*sumPtr = *sumPtr + (i + 1) * HUNDRED;
					break;
				case 4:
					*sumPtr = *sumPtr + (i + 1) * 2 * HUNDRED;
					break;
				case 5:
					*sumPtr = *sumPtr + (i + 1) * 4 * HUNDRED;
					break;
				case 6:
					*sumPtr = *sumPtr + (i + 1) * 8 * HUNDRED;
					break;
				}
			}
			else if (*(amountDicesPtr + i) != 0)                                  /*Обнуление суммы в том случае, если была выбрана одна*/
			{                                                                     /*или две кости со значением 2,3,4,6*/                                                    
				*sumPtr = -1;
				break;
			}
		}
		dicesCounter = dicesCounter + *(amountDicesPtr + i);
	}

	if (dicesCounter == 0)
	{
		*sumPtr = -1;                                                              /*Обнуление суммы в том случае, если не выбрали ни одну кость*/
	}
}
