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
    Behaviour_Attacker *_bh_brr;

    // Behaviours ids!
    enum{
        BHV_SWEEPER,
        BHV_BARRIER
    };

    // Inherited functions
    void configure();
    void run();

    // Mutex
    QMutex _mutex;

    // Players
    QHash<quint8, Player*> _players;

    // Auxiliary functions
    bool ourTeamPossession();
    int playerWithPoss();

public:
    Role_Defender();
    void initializeBehaviours();
    QString name();
};

#endif // ROLE_DEFENDER_H