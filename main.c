#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "TicTacToe.h"

#define CIRCLE_MARK 'O'
#define X_MARK 'X'

/* #define DEBUG_MODE */

/* Author: Tosin Daudu */
/* Description: Simple Tic Tac Toe Game (That happens to be terribly written) */
    /* Edit: Less Terrible now */

char BOARD[3][3] = {
    {  '?' ,  '?' ,  '?'  }, /* ROW 1 */
    {  '?' ,  '?' ,  '?'  }, /* ROW 2 */
    {  '?' ,  '?' ,  '?'  }  /* ROW 3 */
};

/* Checks bounds for move data given against board */
enum ERR_RES private_setBoardPiece(struct MoveData m)
{
    if ((m.offSetX > 3) || (m.offSetY < 1) || (m.offSetY > 3) || (m.offSetX < 1))
    {
        printf(":- Offset Coordinate out of bounds { %c } -:\n", m.symbol);
        printf(":- Error: [Invalid Index / Board Piece doesn't exist] ( %d, %d )-:\n", m.offSetX, m.offSetY);
        return ERR;
    } else {
        if(BOARD[m.offSetY - 1][m.offSetX - 1] != '?') {
            printf(":- Error: [Illegal Set / Board Piece Already Contains Set] ( %d, %d )-:\n", m.offSetX, m.offSetY);
            return ERR;
        } else if(BOARD[m.offSetY - 1][m.offSetX -1] == '!') {
            printf("\nERROR {\n\tPANIC DEBUG CODE ['!'] Debug Character Found\n}\n");
            exit(EXIT_FAILURE);
            return ERR;
        } else {
            BOARD[m.offSetY - 1][m.offSetX - 1] = m.symbol;
            printf("> New Entry Set Successfully ( %c, %d, %d )\n", m.symbol, m.offSetX, m.offSetY);
        }
    }
    return NONE;
}


/* Debugging and Output format */
struct MoveData debugMatch[3] = {
    { 0, 0, '!' },
    { 0, 0, '!' },
    { 0, 0, '!' }
};

void PrintTable()
{
    printf(
        "\n       |     |     \n    %c  |  %c  |  %c  \n  _____|_____|_____\n       |     |     \n    %c  |  %c  |  %c  \n  _____|_____|_____\n       |     |     \n    %c  |  %c  |  %c  \n       |     |     \n",
        BOARD[0][0], BOARD[0][1], BOARD[0][2],
        BOARD[1][0], BOARD[1][1], BOARD[1][2],
        BOARD[2][0], BOARD[2][1], BOARD[2][2]
    );
}

void private_DebugTable()
{
    printf("\n"); PrintTable(); printf("\n");

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            printf(
                ":- Debug Board Piece Print => [ %c | %d | %d ] -:\n",
                BOARD[c][r], c, r
            );
        }
    }
    
    printf("[Printing debug matches]!\n");
    printf("[Match 1]: (C: %d R: %d) -> %c\t", debugMatch[0].offSetX, debugMatch[0].offSetY, debugMatch[0].symbol);
    printf("[Match 2]: (C: %d R: %d) -> %c\t", debugMatch[1].offSetX, debugMatch[1].offSetY, debugMatch[1].symbol);
    printf("[Match 3]: (C: %d R: %d) -> %c\t", debugMatch[2].offSetX, debugMatch[2].offSetY, debugMatch[2].symbol);
}
/* End */


/* Input Handling */
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
        case 'Y': case 'y':
            printf("\n");
            return true;

        case 'N': case 'n':
            printf("\n");
            return false;

        default:
            printf("\n:- Error Invalid Please Try Again -:\n");
            break;
        }
    }
    return false;
}
/* End */


PlayerNames* pickPlayers() /* Assigning Player names / symbols */
{
    PlayerNames* players = (PlayerNames*) malloc(sizeof(PlayerNames));
    players->Player1 = (char*) malloc(255 * sizeof(char));
    players->Player2 = (char*) malloc(255 * sizeof(char));

    printf("> Player 1 [X] , Please Enter Your Name: ");
    fgets(players->Player1, 255, stdin);
    players->Player1[strcspn(players->Player1, "\n")] = 0;
    printf("\n> Player 2 [O], Please Enter Your Name: ");
    fgets(players->Player2, 255, stdin);
    players->Player2[strcspn(players->Player2, "\n")] = 0;
    printf("\n");

    if(!prompt("> Are Both Parties Content With Their Names?: ")) {
        printf("\n");
        pickPlayers();
    }

    return players;
}

