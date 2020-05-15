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
    //printf("ID COM POSSE: %i\n", idWithPoss);

    if (ourPoss == false) {
        int idWithPoss = playerWithPoss(ourPoss);
        if (idWithPoss == BALLPOSS_NONE) {
            if (_isPassComing == true) setBehaviour(BHV_BALLRECEPTOR);
            else setBehaviour(BHV_DONOTHING);
        } else {
            if (PlayerBus::theirPlayer(idWithPoss)->distanceTo(player()->position()) < 1.0) {
                setBehaviour(BHV_MARKBALL);
                previousPoss = false;
            } else {
                setBehaviour(BHV_BARRIER);
                previousPoss = false;
            }
        }
    } else {
        int idWithPoss = playerWithPoss(ourPoss);
        if (idWithPoss == player()->playerId()) {
            _bh_psg->setPlayerId(idWithPoss);
            int passId = _bh_psg->getPassId();
            emit sendPassId(passId);
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
        }
    }
}

bool Role_Def_Midfielder::ourTeamPossession() {
    for (quint8 i = 0; i < 6; i++) {
        float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
        if (distanceToBall < 0.3) {
            return true;
        }
    }
    return false;
}

int Role_Def_Midfielder::playerWithPoss(bool ourPoss) {
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

void Role_Def_Midfielder::receivePassId(int passId) {
    if (passId == player()->playerId()) {
        _isPassComing = true;
    } else _isPassComing = false;
}
