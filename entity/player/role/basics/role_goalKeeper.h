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

#ifndef ROLE_GOALKEEPER_H
#define ROLE_GOALKEEPER_H

#include<entity/player/role/role.h>
#include<entity/player/behaviour/mrcbehaviours.h>

class Role_GoalKeeper: public Role{
    Q_OBJECT
private:
    // variaveis
    int _actualState;
    int _actualPlayer;
    bool state_Penalty;


    // Behaviours
    Behaviour_DoNothing *_bh_dnt;
    Behaviour_Passing *_bh_psg;
    Behaviour_Goalkeeper *_bh_gk;
    Behaviour_Penalty_GK *_bh_pgk;

    // Behaviours ids!
    enum{
        BHV_DONOTHING,  //0
        BHV_PASSING,    //1
        BHV_GOALKEEPER, //2
        BHV_PENALTYGK   //3
    };

    // Inherited functions
    void configure();
    void run();

    // Mutex
    QMutex _mutex;

signals:
    void sendPassId(quint8 passId);

public:
    Role_GoalKeeper();
    void initializeBehaviours();
    QString name();
};

#endif // ROLE_GOALKEEPER_H
