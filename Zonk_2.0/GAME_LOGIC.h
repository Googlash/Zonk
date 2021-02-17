void calculateTheSum(int*, int*);

/*Получает в качестве параметра указатель на массив выбранных костей и указатель на переменную для хранения суммы*/
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
