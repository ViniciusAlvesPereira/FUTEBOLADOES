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

#include "role_kickoff.h"

QString Role_KickOff::name(){
    return "Role_KickOff";
}

Role_KickOff::Role_KickOff() {
}

void Role_KickOff::initializeBehaviours(){
    usesBehaviour(BHV_POSITIONING, _bh_psn = new Behaviour_Positioning());
}

void Role_KickOff::configure(){
    _theirKickOff = false;
}

void Role_KickOff::run(){
    //Nesse KickOff, encontra-se o posicionamento inicial dos jogadores
    switch (_order) {
    case 0: {
        Position CF_Position;
        if (_theirKickOff == true) CF_Position = Position(true, 1.0, 0.5, 0.0);
        else CF_Position = Position(true, 0.2, 0.0, 0.0);
        _bh_psn->setTimeOutPosition(CF_Position);
        break; }
    case 1: {
        const Position SS_Position(true, 1.3, -0.5, 0.0);
        _bh_psn->setTimeOutPosition(SS_Position);
        break; }
    case 2: {
        const Position AMF_Position(true, 2.0, -0.5, 0.0);
        _bh_psn->setTimeOutPosition(AMF_Position);
        break; }
    case 3: {
        const Position DMF_Position(true, 2.3, 0.5, 0.0);
        _bh_psn->setTimeOutPosition(DMF_Position);
        break; }
    case 4: {
        const Position DF_Position(true, 3.0, 0.0, 0.0);
        _bh_psn->setTimeOutPosition(DF_Position);
        break; }
    case 5: {
        const Position GK_Position(true, 4.0, 0.0, 0.0);
        _bh_psn->setTimeOutPosition(GK_Position);
        break; }
    }
    setBehaviour(BHV_POSITIONING);
}
