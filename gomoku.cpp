#include "gomoku.h"
#include <iostream>

using namespace std;


gomoku::gomoku(){
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            board[i][j]=' ';
        }
    }
    gameover=false;
    boardScore=0;
    iMax=7; iMin=7; jMax=7; jMin=7;
    cout<<"Welcome to the gomoku game!\nPlase select your piece you want to play(B/W): ";
    cin>>playerPiece;
    cout<<"\n";
    if(playerPiece=='B')
        computerPiece='W';
    else
        computerPiece='B';
}


//----------------------------------------------------

//----------------------------------------------------
bool gomoku::checkBounds(int a, int b){
    if(a>=0&&a<=14&&b>=0&&b<=14)
        return true;
    else
        return false;
}
//----------------------------------------------------

//----------------------------------------------------
void gomoku::printBoard(){
    cout<<endl;
    cout<<"  ";
    for(char i='a'; i<='o'; i++){
        cout<<i<<"  ";
    }
    cout<<"\n";
    for(char j='a'; j<='o'; j++){
        cout<<j<<" ";
        for(int k=0; k<=14; k++){
            cout<<board[j-97][k];
            if(k!=14)
                cout<<"--";
        }
        cout<<endl;
        cout<<"  ";
        for(int l=0; l<=14&&j!='o'; l++){
            cout<<"|  ";
        }
        cout<<endl;
    }
}
//----------------------------------------------------

//----------------------------------------------------
void gomoku::configureBoard(){
    cout<<"Please enter board configuration for example Bab(end with 0): "<<endl;
    string input;
    bool key=true;
    while(key){
        getline(cin, input);
        if(input[0]!='0')
            board[input[1]-'a'][input[2]-'a']=input[0];
        else
            key=false;
    }
}
//----------------------------------------------------

//----------------------------------------------------
void gomoku::playerMove(){
    cout<<"Please enter your move:"<<endl;
    char input[3];
    scanf("%s", input);
    board[input[0]-'a'][input[1]-'a']=playerPiece;
    range(input[0]-'a', input[1]-'a');
    //moveScore(input[0]-'a', input[1]-'a', playerPiece);
    printBoard();
    cout<<"Player makes a move on "<<input<<" with "<<playerPiece<<endl;
}
//----------------------------------------------------

//----------------------------------------------------
void gomoku::determineWin(){
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            if(board[i][j]=='B'&&fiveORnot('B', i, j)){
                winningPiece='B';
                gameover=true;
                return;
            }
            if(board[i][j]=='W'&&fiveORnot('W', i, j)){
                winningPiece='W';
                gameover=true;
                return;
            }
        }
    }
}

bool gomoku::fiveORnot(char piece, int a, int b){
    for(int i=-1; i<=1; i++){
        for(int j=-1; j<=1; j++){
            if(i==0&&j==0)
                continue;
            int t1; int t2; int numberIN;//numberin is how many pieces of it are in a row
            t1=a; t2=b; numberIN=0;
            while(board[t1][t2]==piece&&checkBounds(t1, t2)&&numberIN<5){
                t1=t1+i;
                t2=t2+j;
                numberIN++;
            }
            if(numberIN==5)
                return true;
        }
    }
    return false;
}
//----------------------------------------------------

//----------------------------------------------------
bool gomoku::selectSPOT(int a, int b){
    int score=0;//check a blank spot and see if it is relevent spot to do
    if(board[a][b]!=' ')
        return false;
    if(checkBounds(a+1, b+1)&&(board[a+1][b+1]=='W'||board[a+1][b+1]=='B'))//right down
        return true;
    if(checkBounds(a, b+1)&&(board[a][b+1]=='W'||board[a][b+1]=='B'))//right
        return true;
    if(checkBounds(a-1, b+1)&&(board[a-1][b+1]=='W'||board[a-1][b+1]=='B'))//right up
        return true;
    if(checkBounds(a+1, b-1)&&(board[a+1][b-1]=='W'||board[a+1][b-1]=='B'))//left down
        return true;
    if(checkBounds(a, b-1)&&(board[a][b-1]=='W'||board[a][b-1]=='B'))//left
        return true;
    if(checkBounds(a-1, b-1)&&(board[a-1][b-1]=='W'||board[a-1][b-1]=='B'))//left up
        return true;
    if(checkBounds(a+1, b)&&(board[a+1][b]=='W'||board[a+1][b]=='B'))//down
        return true;
    if(checkBounds(a-1, b)&&(board[a-1][b]=='W'||board[a-1][b]=='B'))//up
        return true;
    if(checkBounds(a-2, b)&&(board[a-2][b]=='W'||board[a-2][b]=='B'))
        score++;
    if(checkBounds(a, b-2)&&(board[a][b-2]=='W'||board[a][b-2]=='B'))
        score++;
    if(checkBounds(a-2, b-2)&&(board[a-2][b-2]=='W'||board[a-2][b-2]=='B'))
        score++;
    if(checkBounds(a+2, b+2)&&(board[a+2][b+2]=='W'||board[a+2][b+2]=='B'))
        score++;
    if(checkBounds(a-2, b+2)&&(board[a-2][b+2]=='W'||board[a-2][b+2]=='B'))
        score++;
    if(checkBounds(a+2, b-2)&&(board[a+2][b-2]=='W'||board[a+2][b-2]=='B'))
        score++;
    if(checkBounds(a+2, b)&&(board[a+2][b]=='W'||board[a+2][b]=='B'))
        score++;
    if(checkBounds(a, b+2)&&(board[a][b+2]=='W'||board[a][b+2]=='B'))
        score++;
    if(score>=2)
        return true;
    return false;
}
//----------------------------------------------------

