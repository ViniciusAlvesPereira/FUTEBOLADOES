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

#include "playbook_directKick.h"

QString Playbook_DirectKick::name() {
    return "Playbook_KickOff";
}

Playbook_DirectKick::Playbook_DirectKick() {
}

int Playbook_DirectKick::maxNumPlayer() {
    return INT_MAX;
}

void Playbook_DirectKick::configure(int numPlayers) {

    _ourDirectKick = false; //definir pelo referee

    usesRole(_rl_gk = new Role_GoalKeeper());
    usesRole(_rl_df = new Role_Defender());
    usesRole(_rl_dmf = new Role_Def_Midfielder());
    usesRole(_rl_amf = new Role_AdvancedMidfielder());
    usesRole(_rl_ss = new Role_SecondStriker());
    usesRole(_rl_cf = new Role_CentreForward());

    if(_ourDirectKick){
        float smallerDist = 0;
        for(quint8 i; i <= numPlayers - 4; i++){
            if(PlayerBus::ourPlayerAvailable(i)){
                float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());

                if(smallerDist > distanceToBall){
                    smallerDist = distanceToBall;
                    kickerID = i;
                }
            }
        }
        _rl_amf->kickerAtkID(kickerID);
        _rl_ss->kickerAtkID(kickerID);
        _rl_cf->kickerAtkID(kickerID);
    }
}

void Playbook_DirectKick::run(int numPlayers) {

    for(int i = 0; i < numPlayers; i++) {
        quint8 playerId = dist()->getPlayer();

        if (i == numPlayers - 6) {
            setPlayerRole(playerId, _rl_amf);
        }
        if (i == numPlayers - 5) {
            setPlayerRole(playerId, _rl_cf);
        }
        if (i == numPlayers - 4) {
            setPlayerRole(playerId, _rl_ss);
        }
        if (i == numPlayers - 3) {
            setPlayerRole(playerId, _rl_dmf);
        }
        if (i == numPlayers - 2) {
            setPlayerRole(playerId, _rl_df);
        }
        if (i == numPlayers - 1) {
            setPlayerRole(playerId, _rl_gk);
        }
    }
    for(quint8 i = 0; i < numPlayers-4; i++) {

    }

    //PassInformation:
        //AMF
    connect(_rl_amf, SIGNAL(sendPassId(quint8)), _rl_cf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_amf, SIGNAL(sendPassId(quint8)), _rl_ss, SLOT(receivePassId(quint8)), Qt::DirectConnection);

        //SS
    connect(_rl_ss, SIGNAL(sendPassId(quint8)), _rl_amf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_ss, SIGNAL(sendPassId(quint8)), _rl_cf, SLOT(receivePassId(quint8)), Qt::DirectConnection);

        //CF
    connect(_rl_cf, SIGNAL(sendPassId(quint8)), _rl_amf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_cf, SIGNAL(sendPassId(quint8)), _rl_ss, SLOT(receivePassId(quint8)), Qt::DirectConnection);
}
