#include "playbook_donothing.h"

QString Playbook_DoNothing::name() {
    return "Playbook_DoNothing";
}

Playbook_DoNothing::Playbook_DoNothing() {
}

int Playbook_DoNothing::maxNumPlayer() {
    return INT_MAX;
}

void Playbook_DoNothing::configure(int numPlayers) {
    usesRole(_rl_df = new Role_Defender());
    usesRole(_rl_dmf = new Role_Def_Midfielder());
    for(int i = 0; i < numPlayers - 2; i++) {
        Role_Default *rl_dft = new Role_Default();
        usesRole(rl_dft);
        _rl_default.push_back(rl_dft);
    }
}

void Playbook_DoNothing::run(int numPlayers) {
    for(int i = 0; i < numPlayers; i++){
        quint8 playerId = dist()->getPlayer();
        if (i < numPlayers - 2) {
            setPlayerRole(playerId, _rl_default.at(i));
        }
        if (i == numPlayers - 2) {
            setPlayerRole(playerId, _rl_df);
        }
        if (i == numPlayers - 1) {
            setPlayerRole(playerId, _rl_dmf);
        }
    }
}
