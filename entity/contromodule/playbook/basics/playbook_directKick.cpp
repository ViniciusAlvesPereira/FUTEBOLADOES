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
    return "Playbook_DirectKick";
}

Playbook_DirectKick::Playbook_DirectKick() {
}

int Playbook_DirectKick::maxNumPlayer() {
    return INT_MAX;
}

void Playbook_DirectKick::configure(int numPlayers) {

    _ourDirectKick = true; //definir pelo referee

    usesRole(_rl_gk = new Role_GoalKeeper());
    usesRole(_rl_df = new Role_Defender());
    usesRole(_rl_dmf = new Role_Def_Midfielder());
    usesRole(_rl_amf = new Role_AdvancedMidfielder());
    usesRole(_rl_ss = new Role_SecondStriker());
    usesRole(_rl_cf = new Role_CentreForward());

    for (int i = 0; i < 3; i++) {
        Role_Default *_rl_def;
        usesRole(_rl_def = new Role_Default());
        _rl_default.push_back(_rl_def);
    }

    if(_ourDirectKick){
        float smallerDist = 200;
        for(quint8 i = 3; i < numPlayers; i++){
            if(PlayerBus::ourPlayerAvailable(i)){
                float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
                if(smallerDist > distanceToBall){
                    smallerDist = distanceToBall;
                    kickerID = i;

                }
            }
        }
    }
    if(kickerID==5)
        _rl_amf->kickerAtkID(true);
    else
        _rl_amf->kickerAtkID(false);
    if(kickerID==4)
        _rl_cf->kickerAtkID(true);
    else
        _rl_cf->kickerAtkID(false);
    if(kickerID==3){
        _rl_ss->kickerAtkID(true);
    }else
        _rl_ss->kickerAtkID(false);
}

void Playbook_DirectKick::run(int numPlayers) {

    for(quint8 i = 0; i < 3; i++) {
        setPlayerRole(i, _rl_default[i]);
    }

    for(quint8 i = 3; i < numPlayers; i++) {

        if (i == 5) {
            setPlayerRole(i, _rl_amf);
        }
        if (i == 4) {
            setPlayerRole(i, _rl_cf);
        }
        if (i == 3) {
            setPlayerRole(i, _rl_ss);
        }
        if (i == numPlayers - 300) {
            setPlayerRole(i, _rl_dmf);
        }
        if (i == numPlayers - 200) {
            setPlayerRole(i, _rl_df);
        }
        if (i == numPlayers - 100) {
            setPlayerRole(i, _rl_gk);
        }
    }

    connect(_rl_gk, SIGNAL(sendPassId(quint8)), _rl_cf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_gk, SIGNAL(sendPassId(quint8)), _rl_ss, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_gk, SIGNAL(sendPassId(quint8)), _rl_amf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_gk, SIGNAL(sendPassId(quint8)), _rl_dmf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_gk, SIGNAL(sendPassId(quint8)), _rl_df, SLOT(receivePassId(quint8)), Qt::DirectConnection);
        //DF
    connect(_rl_df, SIGNAL(sendPassId(quint8)), _rl_cf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_df, SIGNAL(sendPassId(quint8)), _rl_ss, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_df, SIGNAL(sendPassId(quint8)), _rl_amf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_df, SIGNAL(sendPassId(quint8)), _rl_dmf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
        //DMF
    connect(_rl_dmf, SIGNAL(sendPassId(quint8)), _rl_cf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_dmf, SIGNAL(sendPassId(quint8)), _rl_ss, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_dmf, SIGNAL(sendPassId(quint8)), _rl_amf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_dmf, SIGNAL(sendPassId(quint8)), _rl_df, SLOT(receivePassId(quint8)), Qt::DirectConnection);

    //MarkPlayer Communication:
        //CF
    connect(_rl_cf, SIGNAL(sendMarkInformation(float)), _rl_ss, SLOT(receiveMarkInformation(float)), Qt::DirectConnection);
        //SS
    connect(_rl_ss, SIGNAL(sendMarkInformation(float)), _rl_cf, SLOT(receiveMarkInformation(float)), Qt::DirectConnection);
}
