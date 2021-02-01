#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>
#include "CONST.h"

int creatingRandomBones(int);					/*Создаёт массив из 6 элементов, наполняет его рандомными значениями от 1 до 6 и возвращяет*/
int selectionOfBones(int*, int*);				/*Обрабатывает выбор игрока и возвращает массив с этим выбором*/
void calculatingTheSum(int*, int*);				/*Подсчитывает сумму костей*/
int botMove(int*, int*);						/*Вибирает лучшую комбинацию из возможных и возвращает массив с ней*/

int main()
{
	int playerResult = 0, botResult = 0, sum = 0, i = 1, playerDecision = 1, botDecision = 1,numberOfSelectedBones = 0;

	printf("\t\t\t\t\t\tNew game !\n\n");

	while (playerResult < WINNING_RESULT && botResult < WINNING_RESULT)						/*Условие победы*/
	{
		printf("\t\t\t\t\t\tRound %d\n\n", i);

		printf("\t\t\t\t\t\tPlayer move\n\n");
		while (playerDecision != 0)
		{
			calculatingTheSum(selectionOfBones(creatingRandomBones(6 - numberOfSelectedBones), &numberOfSelectedBones), &sum);

			if (sum == -1)																								/*Игрок выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
			{
				printf("\nThe current result is 0\n\n");
				printf("\nThe final result is %d\n\n", playerResult);
				sum = 0;
				numberOfSelectedBones = 0;
				playerDecision = 0;
				break;
			}
			else if (numberOfSelectedBones == 6)
			{
				printf("\nThe current result is %d\nEnter 0 to save the result, or enter 1 to continue\n", sum);		/*Игрок выбирает 6 костей*/
				scanf_s("%d", &playerDecision);
				numberOfSelectedBones = 0;
			}
			else																										/*Игрок выбирает меньше 6 костей*/
			{
				printf("\nThe current result is %d\nEnter 0 to save the result, or enter 1 to continue\n", sum);
				scanf_s("%d", &playerDecision);

				if (playerDecision == 0)
				{
					playerResult = playerResult + sum;
					sum = 0;
					numberOfSelectedBones = 0;
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
			calculatingTheSum(botMove(creatingRandomBones(6 - numberOfSelectedBones), &numberOfSelectedBones), &sum);
			Sleep (3000);

			if (sum == -1)																								/*Бот выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
			{
				printf("\nBot's current result is 0\n\n");
				printf("\nBot's final result is %d\n\n", botResult);
				sum = 0;
				numberOfSelectedBones = 0;
				botDecision = 0;
				break;
			}
			else if (numberOfSelectedBones == 6)																		/*Бот выбирает 6 костей*/
			{
				printf("\nBot's current result is %d\n\n", sum);														
				numberOfSelectedBones = 0;
			}
			else																										/*Бот выбирает меньше 6 костей*/
			{
				printf("\nBot's current result is %d\n\n", sum);

				if (numberOfSelectedBones >= 4 || (sum > 300 && numberOfSelectedBones >= 3))							/*Условие окончания хода*/
				{
					botResult = botResult + sum;
					sum = 0;
					numberOfSelectedBones = 0;
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


int creatingRandomBones(int allBones)								/*Бросок n костей*/
{
	int i, *randomBones = (int*)malloc(allBones * sizeof(int));		/*Выделение памяти под n элемернтов типа int */

	srand(time(NULL));

	for (i = 0; i <= allBones - 1; i++)								/*Заполняет n элементов случайными числами от 1 до 6*/
	{
		*(randomBones + i) = rand() % 5 + 1;
		printf("|%d|  ", *(randomBones + i));
	}

	return randomBones;
}


int botMove(int* randomBonesPtr, int* selItemsPtr)
{
	int  i;
	static int	amountBones[6];

	for (i = 0; i <= 5; i++)										/*Обнуление массива*/
	{
		amountBones[i] = 0;
	}

	for (i = 0; i <= 5; ++i)										/*Запись в массив количества костей каждого номинала*/
	{
		switch (*(randomBonesPtr + i))
		{
		case 1:
			amountBones[0]++;
			break;
		case 2:
			amountBones[1]++;
			break;
		case 3:
			amountBones[2]++;
			break;
		case 4:
			amountBones[3]++;
			break;
		case 5:
			amountBones[4]++;
			break;
		case 6:
			amountBones[5]++;
			break;
		}
	}

	for (i = 0; i <= 5; i++)										/*Удаление не приносящих очки значений*/
	{
		if ((i != 0 && i != 4) && amountBones[i] <= 2)
		{
			amountBones[i] = 0;
		}
		*selItemsPtr = *selItemsPtr + amountBones[i];						/*Подсчёт количества выбранных костей*/
	}

	if (*selItemsPtr == 0)												/*Если отсутствуют подходящие для выбора элемнеты, то в массив записывается одна 2*/
	{
		amountBones[1] = 1;
	}

	free(randomBonesPtr);

	return amountBones;
}


int selectionOfBones(int* randomBonesPtr, int* selItemsPtr)
{
	int i, d = -1, boneNumbers[6] = { 0 };
	static int amountBones[6];

	printf("\n\nEnter bone numbers (enter 0 to finish)\n");
	for (i = 0; i <= 5 && d != 0; ++i)								/*Игрок выбирает кости и вводи их номера*/
	{
		scanf_s("%d", &d);
		boneNumbers[i] = d;
		if (d != 0)													/*Счётчик не должен защитывать символ завершения ввода*/
		{
			(*selItemsPtr)++;											/*Считает количество выбранных костей*/
		}
	}

	for (i = 0; i <= 5; i++)										/*Обнуление массива*/
	{
		amountBones[i] = 0;
	}

	for (i = 0; boneNumbers[i] != 0 && i <= 5; ++i)					/*Запись в массив количества костей каждого номинала*/
	{
		switch (*(randomBonesPtr + boneNumbers[i] - 1))
		{
		case 1:
			amountBones[0]++;
			break;
		case 2:
			amountBones[1]++;
			break;
		case 3:
			amountBones[2]++;
			break;
		case 4:
			amountBones[3]++;
			break;
		case 5:
			amountBones[4]++;
			break;
		case 6:
			amountBones[5]++;
			break;
		}
	}

	free(randomBonesPtr);

	return amountBones;
}


void calculatingTheSum(int* amountBonesPtr, int* sumPtr)
{
	int i;

	for (i = 0; i <= 5; i++)										/*Подсчёт результата*/
	{
		if (i == 0)													/*Для 1 и 5 действуют отдельные правила подсчёта суммы*/
		{
			switch (*amountBonesPtr)
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
			switch (*(amountBonesPtr + 4))
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
			if (*(amountBonesPtr + i) >= 3)
			{
				switch (*(amountBonesPtr + i))
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
		}
	}

	for (i = 0; i <= 5; i++)											/*Обнуление суммы в том случае, если была выбрана одна или две кости со значением 2,3,4,6*/
	{
		if (i == 1 || i == 2 || i == 3 || i == 5)
		{
			if (*(amountBonesPtr + i) == 1 || *(amountBonesPtr + i) == 2)
			{
				*sumPtr = -1;
			}
		}
	}
}
