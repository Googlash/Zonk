#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>
#include <stdbool.h>
#include "GAME_LOGIC.h"
#include "Utils.h"


int main()
{
    int usedDice = 0, sum = 0, round = 1;
    int* dices = NULL, sortedDice[6];
    int playerResult = 0, playerDecision = 1, selectedDice[6];
    int botResult = 0, botDecision = 1;

    srand(time(NULL));

    printf("\t\t\t\t\t\tNew game !\n\n");

    while (!isWon(playerResult) && !isWon(botResult))
    {
        printf("\t\t\t\t\t\tRound %d\n\n", round);

        printf("\t\t\t\t\t\tPlayer move\n\n");
        while (playerDecision != 0)
        {
            dices = getIntArray(6 - usedDice);
            fillRandomDices(dices, 6 - usedDice, generateRandomDice);
            printDices(dices, 6 - usedDice);
            clearSelectedDice(selectedDice);
            playerMove(&usedDice, selectedDice);
            sortByQuantity(selectedDice, sortedDice, dices);
            calculateTheSum(sortedDice, &sum);
            playerDecision = playersRoundResult(&sum, &usedDice, &playerResult);
            freeMemory(dices);
        }
        printf("\nThe final result is %d\n\n", playerResult);
        playerDecision = 1;

        /*Преждевременное окончание цикла, если игрок набирает необходимую сумму*/
        if (isWon(playerResult))
        {
            break;
        }

        printf("\t\t\t\t\t\tBot's move\n\n");
        while (botDecision != 0)
        {
            dices = getIntArray(6 - usedDice);
            fillRandomDices(dices, 6 - usedDice, generateRandomDice);
            printDices(dices, 6 - usedDice);
            clearSelectedDice(selectedDice);
            selectAllDice(selectedDice, 6 - usedDice);
            sortByQuantity(selectedDice, sortedDice, dices);
            botMove(&usedDice, sortedDice);
            calculateTheSum(sortedDice, &sum);

            Sleep(3000);

            botDecision = botRoundResult(&sum, &usedDice, &botResult);
            freeMemory(dices);
        }
        printf("\nBot's final result is %d\n\n", botResult);
        botDecision = 1;

        round++;
    }

    return 0;
}
