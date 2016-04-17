//
// Created by Sumner B on 4/7/2016.
//

#include "Simple.h"

#include <sstream>
#include <string>
#include <iomanip>


using namespace Gaming;

const char Simple::SIMPLE_ID = 'S';

Simple::Simple(const Game &g, const Position &p, double energy) : Agent (g, p, energy)  {}

Simple::~Simple() {}

void Simple::print(std::ostream &out) const {
    std::string str;
    str = std::to_string(__id);
    std::stringstream ss;

    ss << Simple::SIMPLE_ID;
    ss << str;

    std::getline(ss, str);

    for (int i = 0; i < str.length(); ++i) {
        out << str[i];
    }
}

ActionType Simple::takeTurn(const Surroundings &s) const {
    std::vector <int> tiles;

    for (int i = 0; i < 9; ++i) {
        if (s.array[i] == PieceType::ADVANTAGE || s.array[i] == PieceType::FOOD) tiles.push_back(i);
    }

    if (tiles.size() > 0) {
        std::cout << "Position Resource Options: " << tiles.size() << std::endl;

        PositionRandomizer rand;
        Position pos = rand (tiles);

        return (ActionType)(pos.y + (pos.x * 3));
    }

    for (int i = 0; i < 9; ++i) { if (s.array[i] == PieceType::EMPTY) tiles.push_back(i); }

    if (tiles.size() > 0) {
        std::cout << "Position Empty Options: " << tiles.size() << std::endl;

        PositionRandomizer rand();
        Position pos = rand(tiles);

        std::cout << "Position Chosen: " << pos.y + (pos.x * 3) << std::endl;
        return (ActionType)(pos.y + (pos.x * 3));
    }

    return ActionType::STAY;
}

