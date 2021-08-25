#include <iostream>
#include <stdio.h>
#include <stack>
#include "gomoku.h"
using namespace std;

int main() {
    gomoku game1;
//    game1.configureBoard();
//    cout<<game1.boardState();
    if(game1.computerPiece=='B'){
        game1.board[7][7]='B';
        game1.iMax=9;
        game1.iMin=5;
        game1.jMax=9;
        game1.jMin=5;
        game1.printBoard();
        cout<<"Computer makes a move on hh with B"<<endl;
        while(!game1.gameover){
            game1.playerMove();
            game1.determineWin();
            if(game1.gameover)
                break;
            game1.computerMove();
            game1.determineWin();
        }
        cout<<"Player "<<game1.winningPiece<<" has won the game!"<<endl;
    }
    
    if(game1.computerPiece=='W'){
        while(!game1.gameover){
            game1.printBoard();
            game1.playerMove();
            game1.determineWin();
            if(game1.gameover)
                break;
            game1.computerMove();
            game1.determineWin();
        }
        cout<<"Player "<<game1.winningPiece<<" has won the game!"<<endl;
    }
    return 0;
}