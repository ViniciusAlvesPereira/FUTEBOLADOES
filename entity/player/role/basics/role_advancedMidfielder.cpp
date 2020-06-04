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

#include "role_advancedMidfielder.h"

QString Role_AdvancedMidfielder::name(){
    return "Role_AdvancedMidfielder";
}

Role_AdvancedMidfielder::Role_AdvancedMidfielder() {
}

void Role_AdvancedMidfielder::initializeBehaviours(){
    usesBehaviour(BHV_MARKBALL, _bh_mb = new Behaviour_MarkBall());
    usesBehaviour(BHV_RECEIVER, _bh_re = new Behaviour_Receiver());
    usesBehaviour(BHV_ATTACKER, _bh_at = new Behaviour_Attacker());
    usesBehaviour(BHV_DONOTHING, _bh_dn = new Behaviour_DoNothing());
    usesBehaviour(BHV_BALLRECEPTOR, _bh_brp = new Behaviour_BallReceptor());
}

void Role_AdvancedMidfielder::configure(){
    _actualState = BHV_MARKBALL;
    _isPassComing = false;
    setBehaviour(BHV_MARKBALL);
}

void Role_AdvancedMidfielder::run(){
    _ourPoss = ourTeamPossession();

    switch(getActualBehaviour()){

    case BHV_MARKBALL:{
        if(ourTeamPossession()){
            if(playerWithPoss(_ourPoss) == player()->playerId()){
                emit sendAttackerID(player()->playerId());
                setBehaviour(BHV_ATTACKER);
            } else setBehaviour(BHV_RECEIVER);
        } else {
            if(playerWithPoss(_ourPoss) == BALLPOSS_NONE){
                if (_isPassComing) {
                    _bh_brp->setPlayerId(player()->playerId());
                    setBehaviour(BHV_BALLRECEPTOR);
                } else setBehaviour(BHV_DONOTHING);
            }
        }
    }
    break;

    case BHV_RECEIVER:{
        if(!_ourPoss && playerWithPoss(_ourPoss) != BALLPOSS_NONE)
            setBehaviour(BHV_MARKBALL);

        if(playerWithPoss(_ourPoss) == BALLPOSS_NONE){
            if (_isPassComing) {
                _bh_brp->setPlayerId(player()->playerId());
                setBehaviour(BHV_BALLRECEPTOR);
            }
            if(ourPlayerDist())
                setBehaviour(BHV_MARKBALL);
            else
                setBehaviour(BHV_DONOTHING);
        }

        if(playerWithPoss(_ourPoss) == player()->playerId()){
            emit sendAttackerID(player()->playerId());
            setBehaviour(BHV_ATTACKER);
        }

    }
    break;

    case BHV_ATTACKER:{
        emit sendAttackerID(player()->playerId());

        if(playerWithPoss(_ourPoss) == BALLPOSS_NONE){
            if (_isPassComing) {
                _bh_brp->setPlayerId(player()->playerId());
                setBehaviour(BHV_BALLRECEPTOR);
            }
            if(ourPlayerDist())
                setBehaviour(BHV_MARKBALL);
            else
                setBehaviour(BHV_DONOTHING);
        }

        if(ourTeamPossession()){
            if(playerWithPoss(_ourPoss) != player()->teamId())
            setBehaviour(BHV_RECEIVER);
        } else {
            if(!_ourPoss && playerWithPoss(_ourPoss) != BALLPOSS_NONE)
                setBehaviour(BHV_MARKBALL);
        }

    }
    break;

    case BHV_DONOTHING:{
        if(ourTeamPossession()) {
            if (playerWithPoss(_ourPoss) == player()->playerId()) {
                emit sendAttackerID(player()->playerId());
                setBehaviour(BHV_ATTACKER);
            } else setBehaviour(BHV_RECEIVER);
        } else {
            if (playerWithPoss(_ourPoss) == BALLPOSS_NONE) {
                if (_isPassComing) {
                    _bh_brp->setPlayerId(player()->playerId());
                    setBehaviour(BHV_BALLRECEPTOR);
                }
            } else if (ourPlayerDist())
                setBehaviour(BHV_MARKBALL);
        }

    }
    break;

    case BHV_BALLRECEPTOR: {
        if(ourTeamPossession()) {
            if (playerWithPoss(_ourPoss) == player()->playerId()) {
                emit sendAttackerID(player()->playerId());
                setBehaviour(BHV_ATTACKER);
            } else setBehaviour(BHV_RECEIVER);
        }
        if(playerWithPoss(_ourPoss) == BALLPOSS_NONE){
            if(ourPlayerDist())
                setBehaviour(BHV_MARKBALL);
            else
                setBehaviour(BHV_DONOTHING);
        }
    }
    break;

    }
}

//Avalia se o AMF é o mais próximo à bola
bool Role_AdvancedMidfielder::ourPlayerDist(){

    float _distMin[11];
    float _distSecondStriker;
    quint8 _ourPlayerID = player()->playerId();

    for(quint8 i = 0; i < 11; i++){
        if(PlayerBus::ourPlayerAvailable(i) && i != _ourPlayerID){
            _distMin[i] = WR::Utils::distance(loc()->ball(), PlayerBus::ourPlayer(i)->position());
            //std::cout<<"Distancia: "<<_distMin[i]<<"PlayerId: "<<(int)i<<std::endl;
        }
        else{
            _distMin[i] = 1000;
        }
    }

    _distSecondStriker = WR::Utils::distance(loc()->ball(),player()->position());
    for(int i = 0; i <11 ; i++){
       if(_distSecondStriker > _distMin[i]) return false;
    }
    return true;
}

bool Role_AdvancedMidfielder::ourTeamPossession() {
    for (quint8 i = 0; i < 11; i++) {
        if(PlayerBus::ourPlayerAvailable(i)){
            float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
            if (distanceToBall < 0.3) {
                return true;
            }
        }
    }
    return false;
}

quint8 Role_AdvancedMidfielder::playerWithPoss(bool ourPoss) {
    if (ourPoss == true) {
        for (quint8 i = 0; i < 11; i++) {
            if(PlayerBus::ourPlayerAvailable(i)){
                float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
                if(distanceToBall < 0.3){
                    return i;
                }
            }
        }
    } else {
        for (quint8 i = 0; i < 11; i++) {
            if(PlayerBus::theirPlayerAvailable(i)){
                float distanceToBall = PlayerBus::theirPlayer(i)->distanceTo(loc()->ball());
                if(distanceToBall < 0.3){
                    return i;
                }
            }
        }
    }
    return BALLPOSS_NONE;
}

void Role_AdvancedMidfielder::receiveAttackerID(quint8 id) {
    _bh_re->setAttackerId(id);
    //printf("[CF] AttackerId: %i\n", id);
}

void Role_AdvancedMidfielder::receivePassId(quint8 passId) {
    if (passId == player()->playerId()) {
        _isPassComing = true;
        //std::cout << "[DF] Aqui!\n";
    } else _isPassComing = false;
}
