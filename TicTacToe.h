#include <stdbool.h>

/* Structures */
struct MoveData 
{
    unsigned int offSetX;
    unsigned int offSetY;
    char symbol;
};

typedef struct {
    char* Player1;
    char* Player2;
} PlayerNames;
/* End */


/* Enums */
enum ERR_RES { NONE, ERR };

enum RowMatch { NoPossibleMatch, XMatch, CircleMatch, NilMatch };
/* End */


/* Functions */
enum ERR_RES private_setBoardPiece(struct MoveData m);

void PrintTable();
void private_DebugTable();

char* _promptGets(const char* msg, char* input);
bool prompt(const char* msg);


PlayerNames* pickPlayers();
enum RowMatch hasThreeInRow();
void newSetPrompt(char* playerNames, bool isPlayerOne, bool* gameEnd);
/* End */