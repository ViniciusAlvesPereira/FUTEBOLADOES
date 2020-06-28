#ifndef ROLE_KICKERATK_H
#define ROLE_KICKERATK_H

#include<entity/player/role/role.h>
#include<entity/player/behaviour/mrcbehaviours.h>

class Role_KickerAtk : public Role{
private:
    // Behaviours
    Behaviour_Positioning *_bh_psn;
    Behaviour_Attacker *_bh_atk;

    //Variaveis
    bool _gameStop;
    bool _gameStart;
    Position _kickerPos;
    quint8 _playerId;

    // Behaviours ids!
    enum{
        BHV_POSITIONING,
        BHV_DONOTHING,
        BHV_ATTACKER
    };

    // Inherited functions
    void configure();
    void run();

    // Global Variables
    int _order;
    bool _theirDirectKick;

public:
    Role_KickerAtk();

    void initializeBehaviours();
    QString name();

    void setOrder(int order) { _order = order; }
    //void setKickOffSide(bool kickOffSide) { _theirDirectKick = kickOffSide; }

};

#endif // ROLE_KICKERATK_H
