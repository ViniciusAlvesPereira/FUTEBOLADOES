#ifndef PLAYBOOK_FREEKICK_H
#define PLAYBOOK_FREEKICK_H

#include <entity/contromodule/playbook/playbook.h>
#include <entity/player/role/mrcroles.h>
#include <entity/player/player.h>
#include <entity/referee/SSLReferee/sslgameinfo.h>

class Playbook_FreeKick: public Playbook {
private:

    // Roles
    Role_GoalKeeper *_rl_gk;
    Role_Defender *_rl_df;
    Role_Def_Midfielder *_rl_dmf;
    Role_AdvancedMidfielder *_rl_amf;
    Role_SecondStriker *_rl_ss;
    Role_CentreForward *_rl_cf;

    //Referee
    SSLReferee _gameInfo;

    void configure(int numPlayers);
    void run(int numPlayers);
    int maxNumPlayer();

    // Global Variables
    bool _ourDirectKick;
    quint8 kickerID;

public:
    Playbook_FreeKick();
    QString name();
};

#endif // PLAYBOOK_FREEKICK_H
