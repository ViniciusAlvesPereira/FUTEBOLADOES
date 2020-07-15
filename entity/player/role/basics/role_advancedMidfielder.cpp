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
#include <entity/referee/SSLReferee/sslgameinfo.h>

QString Role_AdvancedMidfielder::name(){
    return "Role_AdvancedMidfielder";
}

Role_AdvancedMidfielder::Role_AdvancedMidfielder() {
}

void Role_AdvancedMidfielder::initializeBehaviours(){
    usesBehaviour(BHV_MARKBALL, _bh_mkb = new Behaviour_MarkBall());
    usesBehaviour(BHV_RECEIVER, _bh_rcv = new Behaviour_Receiver());
    usesBehaviour(BHV_ATTACKER, _bh_atk = new Behaviour_Attacker());
    usesBehaviour(BHV_DONOTHING, _bh_dnt = new Behaviour_DoNothing());
    usesBehaviour(BHV_BALLRECEPTOR, _bh_brp = new Behaviour_BallReceptor());
    usesBehaviour(BHV_MARKPLAYER, _bh_mkp = new Behaviour_MarkPlayer());
    usesBehaviour(BHV_BARRIER, _bh_rr = new Behaviour_Barrier());
}

void Role_AdvancedMidfielder::configure(){
    _actualState = BHV_MARKBALL;
    _isPassComing = false;
    setBehaviour(BHV_MARKBALL);
}

void Role_AdvancedMidfielder::run(){
    //_gameInfo = ref()->getGameInfo(player()->team()->teamColor());
    _gameInfo = ref()->getGameInfo(player()->team()->teamColor());

    bool ourPoss = ourTeamPossession();
    static bool previousPoss = false;


    if(_gameInfo->gameOn()){
        if (ourPoss == false) {
            quint8 idWithPoss = playerWithPoss(ourPoss);
            if (idWithPoss == BALLPOSS_NONE) {
                if (_isPassComing == true) {
                    _bh_brp->setPlayerId(player()->playerId());
                    setBehaviour(BHV_BALLRECEPTOR);
                } else if (previousPoss == true) setBehaviour(BHV_DONOTHING);
            } else {
                setBehaviour(BHV_MARKBALL);
                previousPoss = false;
                _isPassComing = false;
            }
        } else {
            quint8 idWithPoss = playerWithPoss(ourPoss);
            if (idWithPoss == player()->playerId()) {
                setBehaviour(BHV_ATTACKER);
                previousPoss = true;
            } else {
                _bh_rcv->setAttackerId(idWithPoss);
                setBehaviour(BHV_RECEIVER);
                previousPoss = true;
            }
        }
    }
    else if(_gameInfo->directKick() || _gameInfo->indirectKick()){

        if(_kickerID){
            previousPoss = true;
            setBehaviour(BHV_ATTACKER);

        }

        else if(_gameInfo->STATE_OURDIRECTKICK || _gameInfo->STATE_OURINDIRECTKICK){

            if(PlayerBus::ourPlayerAvailable(_kickerID)){

                _bh_rcv->setAttackerId(_kickerID);
                setBehaviour(BHV_RECEIVER);
                previousPoss = true;
             }
        }    
        else if(_gameInfo->STATE_THEIRDIRECTKICK || _gameInfo->STATE_THEIRINDIRECTKICK){

            _playerWithPoss = playerWithPoss(ourPoss);
            _bh_mkp->setTargetID(_playerWithPoss);
            _bh_mkp->setMarkDistance(0.8);
            setBehaviour(BHV_MARKPLAYER);

        }
    }
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

void Role_AdvancedMidfielder::receivePassId(quint8 passId) {
    _mutex.lock();
    if (passId == player()->playerId()) {
        _isPassComing = true;
    }
    _mutex.unlock();
}
