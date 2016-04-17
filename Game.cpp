//
// Created by Sumner B on 4/7/2016.
//

#include <set>
#include "Game.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include "Strategic.h"

namespace  Gaming {


const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

const unsigned Game::MIN_WIDTH = 3;
const unsigned Game::MIN_HEIGHT = 3;

const double Game::STARTING_AGENT_ENERGY = 20;
const double Game::STARTING_RESOURCE_CAPACITY = 10;

PositionRandomizer Game::__posRandomizer = PositionRandomizer();

void Game::populate(){

    std::default_random_engine gen;
    std::uniform_int_distribution<int> d(0, __width * __height);

    __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
    __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

    unsigned int numStrategic = __numInitAgents / 2;

    unsigned int numSimple = __numInitAgents - numStrategic;

    unsigned int numAdvantages = __numInitResources / 4;

    unsigned int numFoods = __numInitResources - numAdvantages;

    while (numStrategic > 0) {
        int i = d(gen);
        if (i != (__width * __height) && __grid[i] == nullptr) {
            Position pos(i / __width, i % __width);
            __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
            numStrategic--;
        }
    }

    while (numSimple > 0) {
        int i = d(gen);
        if (i != (__width * __height) && __grid[i] == nullptr) {
            Position pos(i / __width, i % __width);
            __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
            numSimple--;
        }
    }

    while (numFoods > 0) {
        int i = d(gen);
        if (i != (__width * __height) && __grid[i] == nullptr) {
            Position pos(i / __width, i % __width);
            __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
            numFoods--;
        }
    }

    while (numAdvantages > 0) {
        int i = d(gen);
        if (i != (__width * __height) && __grid[i] == nullptr) {
            Position pos(i / __width, i % __width);
            __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
            numAdvantages--;
        }
    }

}

Game::Game():__numInitAgents(0),__numInitResources(0),
             __width(MIN_WIDTH), __height(MIN_HEIGHT), __grid(__width * __height, nullptr), __round(0),
             __status(NOT_STARTED), __verbose(false)
{}

Game::Game(unsigned int width, unsigned int height, bool manual):
        __numInitAgents(0), __numInitResources(0), __grid(__width * __height, nullptr),
        __round(0),__status(NOT_STARTED), __verbose(false)
{
    if(width < MIN_WIDTH || height < MIN_HEIGHT)
        throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
    __width = width;
    __height = height;
    __grid.resize(__width * __height, nullptr);
    if(!(manual))   populate();
}

Game::~Game(){

    for (auto it = __grid.begin(); it != __grid.end(); ++it) { if (*it != nullptr) { delete *it; } }

}

// getters
    unsigned int Game::getNumPieces() const {

        unsigned int pieces = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) { if (*it != nullptr) ++pieces; }

        return pieces;

    }

    unsigned int Game::getNumAgents() const {

        unsigned int agents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) { Agent *simple = dynamic_cast<Agent*>(*it); if (simple) ++agents; }

        return agents;

    }

    unsigned int Game::getNumSimple() const {

        unsigned int agents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) { Simple *simple = dynamic_cast<Simple*>(*it); if (simple) ++agents; }

        return agents;

    }

    unsigned int Game::getNumStrategic() const {

        unsigned int agents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) { Strategic *simple = dynamic_cast<Strategic*>(*it); if (simple) ++agents; }

        return agents;

    }

    unsigned int Game::getNumResources() const {

        unsigned int agents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) { Resource *simple = dynamic_cast<Resource*>(*it); if (simple) ++agents; }

        return agents;

    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const {

        if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[y + (x * __width)] == nullptr) throw PositionEmptyEx(x, y);

        return __grid[y + (x * __width)];

    }

// grid population methods
void Game::addSimple(const Position &position){

    int i = position.y + (position.x * __width);

    if (position.y >= __width || position.x >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);

    if (__grid[i]) throw PositionNonemptyEx(position.x, position.y);

    __grid[i] = new Simple(*this, position, STARTING_AGENT_ENERGY);

}

void Game::addSimple(const Position &position, double energy) { // used for testing only

    int i = position.y + (position.x * __width);

    if (position.y >= __width || position.x >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);

    if (__grid[i]) throw PositionNonemptyEx(position.x, position.y);

    __grid[i] = new Simple(*this, position, energy);

}

void Game::addSimple(unsigned x, unsigned y){

    int i = y + (x * __width);

    if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);

    if (__grid[i]) throw PositionNonemptyEx(x, y);

    __grid[i] = new Simple(*this, Position(x, y), STARTING_AGENT_ENERGY);

}

void Game::addSimple(unsigned x, unsigned y, double energy){

    int i = y + (x * __width);

    if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);

    if (__grid[i]) throw PositionNonemptyEx(x, y);

    __grid[i] = new Simple(*this, Position(x, y), energy);

}

void Game::addStrategic(const Position &position, Strategy *s) {
    if(position.y > __width || position.x > __height) {
        throw OutOfBoundsEx(__width, __height, position.x, position.y);
    }

    unsigned int temp = position.x * __width;

    __grid[temp + position.y] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
}

void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
    Position position(x, y);
    addStrategic(position, s);
}

void Game::addFood(const Position &position){

    int i = position.y + (position.x * __width);

    if (position.y >= __width || position.x >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);

    if (__grid[i]) throw PositionNonemptyEx(position.x, position.y);

    __grid[i] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);

}

void Game::addFood(unsigned x, unsigned y){

    int i = y + (x * __width);

    if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);

    if (__grid[i]) throw PositionNonemptyEx(x, y);

    __grid[i] = new Food(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);

}

