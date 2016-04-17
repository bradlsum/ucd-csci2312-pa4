//
// Created by Sumner B on 4/12/2016.
//

#include "DefaultAgentStrategy.h"

using namespace Gaming;

DefaultAgentStrategy::DefaultAgentStrategy() {}

DefaultAgentStrategy::~DefaultAgentStrategy() {}

ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {

    // Advantage
    for (int i = 0; i < 9; ++i) { if (s.array[i] == PieceType::ADVANTAGE) return (ActionType)i; }

    // Food
    for (int i = 0; i < 9; ++i) { if (s.array[i] == PieceType::FOOD) return (ActionType)i; }

    // Agent
    for (int i = 0; i < 9; ++i) { if (s.array[i] == PieceType::SIMPLE) return (ActionType)i; }

    // Empty
    for (int i = 0; i < 9; ++i) { if (s.array[i] == PieceType::EMPTY) return (ActionType)i; }

    return ActionType::STAY;
}

