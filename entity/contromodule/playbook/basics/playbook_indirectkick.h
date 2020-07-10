#ifndef PLAYBOOK_INDIRECTKICK_H
#define PLAYBOOK_INDIRECTKICK_H

#include <entity/contromodule/playbook/playbook.h>
#include <entity/player/role/mrcroles.h>

class Playbook_IndirectKick: public Playbook {
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
    bool _ourIndirectKick;
    quint8 kickerID;
public:
    Playbook_IndirectKick();
    QString name();
};

#endif // PLAYBOOK_INDIRECTKICK_H
