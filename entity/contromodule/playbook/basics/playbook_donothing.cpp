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
    for(int i = 0; i < numPlayers - 3; i++) {
        Role_Default *rl_dft = new Role_Default();
        usesRole(rl_dft);
        _rl_default.push_back(rl_dft);
    }
}

void Playbook_DoNothing::run(int numPlayers) {
    for(int i = 0; i < numPlayers; i++){
        quint8 playerId = dist()->getPlayer();
        if (i < numPlayers - 3) {
            setPlayerRole(playerId, _rl_default.at(i));
        }
        if (i == numPlayers - 3) {
            setPlayerRole(playerId, _rl_ss);
        }
        if (i == numPlayers - 2) {
            setPlayerRole(playerId, _rl_df);
        }
        if (i == numPlayers - 1) {
            setPlayerRole(playerId, _rl_dmf);
        }
    }
}
