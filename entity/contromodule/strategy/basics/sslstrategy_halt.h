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

#ifndef SSLSTRATEGY_HALT_H
#define SSLSTRATEGY_HALT_H

#include <entity/contromodule/strategy/strategystate.h>
#include <entity/contromodule/playbook/mrcplaybook.h>

class SSLStrategy_Halt : public StrategyState {
private:
    // Playbooks
    Playbook_KickOff *_pb_KickOff;
    Playbook_DirectKick *_pb_DirectKick;
    Playbook_Training *_pb_Training;

    void configure(int numOurPlayers);
    void run(int numOurPlayers);

public:
    SSLStrategy_Halt();
    QString name();
};


#endif // SSLSTRATEGY_HALT_H
