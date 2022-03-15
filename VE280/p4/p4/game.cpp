#include <iostream>
#include "board.h"
#include "exceptions.h"
#include "player.h"
#include "piece.h"
#include "pool.h"
#include "quarto.h"
#include "square.h"


using namespace std;

bool driver(Board &board, Pool &pool, Player *p1, Player *p2, int &who_choose);

int main(int argc, char *argv[]) {
    string s1 = argv[1];
    string s2 = argv[2];
    string s3;
    unsigned int seed;
    if(argc == 4){
        s3 = argv[3];
        istringstream iStream;
        iStream.str(s3);
        iStream>>seed;
    }
    //Begin initialize
    Board board;
    Pool pool;
    Player * p1;
    Player * p2;
    if(s1 == "h"){
        p1 = getHumanPlayer(&board,&pool);
    }
    else{
        p1 = getMyopicPlayer(&board,&pool,seed);
    }
    if(s2 == "h"){
        p2 = getHumanPlayer(&board,&pool);
    }
    else{
        p2 = getMyopicPlayer(&board,&pool,seed);
    }

    bool win;
    int who_choose = 0;//if 0, player1 choose a piece, if 1, player2 choose a piece.
    for(int i = 0; i < 16; i++){
        cout<<board.toString()<<endl;
        cout<<pool.toString();
        if(who_choose == 0) {//player1 to choose, then player 2 to select a square
            win = driver(board, pool, p1, p2, who_choose);
            if(win){
                cout<<board.toString()<<endl;
                if(i < 15)cout<<pool.toString();
                cout<<"Player 2 has won!"<<endl;
                return 0;
            }
        }
        else {
            win = driver(board, pool, p2, p1, who_choose);
            if(win){
                cout<<board.toString()<<endl;
                if(i < 15)cout<<pool.toString();
                cout<<"Player 1 has won!"<<endl;
                return 0;
            }
        }
    }
    cout<<board.toString()<<endl;
    cout<<"It is a draw."<<endl;
    return 0;
}

bool driver(Board &board, Pool &pool, Player *p1, Player *p2, int &who_choose){
    //p1 choose a piece, p2 choose a square
    if(who_choose == 0) cout<<"Player 1's turn to select a piece:"<<endl;
    else cout<<"Player 2's turn to select a piece:"<<endl;
    Piece & piece = p1->selectPiece();
    cout<<piece.toString()<<" selected."<<endl<<endl;
    if(who_choose == 0) cout<<"Player 2's turn to select a square:"<<endl;
    else cout<<"Player 1's turn to select a square:"<<endl;
    Square & square = p2->selectSquare(piece);
    cout<<square.toString()<<" selected."<<endl<<endl;
    board.place(piece,square);
    who_choose = 1 - who_choose;
    return board.isWinning(piece,square);
}