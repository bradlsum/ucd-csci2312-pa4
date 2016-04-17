//
// Created by Sumner Bradley on 4/12/2016.
//

#include "Advantage.h"

#include <sstream>
#include <iomanip>

using namespace Gaming;

const char Advantage::ADVANTAGE_ID = 'D';
const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {}

Advantage::~Advantage() {}

void Advantage::print(std::ostream & out) const {
    std::string str;
    str = std::to_string(__id);

    std::stringstream ss;
    ss << Advantage::ADVANTAGE_ID;
    ss << str;

    std::getline(ss, str);

    for (int i = 0; i < str.length(); ++i) { out << str[i]; }
}

double Advantage::getCapacity() const { return __capacity * ADVANTAGE_MULT_FACTOR; }

double Advantage::consume() {
    double value = getCapacity();
    __capacity = 0;

    return value;
}
