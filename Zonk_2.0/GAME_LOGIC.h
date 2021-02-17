void calculateTheSum(int*, int*);

/*�������� � �������� ��������� ��������� �� ������ ��������� ������ � ��������� �� ���������� ��� �������� �����*/
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
