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

#include "role_centreforward.h"

struct marking {
    float distance;
    int id;
};

QString Role_CentreForward::name(){
    return "Role_CentreForward";
}

Role_CentreForward::Role_CentreForward() {
}

void Role_CentreForward::initializeBehaviours(){
    usesBehaviour(BHV_MARKBALL, _bh_mkb = new Behaviour_MarkBall());
    usesBehaviour(BHV_MARKPLAYER, _bh_mkp = new Behaviour_MarkPlayer());
    usesBehaviour(BHV_RECEIVER, _bh_rcv = new Behaviour_Receiver());
    usesBehaviour(BHV_ATTACKER, _bh_atk = new Behaviour_Attacker());
    usesBehaviour(BHV_DONOTHING, _bh_dnt = new Behaviour_DoNothing());
    usesBehaviour(BHV_BALLRECEPTOR, _bh_brp = new Behaviour_BallReceptor());
}

void Role_CentreForward::configure(){
    standardDistance = abs(loc()->ourGoal().x() - loc()->theirGoal().x());
    markChoice = false;
    _isPassComing = false;
}

void Role_CentreForward::run(){
    bool ourPoss = ourTeamPossession();
    static bool previousPoss = false;

    if (ourPoss == false) {
        int idWithPoss = playerWithPoss(ourPoss);
        if (idWithPoss == BALLPOSS_NONE) {
            if (previousPoss == true) setBehaviour(BHV_BALLRECEPTOR );
            else setBehaviour(BHV_DONOTHING);
        } else {
            if (PlayerBus::theirPlayer(idWithPoss)->distanceTo(player()->position()) < 1.0) {
                setBehaviour(BHV_MARKBALL);
                previousPoss = false;
            } else {
                QList<marking> markOptions;
                for (int i = 0; i < 6; i++) {
                    if (i != idWithPoss) {
                        marking fon;
                        fon.distance = PlayerBus::theirPlayer(i)->distanceTo(PlayerBus::theirPlayer(idWithPoss)->position());
                        fon.id = i;
                        markOptions.push_back(fon);
                    }
                }
                for (int x = 0; x < markOptions.size() - 1; x++) {
                    for (int y = x; y < markOptions.size(); y++) {
                        if (markOptions[x].distance > markOptions[y].distance) markOptions.swap(x, y);
                    }
                }
                standardDistance = PlayerBus::theirPlayer(markOptions[0].id)->distanceTo(player()->position());
                emit sendMarkInformation(standardDistance);
                if (markChoice == true) _bh_mkp->setTargetID(markOptions[0].id);
                else _bh_mkp->setTargetID(markOptions[1].id);
                setBehaviour(BHV_MARKPLAYER);
                previousPoss = false;
            }
        }
    } else {
        int idWithPoss = playerWithPoss(ourPoss);
        if (idWithPoss == player()->playerId()) {
            setBehaviour(BHV_ATTACKER);
            previousPoss = true;
            emit sendAttackerID(idWithPoss);
        } else {
            setBehaviour(BHV_RECEIVER);
            previousPoss = true;
        }
    }
}

bool Role_CentreForward::ourTeamPossession() {
    for (quint8 i = 0; i < 6; i++) {
        float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
        if (distanceToBall < 0.3) {
            return true;
        }
    }
    return false;
}

int Role_CentreForward::playerWithPoss(bool ourPoss) {
    if (ourPoss == true) {
        for (quint8 i = 0; i < 6; i++) {
            float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
            if(distanceToBall < 0.3){
                return i;
            }
        }
    } else {
        for (quint8 i = 0; i < 6; i++) {
            float distanceToBall = PlayerBus::theirPlayer(i)->distanceTo(loc()->ball());
            if(distanceToBall < 0.3){
                return i;
            }
        }
    }
    return BALLPOSS_NONE;
}

void Role_CentreForward::receiveAttackerID(int id) {
    _bh_rcv->setAttackerId(id);
    //printf("[CF] AttackerId: %i\n", id);
}

void Role_CentreForward::receiveMarkInformation(float distance) {
    if (standardDistance < distance) {
        markChoice = true;
        //printf("[CF] Obtendo vantagem posicional\n");
    } else markChoice = false;
}

void Role_CentreForward::receivePassId(int passId) {
    if (passId == player()->playerId()) {
        _isPassComing = true;
    } else _isPassComing = false;
}