//----------------------------------------------------
int gomoku::boardState(){//remember to set gameover to false when ending the function; do not modify board!!!!!
    int score=0;
    for(int i=0; i<=14; i++){
        for(int j=0; j<=14; j++){
            if(board[i][j]==computerPiece){
                score+=2;
                score+=singlePieceEval(computerPiece, playerPiece, i, j, 1, 1);
                score+=singlePieceEval(computerPiece, playerPiece, i, j, 1, 0);
                score+=singlePieceEval(computerPiece, playerPiece, i, j, 0, 1);
                score+=singlePieceEval(computerPiece, playerPiece, i, j, 1, -1);
            }else if(board[i][j]==playerPiece){
                score-=2;
                score-=singlePieceEval(playerPiece, computerPiece, i, j, 1, 1);
                score-=singlePieceEval(playerPiece, computerPiece, i, j, 1, 0);
                score-=singlePieceEval(playerPiece, computerPiece, i, j, 0, 1);
                score-=singlePieceEval(playerPiece, computerPiece, i, j, 1, -1);
            }
        }
    }
    return score;
}


int gomoku::singlePieceEval(char piece, char opponent, int a, int b, int dirX, int dirY){
    int score=0;
    int skip=0;
    bool endkey=true;
    for(int i=dirX, j=dirY; endkey&&skip<2; i+=dirX, j+=dirY){
        if(checkBounds(a+i, b+j)&&board[a+i][b+j]==opponent){
            score--;
            break;
        }else if(!checkBounds(a+i, b+j)){
            score--;
            break;
        }
        if(board[a+i][b+j]==piece){
            score++;
        }
        if(board[a+i][b+j]==' '){
                if(checkBounds(a+i+dirX, b+j+dirY)&&board[a+i+dirX][b+j+dirY]==piece){
                    score++;
                    skip++;
                    i+=dirX;
                    j+=dirY;
                }
                if(checkBounds(a+i+dirX, b+j+dirY)&&board[a+i+dirX][b+j+dirY]==' ')
                    break;
        }
    }
    for(int i=-dirX, j=-dirY; endkey&&skip<2; i-=dirX, j-=dirY){
        if(checkBounds(a+i, b+j)&&board[a+i][b+j]==opponent){
            score--;
            break;
        }else if(!checkBounds(a+i, b+j)){
            score--;
            break;
        }
        if(board[a+i][b+j]==piece){
            score++;
        }
        if(board[a+i][b+j]==' '){
            if(checkBounds(a+i-dirX, b+j-dirY)&&board[a+i-dirX][b+j-dirY]==piece){
                    score++;
                    skip++;
                    i-=dirX;
                    j-=dirY;
                }
                if(checkBounds(a+i-dirX, b+j-dirY)&&board[a+i-dirX][b+j-dirY]==' ')
                    break;
        }
    }
    return score;
}
//----------------------------------------------------

//----------------------------------------------------
void gomoku::computerMove(){
    int score=-9999999;
    int a=0, b=0;
    for(int i=iMin; i<=iMax; i++){
        for(int j=jMin; j<=jMax; j++){
            if(selectSPOT(i, j)){
                board[i][j]=computerPiece;
                int t1=iMax, t2=iMin, t3=jMax, t4=jMin;
                range(i, j);
                gameover=winORnot(i, j);
                int temp=miniMax(3, playerPiece);
                if(temp>score){
                    score=temp;
                    a=i;
                    b=j;
                }
                board[i][j]=' ';
                iMax=t1, iMin=t2, jMax=t3, jMin=t4;
            }
        }
    }
    board[a][b]=computerPiece;
    range(a, b);
    printBoard();
    char a11=a+'a', b11=b+'a';
    cout<<"Computer makes a move on "<<a11<<b11<<" with"<<computerPiece<<endl;
}

