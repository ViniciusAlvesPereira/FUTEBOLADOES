#ifndef ROLE_SECONDSTRIKER_H
#define ROLE_SECONDSTRIKER_H

#include <entity/player/behaviour/mrcbehaviours.h>
#include <entity/player/role/role.h>

class Role_Secondstriker : public Role
{
private:
    // Behaviours
    Behaviour_DoNothing *_bh_dn;
    Behaviour_MarkPlayer *_bh_mkp;
    Behaviour_MarkBall *_bh_mkb;
    Behaviour_FollowBall *_bh_flb;
    Behaviour_Attacker *_bh_att;
    Behaviour_Receiver *_bh_rec;

    // Behaviours ids!
    enum{
        BHV_DONOTHING,
        BHV_MARKPLAYER,
        BHV_MARKBALL,
        BHV_FOLLOWBALL,
        BHV_ATTACKER,
        BHV_RECIEVER
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
    float menDistPlayer();

public:
    Role_Secondstriker();
    void initializeBehaviours();
    QString name();
};

#endif // ROLE_SECONDSTRIKER_H
