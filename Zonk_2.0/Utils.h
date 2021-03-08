int* getIntArray(int unusedDice)
{
	int* dices = (int*)malloc(unusedDice * sizeof(int));

	return dices;
}

void freeMemory(int* diceArray)
{
	free(diceArray);
}

/*������� ��������� ������ ��������� ������ 0-��. 
�������� � �������� ��������� ��������� �� ������ ��������� ������*/
void fillWithZeros(int* array, int arraySize)
{
	int i;

	for (i = 0; i < arraySize; i++)
	{
		*(array + i) = 0;
	}
}