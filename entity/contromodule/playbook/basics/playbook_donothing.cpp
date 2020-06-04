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

#include "playbook_donothing.h"

QString Playbook_DoNothing::name() {
    return "Playbook_DoNothing";
}

Playbook_DoNothing::Playbook_DoNothing() {
}

int Playbook_DoNothing::maxNumPlayer() {
    return INT_MAX;
}

void Playbook_DoNothing::configure(int numPlayers) {
    usesRole(_rl_gk = new Role_GoalKeeper());
    usesRole(_rl_df = new Role_Defender());
    usesRole(_rl_dmf = new Role_Def_Midfielder());
    usesRole(_rl_amf = new Role_AdvancedMidfielder());
    usesRole(_rl_ss = new Role_SecondStriker());
    usesRole(_rl_cf = new Role_CentreForward());
}

void Playbook_DoNothing::run(int numPlayers) {
    for(int i = 0; i < numPlayers; i++){
        quint8 playerId = dist()->getPlayer();
        if (i == numPlayers - 6) {
            setPlayerRole(playerId, _rl_cf);
        }
        if (i == numPlayers - 5) {
            setPlayerRole(playerId, _rl_ss);
        }
        if (i == numPlayers - 4) {
            setPlayerRole(playerId, _rl_amf);
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

    //PassInformation:
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

    //Attacker/Receiver Communication:
        //CF
    connect(_rl_cf, SIGNAL(sendAttackerID(quint8)), _rl_ss, SLOT(receiveAttackerID(quint8)), Qt::DirectConnection);
    connect(_rl_cf, SIGNAL(sendAttackerID(quint8)), _rl_amf, SLOT(receiveAttackerID(quint8)), Qt::DirectConnection);
        //SS
    connect(_rl_ss, SIGNAL(sendAttackerID(quint8)), _rl_cf, SLOT(receiveAttackerID(quint8)), Qt::DirectConnection);
    connect(_rl_ss, SIGNAL(sendAttackerID(quint8)), _rl_amf, SLOT(receiveAttackerID(quint8)), Qt::DirectConnection);
        //AMF
    connect(_rl_amf, SIGNAL(sendAttackerID(quint8)), _rl_cf, SLOT(receiveAttackerID(quint8)), Qt::DirectConnection);
    connect(_rl_amf, SIGNAL(sendAttackerID(quint8)), _rl_ss, SLOT(receiveAttackerID(quint8)), Qt::DirectConnection);
}
