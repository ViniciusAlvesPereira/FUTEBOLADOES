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

#ifndef ROLE_SECONDSTRIKER_H
#define ROLE_SECONDSTRIKER_H

#include <entity/player/behaviour/mrcbehaviours.h>
#include <entity/player/role/role.h>

class Role_SecondStriker : public Role {
    Q_OBJECT
private:
    //Variaveis
    int _actualState;
    int _beforeState;
    int _actualPlayer;
    bool _ourPlayer;
    bool _ourPoss;
    bool _theirPoss;
    Position _receveirPosition;
    //quint8 _ourPlayerID;
    //float _distMin[6];
    //float _distSecondStriker;
    //bool _ativarMarkBall;

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

    //Global variables
    float standardDistance;
    bool markChoice;
    bool _isPassComing;

    // Auxiliary functions
    bool ourTeamPossession();
    int playerWithPoss(bool ourPoss);

signals:
    void sendAttackerID(int id);
    void sendMarkInformation(float distance);

public slots:
    void receiveAttackerID(int id);
    void receiveMarkInformation(float distance);
    void receivePassId(int passId);

public:
    Role_SecondStriker();
    void initializeBehaviours();
    QString name();
};

#endif // ROLE_SECONDSTRIKER_H