void Game::addAdvantage(const Position &position){

    int i = position.y + (position.x * __width);

    if (position.y >= __width || position.x >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);

    if (__grid[i]) throw PositionNonemptyEx(position.x, position.y);

    __grid[i] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);

}

void Game::addAdvantage(unsigned x, unsigned y){

    int i = y + (x * __width);

    if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);

    if (__grid[i]) throw PositionNonemptyEx(x, y);

    __grid[i] = new Advantage(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);

}

const Surroundings Game::getSurroundings(const Position &pos) const{

    Surroundings __surounding;

    for (int i = 0; i < 9; ++i) { __surounding.array[i] = EMPTY; }

    for (int R = -1; R <= 1; ++R) {

        for (int C = -1; C <= 1; ++C) {

            if (pos.x + R >= 0 && pos.x + R < __height && pos.y + C >= 0 && pos.y + C < __width) {

                unsigned int index = pos.y + C + ((pos.x + R) * __width);

                if (__grid[index]) __surounding.array[C + 1 + ((R + 1) * 3)] = __grid[index]->getType();

            }

            else { __surounding.array[C + 1 + ((R + 1) * 3)] = INACCESSIBLE; }

        }
    }

    __surounding.array[4] = SELF;

    return (__surounding);

}

// gameplay methods
const ActionType Game::reachSurroundings(const Position &from, const Position &to) {

    if(from.x == to.x && from.y == to.y) { return STAY; }

    if(from.x < to.x && from.y == to.y) { return W; }

    if(from.x > to.x && from.y == to.y) { return E; }

    if(from.x == to.x && from.y < to.y) { return S; }

    if(from.x == to.x && from.y > to.y) { return N; }

    if(from.x < to.x && from.y < to.y) { return SW; }

    if(from.x < to.x && from.y > to.y) { return NW; }

    if(from.x > to.x && from.y < to.y) { return SE; }

    if(from.x > to.x && from.y > to.y) { return NE; }

}

bool Game::isLegal(const ActionType &ac, const Position &pos) const{

    int x, y;

    x = pos.x;
    y = pos.y;

    switch (ac) {

        case E: y++; break;

        case NE: y++; x--; break;

        case N: x--; break;

        case NW: y--; x--; break;

        case W: y--; break;

        case SW: y--; x++; break;

        case S: x++; break;

        case SE: x++; y++; break;

        default: break;
    }

    Position p((unsigned )x, (unsigned)y);

    if (p.x < __height && p.y < __width) return true;

    return false;

}

const Position Game::move(const Position &pos, const ActionType &ac) const { // note: assumes legal, use with isLegal()

    if (isLegal(ac, pos)) {

        int x, y;

        x = pos.x;
        y = pos.y;

        switch (ac) {

            case E: y++; break;

            case NE: y++; x--; break;

            case N: x--; break;

            case NW: y--; x--; break;

            case W: y--; break;

            case SW: y--; x++; break;

            case S: x++; break;

            case SE: x++; y++; break;

            default: break;

        }

        Position p((unsigned )x, (unsigned)y);

        return p;

    }

    return pos;

}

void Game::round() {   // play a single round

    std::set<Piece*> pieces;

    for (auto it = __grid.begin(); it != __grid.end(); ++it) {

        if (*it) { pieces.insert(pieces.end(), *it); (*it)->setTurned(false); }

    }

    for (auto item = pieces.begin(); item != pieces.end(); ++item) {

        if (!(*item)->getTurned()) {

            (*item)->setTurned(true);

            (*item)->age();

            ActionType ac = (*item)->takeTurn(getSurroundings((*item)->getPosition()));

            Position pos0 = (*item)->getPosition();

            Position pos1 = move(pos0, ac);

            if (pos0.x != pos1.x || pos0.y != pos1.y) { Piece *p = __grid[pos1.y + (pos1.x * __width)];

                if (p) {

                    //(*(*item)) * (*p);

                    if ((*item)->getPosition().x != pos0.x || (*item)->getPosition().y != pos0.y) {
                        __grid[pos1.y + (pos1.x * __width)] = (*item); __grid[pos0.y + (pos0.x * __width)] = p; }
                }
                else {

                    (*item)->setPosition(pos1);

                    __grid[pos1.y + (pos1.x * __width)] = (*item);

                    __grid[pos0.y + (pos0.x * __width)] = nullptr;

                }
            }
        }
    }

    for (unsigned int i = 0; i < __grid.size(); ++i) {

        if (__grid[i] && !(__grid[i]->isViable())) { delete __grid[i]; __grid[i] = nullptr; }

    }

    if (getNumResources() <= 0) { __status = Status::OVER; }

    ++__round;

}

void Game::play(bool verbose) {
    __verbose = verbose;
    __status = PLAYING;
    operator<<(std::cout, *this);
    while (__status != OVER) {
        round();
        if (verbose) operator<<(std::cout, *this);
    }
    if (!verbose) operator<<(std::cout, *this);
    }

std::ostream &operator<<(std::ostream &os, const Game &game) {
    for(unsigned int i = 0; i < game.getWidth() * game.getHeight(); i++) {
        if(game.__grid[i] == nullptr) {
            os << "[     ]";
        }
        else {
            os << "[" << *(game.__grid[i]) << "]";
        }

        if(i % game.getWidth() == 0) {
            os << std::endl;
        }

    }
    os << "Status: " << game.getStatus() << std::endl;

    return os;
}
}