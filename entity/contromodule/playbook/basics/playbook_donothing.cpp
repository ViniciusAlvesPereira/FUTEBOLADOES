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
    usesRole(_rl_df = new Role_Defender());
    usesRole(_rl_dmf = new Role_Def_Midfielder());
    usesRole(_rl_ss = new Role_SecondStriker());
    usesRole(_rl_cf = new Role_CentreForward());
    usesRole(_rl_default = new Role_Default());
    usesRole(_rl_dft = new Role_Default());
}

void Playbook_DoNothing::run(int numPlayers) {
    for(int i = 0; i < numPlayers; i++){
        quint8 playerId = dist()->getPlayer();
        if (i == numPlayers - 6) {
            setPlayerRole(playerId, _rl_dft);
        }
        if (i == numPlayers - 5) {
            setPlayerRole(playerId, _rl_default);
        }
        if (i == numPlayers - 4) {
            setPlayerRole(playerId, _rl_cf);
        }
        if (i == numPlayers - 3) {
            setPlayerRole(playerId, _rl_ss);
        }
        if (i == numPlayers - 2) {
            setPlayerRole(playerId, _rl_dmf);
        }
        if (i == numPlayers - 1) {
            setPlayerRole(playerId, _rl_df);
        }
    }

    //setPlayerRole(0, _rl_dft);
    //setPlayerRole(1, _rl_df);
    //setPlayerRole(2, _rl_default);
    //setPlayerRole(3, _rl_dmf);

    //PassInformation:
        //DF
    connect(_rl_df, SIGNAL(sendPassId(int)), _rl_cf, SLOT(receivePassId(int)), Qt::DirectConnection);
    connect(_rl_df, SIGNAL(sendPassId(int)), _rl_ss, SLOT(receivePassId(int)), Qt::DirectConnection);
    connect(_rl_df, SIGNAL(sendPassId(int)), _rl_dmf, SLOT(receivePassId(int)), Qt::DirectConnection);
    connect(_rl_df, SIGNAL(sendPassId(int)), _rl_dft, SLOT(receivePassId(int)), Qt::DirectConnection);
    connect(_rl_df, SIGNAL(sendPassId(int)), _rl_default, SLOT(receivePassId(int)), Qt::DirectConnection);
        //DMF
    connect(_rl_dmf, SIGNAL(sendPassId(int)), _rl_cf, SLOT(receivePassId(int)), Qt::DirectConnection);
    connect(_rl_dmf, SIGNAL(sendPassId(int)), _rl_ss, SLOT(receivePassId(int)), Qt::DirectConnection);
    connect(_rl_dmf, SIGNAL(sendPassId(int)), _rl_df, SLOT(receivePassId(int)), Qt::DirectConnection);
    connect(_rl_dmf, SIGNAL(sendPassId(int)), _rl_dft, SLOT(receivePassId(int)), Qt::DirectConnection);
    connect(_rl_dmf, SIGNAL(sendPassId(int)), _rl_default, SLOT(receivePassId(int)), Qt::DirectConnection);

    //MarkPlayer Communication:
        //CF
    connect(_rl_cf, SIGNAL(sendMarkInformation(float)), _rl_ss, SLOT(receiveMarkInformation(float)), Qt::DirectConnection);
        //SS
    connect(_rl_ss, SIGNAL(sendMarkInformation(float)), _rl_cf, SLOT(receiveMarkInformation(float)), Qt::DirectConnection);

    //Attacker/Receiver Communication:
        //CF
    connect(_rl_cf, SIGNAL(sendAttackerID(int)), _rl_ss, SLOT(receiveAttackerID(int)), Qt::DirectConnection);
        //SS
    connect(_rl_ss, SIGNAL(sendAttackerID(int)), _rl_cf, SLOT(receiveAttackerID(int)), Qt::DirectConnection);
}
