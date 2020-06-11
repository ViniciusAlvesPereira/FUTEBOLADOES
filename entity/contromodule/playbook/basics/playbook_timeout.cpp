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

#include "playbook_timeout.h"

QString Playbook_TimeOut::name() {
    return "Playbook_TimeOut";
}

Playbook_TimeOut::Playbook_TimeOut() {
}

int Playbook_TimeOut::maxNumPlayer() {
    return INT_MAX;
}

void Playbook_TimeOut::configure(int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        Role_TimeOut *_rl_tmt;
        usesRole(_rl_tmt = new Role_TimeOut());
        _rl_TimeOut.push_back(_rl_tmt);
    }
}

void Playbook_TimeOut::run(int numPlayers) {
    for(int i = 0; i < numPlayers; i++) {
        quint8 playerId = dist()->getPlayer();
        _rl_TimeOut[i]->setOrder(i);
        setPlayerRole(playerId, _rl_TimeOut[i]);
    }
}

