//
// Created by Sumner Bradley on 4/12/2016.
//

#include "AggressiveAgentStrategy.h"
#include "Game.h"

using namespace Gaming;

const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) { __agentEnergy = agentEnergy; }

AggressiveAgentStrategy::~AggressiveAgentStrategy() {}

ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {

    // Agent
    for (int i = 0; i < 9; ++i) {
        if  ((s.array[i] == PieceType::SIMPLE || s.array[i] == PieceType::STRATEGIC) &&
             __agentEnergy > DEFAULT_AGGRESSION_THRESHOLD ) return (ActionType)i; }

    // Advantage
    for (int i = 0; i < 9; ++i) { if (s.array[i] == PieceType::ADVANTAGE) return (ActionType)i; }

    // Food
    for (int i = 0; i < 9; ++i) { if (s.array[i] == PieceType::FOOD) return (ActionType)i; }

    // Empty
    for (int i = 0; i < 9; ++i) { if (s.array[i] == PieceType::EMPTY) return (ActionType)i; }

    return (ActionType::STAY);

}

