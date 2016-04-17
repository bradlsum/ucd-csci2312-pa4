//
// Created by Sumner B on 4/5/2016.
//

#include "Piece.h"

using namespace Gaming;

unsigned int Piece::__idGen = 1000;

Piece::Piece(const Game &g, const Position &p): __game(g), __position(p){

    __id = __idGen++;

    __turned = false;

    __finished = false;

}

Piece::~Piece() {}

std::ostream &operator<<(std::ostream &os, const Piece &piece) {

    piece.print(os);

    return os;

}



