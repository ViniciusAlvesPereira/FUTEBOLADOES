#ifndef ROLE_DEF_MIDFIELDER_H
#define ROLE_DEF_MIDFIELDER_H

#include <entity/player/behaviour/mrcbehaviours.h>
#include <entity/player/role/role.h>

class Role_Def_Midfielder : public Role
{
private:
    // Behaviours
    Behaviour_Attacker *_bh_atk;
    //Behaviour_Attacker *_bh_def;

    // Behaviours ids!
    enum{
        BHV_ATTACKER
        //BHV_BARRIER
    };

    // Inherited functions
    void configure();
    void run();

    // Mutex
    QMutex _mutex;

public:
    Role_Def_Midfielder();
    void initializeBehaviours();
    QString name();
};

#endif // ROLE_DEF_MIDFIELDER_H
