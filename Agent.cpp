//
// Created by Sumner B on 4/7/2016.
//

#include "Food.h"
#include "Agent.h"
#include "Advantage.h"

namespace Gaming {

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p), __energy(energy) {


    }

    Agent::~Agent() { }

    void Agent::age() {

        __energy -= AGENT_FATIGUE_RATE;

    }

    Piece &Agent::operator*(Piece &other) {

        Piece *p = &other;

        Resource *res = dynamic_cast <Resource *> (p);

        if (res) { interact(res); }
        Agent *agent = dynamic_cast <Agent *> (p);

        if (agent) { interact(agent); }

        if (!isFinished()) {

            Position OLD;
            OLD = getPosition();

            Position NEW;
            NEW = other.getPosition();

            other.setPosition(OLD);
            setPosition(NEW);

        }

        return *this;

    }

    Piece &Agent::interact(Agent *target) {

        if (__energy == target->__energy) {
            target->finish();

            finish();
        }

        else if (__energy < target->__energy) {
            target->__energy -= __energy;

            finish();
        }
        else {
            __energy -= target->__energy;

            target->finish();
        }

        return *this;

    }

    Piece &Agent::interact(Resource *target) {

        __energy += target->consume();

        return *this;

    }
}

