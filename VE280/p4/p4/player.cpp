//
// Created by 69009 on 2019/7/13.
//

#include <iostream>
#include "player.h"

class HumanPlayer: public Player{
public:
    HumanPlayer(Board *board, Pool *pool): Player(board, pool){}
    Piece & judge_piece(const std::string &s){
        if(s[0] == HCODE[0] || s[0] == HCODE[1]){
            if(s[1] == CCODE[0] || s[1] == CCODE[1]){
                if(s[2] == SCODE[0] || s[2] == SCODE[1]){
                    if(s[3] == TCODE[0] || s[3] == TCODE[1]){
                        return pool->getUnusedPiece(s);
                    }
                }
            }
        }
        throw InvalidInputException(s);
    }
    Piece& selectPiece() override{
        std::string input_piece;
        while(true){
            std::cout<<"Enter a piece:";
            std::cin>>input_piece;
            try{
                return judge_piece(input_piece);
            }
            catch(UsedPieceException &n) {
                std::string s = n.what();
                std::cout<<s<<std::endl;
            }
            catch(InvalidInputException &n){
                std::string s = n.what();
                std::cout<<s<<std::endl;
            }
        }
    }

    Square & judge_square(const std::string &s){
        if(s[0] == 'A' || s[0] == 'B' || s[0] == 'C' || s[0] == 'D'){
            if(s[1] == '1' || s[1] == '2' || s[1] == '3' || s[1] == '4') {
                return board->getEmptySquare(s);}
        }
        throw InvalidInputException(s);
    }
    Square& selectSquare(const Piece &p) override{
        std::string input_square;
        while(true) {
            std::cout << "Enter a position:";
            std::cin >> input_square;
            try{
                return judge_square(input_square);
            }
            catch(SquareException &n) {
                std::string s = n.what();
                std::cout<<s<<std::endl;
            }
            catch(InvalidInputException &n){
                std::string s = n.what();
                std::cout<<s<<std::endl;
            }
        }
    }
};





class MyopicPlayer: public Player{
public:
    MyopicPlayer(Board * board, Pool * pool): Player(board, pool){}

    Piece & selectPiece() override {
        Piece *unused_pieces[NP];
        Piece *good_pieces[NP];
        //Find unused pieces
        int count_unused = 0;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j<2; j++){
                for(int m = 0; m < 2; m++){
                    for(int n = 0; n<2; n++){
                        try{
                            unused_pieces[count_unused] = &pool->getUnusedPiece((Height)i, (Color) j, (Shape) m, (Top) n);
                            count_unused ++;
                        }
                        catch(...){}
                    }
                }
            }
        }
        //distinguish good or bad
        int count_good = 0;
        for(int i = 0; i < count_unused; i++){
            bool if_good = true;
            for(int v = 0; v < N; v++){
                for(int h = 0; h < N; h++){
                    try{if_good = (if_good && !board->isWinning(*unused_pieces[i],board->getEmptySquare((Vaxis)v, (Haxis)h)));}
                    catch(...){}
                }
            }
            if(if_good){
                good_pieces[count_good] = unused_pieces[i];
                count_good ++;
            }
        }
        //Decide what to return
        if(count_good == 0){
            return *unused_pieces[rand()%count_unused];
        }
        else return *good_pieces[rand()%count_good];
    }

    Square & selectSquare(const Piece &p) override{
        Square *empty_square[NP];
        Square *win_square[NP];
        //Find empty squares
        int count_empty = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                try{
                    empty_square[count_empty] = &board->getEmptySquare((Vaxis)i, (Haxis)j);
                    count_empty ++;
                }
                catch(...){}
            }
        }
        //Find win squares
        int count_win = 0;
        for(int i = 0; i < count_empty; i++){
            if(board->isWinning(p,*empty_square[i])){
                win_square[count_win] = empty_square[i];
                count_win ++;
            }
        }
        //Decide what to return
        if(count_win == 0) return *empty_square[rand()%count_empty];
        else return *win_square[0];
    }
};

extern Player *getHumanPlayer(Board *b, Pool *p){
    static HumanPlayer p1(b,p);
    return &p1;
}

extern Player *getMyopicPlayer(Board *b, Pool *p, unsigned int s){
    srand(s);
    static MyopicPlayer p2(b,p);
    return &p2;
}
