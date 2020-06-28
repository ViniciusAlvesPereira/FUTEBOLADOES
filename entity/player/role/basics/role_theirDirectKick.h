#ifndef ROLE_THEIRDIRECTKICK_H
#define ROLE_THEIRDIRECTKICK_H

#include<entity/player/role/role.h>
#include<entity/player/behaviour/mrcbehaviours.h>


class Role_TheirDirectKick: public Role{
private:
    // Behaviours
    Behaviour_Positioning *_bh_psn;

    // Behaviours ids!
    enum{
        BHV_POSITIONING
    };

    //Roles ids

    enum{
        AMF,
        CF,
        SS,
        DMF,
        DF
    };

    // Inherited functions
    void configure();
    void run();

    // Global Variables
    int _order;
    bool _theirKickOff;

public:
    Role_TheirDirectKick();
    void initializeBehaviours();
    QString name();

    void setOrder(int order) { _order = order; }
};

#endif // ROLE_THEIRDIRECTKICK_H
