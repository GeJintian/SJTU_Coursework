//
// Created by 69009 on 2019/7/13.
//
#include "pool.h"

Pool::Pool() {
    int count = 0;
    //i for Height, j for Color, m for Shape, n for Top
    for(int i = 0;i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int m = 0; m < 2; m++){
                for(int n = 0; n < 2; n++){
                    Piece p((Height) i, (Color) j, (Shape) m, (Top) n);
                    p.setUsed(false);
                    pieces[count] = p;
                    count ++;
                }
            }
        }
    }
}

Piece& Pool::getUnusedPiece(int index) {
    Piece &result = pieces[index];
    if(result.isUsed()){
        throw UsedPieceException(result);
    }
    return result;
}

Piece& Pool::getUnusedPiece(Height h, Color c, Shape s, Top t) {
    Piece p(h,c,s,t);
    int j = 0;
    for(int i = 0; i < NP; i++){
        if(pieces[i].toString() == p.toString()){
            j = i;
        }
    }
    return getUnusedPiece(j);
}

Piece& Pool::getUnusedPiece(const std::string &in) {
    int j = 0;
    for(int i = 0; i < NP; i++){
        if(pieces[i].toString() == in){
            j=i;
        }
    }
    return getUnusedPiece(j);
}

std::string Pool::toString() const {
    std::ostringstream oStream1; //For the fist line
    std::ostringstream oStream2; //For the second line
    std::ostringstream oStream3; //For the third line
    oStream1<<"Available:"<<"\n";
    for(int i = 0; i < NP-1; i++){
        if(!pieces[i].isUsed()){
            oStream2<<pieces[i].toString()[0]<<pieces[i].toString()[1]<<" ";
            oStream3<<pieces[i].toString()[2]<<pieces[i].toString()[3]<<" ";
        }
    }
    if(!pieces[15].isUsed()){
        oStream2<<pieces[15].toString()[0]<<pieces[15].toString()[1];
        oStream3<<pieces[15].toString()[2]<<pieces[15].toString()[3];
    }
    oStream2<<"\n";
    oStream3<<"\n";
    std::string result;
    result = oStream1.str() + oStream2.str() + oStream3.str()+"\n";
    return result;
}