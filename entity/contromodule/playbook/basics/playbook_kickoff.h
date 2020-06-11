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

#ifndef PLAYBOOK_KICKOFF_H
#define PLAYBOOK_KICKOFF_H

#include <entity/contromodule/playbook/playbook.h>
#include <entity/player/role/mrcroles.h>

class Playbook_KickOff : public Playbook {
private:
    // Roles
    QList<Role_KickOff*> _rl_KickOff;

    void configure(int numPlayers);
    void run(int numPlayers);
    int maxNumPlayer();

    // Global Variables
    bool _theirKickOff;

public:
    Playbook_KickOff();
    QString name();
};
#endif // PLAYBOOK_KICKOFF_H
