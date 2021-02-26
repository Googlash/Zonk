int* allocateMemory(int unusedDice)
{
	int* dices = (int*)malloc(unusedDice * sizeof(int));

	return dices;
}