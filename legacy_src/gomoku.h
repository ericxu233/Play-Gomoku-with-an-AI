#pragma once


class gomoku{
private:
    int boardScore;
public:
    int iMax;
    int iMin;
    int jMax;
    int jMin;
    char board[15][15];
//    int poping[15][15];
    char playerPiece;
    char computerPiece;
    char winningPiece;
    bool gameover;
public:
    int moveScore(int a, int b, char piece);
    void determineWin(); //see wether one side won or not
    void printBoard();
    void computerMove(); //AI move for computer
    void playerMove(); //Let Player to input move
    void configureBoard(); //optional board configuration, optional execution in code
    gomoku();
    void range(int a, int b);
//    void stacking(int a, int b, int i_min, int i_max, int j_min, int j_max, int* a1, int* a2, int* a3, int* a4, record* r);
//    void stackHelp(int a, int b, record* r);
//    void pushStack(record* r);
//private:
    bool checkBounds(int a, int b); //checking if one is out of bounds
    bool fiveORnot(char piece, int a, int b);
    bool selectSPOT(int a, int b); //selection of perfect spot
    int miniMax(int depth, char maximizing);
    int boardState();
    int singlePieceEval(char piece, char opponent, int a, int b, int dirX, int dirY);
    bool winORnot(int a, int b);
    int winningRecursion(int a, int b, char piece, int counter, int i, int j);
};
