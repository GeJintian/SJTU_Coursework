//
// Created by 69009 on 2019/7/13.
//
#include <iostream>
#include <sstream>
#include "board.h"
#include "exceptions.h"
#include "player.h"
#include "piece.h"
#include "pool.h"
#include "quarto.h"
#include "square.h"

using namespace std;


int main(){
    Board board;
    Pool pool;
    Player *p1 = getMyopicPlayer(&board,&pool, 280);
    Piece & piece1 = p1->selectPiece();
    Square & square1 = p1->selectSquare(piece1);
    board.place(piece1,square1);
    //cout<<board.toString();
    Piece & piece2 = p1->selectPiece();
    //cout<<board.toString();
    Square & square2 = p1->selectSquare(piece2);
    //cout<<board.toString();
    board.place(piece2,square2);
    cout<<board.toString();






    return 0;
}
