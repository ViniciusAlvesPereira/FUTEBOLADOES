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
}

void Role_Def_Midfielder::configure(){
    // Aqui são setados parametros que devem ser configurados
}

void Role_Def_Midfielder::run(){
    bool ourPoss = ourTeamPossession();
    int idWithPoss = playerWithPoss();
    //printf("ID COM POSSE: %i\n", idWithPoss);

    if (ourPoss == false) {
        if (PlayerBus::theirPlayer(0)->distanceTo(player()->position()) < 1.0) {
            setBehaviour(BHV_MARKBALL);
        } else {
            setBehaviour(BHV_BARRIER);
        }
    } else {
        if (idWithPoss == player()->playerId()) {
            _bh_psg->setPlayerId(idWithPoss);
            setBehaviour(BHV_PASSING);
        } else {
            _bh_cvr->setIdOfPoss(idWithPoss);
            setBehaviour(BHV_COVER);
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

int Role_Def_Midfielder::playerWithPoss() {
    for (quint8 i = 0; i < 6; i++) {
        float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
        if(distanceToBall < 0.3){
            return PlayerBus::ourPlayer(i)->playerId();
        }
    }
    return BALLPOSS_NONE;
}
