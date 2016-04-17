//
// Created by Sumner B on 4/7/2016.
//

#include "Strategic.h"

#include <sstream>
#include <iomanip>

using namespace Gaming;

const char Strategic::STRATEGIC_ID = 'T';

Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent (g, p, energy) { __strategy = s; }

Strategic::~Strategic() {}

void Strategic::print(std::ostream &out) const {

    std::string str;
    str = std::to_string (__id);
    std::stringstream ss;

    ss << Strategic::STRATEGIC_ID;
    ss << str;

    std::getline(ss, str);
    for (int inc = 0; inc < str.length(); inc++) { out << str[inc]; }
}

ActionType Strategic::takeTurn(const Surroundings &Sur) const { return (*__strategy)(Sur); }
