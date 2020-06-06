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

#include "role_goalKeeper.h"

QString Role_GoalKeeper::name(){
    return "Role_GoalKeeper";
}

Role_GoalKeeper::Role_GoalKeeper() {
}

void Role_GoalKeeper::initializeBehaviours(){
    usesBehaviour(BHV_DONOTHING, _bh_dnt = new Behaviour_DoNothing());
    usesBehaviour(BHV_PASSING, _bh_psg = new Behaviour_Passing());
    usesBehaviour(BHV_PENALTYGK, _bh_pgk = new Behaviour_Penalty_GK());
    usesBehaviour(BHV_GOALKEEPER, _bh_gk = new Behaviour_Goalkeeper());
}

void Role_GoalKeeper::configure(){
    _actualState = BHV_GOALKEEPER;
    setBehaviour(BHV_GOALKEEPER);
    state_Penalty = false;
}

void Role_GoalKeeper::run(){
    switch(getActualBehaviour()){
    case BHV_GOALKEEPER:{

        _actualState = getActualBehaviour();
        //Definir State Penalty
        if(state_Penalty)
           setBehaviour(BHV_PENALTYGK);
        else{
           if(loc()->isInsideOurArea(loc()->ball(), 1.0)) {
               _bh_psg->setPlayerId(player()->playerId());
               quint8 passId = _bh_psg->getPassId();
               if (passId != NO_PASS) {
                   emit sendPassId(passId);
               }
               setBehaviour(BHV_PASSING);
           }
        }
    }
    break;

    case BHV_PASSING:{

        _actualState = getActualBehaviour();
        if(!(loc()->isInsideOurArea(loc()->ball(), 1.0)))
            setBehaviour(BHV_GOALKEEPER);

    }
    break;

    case BHV_PENALTYGK:{

        _actualState = getActualBehaviour();
        if(loc()->isInsideOurArea(loc()->ball(), 1.0)) {
            _bh_psg->setPlayerId(player()->playerId());
            quint8 passId = _bh_psg->getPassId();
            if (passId != NO_PASS) {
                emit sendPassId(passId);
            }
            setBehaviour(BHV_PASSING);
        } else setBehaviour(BHV_GOALKEEPER);
    }
    break;

    case BHV_DONOTHING:{

        _actualState = getActualBehaviour();

    }
    break;
    }
}
