#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <windows.h>
#include <stdbool.h>
#include "GAME_LOGIC.h"

int main()
{
    int selectedDiceCounter = 0, sum = 0, round = 1;
    int* dices, amountDices[6];
    int playerResult = 0, playerDecision = 1;
    int botResult = 0, botDecision = 1;

    srand(time(NULL));

    printf("\t\t\t\t\t\tNew game !\n\n");

    while (!checkWin(playerResult) && !checkWin(botResult))
    {
        printf("\t\t\t\t\t\tRound %d\n\n", round);

        printf("\t\t\t\t\t\tPlayer move\n\n");
        while (playerDecision != 0)
        {
            dices = createRandomDices(6 - selectedDiceCounter);
            printDices(dices, 6 - selectedDiceCounter);
            playerMove(dices, &selectedDiceCounter, amountDices);
            calculateTheSum(amountDices, &sum);
            playerDecision = playersRoundResult(&sum, &selectedDiceCounter, &playerResult);
        }
        printf("\nThe final result is %d\n\n", playerResult);
        playerDecision = 1;

        /*Преждевременное окончание цикла, если игрок набирает необходимую сумму*/
        if (checkWin(playerResult))
        {
            break;
        }

        printf("\t\t\t\t\t\tBot's move\n\n");
        while (botDecision != 0)
        {
            dices = createRandomDices(6 - selectedDiceCounter);
            printDices(dices, 6 - selectedDiceCounter);
            botMove(dices, &selectedDiceCounter, amountDices);
            calculateTheSum(amountDices, &sum);

            Sleep(3000);

            botDecision = botRoundResult(&sum, &selectedDiceCounter, &botResult);
        }
        printf("\nBot's final result is %d\n\n", botResult);
        botDecision = 1;

        round++;
    }

    return 0;
}
