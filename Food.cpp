//
// Created by Sumner Bradley on 4/12/2016.
//

#include "Food.h"

#include <sstream>
#include <iomanip>

using namespace Gaming;

const char Food::FOOD_ID = 'F';

Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {}

Food::~Food() {}

void Food::print(std::ostream &out) const {
    std::string str;
    str = std::to_string(__id);
    std::stringstream ss;

    ss << Food::FOOD_ID;
    ss << str;

    std::getline(ss, str);

    for (int i = 0; i < str.length(); ++i) { out << str[i]; }
}
