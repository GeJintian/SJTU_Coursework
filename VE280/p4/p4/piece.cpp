//
// Created by 69009 on 2019/7/12.
//
#include "piece.h"

Piece::Piece(Height h, Color c, Shape s, Top t): h(h),c(c),s(s),t(t){}

bool Piece::compareHeight(const Piece &p) const {
    return (p.h == h);
}

bool Piece::compareColor(const Piece &p) const {
    return (p.c == c);
}

bool Piece::compareShape(const Piece &p) const {
    return (p.s == s);
}

bool Piece::compareTop(const Piece &p) const {
    return (p.t == t);
}

bool Piece::isUsed() const {
    return used;
}

void Piece::setUsed(bool u) {
    used = u;
}

std::string Piece::toString() const {
    std::string feature;
    std::ostringstream oStream;
    oStream<<ALLCODE[0][h]<<ALLCODE[1][c]<<ALLCODE[2][s]<<ALLCODE[3][t];
    feature = oStream.str();
    return feature;
}