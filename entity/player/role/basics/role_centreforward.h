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

#ifndef ROLE_CENTREFORWARD_H
#define ROLE_CENTREFORWARD_H

#include <entity/player/behaviour/mrcbehaviours.h>
#include <entity/player/role/role.h>

class Role_CentreForward : public Role {
    Q_OBJECT
private:
    // Behaviours
    Behaviour_MarkBall *_bh_mkb;
    Behaviour_MarkPlayer *_bh_mkp;
    Behaviour_Receiver *_bh_rcv;
    Behaviour_Attacker *_bh_atk;
    Behaviour_DoNothing *_bh_dnt;
    Behaviour_BallReceptor *_bh_brp;

    // Behaviours ids!
    enum{
        BHV_MARKBALL,
        BHV_MARKPLAYER,
        BHV_RECEIVER,
        BHV_ATTACKER,
        BHV_DONOTHING,
        BHV_BALLRECEPTOR
    };

    // Inherited functions
    void configure();
    void run();

    // Mutex
    QMutex _mutex;

    // Global variables
    float standardDistance;
    bool markChoice;
    bool _isPassComing;

    // Auxiliary functions
    bool ourTeamPossession();
    quint8 playerWithPoss(bool ourPoss);

signals:
    void sendMarkInformation(float distance);

public slots:
    void receiveMarkInformation(float distance);
    void receivePassId(quint8 passId);

public:
    Role_CentreForward();
    void initializeBehaviours();
    QString name();
};

#endif // ROLE_CENTREFORWARD_H
