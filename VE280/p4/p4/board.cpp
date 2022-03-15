//
// Created by 69009 on 2019/7/13.
//
#include <iostream>
#include "board.h"

Board::Board() {
    for(int i = 0; i < N; i++){// Vertical
        for(int j = 0; j < N; j++){//Horizontal
            Square sq((Vaxis) i, (Haxis) j);
            grid[i][j] = sq;
        }
    }
}

Square& Board::getSquare(Vaxis v, Haxis h) {
    return grid[v][h];
}

Square& Board::getEmptySquare(Vaxis v, Haxis h) {
    Square &sq = getSquare(v,h);
    if(!sq.isEmpty()){
        throw SquareException(sq,"not empty");
    }
    return sq;
}

Square& Board::getEmptySquare(const std::string &s) {
    int v = 0;
    int h = 0;
    for(int i = 0; i < N; i++){// Vertical
        for(int j = 0; j < N; j++){//Horizontal
            if(grid[i][j].toString() == s) {
                v = i;
                h = j;
            }
        }
    }
    return getEmptySquare((Vaxis)v,(Haxis)h);
}

void Board::place(Piece &p, Square &sq) {
    p.setUsed(true);
    sq.setPiece(&p);
}

void judge_helper(const Piece p1, const Piece p2, bool *feature){
    for(int i = 0; i < 4; i++){
        if(feature[i]){
            if(p1.toString()[i] != p2.toString()[i]) feature[i] = false;
        }
    }
}
bool judge(const Piece *collection[]){//Return true if all pieces in the collection has one same attributes
    bool feature[4] = {true, true, true, true};//[0] for Height, [1] for Color, [2] for Shape, [3] for Top
                                                 //True = same, False otherwise.

    Piece A = *collection[0];
    Piece B = *collection[1];
    Piece C = *collection[2];
    Piece D = *collection[3];
    judge_helper(A, B, feature);
    judge_helper(B, C, feature);
    judge_helper(C, D, feature);
    for(int i = 0; i < 4; i++){
        if(feature[i]) return true;
    }
    return false;
}

bool Board::isWinning(const Piece &p, const Square &sq) {
    bool if_place = p.isUsed();
    Vaxis v = sq.getV();
    Haxis h = sq.getH();
    if(!if_place) grid[v][h].setPiece(&p);
    const Piece *p_collection[4];

    //Exam vertical
    try{
        for(int i = 0; i < 4; i++){
            p_collection[i] = &grid[i][h].getPiece();
        }
        if(judge(p_collection)) {
            if(!if_place)grid[v][h].setPiece(nullptr);
            return true;
        }
    }
    catch(...){}

    //Exam horizontal
    try{
    for(int i = 0; i < 4; i++){
        p_collection[i] = &grid[v][i].getPiece();
    }
    if(judge(p_collection)) {
        if(!if_place)grid[v][h].setPiece(nullptr);
        return true;
    }
    }
    catch(...){}

    //Exam First diagonal
    try {
        if (sq.isOnFirstDiagonal()) {
            for (int i = 0; i < 4; i++) {
                p_collection[i] = &grid[i][i].getPiece();
            }
                if (judge(p_collection)) {
                    if (!if_place)grid[v][h].setPiece(nullptr);
                    return true;
                }
            }
        }
    catch(...){}

    //Exam Second diagonal
    try{
    if(sq.isOnSecondDiagonal()){
        for(int i = 0; i < 4; i++){
            p_collection[i] = &grid[i][3 - i].getPiece();
        }
        if(judge(p_collection)) {
            if(!if_place)grid[v][h].setPiece(nullptr);
            return true;
        }
    }
    }
    catch(...){}
    if(!if_place)grid[v][h].setPiece(nullptr);
    return false;
}

std::string Board::toString() const {
    char letter[] = {'a','b','c','d'};
    std::ostringstream oStream;
    std::ostringstream oStream1;
    for(int i = 0; i < 20; i++){
        if(i == 4) oStream1<<"1";
        else if(i == 9) oStream1<<"2";
        else if(i == 14) oStream1<<"3";
        else if(i == 19) oStream1<<"4";
        else oStream1<<" ";
    }
    oStream1<<"\n";
    oStream<<oStream1.str();

    std::ostringstream oStream2;
    oStream2<<"  ";
    for(int i = 0; i < 21; i++){
        if(i == 0 || i == 5 || i == 10 || i == 15 || i == 20){
            oStream2<<"+";
        }
        else oStream2<<"-";
    }

    for(int v = 0; v < 4; v++){
        oStream<<oStream2.str()<<"\n";
        std::ostringstream oStream3;
        std::ostringstream oStream4;
        oStream3<<letter[v]<<" |";
        oStream4<<"  |";
        for(int h = 0; h < 4; h++){
            if(!grid[v][h].isEmpty()){
                oStream3<<" "<<grid[v][h].getPiece().toString()[0]<<grid[v][h].getPiece().toString()[1]<<" ";
                oStream4<<" "<<grid[v][h].getPiece().toString()[2]<<grid[v][h].getPiece().toString()[3]<<" ";
            }
            else{
                oStream3<<"    ";
                oStream4<<"    ";
            }
            oStream3<<"|";
            oStream4<<"|";
        }
        oStream3<<"\n";
        oStream4<<"\n";
        oStream<<oStream3.str()<<oStream4.str();
    }
    oStream<<oStream2.str()<<"\n";
    return oStream.str();
}