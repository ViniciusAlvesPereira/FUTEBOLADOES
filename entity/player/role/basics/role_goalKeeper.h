#ifndef ROLE_GOALKEEPER_H
#define ROLE_GOALKEEPER_H

#include<entity/player/role/role.h>
#include<entity/player/behaviour/mrcbehaviours.h>

class Role_GoalKeeper: public Role{
private:
    // variaveis
    int _actualState;
    int _beforeState;
    quint8 _actualPlayer;
    bool state_Penalty;


    // Behaviours
    Behaviour_DoNothing *_bh_dn;
    Behaviour_Passing *_bh_pg;
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

    bool ourPlayerPoss();

public:
    Role_GoalKeeper();
    void initializeBehaviours();
    QString name();
};

#endif // ROLE_GOALKEEPER_H
