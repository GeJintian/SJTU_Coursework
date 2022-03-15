//
// Created by 69009 on 2019/7/13.
//
#include "square.h"

Square::Square(Vaxis v, Haxis h):v(v), h(h), p(nullptr) {}

Vaxis Square::getV() const {
    return v;
}

void Square::setV(Vaxis v) {
    this->v = v;
}

Haxis Square::getH() const {
    return h;
}

void Square::setH(Haxis h) {
    this->h = h;
}

const Piece& Square::getPiece() const {
    if(this->isEmpty()){
        throw SquareException(*this, "empty");
    }
    return *p;
}

void Square::setPiece(const Piece *p) {
    this->p = p;
}

bool Square::isEmpty() const {
    return (p == nullptr);
}

bool Square::isOnFirstDiagonal() const {
    return ((int) v == (int) h);
}

bool Square::isOnSecondDiagonal() const {
    return ((3 - (int) v) == (int) h);
}

std::string Square::toString() const {
    char vname[] = {'A', 'B', 'C', 'D'};
    std::ostringstream oStream;
    oStream<<vname[v]<<(int) h + 1;
    return oStream.str();
}