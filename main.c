#include "stdio.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CIRCLE_MARK 'O'
#define X_MARK 'X'

// Author: Tosin Daudu
// Description: Simple Tic Tac Toe Game

struct MoveData
{
    unsigned int offsetx;
    unsigned int offsety;
    char symbol;
};

struct MoveData BOARD[3][3] = {
    { { 1, 1, '?' }, { 1, 2, '?' }, { 1, 3, '?' } },
    { { 2, 1, '?' }, { 2, 2, '?' }, { 2, 3, '?' } },
    { { 3, 1, '?' }, { 3, 2, '?' }, { 3, 3, '?' } }
}; 

enum ERR_RES { NONE, ERR };

enum ERR_RES _setBoardPiece(struct MoveData m)
{
    if ((m.offsetx > 3) || (m.offsety < 1) || (m.offsety > 3) || (m.offsetx < 1))
    {
        printf(":- Offset Coordinate out of bounds { %c } -:\n", m.symbol);
        printf(":- Error: [Invalid Index / Board Piece doesn't exist] ( %d, %d )-:\n", m.offsetx, m.offsety);
        return ERR;
    } else {
        if(BOARD[m.offsety - 1][m.offsetx - 1].symbol != '?') {
            printf(":- Error: [Illegal Set / Board Piece Already Contains Set] ( %d, %d )-:\n", m.offsetx, m.offsety);
            return ERR;
        } else {
            BOARD[m.offsety - 1][m.offsetx - 1].symbol = m.symbol;
            printf("> New Entry Set Successfully ( %c, %d, %d )\n", m.symbol, m.offsetx, m.offsety);
        }
    }
    return NONE;
}

void debugTable()
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            printf(
                ":- Debug Board Piece Print => [ %c | %d | %d ] -:\n",
                BOARD[c][r].symbol, 
                BOARD[c][r].offsetx,
                BOARD[c][r].offsety
            );
        }
    }
}

void _printTable()
{
    printf(
        "\n       |     |     \n    %c  |  %c  |  %c  \n  _____|_____|_____\n       |     |     \n    %c  |  %c  |  %c  \n  _____|_____|_____\n       |     |     \n    %c  |  %c  |  %c  \n       |     |     \n",
        BOARD[0][0].symbol,
        BOARD[0][1].symbol,
        BOARD[0][2].symbol,
        BOARD[1][0].symbol,
        BOARD[1][1].symbol,
        BOARD[1][2].symbol,
        BOARD[2][0].symbol,
        BOARD[2][1].symbol,
        BOARD[2][2].symbol
    );
    
}

char* _promptGets(const char* msg, char* input)
{
    printf("\n> Prompt [ %s ] => [Yes or No ( Y / N ) ]  ", msg);
    return fgets(input, 255, stdin);
}

bool prompt(const char* msg)
{
    char input[255];
    while (_promptGets(msg, input) != NULL)
    {
        switch (input[0])
        {
        case 'Y':
            printf("\n");
            return true;
        
        case 'N':
            printf("\n");
            return false;

        default:
            printf("\n:- Error Invalid Please Try Again -:\n");
            break;
        }
    } 
    return false;
}

struct PlayerData
{
    char* Player1;
    char* Player2;
} players;

void pickPlayers()
{
    players.Player1 = (char*) malloc(255 * sizeof(char));
    players.Player2 = (char*) malloc(255 * sizeof(char));

    printf("> Player 1 [X] , Please Enter Your Name: ");
    fgets(players.Player1, 255, stdin); 
    players.Player1[strcspn(players.Player1, "\n")] = 0;
    printf("\n> Player 2 [O], Please Enter Your Name: ");
    fgets(players.Player2, 255, stdin);
    players.Player2[strcspn(players.Player2, "\n")] = 0;
    printf("\n");
    
    if(prompt("> Are Both Parties Content With Their Names?: ")) {
        printf("\n");
        return;
    } else {
        printf("\n");
        pickPlayers();
    }
}

enum RowMatch
{
    NoPossibleMatch,
    NilMatch,
    XMatch,
    CircleMatch
};

