#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>
#include <stdbool.h>
#include "GAME_CONST.h"

/*Функция получает в качестве параметра итоговый результат. Если победа достигнута - возвращает истину, в противном случае - ложь*/
bool checkWin(int result)
{
	return result > WINNING_RESULT - 1;
}

/*Функия возвращает случайне число от 1 до 6*/
int generatingRandomDice()
{
	int number;
	number = rand() % 5 + 1;

	return number;
}


/*Функия получает в качестве параметра количество неиспользованных костей и возвращает указатель на массив рандомных костей*/
void fillRandomDices(int unusedDice, int(*fun)(), int* dices)
{
	int i;

	if (dices != NULL)
	{
		for (i = 0; i < unusedDice; i++)
		{
			*(dices + i) = fun();
		}
	}
}


/*Функция получает в качестве параметра указатель на массив костей и количество неиспользованных костей*/
void printDices(int* dices, int unusedDice)
{
	int i;

	for (i = 0; i < unusedDice; i++)
	{
		printf("|%d|  ", *(dices + i));
	}
}


/*Функция получает в качестве параметра указатель на количество использованных костей и указатель на массив выбранных костей*/
void playerMove(int* usedDice, int* selectedDice)
{
	int i, d = -1;

	for (i = 0; i < INITIAL_AMOUNT_DICE; i++)
	{
		*(selectedDice + i) = 0;
	}

	printf("\n\nEnter bone numbers (enter 0 to finish)\n");
	for (i = 0; i < INITIAL_AMOUNT_DICE && d != 0; ++i)
	{
		scanf_s("%d", &d);
		*(selectedDice + i) = d;

		/*Счётчик не должен защитывать символ завершения ввода*/
		if (d != 0)
		{
			(*usedDice)++;
		}
	}

}


/*Функция получает в качестве параметра указатель на количество использованных костей и указатель на массив кол-ва костей каждого номинла*/
void botMove(int* usedDice, int* sortedDice)
{
	int  i;

	/*Удаление не приносящих очки значений*/
	for (i = 0; i < 6; i++)
	{
		if ((i != 0 && i != 4) && sortedDice[i] < 3)
		{
			sortedDice[i] = 0;
		}
		*usedDice = *usedDice + sortedDice[i];
	}
}

/*Функция получает в качестве параметра указатель на массив выбранных костей и количество неиспользованных костей*/
void selectAllDice(int* selectedDice, int unusedDice)
{
	int i;

	for (i = 0; i < INITIAL_AMOUNT_DICE; i++)
	{
		*(selectedDice + i) = 0;
	}

	for (i = 0; i < unusedDice; i++)
	{
		*(selectedDice + i) = i + 1;
	}
}


/*Функция получает в качестве параметра указатель на массив выбранных костей, указатель на массив всех сгенерированных костей и указатель на массив отсортированных костей*/
void sortByQuantity(int* selectedDice, int* sortedDice, int* dices)
{
	int i;

	for (i = 0; i < INITIAL_AMOUNT_DICE; i++)
	{
		*(sortedDice + i) = 0;
	}

	/*Запись в массив количества костей каждого номинала*/
	for (i = 0; *(selectedDice + i) != 0 && i < INITIAL_AMOUNT_DICE; ++i)
	{
		switch (*(dices + *(selectedDice + i) - 1))
		{
		case 1:
			(*(sortedDice + 0))++;
			break;
		case 2:
			(*(sortedDice + 1))++;
			break;
		case 3:
			(*(sortedDice + 2))++;
			break;
		case 4:
			(*(sortedDice + 3))++;
			break;
		case 5:
			(*(sortedDice + 4))++;
			break;
		case 6:
			(*(sortedDice + 5))++;
			break;
		}
	}

	free(dices);
}


/*Функция получает в качестве параметра указатель на массив кол-ва костей каждого номинала и указатель на переменную для записи суммы*/
void calculateTheSum(int* sortedDice, int* sum)
{
	int i, dicesCounter = 0;

	/*Для 1 и 5 действуют отдельные правила подсчёта суммы*/
	for (i = 0; i < INITIAL_AMOUNT_DICE; i++)
	{
		if (i == 0)
		{
			switch (*sortedDice)
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
			switch (*(sortedDice + 4))
			{
			case 1:
				*sum = *sum + FIFTY;
				break;
			case 2:
				*sum = *sum + 2 * FIFTY;
				break;
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
		else
		{
			if (*(sortedDice + i) > 2)
			{
				switch (*(sortedDice + i))
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
			else if (*(sortedDice + i) != 0)
			{
				*sum = -1;
				break;
			}
		}

		/*Отслеживает количество выбранных костей на текущей итерации хода*/
		dicesCounter = dicesCounter + *(sortedDice + i);
	}

	/*Обнуление суммы в том случае, если не выбрали ни одну кость*/
	if (dicesCounter == 0)
	{
		*sum = -1;
	}
}


/*Функция получает в качестве параметра указатель на сумму, указатель на кол-во выбранных костей, указатель на итоговый результат игрока и возвращает выбор игрока*/
int playersRoundResult(int* sum, int* usedDice, int* playerResult)
{
	int playerDecision;

	/*Игрок выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
	if (*sum == -1)
	{
		printf("\nThe current result is 0\n\n");
		*sum = 0;
		*usedDice = 0;
		return 0;
	}

	/*Игрок выбирает 6 костей*/
	else if (*usedDice == 6)
	{
		printf("\nThe current result is %d\nEnter 0 to save the result, or enter 1 to continue\n", *sum);
		scanf_s("%d", &playerDecision);

		if (playerDecision == 0)
		{
			*playerResult = *playerResult + *sum;
			*sum = 0;
			*usedDice = 0;
		}
		else
		{
			*usedDice = 0;
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
			*usedDice = 0;
		}
		return playerDecision;
	}
}


/*Функция получает в качестве параметра указатель на сумму, указатель на кол-во выбранных костей, указатель на итоговый результат бота и возвращает выбор бота*/
int botRoundResult(int* sum, int* usedDice, int* botResult)
{
	/*Бот выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
	if (*sum == -1)
	{
		printf("\nBot's current result is 0\n\n");
		*sum = 0;
		*usedDice = 0;
		return 0;
	}

	/*Бот выбирает 6 костей*/
	else if (*usedDice == 6)
	{
		printf("\nBot's current result is %d\n\n", *sum);
		*usedDice = 0;
		return 1;
	}

	/*Бот выбирает меньше 6 костей*/
	else
	{
		printf("\nBot's current result is %d\n\n", *sum);

		/*Условие окончания хода*/
		if (*usedDice > 3 || (*sum > 300 && *usedDice > 2))
		{
			*botResult = *botResult + *sum;
			*sum = 0;
			*usedDice = 0;
			return 0;
		}
		else
		{
			return 1;
		}
	}
}