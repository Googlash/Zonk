int* createRandomDices(int);
void printDices(int*, int);
void playerMove(int*, int*, int*);
void botMove(int*, int*, int*);
void calculateTheSum(int*, int*);
int playersRoundResult(int*, int*, int*);
int botRoundResult(int*, int*, int*);


/*Функция получает в качестве параметра итоговый результат. Если победа достигнута - возвращает истину, в противном случае - ложь*/
bool checkWin(int result)
{
	if (result > 4000 - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*Функия получает в качестве параметра количество костей и возвращает указатель на массив рандомных костей*/
int* createRandomDices(int diceCount)
{
	int i, * dices = (int*)malloc(diceCount * sizeof(int));

	for (i = 0; i < diceCount; i++)
	{
		*(dices + i) = rand() % 5 + 1;
	}

	return dices;
}


/*Функция получает в качестве параметра указатель на массив костей и количество костей*/
void printDices(int* dices, int diceCount)
{
	int i;

	for (i = 0; i < diceCount; i++)
	{
		printf("|%d|  ", *(dices + i));
	}
}


/*Функция получает в качестве параметра указатель на массив костей, указатель на количество выбранных костей и указатель на массив кол-ва костей каждого номинла*/
void playerMove(int* dices, int* selectedDicesCounter, int* amountDices)
{
	int i, d = -1, diceNumbers[6] = { 0 };

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
		*(amountDices + i) = 0;
	}

	/*Запись в массив количества костей каждого номинала*/
	for (i = 0; diceNumbers[i] != 0 && i < 6; ++i)
	{
		switch (*(dices + diceNumbers[i] - 1))
		{
		case 1:
			(*(amountDices + 0))++;
			break;
		case 2:
			(*(amountDices + 1))++;
			break;
		case 3:
			(*(amountDices + 2))++;
			break;
		case 4:
			(*(amountDices + 3))++;
			break;
		case 5:
			(*(amountDices + 4))++;
			break;
		case 6:
			(*(amountDices + 5))++;
			break;
		}
	}

	free(dices);
}


/*Функция получает в качестве параметра указатель на массив костей, указатель на количество выбранных костей и указатель на массив кол-ва костей каждого номинла*/
void botMove(int* dices, int* selectedDicesCounter, int* amountDices)
{
	int  i;

	for (i = 0; i < 6; i++)
	{
		*(amountDices + i) = 0;
	}

	/*Запись в массив количества костей каждого номинала*/
	for (i = 0; i < 6; ++i)
	{
		switch (*(dices + i))
		{
		case 1:
			(*(amountDices + 0))++;
			break;
		case 2:
			(*(amountDices + 1))++;
			break;
		case 3:
			(*(amountDices + 2))++;
			break;
		case 4:
			(*(amountDices + 3))++;
			break;
		case 5:
			(*(amountDices + 4))++;
			break;
		case 6:
			(*(amountDices + 5))++;
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
}


/*Функция получает в качестве параметра указатель на массив кол-ва костей каждого номинала и указатель на переменную для записи суммы*/
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
				*sum = *sum + 100;
				break;
			case 2:
				*sum = *sum + 2 * 100;
				break;
			case 3:
				*sum = *sum + 1000;
				break;
			case 4:
				*sum = *sum + 2 * 1000;
				break;
			case 5:
				*sum = *sum + 4 * 1000;
				break;
			case 6:
				*sum = *sum + 8 * 1000;
				break;
			}
		}
		else if (i == 4)
		{
			switch (*(amountDices + 4))
			{
			case 1:
				*sum = *sum + 50;
				break;
			case 2:
				*sum = *sum + 2 * 50;
				break;
			case 3:
				*sum = *sum + 500;
				break;
			case 4:
				*sum = *sum + 2 * 500;
				break;
			case 5:
				*sum = *sum + 4 * 500;
				break;
			case 6:
				*sum = *sum + 8 * 500;
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
					*sum = *sum + (i + 1) * 100;
					break;
				case 4:
					*sum = *sum + (i + 1) * 2 * 100;
					break;
				case 5:
					*sum = *sum + (i + 1) * 4 * 100;
					break;
				case 6:
					*sum = *sum + (i + 1) * 8 * 100;
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


/*Функция получает в качестве параметра указатель на сумму, указатель на кол-во выбранных костей, указатель на итоговый результат игрока и возвращает выбор игрока*/
int playersRoundResult(int* sum, int* selectedDicesCounter, int* playerResult)
{
	int playerDecision;

	/*Игрок выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
	if (*sum == -1)
	{
		printf("\nThe current result is 0\n\n");
		*sum = 0;
		*selectedDicesCounter = 0;
		return 0;
	}

	/*Игрок выбирает 6 костей*/
	else if (*selectedDicesCounter == 6)
	{
		printf("\nThe current result is %d\nEnter 0 to save the result, or enter 1 to continue\n", *sum);
		scanf_s("%d", &playerDecision);

		if (playerDecision == 0)
		{
			*playerResult = *playerResult + *sum;
			*sum = 0;
			*selectedDicesCounter = 0;
		}
		else
		{
			*selectedDicesCounter = 0;
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
			*selectedDicesCounter = 0;
		}
		return playerDecision;
	}
}


/*Функция получает в качестве параметра указатель на сумму, указатель на кол-во выбранных костей, указатель на итоговый результат бота и возвращает выбор бота*/
int botRoundResult(int* sum, int* selectedDicesCounter, int* botResult)
{
	/*Бот выбирает комбинацию, которая не приносит очков и вызывает обнуление текущей суммы*/
	if (*sum == -1)
	{
		printf("\nBot's current result is 0\n\n");
		*sum = 0;
		*selectedDicesCounter = 0;
		return 0;
	}

	/*Бот выбирает 6 костей*/
	else if (*selectedDicesCounter == 6)
	{
		printf("\nBot's current result is %d\n\n", *sum);
		*selectedDicesCounter = 0;
		return 1;
	}

	/*Бот выбирает меньше 6 костей*/
	else
	{
		printf("\nBot's current result is %d\n\n", *sum);

		/*Условие окончания хода*/
		if (*selectedDicesCounter > 3 || (*sum > 300 && *selectedDicesCounter > 2))
		{
			*botResult = *botResult + *sum;
			*sum = 0;
			*selectedDicesCounter = 0;
			return 0;
		}
		else
		{
			return 1;
		}
	}
}