enum RowMatch hasThreeInRow() /* There is probably a better way to do this like a  for loop or something but idc */
{
     /* Horizontal */
    if((BOARD[1][0].symbol == BOARD[1][1].symbol) && (BOARD[1][1].symbol == BOARD[1][2].symbol) && (BOARD[1][1].symbol != '?')) {
        if (BOARD[1][1].symbol == X_MARK) {
            return XMatch;
        } else {
            return CircleMatch;
        }
    } else if((BOARD[0][0].symbol == BOARD[0][1].symbol) && (BOARD[0][1].symbol == BOARD[0][2].symbol) && (BOARD[0][1].symbol != '?')) {
        if (BOARD[0][1].symbol == X_MARK) {
            return XMatch;
        } else {
            return CircleMatch;
        }
    } else if((BOARD[2][0].symbol == BOARD[2][1].symbol) && (BOARD[2][1].symbol == BOARD[2][2].symbol) && ((BOARD[2][1].symbol != '?'))) {
        if (BOARD[2][1].symbol == X_MARK) {
            return XMatch;
        } else {
            return CircleMatch;
        }
    }

    /* Vertical */
    else if((BOARD[0][0].symbol == BOARD[1][0].symbol) && (BOARD[1][0].symbol == BOARD[2][0].symbol) && (BOARD[1][0].symbol != '?')) {
        if (BOARD[1][0].symbol == X_MARK) {
            return XMatch;
        } else {
            return CircleMatch;
        }
    } else if((BOARD[0][1].symbol == BOARD[1][1].symbol) && (BOARD[1][1].symbol == BOARD[2][1].symbol) && (BOARD[1][1].symbol != '?')) {
        if (BOARD[1][1].symbol == X_MARK) {
            return XMatch;
        } else {
            return CircleMatch;
        }
    } else if((BOARD[0][2].symbol == BOARD[1][2].symbol) && (BOARD[1][2].symbol == BOARD[2][2].symbol) && ((BOARD[1][2].symbol != '?'))) {
        if (BOARD[1][2].symbol == X_MARK) {
            return XMatch;
        } else {
            return CircleMatch;
        }
    }
    
    else if ( /* Across */
        ((BOARD[0][0].symbol == BOARD[1][1].symbol) && (BOARD[1][1].symbol == BOARD[2][2].symbol)) ||
        ((BOARD[0][2].symbol == BOARD[1][1].symbol) && (BOARD[1][1].symbol == BOARD[2][0].symbol) && (BOARD[1][1].symbol != '?'))
    ) {
        if (BOARD[1][1].symbol == X_MARK) {
            return XMatch;
        } else {
            return CircleMatch;
        }
    } else {
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                if(BOARD[r][c].symbol == '?'){
                    return NilMatch;
                }
            }
        }
        return NoPossibleMatch;
    }
}

void cleanup(void);

void newSetPrompt(char* playerData, bool isPlayerOne) 
{
    _printTable();
    struct MoveData data = { 0, 0, '?' };

    printf("> Player [ %s ] Please Enter Row for Entry: ", playerData);
    scanf("%u", &data.offsety);

    printf("\n> Player [ %s ] Please Enter Column for Entry: ", playerData);
    scanf("%u", &data.offsetx);
    printf("\n");

    if (isPlayerOne) {
        data.symbol = X_MARK;
    } else {
        data.symbol = CIRCLE_MARK;
    }

    if (_setBoardPiece(data) == ERR){
        newSetPrompt(playerData, isPlayerOne);
    }
    
    switch (hasThreeInRow())
    {
    case XMatch:
        printf("> Game Over Player 1 ( %s ) Wins !\n", playerData);
        cleanup(); exit(EXIT_SUCCESS);
        break;

    case CircleMatch:
        printf("> Game Over Player 2 ( %s ) Wins !\n", playerData);
        cleanup(); exit(EXIT_SUCCESS);
        break;

    case NoPossibleMatch:
        printf("> Game Over, Its a Draw !\n");
        cleanup(); exit(EXIT_SUCCESS);
        break;

    default: /* Nothing */
        break;
    }
}

/*  
     (currently ignoring what happens when you enter a invalid result for a coordinate)
*/

int main();

void cleanup(void)
{
    int* youngthug;
    youngthug = malloc(0);
    printf(":- Dumping Board -: \n");
    debugTable();
    free(players.Player1);
    free(players.Player2);
    free(youngthug);
    if (prompt("Play again?")) {
        main();
    }
}

int main()
{
    printf(":- Test Program %s \n\n", "{ ... } -:");

    printf("> Game Start \n");
    bool gameFinished = false;
    bool currentIsPlayer1 = true;
    pickPlayers();

    while (!gameFinished) {
        if (currentIsPlayer1) {
            newSetPrompt(players.Player1, currentIsPlayer1);
        } else {
            newSetPrompt(players.Player2, currentIsPlayer1);
        }
        
        currentIsPlayer1 = !currentIsPlayer1;
    }
    
    cleanup();
    return 0;
}