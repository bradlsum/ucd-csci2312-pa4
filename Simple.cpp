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

    ActionType ac = STAY;

    std::vector<int> positions;
    for(int i = 0; i < 9; i++) {
        if(s.array[i] == ADVANTAGE || s.array[i] == FOOD) {
            positions.push_back(i);
        }
    }

    if(positions.size() == 0) {

        for(int i = 0; i < 9; i++) { if(s.array[i] == EMPTY) { positions.push_back(i); }}

        if(positions.size() == 0) { positions.push_back(100000); }

    }

    int push = rand() % positions.size();

    if(positions.size() == 1) { push = 0; }

    if(push >= 9) { push = 8; }

    switch (positions[push]) {
        case 0:
            ac = NW;
            break;
        case 1:
            ac = N;
            break;
        case 2:
            ac = NE;
            break;
        case 3:
            ac = W;
            break;
        case 4:
            ac = STAY;
            break;
        case 5:
            ac = E;
            break;
        case 6:
            ac = SW;
            break;
        case 7:
            ac = S;
            break;
        case 8:
            ac = SE;
            break;
        default:
            ac = STAY;
            break;
    }
    return ac;
}

