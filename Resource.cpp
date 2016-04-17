//
// Created by Sumner B on 4/7/2016.
//

#include <iostream>
#include "Resource.h"

using namespace Gaming;

const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p), __capacity(capacity)  {}

Resource::~Resource() {}

double Resource::consume() {

    double value;
    value = __capacity;

    __capacity = 0;

    return value;
}

void Resource::age() {

    __capacity -= RESOURCE_SPOIL_FACTOR;

}

ActionType Resource::takeTurn(const Surroundings &s) const { return ActionType::STAY; }

Piece &Resource::operator*(Piece &other) { return *this; }

Piece &Resource::interact(Agent *agent) { return *this; }

Piece &Resource::interact(Resource *resource) { return *this; }
