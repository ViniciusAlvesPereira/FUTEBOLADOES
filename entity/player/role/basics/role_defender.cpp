#include "role_defender.h"

QString Role_Defender::name(){
    return "Role_Default";
}

Role_Defender::Role_Defender() {
}

void Role_Defender::initializeBehaviours(){
    // Aqui são inseridos os behaviours possíveis de serem usados
    // na ordem: ID do behaviour, instanciação dele
    usesBehaviour(BHV_SWEEPER, _bh_swp = new Behaviour_Sweeper());
    usesBehaviour(BHV_BARRIER, _bh_brr = new Behaviour_Barrier());
}

void Role_Defender::configure(){
    // Aqui são setados parametros que devem ser configurados
}

void Role_Defender::run(){
    /*
     * Aqui devem ocorrer os sets de parametros de acordo com o behaviour
     * que estiver sendo executado, de preferencia declare todos os parametros
     * na classe da role, sete-os aqui e envie para o behaviour (usando as funções
     * set presentes neles)
    */

    if (ourTeamPossession()) {
        _bh_swp->setIdOfPoss(playerWithPoss());
        setBehaviour(BHV_SWEEPER);
    }
    else setBehaviour(BHV_BARRIER);

}

bool Role_Defender::ourTeamPossession() {
    const QList<Player*> players = _players.values();
    QList<Player*>::const_iterator it;
    for(it = players.constBegin(); it != players.end(); it++){
        const Player* player = *it;
        if(player->hasBallPossession()){
            return true;
        }
    }
    return false;
}

int Role_Defender::playerWithPoss() {
    const QList<Player*> players = _players.values();
    QList<Player*>::const_iterator it;
    for(it = players.constBegin(); it != players.end(); it++){
        const Player* player = *it;
        if(player->hasBallPossession()){
            return player->playerId();
        }
    }
    return BALLPOSS_NONE;
}
