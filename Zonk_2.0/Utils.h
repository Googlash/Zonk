int* getIntArray(int unusedDice)
{
	int* dices = (int*)malloc(unusedDice * sizeof(int));

	return dices;
}

void freeMemory(int* diceArray)
{
	free(diceArray);
}