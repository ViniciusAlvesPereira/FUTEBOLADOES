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

#ifndef ROLE_ADVANCEDMIDFILDER_H
#define ROLE_ADVANCEDMIDFILDER_H

#include <entity/player/behaviour/mrcbehaviours.h>
#include <entity/player/role/role.h>
#include <entity/player/behaviour/basics/behaviour_receiver.h>
#include <entity/player/skills/skills_include.h>
#include <entity/referee/SSLReferee/sslgameinfo.h>

class Role_AdvancedMidfielder : public Role {
    Q_OBJECT
private:
    // Behaviours
    Behaviour_MarkBall *_bh_mkb;
    Behaviour_Receiver *_bh_rcv;
    Behaviour_Attacker *_bh_atk;
    Behaviour_DoNothing *_bh_dnt;
    Behaviour_BallReceptor *_bh_brp;
    Behaviour_Passing *_bh_psg;
    Behaviour_MarkPlayer *_bh_mkp;
    Behaviour_Barrier *_bh_rr;

    //Referee
    SSLGameInfo *_gameInfo;

    //Variaveis
    bool _kickerID;
    bool _kickGoal;
    quint8 _playerWithPoss;

    // Behaviours ids!
    enum{
        BHV_MARKBALL,
        BHV_RECEIVER,
        BHV_ATTACKER,
        BHV_DONOTHING,
        BHV_BALLRECEPTOR,
        BHV_PASSING,
        BHV_MARKPLAYER,
        BHV_BARRIER
    };

    // Inherited functions
    void configure();
    void run();

    // Mutex
    QMutex _mutex;

    // Global Variables
    int _actualState;
    bool _ourPoss;
    bool _isPassComing;

    // Auxiliary functions
    bool ourTeamPossession();
    quint8 playerWithPoss(bool ourPoss);
    bool ourPlayerDist();

signals:
    void sendPassId(quint8 passId);

public slots:
    void receivePassId(quint8 passId);

public:
    Role_AdvancedMidfielder();
    void initializeBehaviours();
    void kickerAtkID(quint8 kickerID){_kickerID = kickerID;}
    QString name();
};

#endif // ROLE_ADVANCEDMIDFILDER_H
