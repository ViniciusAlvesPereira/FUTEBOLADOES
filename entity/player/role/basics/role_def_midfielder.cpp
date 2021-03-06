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

#include "role_def_midfielder.h"

QString Role_Def_Midfielder::name(){
    return "Role_Def_Midfielder";
}

Role_Def_Midfielder::Role_Def_Midfielder() {
}

void Role_Def_Midfielder::initializeBehaviours(){
   usesBehaviour(BHV_BARRIER, _bh_brr = new Behaviour_Barrier());
   usesBehaviour(BHV_COVER, _bh_cvr = new Behaviour_Cover());
   usesBehaviour(BHV_PASSING, _bh_psg = new Behaviour_Passing());
   usesBehaviour(BHV_MARKBALL, _bh_mkb = new Behaviour_MarkBall());
   usesBehaviour(BHV_DONOTHING, _bh_dnt = new Behaviour_DoNothing());
   usesBehaviour(BHV_BALLRECEPTOR, _bh_brp = new Behaviour_BallReceptor());
}

void Role_Def_Midfielder::configure(){
    _isPassComing = false;
}

void Role_Def_Midfielder::run(){
    bool ourPoss = ourTeamPossession();
    static bool previousPoss = false;

    if (ourPoss == false) {
        quint8 idWithPoss = playerWithPoss(ourPoss);
        if (idWithPoss == BALLPOSS_NONE) {
            if (_isPassComing == true) {
                _bh_brp->setPlayerId(player()->playerId());
                setBehaviour(BHV_BALLRECEPTOR);
            } else if (previousPoss == true) setBehaviour(BHV_DONOTHING);
        } else {
            if (PlayerBus::theirPlayer(idWithPoss)->distanceTo(player()->position()) < 1.0) {
                setBehaviour(BHV_MARKBALL);
                previousPoss = false;
                _isPassComing = false;
            } else {
                setBehaviour(BHV_BARRIER);
                previousPoss = false;
                _isPassComing = false;
            }
        }
    } else {
        quint8 idWithPoss = playerWithPoss(ourPoss);
        if (idWithPoss == player()->playerId()) {
            _bh_psg->setPlayerId(idWithPoss);
            quint8 passId = _bh_psg->getPassId();
            if (passId != NO_PASS) {
                emit sendPassId(passId);
            }
            setBehaviour(BHV_PASSING);
            previousPoss = true;
        } else {
            _bh_cvr->setIdOfPoss(idWithPoss);

            //Equação característica: y = -0.13x² + 0.7x - 0.1
            _bh_cvr->setACoeficient(-0.13);
            _bh_cvr->setBCoeficient(0.7);
            _bh_cvr->setCCoeficient(-0.1);

            setBehaviour(BHV_COVER);
            previousPoss = true;
            _isPassComing = false;
        }
    }
}

bool Role_Def_Midfielder::ourTeamPossession() {
    for (quint8 i = 0; i < MRCConstants::_qtPlayers; i++) {
        if (PlayerBus::ourPlayerAvailable(i)) {
            float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
            if(distanceToBall < 0.3){
                return true;
            }
        }
    }
    return false;
}

quint8 Role_Def_Midfielder::playerWithPoss(bool ourPoss) {
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

void Role_Def_Midfielder::receivePassId(quint8 passId) {
    _mutex.lock();
    if (passId == player()->playerId()) {
        _isPassComing = true;
    }
    _mutex.unlock();
}
