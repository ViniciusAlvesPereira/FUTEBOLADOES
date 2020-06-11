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

#ifndef ROLE_TIMEOUT_H
#define ROLE_TIMEOUT_H

#include<entity/player/role/role.h>
#include<entity/player/behaviour/mrcbehaviours.h>

class Role_TimeOut: public Role{
private:
    // Behaviours
    Behaviour_Positioning *_bh_psn;

    // Behaviours ids!
    enum{
        BHV_POSITIONING
    };

    // Inherited functions
    void configure();
    void run();

    // Global Variables
    int _order;

public:
    Role_TimeOut();
    void initializeBehaviours();
    QString name();

    void setOrder(int order) { _order = order; }
};

#endif // ROLE_TIMEOUT_H
