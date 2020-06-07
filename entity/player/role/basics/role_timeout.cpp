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

#include "role_timeout.h"

QString Role_TimeOut::name(){
    return "Role_TimeOut";
}

Role_TimeOut::Role_TimeOut() {
}

void Role_TimeOut::initializeBehaviours(){
    usesBehaviour(BHV_TIMEOUT, _bh_tmt = new Behaviour_TimeOut());
}

void Role_TimeOut::configure(){
}

void Role_TimeOut::run(){
    //Nesse TimeOut, a figura formada é um 'M'
    switch (_order) {
    case 0: {
        const Position bottomWest(true, 1.5, -0.5, 0.0);
        _bh_tmt->setTimeOutPosition(bottomWest);
        break; }
    case 1: {
        const Position topWest(true, 2.5, -0.3, 0.0);
        _bh_tmt->setTimeOutPosition(topWest);
        break; }
    case 2: {
        const Position leftCenter(true, 2.1, -0.1, 0.0);
        _bh_tmt->setTimeOutPosition(leftCenter);
        break; }
    case 3: {
        const Position rightCenter(true, 2.1, 0.1, 0.0);
        _bh_tmt->setTimeOutPosition(rightCenter);
        break; }
    case 4: {
        const Position topEast(true, 2.5, 0.3, 0.0);
        _bh_tmt->setTimeOutPosition(topEast);
        break; }
    case 5: {
        const Position bottomEast(true, 1.5, 0.5, 0.0);
        _bh_tmt->setTimeOutPosition(bottomEast);
        break; }
    }
    setBehaviour(BHV_TIMEOUT);
}
