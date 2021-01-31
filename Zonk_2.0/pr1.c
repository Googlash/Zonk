#include <stdio.h>/*ass*/
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>
#include "CONST.h"

int creatingRandomBones(int);									/*������ ������ �� 6 ���������, ��������� ��� ���������� ���������� �� 1 �� 6 � ����������*/
int selectionOfBones(int*, int*);								/*������������ ����� ������ � ���������� ������ � ���� �������*/
void calculatingTheSum(int*, int*);								/*������������ ����� ������*/
int botMove(int*, int*);										/*�������� ������ ���������� �� ��������� � ���������� ������ � ���*/

int main()
{
	int playerResult = 0, botResult = 0, sum = 0, i = 1, playerDecision = 1, botDecision = 1,numberOfSelectedBones = 0;

	printf("\t\t\t\t\t\tNew game !\n\n");

	while (playerResult < WINNING_RESULT && botResult < WINNING_RESULT)													/*������� ������*/
	{
		printf("\t\t\t\t\t\tRound %d\n\n", i);

		printf("\t\t\t\t\t\tPlayer move\n\n");
		while (playerDecision != 0)
		{
			calculatingTheSum(selectionOfBones(creatingRandomBones(6 - numberOfSelectedBones), &numberOfSelectedBones), &sum);

			if (sum == -1)																								/*����� �������� ����������, ������� �� �������� ����� � �������� ��������� ������� �����*/
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
				printf("\nThe current result is %d\nEnter 0 to save the result, or enter 1 to continue\n", sum);		/*����� �������� 6 ������*/
				scanf_s("%d", &playerDecision);
				numberOfSelectedBones = 0;
			}
			else																										/*����� �������� ������ 6 ������*/
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

			if (sum == -1)																								/*��� �������� ����������, ������� �� �������� ����� � �������� ��������� ������� �����*/
			{
				printf("\nBot's current result is 0\n\n");
				printf("\nBot's final result is %d\n\n", botResult);
				sum = 0;
				numberOfSelectedBones = 0;
				botDecision = 0;
				break;
			}
			else if (numberOfSelectedBones == 6)																		/*��� �������� 6 ������*/
			{
				printf("\nBot's current result is %d\n\n", sum);														
				numberOfSelectedBones = 0;
			}
			else																										/*��� �������� ������ 6 ������*/
			{
				printf("\nBot's current result is %d\n\n", sum);

				if (numberOfSelectedBones >= 4 || (sum > 300 && numberOfSelectedBones >= 3))							/*������� ��������� ����*/
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


int creatingRandomBones(int allBones)								/*������ n ������*/
{
	int i, *randomBones = (int*)malloc(allBones * sizeof(int));		/*��������� ������ ��� n ���������� ���� int */

	srand(time(NULL));

	for (i = 0; i <= allBones - 1; i++)								/*��������� n ��������� ���������� ������� �� 1 �� 6*/
	{
		*(randomBones + i) = rand() % 5 + 1;
		printf("|%d|  ", *(randomBones + i));
	}

	return randomBones;
}


int botMove(int* randomBones, int* selItems)
{
	int  i;
	static int	amountBones[6];

	for (i = 0; i <= 5; i++)										/*��������� �������*/
	{
		amountBones[i] = 0;
	}

	for (i = 0; i <= 5; ++i)										/*������ � ������ ���������� ������ ������� ��������*/
	{
		switch (*(randomBones + i))
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

	for (i = 0; i <= 5; i++)										/*�������� �� ���������� ���� ��������*/
	{
		if ((i != 0 && i != 4) && amountBones[i] <= 2)
		{
			amountBones[i] = 0;
		}
		*selItems = *selItems + amountBones[i];						/*������� ���������� ��������� ������*/
	}

	if (*selItems == 0)												/*���� ����������� ���������� ��� ������ ��������, �� � ������ ������������ ���� 2*/
	{
		amountBones[1] = 1;
	}

	free(randomBones);

	return amountBones;
}


int selectionOfBones(int* randomBones, int* selItems)
{
	int i, d = -1, boneNumbers[6] = { 0 };
	static int amountBones[6];

	printf("\n\nEnter bone numbers (enter 0 to finish)\n");
	for (i = 0; i <= 5 && d != 0; ++i)								/*����� �������� ����� � ����� �� ������*/
	{
		scanf_s("%d", &d);
		boneNumbers[i] = d;
		if (d != 0)													/*������� �� ������ ���������� ������ ���������� �����*/
		{
			(*selItems)++;											/*������� ���������� ��������� ������*/
		}
	}

	for (i = 0; i <= 5; i++)										/*��������� �������*/
	{
		amountBones[i] = 0;
	}

	for (i = 0; boneNumbers[i] != 0 && i <= 5; ++i)					/*������ � ������ ���������� ������ ������� ��������*/
	{
		switch (*(randomBones + boneNumbers[i] - 1))
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

	free(randomBones);

	return amountBones;
}


void calculatingTheSum(int* amountBones, int* sum)
{
	int i;

	for (i = 0; i <= 5; i++)										/*������� ����������*/
	{
		if (i == 0)													/*��� 1 � 5 ��������� ��������� ������� �������� �����*/
		{
			switch (*amountBones)
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
			switch (*(amountBones + 4))
			{
			case 1:
				*sum = *sum + FIFTY;
				break;
			case 2:
				*sum = *sum + 2 * FIFTY;
				break;
			case 3:
				*sum = *sum + FIVE_HUNDRED;
				break;
			case 4:
				*sum = *sum + 2 * FIVE_HUNDRED;
				break;
			case 5:
				*sum = *sum + 4 * FIVE_HUNDRED;
				break;
			case 6:
				*sum = *sum + 8 * FIVE_HUNDRED;
				break;
			}
		}
		else
		{
			if (*(amountBones + i) >= 3)
			{
				switch (*(amountBones + i))
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
		}
	}

	for (i = 0; i <= 5; i++)											/*��������� ����� � ��� ������, ���� ���� ������� ���� ��� ��� ����� �� ��������� 2,3,4,6*/
	{
		if (i == 1 || i == 2 || i == 3 || i == 5)
		{
			if (*(amountBones + i) == 1 || *(amountBones + i) == 2)
			{
				*sum = -1;
			}
		}
	}
}