enum RowMatch hasThreeInRow() /* made better*/
{
    for (unsigned int X = 0; X < 3; X++) /* Iterate through all rows / columns */
    {
        if((BOARD[X][0] == BOARD[X][1]) && (BOARD[X][1] == BOARD[X][2]) && (BOARD[X][1] != '?')) /* Check for horizontal match */
        { 
            /* If match store in tmp to debug */
            struct MoveData tmp[3] = { 
                { X, 0, BOARD[1][0] }, { X, 1, BOARD[1][1] }, { X, 2, BOARD[1][2] } 
            };     
            debugMatch[0] = tmp [0]; debugMatch[1] = tmp[1]; debugMatch[2] = tmp[2];
            
            if (BOARD[X][1] == X_MARK) { return XMatch; } else { /* return match type */
                return CircleMatch;
            }
        }

        else if((BOARD[0][X] == BOARD[1][X]) && (BOARD[1][X] == BOARD[2][X]) && (BOARD[1][X] != '?')) /* Check for vertical match */
        {
            /* If match store in tmp to debug */
            struct MoveData tmp[3] = { 
                { 0, X, BOARD[0][X] }, { 1, X, BOARD[1][X] }, { 2, X, BOARD[2][X] } 
            };
            debugMatch[0] = tmp [0]; debugMatch[1] = tmp[1]; debugMatch[2] = tmp[2];
            
            if (BOARD[1][X] == X_MARK) { return XMatch; } else { /* return match type */
                return CircleMatch;
            }
        }
        
    }

    /* Across */
    bool acrossLeft = (BOARD[0][0] == BOARD[1][1]) && (BOARD[1][1] == BOARD[2][2]), acrossRight = (BOARD[0][2] == BOARD[1][1]) && (BOARD[1][1] == BOARD[2][0]); 
    
    if ((acrossRight || acrossLeft) && (BOARD[1][1] != '?')) /* Check for across match */
    {
        if (BOARD[1][1] == X_MARK) { return XMatch; } else { /* return match type */
            return CircleMatch;
        }
    } else { /* Otherwise check for possible remaining moves */
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if(BOARD[r][c] == '?') { return NilMatch; }
            }
        }
        return NoPossibleMatch; /* No moves left, game over */
    }
}

void newSetPrompt(char* playerNamePlayerNames, bool isPlayerOne, bool* gameEnd) 
{
    PrintTable();
    struct MoveData data = { 0, 0, '?' };

    printf("> Player [ %s ] Please Enter Row for Entry: ", playerNamePlayerNames);
    scanf("%u", &data.offSetY);

    printf("\n> Player [ %s ] Please Enter Column for Entry: ", playerNamePlayerNames);
    scanf("%u", &data.offSetX); printf("\n");

    if (isPlayerOne) {
        data.symbol = X_MARK;
    } else {
        data.symbol = CIRCLE_MARK;
    }

    if (private_setBoardPiece(data) == ERR){
        newSetPrompt(playerNamePlayerNames, isPlayerOne, gameEnd);
    }
    
    switch (hasThreeInRow())
    {
    case XMatch:
        printf("> Game Over Player 1 ( %s ) Wins !\n", playerNamePlayerNames);
        (*gameEnd) = true;
        break;

    case CircleMatch:
        printf("> Game Over Player 2 ( %s ) Wins !\n", playerNamePlayerNames);
        (*gameEnd) = true;
        break;

    case NoPossibleMatch:
        printf("> Game Over, Its a Draw !\n");
        (*gameEnd) = true;
        break;

    default: /* Nothing */
        break;
    }
}

/*
     (currently ignoring what happens when you enter a invalid result for a coordinate)
     (todo add clean board function) - for playing again
     +
     (fix memory allocations)
     (optimization and clean - make shorter)
     (add debug macro for build)
     (figure out memory)
     figure out character / operator input for row/column error

     !! add debug section back in 
     double check memory situation with valgrind
     make sure string/input manip is secure
*/

int main()
{
    #ifdef DEBUG_MODE
        printf(":- Test Program %s \n", "{ ... } -:");
    #endif
    printf("\n> Game Start \n");

    bool gameFinished = false;
    bool currentIsPlayer1 = true;
    PlayerNames* players = pickPlayers();

    while (!gameFinished) 
    {
        if (currentIsPlayer1) {
            newSetPrompt(players->Player1, currentIsPlayer1, &gameFinished);
        } else {
            newSetPrompt(players->Player2, currentIsPlayer1, &gameFinished);
        }    
        currentIsPlayer1 = !currentIsPlayer1;
    }
    
    /* Clean Up Section */
    #ifdef DEBUG_MODE
        printf(":- Dumping Board -: \n");
        private_DebugTable();    
    #else
        printf("\n"); PrintTable(); printf("\n");
    #endif

        free(players->Player1);
        free(players->Player2);
        free(players);

        if (prompt("Play again?")) 
        {
            char tmp1[3][3] = {
                {  '?' ,  '?' ,  '?'  }, {  '?' ,  '?' ,  '?'  }, {  '?' ,  '?' ,  '?'  } 
            };
            memcpy(BOARD, tmp1, sizeof(BOARD));

            struct MoveData tmp2[3] = {
                { 0 ,  0 ,  '!'  }, {  0 ,  0 ,  '!'  }, {  0 ,  0 ,  '!'  }
            };
            memcpy(debugMatch, tmp2, sizeof(debugMatch));

            main();
        }
    /* End Section*/

    return EXIT_SUCCESS;
}
