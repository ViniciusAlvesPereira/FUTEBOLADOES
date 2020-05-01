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

#include "role_secondstriker.h"
#include <const/constants.h>"

struct marking {
    float distance;
    int id;
};

QString Role_SecondStriker::name(){
    return "Role_SecondStriker";
}

Role_SecondStriker::Role_SecondStriker() {
}

void Role_SecondStriker::initializeBehaviours(){
    usesBehaviour(BHV_MARKBALL, _bh_mkb = new Behaviour_MarkBall());
    usesBehaviour(BHV_MARKPLAYER, _bh_mkp = new Behaviour_MarkPlayer());
    usesBehaviour(BHV_RECEIVER, _bh_rcv = new Behaviour_Receiver());
    usesBehaviour(BHV_ATTACKER, _bh_atk = new Behaviour_Attacker());
    usesBehaviour(BHV_DONOTHING, _bh_dnt = new Behaviour_DoNothing());
    usesBehaviour(BHV_BALLRECEPTOR, _bh_brp = new Behaviour_BallReceptor());
}

void Role_SecondStriker::configure(){
    standardDistance = abs(loc()->ourGoal().x() - loc()->theirGoal().x());
    markChoice = false;
    _isPassComing = false;
}

bool Role_SecondStriker::ourTeamPossession() {
    for (quint8 i = 0; i < 6; i++) {
        if(PlayerBus::ourPlayerAvailable(i)){
            float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
            if (distanceToBall < 0.3) {
                return true;
            }
        }
    }
    return false;
}

bool Role_SecondStriker::ourPlayerPoss() {

    _ourPlayer = player()->playerId();
    float distanceToBall = PlayerBus::ourPlayer(_ourPlayer)->distanceTo(loc()->ball());
    if (distanceToBall < 0.3)
        return true;

    return false;

}

bool Role_SecondStriker::ourPlayerDist(){

    float _distMin[6];
    float _distSecondStriker;
    quint8 _ourPlayerID = player()->playerId();

    for(quint8 i = 0; i < 6; i++){
        if(PlayerBus::ourPlayerAvailable(i) && i != _ourPlayerID){
            _distMin[i] = WR::Utils::distance(loc()->ball(), PlayerBus::ourPlayer(i)->position());
        }
        else{
            _distMin[i] = 1000;
        }
    }

    _distSecondStriker = WR::Utils::distance(loc()->ball(),player()->position());
    for(int i = 0; i <6 ; i++){
       if(_distSecondStriker > _distMin[i]){
           return false;
       }
    }

    return true;
}

void Role_SecondStriker::run(){
    bool ourPoss = ourTeamPossession();
    static bool previousPoss = false;

    if (ourPoss == false) {
        int idWithPoss = playerWithPoss(ourPoss);
        if (idWithPoss == BALLPOSS_NONE) {
            if (_isPassComing == true) {
                _bh_brp->setPlayerId(player()->playerId());
                setBehaviour(BHV_BALLRECEPTOR);
            } else if (previousPoss == true) setBehaviour(BHV_DONOTHING);
        } else {
            if (PlayerBus::theirPlayer(idWithPoss)->distanceTo(player()->position()) < 1.0) {
                setBehaviour(BHV_MARKBALL);
                previousPoss = false;
            } else {
                QList<marking> markOptions;
                for (int i = 0; i < MRCConstants::_qtPlayers; i++) {
                    if (PlayerBus::theirPlayerAvailable(i)) {
                        if (i != idWithPoss) {
                            marking fon;
                            fon.distance = PlayerBus::theirPlayer(i)->distanceTo(PlayerBus::theirPlayer(idWithPoss)->position());
                            fon.id = i;
                            markOptions.push_back(fon);
                        }
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

bool Role_SecondStriker::ourTeamPossession() {
    for (quint8 i = 0; i < MRCConstants::_qtPlayers; i++) {
        if (PlayerBus::ourPlayerAvailable(i)) {
            float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
            if(distanceToBall < 0.3){
                return true;
            }
        }
    }
    return false;
}*/

int Role_SecondStriker::playerWithPoss(bool ourPoss) {
    if (ourPoss == true) {
        for (quint8 i = 0; i < MRCConstants::_qtPlayers; i++) {
            if (PlayerBus::ourPlayerAvailable(i)) {
                float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
                if(distanceToBall < 0.3){
                    return i;
                }
            }
        }
    } else {
        for (quint8 i = 0; i < MRCConstants::_qtPlayers; i++) {
            if (PlayerBus::theirPlayerAvailable(i)) {
                float distanceToBall = PlayerBus::theirPlayer(i)->distanceTo(loc()->ball());
                if(distanceToBall < 0.3){
                    return i;
                }
            }
        }
    }
    return BALLPOSS_NONE;
}

void Role_SecondStriker::receiveAttackerID(int id) {
    _bh_rcv->setAttackerId(id);
    //printf("[SS] AttackerId: %i\n", id);
}

void Role_SecondStriker::receiveMarkInformation(float distance) {
    if (standardDistance < distance) {
        markChoice = true;
        //printf("[SS] Obtendo vantagem posicional\n");
    } else markChoice = false;
}

void Role_SecondStriker::receivePassId(int passId) {
    if (passId == player()->playerId()) {
        _isPassComing = true;
        //std::cout << "[SS] Aqui!\n";
    } else _isPassComing = false;
}