int gomoku::miniMax(int depth, char maximizing){
    if(gameover){
        if(winningPiece==playerPiece){
            gameover=false;
            return -999999;
        }
        else if(winningPiece==computerPiece){
            gameover=false;
            return 999999;
        }
    }
    if(depth==0){
        return boardScore;
    }
    
    if(maximizing==computerPiece){
        int maxEval=-999999;
        for(int i=iMin; i<=iMax; i++){
            for(int j=jMin; j<=jMax; j++){
                if(selectSPOT(i, j)){
                    board[i][j]=computerPiece;
                    int t1=iMax, t2=iMin, t3=jMax, t4=jMin;
                    range(i, j);
                    int tScore;
                    if(depth>=2)
                        tScore=moveScore(i, j, computerPiece);
                    gameover=winORnot(i, j);
                    int eval=miniMax(depth-1, playerPiece);
                    if(maxEval<eval)
                        maxEval=eval;
                    board[i][j]=' ';
                    if(depth>=2)
                        boardScore=tScore;
                    iMax=t1, iMin=t2, jMax=t3, jMin=t4;
                }
            }
        }
        return maxEval;
    }
    
    if(maximizing==playerPiece){
        int minEval=999999;
        for(int i=iMin; i<=iMax; i++){
            for(int j=jMin; j<=jMax; j++){
                if(selectSPOT(i, j)){
                    board[i][j]=playerPiece;
                    int t1=iMax, t2=iMin, t3=jMax, t4=jMin;
                    range(i, j);
                    int tScore;
                    if(depth>=2)
                        tScore=moveScore(i, j, playerPiece);
                    gameover=winORnot(i, j);
                    int eval=miniMax(depth-1, computerPiece);
                    if(minEval>eval)
                        minEval=eval;
                    board[i][j]=' ';
                    if(depth>=2)
                        boardScore=tScore;
                    iMax=t1, iMin=t2, jMax=t3, jMin=t4;
                }
            }
        }
        return minEval;
    }
    return 0;
}
//----------------------------------------------------

//----------------------------------------------------
void gomoku::range(int a, int b){
    if(!checkBounds(a+2, b+2)){
        iMax=14;
        jMax=14;
    }
    if(!checkBounds(a-2, b-2)){
        iMax=0;
        jMax=0;
    }
    iMax=max(a+2, iMax);
    iMin=min(a-2, iMin);
    jMax=max(b+2, jMax);
    jMin=min(b-2, jMin);
}

int gomoku::moveScore(int a, int b, char piece){
    int result=boardScore;
    int score_v=1, score_h=1, score_13=1, score_24=1;
    if(piece==computerPiece){
        score_v+=singlePieceEval(computerPiece, playerPiece, a, b, 1, 1);
        score_h+=singlePieceEval(computerPiece, playerPiece, a, b, 1, 0);
        score_13+=singlePieceEval(computerPiece, playerPiece, a, b, 0, 1);
        score_24+=singlePieceEval(computerPiece, playerPiece, a, b, 1, -1);
        if(score_v==2)
            boardScore+=10;
        if(score_v==3)
            boardScore+=100;
        if(score_v==4)
            boardScore+=1000;
        if(score_h==2)
            boardScore+=10;
        if(score_h==3)
            boardScore+=100;
        if(score_h==4)
            boardScore+=1000;
        if(score_13==2)
            boardScore+=10;
        if(score_13==3)
            boardScore+=100;
        if(score_13==4)
            boardScore+=1000;
        if(score_24==2)
            boardScore+=10;
        if(score_24==3)
            boardScore+=100;
        if(score_24==4)
            boardScore+=1000;
    }
    if(piece==playerPiece){
        score_v+=singlePieceEval(playerPiece, computerPiece, a, b, 1, 1);
        score_h+=singlePieceEval(playerPiece, computerPiece, a, b, 1, 0);
        score_13+=singlePieceEval(playerPiece, computerPiece, a, b, 0, 1);
        score_24+=singlePieceEval(playerPiece, computerPiece, a, b, 1, -1);
        if(score_v==2)
            boardScore-=100;
        if(score_v==3)
            boardScore-=1000;
        if(score_v==4)
            boardScore-=10000;
        if(score_h==2)
            boardScore-=100;
        if(score_h==3)
            boardScore-=1000;
        if(score_h==4)
            boardScore-=10000;
        if(score_13==2)
            boardScore-=100;
        if(score_13==3)
            boardScore-=1000;
        if(score_13==4)
            boardScore-=10000;
        if(score_24==2)
            boardScore-=100;
        if(score_24==3)
            boardScore-=1000;
        if(score_24==4)
            boardScore-=10000;
    }
    return result;
}

bool gomoku::winORnot(int a, int b){
    if(winningRecursion(a, b, board[a][b], 0, 1, 1)+winningRecursion(a, b, board[a][b], 0, -1, -1)-1==5){
        winningPiece=board[a][b];
        return true;
    }
    if(winningRecursion(a, b, board[a][b], 0, -1, 1)+winningRecursion(a, b, board[a][b], 0, 1, -1)-1==5){
        winningPiece=board[a][b];
        return true;
    }
    if(winningRecursion(a, b, board[a][b], 0, 0, 1)+winningRecursion(a, b, board[a][b], 0, 0, -1)-1==5){
        winningPiece=board[a][b];
        return true;
    }
    if(winningRecursion(a, b, board[a][b], 0, 1, 0)+winningRecursion(a, b, board[a][b], 0, -1, 0)-1==5){
        winningPiece=board[a][b];
        return true;
    }
    return false;
}

int gomoku::winningRecursion(int a, int b, char piece, int counter, int i, int j){
    if(checkBounds(a, b)&&board[a][b]==piece)
        return winningRecursion(a+i, b+j, piece, counter+1, i, j);
    return counter;
}
