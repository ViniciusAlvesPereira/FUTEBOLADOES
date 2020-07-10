#include "playbook_indirectkick.h"

QString Playbook_IndirectKick::name() {
    return "Playbook_KickOff";
}

Playbook_IndirectKick::Playbook_IndirectKick(){  
}

int Playbook_IndirectKick::maxNumPlayer() {
    return INT_MAX;
}

void Playbook_IndirectKick::configure(int numPlayers) {
    _ourIndirectKick = false; //definir pelo referee

    usesRole(_rl_gk = new Role_GoalKeeper());
    usesRole(_rl_df = new Role_Defender());
    usesRole(_rl_dmf = new Role_Def_Midfielder());
    usesRole(_rl_amf = new Role_AdvancedMidfielder());
    usesRole(_rl_ss = new Role_SecondStriker());
    usesRole(_rl_cf = new Role_CentreForward());

    if(_ourIndirectKick){
        float smallerDist = 0;
        for(quint8 i; i <= numPlayers - 4; i++){
            if(PlayerBus::ourPlayerAvailable(i)){
                float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());

                if(smallerDist > distanceToBall){
                    smallerDist = distanceToBall;
                    kickerID = i;
                }
            }
        }
    }
}

void Playbook_IndirectKick::run(int numPlayers) {

    for(int i = 0; i < numPlayers; i++) {
        quint8 playerId = dist()->getPlayer();

        if (i == numPlayers - 6) {
            setPlayerRole(playerId, _rl_amf);
        }
        if (i == numPlayers - 5) {
            setPlayerRole(playerId, _rl_cf);
        }
        if (i == numPlayers - 4) {
            setPlayerRole(playerId, _rl_ss);
        }
        if (i == numPlayers - 3) {
            setPlayerRole(playerId, _rl_dmf);
        }
        if (i == numPlayers - 2) {
            setPlayerRole(playerId, _rl_df);
        }
        if (i == numPlayers - 1) {
            setPlayerRole(playerId, _rl_gk);
        }
    }
    for(quint8 i = 0; i < numPlayers-4; i++) {

    }
    //PassInformation:
        //AMF
    connect(_rl_amf, SIGNAL(sendPassId(quint8)), _rl_cf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_amf, SIGNAL(sendPassId(quint8)), _rl_ss, SLOT(receivePassId(quint8)), Qt::DirectConnection);

        //SS
    connect(_rl_ss, SIGNAL(sendPassId(quint8)), _rl_amf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_ss, SIGNAL(sendPassId(quint8)), _rl_cf, SLOT(receivePassId(quint8)), Qt::DirectConnection);

        //CF
    connect(_rl_cf, SIGNAL(sendPassId(quint8)), _rl_amf, SLOT(receivePassId(quint8)), Qt::DirectConnection);
    connect(_rl_cf, SIGNAL(sendPassId(quint8)), _rl_ss, SLOT(receivePassId(quint8)), Qt::DirectConnection);
}

