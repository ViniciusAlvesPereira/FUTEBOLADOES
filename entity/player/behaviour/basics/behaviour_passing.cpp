#include "behaviour_passing.h"
#include <utils/freeangles/freeangles.h>

QString Behaviour_Passing::name() {
    return "Behaviour_Passing";
}

Behaviour_Passing::Behaviour_Passing() {
    _skill_kick->setIsPass(true);

    _skill_kick = NULL;
    _skill_goToLookTo = NULL;
}

void Behaviour_Passing::configure() {
    usesSkill(_skill_goToLookTo = new Skill_GoToLookTo());
    usesSkill(_skill_kick = new Skill_Kick());

    // Setting initial skill
    setInitialSkill(_skill_goToLookTo);

    // Transitions
    addTransition(STATE_GOTO, _skill_kick, _skill_goToLookTo);
    addTransition(STATE_KICK, _skill_goToLookTo, _skill_kick);
};

void Behaviour_Passing::run() {
    float distaceToBall = PlayerBus::ourPlayer(_id)->distanceTo(loc()->ball());
    Position playerPosition = PlayerBus::ourPlayer(_id)->position();

    int passId = getBestPassOption(playerPosition);
    Position passDestination = PlayerBus::ourPlayer(passId)->position();

    _skill_goToLookTo->setDesiredPosition(loc()->ball());
    _skill_goToLookTo->setAimPosition(passDestination);

    if (distaceToBall < 0.15) {
        enableTransition(STATE_KICK);
    } else {
        enableTransition(STATE_GOTO);
    }
}

int Behaviour_Passing::getBestPassOption(Position &watcher) {
    float minAngle, maxAngle;
    if (watcher.x() < 0) {
        minAngle = WR::Utils::getAngle(loc()->ball(), Position(true, -3.0, 3.0, 0.0));
        maxAngle = WR::Utils::getAngle(loc()->ball(), Position(true, -3.0, -3.0, 0.0));
    } else {
        minAngle = WR::Utils::getAngle(loc()->ball(), Position(true, 3.0, -3.0, 0.0));
        maxAngle = WR::Utils::getAngle(loc()->ball(), Position(true, 3.0, 3.0, 0.0));
    }
    QList<FreeAngles::Interval> freeAngles = FreeAngles::getFreeAngles(loc()->ball(), minAngle, maxAngle);
    QList<int> receptors;

    // get the largest interval
    if(freeAngles.size() == 0){
        return -1; // debugar isso dps
    }else{
        QList<FreeAngles::Interval>::iterator it;
        for(it = freeAngles.begin(); it != freeAngles.end(); it++){
            if(it->obstructed()) continue;
            float initAngle = it->angInitial();
            float endAngle = it->angFinal();
            WR::Utils::angleLimitZeroTwoPi(&initAngle);
            WR::Utils::angleLimitZeroTwoPi(&endAngle);

            QList<Player*> players = _players.values();
            QList<Player*>::const_iterator plr;
            for(plr = players.constBegin(); plr != players.end(); plr++){
                const Player* player = *plr;
                float angleToPlayer = WR::Utils::getAngle(watcher, player->position());
                if (angleToPlayer > initAngle && angleToPlayer < maxAngle) {
                    receptors.push_back(player->playerId());
                }
            }
        }
    }

    QList<int>::iterator id;
    float standardDistance = loc()->ourGoal().x() - loc()->theirGoal().x();
    if (standardDistance < 0) standardDistance = -standardDistance;
    int idChoice = -1;
    //float
    for (id = receptors.begin(); id != receptors.end(); id++) {
        //const int
        if (receptors[*id] == player()->playerId()) {
            continue;
        } else {
            if (PlayerBus::ourPlayer(receptors[*id])->distanceTo(watcher) < standardDistance) {
                standardDistance = PlayerBus::ourPlayer(receptors[*id])->distanceTo(watcher);
                idChoice = receptors[*id];
            } else continue;
        }
    }
    return idChoice;
}

