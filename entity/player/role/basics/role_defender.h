#ifndef ROLE_DEFENDER_H
#define ROLE_DEFENDER_H

#include <entity/player/behaviour/mrcbehaviours.h>
#include <entity/player/role/role.h>

#define BALLPOSS_NONE 100

class Role_Defender : public Role
{
private:
    // Behaviours
    Behaviour_Sweeper *_bh_swp;
    Behaviour_Barrier *_bh_brr;
    Behaviour_Passing *_bh_psg;

    // Behaviours ids!
    enum{
        BHV_SWEEPER,
        BHV_BARRIER,
        BHV_PASSING
    };

    // Inherited functions
    void configure();
    void run();

    // Auxiliary functions
    bool ourTeamPossession();
    int playerWithPoss();

public:
    Role_Defender();
    void initializeBehaviours();
    QString name();
};

#endif // ROLE_DEFENDER_H
