int* createRandomDices(int);
void printDices(int*, int);
void playerMove(int*, int*, int*);
void botMove(int*, int*, int*);
void calculateTheSum(int*, int*);
int playersRoundResult(int*, int*, int*);
int botRoundResult(int*, int*, int*);


/*������� �������� � �������� ��������� �������� ���������. ���� ������ ���������� - ���������� ������, � ��������� ������ - ����*/
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


/*������ �������� � �������� ��������� ���������� ������ � ���������� ��������� �� ������ ��������� ������*/
int* createRandomDices(int diceCount)
{
	int i, * dices = (int*)malloc(diceCount * sizeof(int));

	for (i = 0; i < diceCount; i++)
	{
		*(dices + i) = rand() % 5 + 1;
	}

	return dices;
}


/*������� �������� � �������� ��������� ��������� �� ������ ������ � ���������� ������*/
void printDices(int* dices, int diceCount)
{
	int i;

	for (i = 0; i < diceCount; i++)
	{
		printf("|%d|  ", *(dices + i));
	}
}


/*������� �������� � �������� ��������� ��������� �� ������ ������, ��������� �� ���������� ��������� ������ � ��������� �� ������ ���-�� ������ ������� �������*/
void playerMove(int* dices, int* selectedDicesCounter, int* amountDices)
{
	int i, d = -1, diceNumbers[6] = { 0 };

	printf("\n\nEnter bone numbers (enter 0 to finish)\n");
	for (i = 0; i < 6 && d != 0; ++i)
	{
		scanf_s("%d", &d);
		diceNumbers[i] = d;

		/*������� �� ������ ���������� ������ ���������� �����*/
		if (d != 0)
		{
			(*selectedDicesCounter)++;
		}
	}

	for (i = 0; i < 6; i++)
	{
		*(amountDices + i) = 0;
	}

	/*������ � ������ ���������� ������ ������� ��������*/
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


/*������� �������� � �������� ��������� ��������� �� ������ ������, ��������� �� ���������� ��������� ������ � ��������� �� ������ ���-�� ������ ������� �������*/
void botMove(int* dices, int* selectedDicesCounter, int* amountDices)
{
	int  i;

	for (i = 0; i < 6; i++)
	{
		*(amountDices + i) = 0;
	}

	/*������ � ������ ���������� ������ ������� ��������*/
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

	/*�������� �� ���������� ���� ��������*/
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


/*������� �������� � �������� ��������� ��������� �� ������ ���-�� ������ ������� �������� � ��������� �� ���������� ��� ������ �����*/
void calculateTheSum(int* amountDices, int* sum)
{
	int i, dicesCounter = 0;

	/*��� 1 � 5 ��������� ��������� ������� �������� �����*/
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

			/*��������� ����� � ��� ������, ���� ���� ������� ����*/
			/*��� ��� ����� �� ��������� 2,3,4,6*/
			else if (*(amountDices + i) != 0)
			{
				*sum = -1;
				break;
			}
		}
		dicesCounter = dicesCounter + *(amountDices + i);
	}

	/*��������� ����� � ��� ������, ���� �� ������� �� ���� �����*/
	if (dicesCounter == 0)
	{
		*sum = -1;
	}
}


/*������� �������� � �������� ��������� ��������� �� �����, ��������� �� ���-�� ��������� ������, ��������� �� �������� ��������� ������ � ���������� ����� ������*/
int playersRoundResult(int* sum, int* selectedDicesCounter, int* playerResult)
{
	int playerDecision;

	/*����� �������� ����������, ������� �� �������� ����� � �������� ��������� ������� �����*/
	if (*sum == -1)
	{
		printf("\nThe current result is 0\n\n");
		*sum = 0;
		*selectedDicesCounter = 0;
		return 0;
	}

	/*����� �������� 6 ������*/
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

	/*����� �������� ������ 6 ������*/
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


/*������� �������� � �������� ��������� ��������� �� �����, ��������� �� ���-�� ��������� ������, ��������� �� �������� ��������� ���� � ���������� ����� ����*/
int botRoundResult(int* sum, int* selectedDicesCounter, int* botResult)
{
	/*��� �������� ����������, ������� �� �������� ����� � �������� ��������� ������� �����*/
	if (*sum == -1)
	{
		printf("\nBot's current result is 0\n\n");
		*sum = 0;
		*selectedDicesCounter = 0;
		return 0;
	}

	/*��� �������� 6 ������*/
	else if (*selectedDicesCounter == 6)
	{
		printf("\nBot's current result is %d\n\n", *sum);
		*selectedDicesCounter = 0;
		return 1;
	}

	/*��� �������� ������ 6 ������*/
	else
	{
		printf("\nBot's current result is %d\n\n", *sum);

		/*������� ��������� ����*/
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