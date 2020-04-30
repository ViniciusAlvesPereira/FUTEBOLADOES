#ifndef ROLE_ADVANCEDMIDFILDER_H
#define ROLE_ADVANCEDMIDFILDER_H

#include <entity/player/behaviour/mrcbehaviours.h>
#include <entity/player/role/role.h>
#include <entity/player/behaviour/basics/behaviour_receiver.h>

class Role_AdvancedMidfielder : public Role
{
private:
    //Variaveis
    int _actualState;
    int _beforeState;
    int _actualPayer;
    bool _ourPlayer;



    // Behaviours
    Behaviour_MarkBall *_bh_mb;
    Behaviour_Receiver *_bh_re;
    Behaviour_Attacker *_bh_at;
    Behaviour_DoNothing *_bh_dn;

    // Behaviours ids!
    enum{
        BHV_MARKBALL,       //0
        BHV_RECEIVER,       //1
        BHV_ATTACKER,       //2
        BHV_DONOTHING       //3
    };

    // Inherited functions
    void configure();
    void run();

    // Mutex
    QMutex _mutex;

    //Time com posse de bola
    bool ourTeamPossession();
    bool ourPlayerPoss();

public:
    Role_AdvancedMidfielder();
    void initializeBehaviours();
    QString name();
};

#endif // ROLE_ADVANCEDMIDFILDER_H
