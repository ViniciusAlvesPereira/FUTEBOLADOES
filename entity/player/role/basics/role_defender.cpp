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

#include "role_defender.h"

QString Role_Defender::name(){
    return "Role_Defender";
}

Role_Defender::Role_Defender() {
}

void Role_Defender::initializeBehaviours(){
    usesBehaviour(BHV_SWEEPER, _bh_swp = new Behaviour_Sweeper());
    usesBehaviour(BHV_BARRIER, _bh_brr = new Behaviour_Barrier());
    usesBehaviour(BHV_PASSING, _bh_psg = new Behaviour_Passing());
}

void Role_Defender::configure(){
}

void Role_Defender::run(){
    bool ourPoss = ourTeamPossession();
    int idWithPoss = playerWithPoss();
    //printf("ID COM POSSE: %i\n", idWithPoss);

    if (ourPoss == false) {
        setBehaviour(BHV_BARRIER);
    }
    else {
        if (idWithPoss == player()->playerId()) {
            _bh_psg->setPlayerId(idWithPoss);
            setBehaviour(BHV_PASSING);
        } else {
            _bh_swp->setIdOfPoss(idWithPoss);
            setBehaviour(BHV_SWEEPER);
        }
    }
}

bool Role_Defender::ourTeamPossession() {
    for (quint8 i = 0; i < 6; i++) {
        float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
        if (distanceToBall < 0.5) {
            return true;
        }
    }
    return false;
}

int Role_Defender::playerWithPoss() {
    for (quint8 i = 0; i < 6; i++) {
        float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
        if(distanceToBall < 0.5){
            return PlayerBus::ourPlayer(i)->playerId();
        }
    }
    return BALLPOSS_NONE;
}
