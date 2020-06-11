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

#include "playbook_kickoff.h"

QString Playbook_KickOff::name() {
    return "Playbook_KickOff";
}

Playbook_KickOff::Playbook_KickOff() {
}

int Playbook_KickOff::maxNumPlayer() {
    return INT_MAX;
}

void Playbook_KickOff::configure(int numPlayers) {
    _theirKickOff = true;
    for (int i = 0; i < numPlayers; i++) {
        Role_KickOff *_rl_kko;
        usesRole(_rl_kko = new Role_KickOff());
        _rl_KickOff.push_back(_rl_kko);
    }
}

void Playbook_KickOff::run(int numPlayers) {
    for(int i = 0; i < numPlayers; i++) {
        quint8 playerId = dist()->getPlayer();
        _rl_KickOff[i]->setKickOffSide(_theirKickOff);
        _rl_KickOff[i]->setOrder(i);
        setPlayerRole(playerId, _rl_KickOff[i]);
    }
}
