int* getIntArray(int unusedDice)
{
	int* dices = (int*)malloc(unusedDice * sizeof(int));

	return dices;
}

void freeMemory(int* diceArray)
{
	free(diceArray);
}

/*‘ункци€ заполн€ет массив выбранных костей 0-ми. 
ѕолучает в качестве параметра указатель на массив выбранных костей*/
void fillWithZeros(int* array, int arraySize)
{
	int i;

	for (i = 0; i < arraySize; i++)
	{
		*(array + i) = 0;
	}
}