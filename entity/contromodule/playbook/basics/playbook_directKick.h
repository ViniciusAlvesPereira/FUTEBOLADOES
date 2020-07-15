#ifndef PLAYBOOK_DIRECTKICK_H
#define PLAYBOOK_DIRECTKICK_H

#include <entity/contromodule/playbook/playbook.h>
#include <entity/player/role/mrcroles.h>
#include <entity/referee/SSLReferee/sslgameinfo.h>

class Playbook_DirectKick: public Playbook {
private:

    // Roles
    Role_GoalKeeper *_rl_gk;
    Role_Defender *_rl_df;
    Role_Def_Midfielder *_rl_dmf;
    Role_AdvancedMidfielder *_rl_amf;
    Role_SecondStriker *_rl_ss;
    Role_CentreForward *_rl_cf;

    //Referee
    //SSLGameInfo _gameInfo;

    void configure(int numPlayers);
    void run(int numPlayers);
    int maxNumPlayer();

    // Global Variables
    bool _ourDirectKick;
    quint8 kickerID;

public:
    Playbook_DirectKick();
    QString name();
};

#endif // PLAYBOOK_DIRECTKICK_H
