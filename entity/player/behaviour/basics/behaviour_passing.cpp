/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#include "behaviour_passing.h"
#include <utils/freeangles/freeangles.h>

QString Behaviour_Passing::name() {
    return "Behaviour_Passing";
}

Behaviour_Passing::Behaviour_Passing() {
}

void Behaviour_Passing::configure() {
    usesSkill(_skill_kick = new Skill_Kick());
    _skill_kick->setIsPass(true);
};

void Behaviour_Passing::run() {
    Position playerPosition = PlayerBus::ourPlayer(_id)->position();
    passId = getBestPassOption(playerPosition);
    //printf("Id escolhido: %i\n", passId);

    if (passId == -1) {
        _skill_kick->setAim(loc()->theirGoal());
        _skill_kick->setZPower(5.0);
    } else {
        Position passDestination = PlayerBus::ourPlayer(passId)->position();
        _skill_kick->setAim(passDestination);
        _skill_kick->setZPower(0.0);
    }
}

int Behaviour_Passing::getBestPassOption(Position &watcher) {
    float minAngle, maxAngle;
    if (loc()->ourGoal().x() < 0) {
        minAngle = WR::Utils::getAngle(loc()->ball(), Position(true, -3.0, 3.0, 0.0));
        maxAngle = WR::Utils::getAngle(loc()->ball(), Position(true, -3.0, -3.0, 0.0));
    } else {
        minAngle = WR::Utils::getAngle(loc()->ball(), Position(true, 3.0, -3.0, 0.0));
        maxAngle = WR::Utils::getAngle(loc()->ball(), Position(true, 3.0, 3.0, 0.0));
    }
    QList<FreeAngles::Interval> freeAngles = FreeAngles::getFreeAngles(loc()->ball(), minAngle, maxAngle); //List of intervals of free angles

    // get the largest interval
    if(freeAngles.size() == 0){
        //printf("Término no FreeAngles");
        return -1;
    } else {
        QList<int> receptors; //List of avaliable receptors

        //Getting the inteval extremes
        QList<FreeAngles::Interval>::iterator it;
        for(it = freeAngles.begin(); it != freeAngles.end(); it++){
            if(it->obstructed()) continue;
            float initAngle = it->angInitial();
            float endAngle = it->angFinal();
            WR::Utils::angleLimitZeroTwoPi(&initAngle);
            WR::Utils::angleLimitZeroTwoPi(&endAngle);

            //Avaliating if there are player within the interval
            const QList<Player*> players = player()->team()->avPlayers().values();
            QList<Player*>::const_iterator plr;
            for(plr = players.constBegin(); plr != players.end(); plr++){
                const Player* player = *plr;
                //if (PlayerBus::ourPlayer(_id)->playerId() == player->playerId()) continue;
                float angleToPlayer = WR::Utils::getAngle(watcher, player->position());
                if (angleToPlayer < 0) angleToPlayer += GEARSystem::Angle::twoPi;
                if (angleToPlayer < initAngle && angleToPlayer > maxAngle) {
                    receptors.push_back(player->playerId());
                }
            }
        }

        //Choice logic
        if (receptors.size() == 0) {
            //printf("Término no receptor\n");
            return -1;
        } else {
            int idChoice = -1;
            for (int id = 0; id < receptors.size(); id++) {
                if (receptors[id] == player()->playerId()) {
                    continue;
                } else {
                    float standardDistance = abs(loc()->ourGoal().x() - loc()->theirGoal().x());
                    float distanceToWatcher = PlayerBus::ourPlayer(receptors[id])->distanceTo(watcher);
                    if (distanceToWatcher < standardDistance) {
                        standardDistance = distanceToWatcher;
                        idChoice = receptors[id];
                    }
                }
            }
            return idChoice;
        }
    }
}
