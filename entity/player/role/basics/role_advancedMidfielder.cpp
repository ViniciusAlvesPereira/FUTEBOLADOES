#include "role_advancedMidfielder.h"

QString Role_AdvancedMidfielder::name(){
    return "Role_AdvancedMidfielder";
}

Role_AdvancedMidfielder::Role_AdvancedMidfielder() {
}

void Role_AdvancedMidfielder::initializeBehaviours(){
    // Aqui são inseridos os behaviours possíveis de serem usados
    // na ordem: ID do behaviour, instanciação dele
    usesBehaviour(BHV_MARKBALL, _bh_mb = new Behaviour_MarkBall());
    usesBehaviour(BHV_RECEIVER, _bh_re = new Behaviour_Receiver());
    usesBehaviour(BHV_ATTACKER, _bh_at = new Behaviour_Attacker());
    usesBehaviour(BHV_DONOTHING, _bh_dn = new Behaviour_DoNothing());
}

void Role_AdvancedMidfielder::configure(){
    //Controle dos estados
    _actualState = BHV_MARKBALL;
    _beforeState = 200;
    setBehaviour(BHV_MARKBALL);

}

void Role_AdvancedMidfielder::run(){
    /*
     * Aqui devem ocorrer os sets de parametros de acordo com o behaviour
     * que estiver sendo executado, de preferencia declare todos os parametros
     * na classe da role, sete-os aqui e envie para o behaviour (usando as funções
     * set presentes neles)
    */

    //if(nearestPlayer())
      //  std::cout<<"Mais proximo"<<std::endl;

    //Até aqui tá indo nenhum erro até agora

    _ourPoss = ourTeamPossession();
    if(playerWithPoss(_ourPoss)!=BALLPOSS_NONE && !_ourPoss)
        _theirPoss = true;
    else
        _theirPoss = false;

    switch(getActualBehaviour()){

    case BHV_MARKBALL:{
        _actualState = getActualBehaviour();
        _ourPoss = ourTeamPossession();
        if(playerWithPoss(_ourPoss)!=BALLPOSS_NONE && !_ourPoss)
            _theirPoss = true;


        if(ourTeamPossession()){
            if(playerWithPoss(_ourPoss) == player()->playerId()){
                emit sendAttackerID(player()->playerId());
                setBehaviour(BHV_ATTACKER);
            }
            else{
                setBehaviour(BHV_RECEIVER);
            }
        }
        if(!_theirPoss){
            if(playerWithPoss(_ourPoss) == BALLPOSS_NONE && !ourPlayerDist()){
                setBehaviour(BHV_DONOTHING);
            }
        }
    }
    break;

    case BHV_RECEIVER:{
        _actualState = getActualBehaviour();

        //_bh_re->setAttackerId(1);

        if(_theirPoss)
            setBehaviour(BHV_MARKBALL);

        if(playerWithPoss(_ourPoss) == BALLPOSS_NONE){
            if(ourPlayerDist())
                setBehaviour(BHV_MARKBALL);
            else
                setBehaviour(BHV_DONOTHING);
        }

        if(playerWithPoss(_ourPoss) == player()->playerId()){
            emit sendAttackerID(player()->playerId());
            setBehaviour(BHV_ATTACKER);
        }

    }
    break;

    case BHV_ATTACKER:{
        _actualState = getActualBehaviour();
        emit sendAttackerID(player()->playerId());

        if(playerWithPoss(_ourPoss) == BALLPOSS_NONE){
            if(ourPlayerDist())
                setBehaviour(BHV_MARKBALL);
            else
                setBehaviour(BHV_DONOTHING);
        }

        if(ourTeamPossession()){
            if(playerWithPoss(_ourPoss) != player()->teamId())
            setBehaviour(BHV_RECEIVER);
        }
        else{
            if(_theirPoss)
                setBehaviour(BHV_MARKBALL);
        }

    }
    break;

    case BHV_DONOTHING:{
        _actualState = getActualBehaviour();

        if(ourTeamPossession()) {
            if (playerWithPoss(_ourPoss) == player()->playerId()) setBehaviour(BHV_ATTACKER);
            else setBehaviour(BHV_RECEIVER);
        } else {
            if(ourPlayerDist() || _theirPoss) setBehaviour(BHV_MARKBALL);
        }

    }
    break;

    }
}

bool Role_AdvancedMidfielder::ourPlayerDist(){

    float _distMin[11];
    float _distSecondStriker;
    quint8 _ourPlayerID = player()->playerId();

    for(quint8 i = 0; i < 11; i++){
        if(PlayerBus::ourPlayerAvailable(i) && i != _ourPlayerID){
            _distMin[i] = WR::Utils::distance(loc()->ball(), PlayerBus::ourPlayer(i)->position());
            //std::cout<<"Distancia: "<<_distMin[i]<<"PlayerId: "<<(int)i<<std::endl;
        }
        else{
            _distMin[i] = 1000;
        }
    }

    _distSecondStriker = WR::Utils::distance(loc()->ball(),player()->position());
    for(int i = 0; i <11 ; i++){
       if(_distSecondStriker > _distMin[i]){
           return false;
       }
    }

    return true;
}

bool Role_AdvancedMidfielder::ourTeamPossession() {
    for (quint8 i = 0; i < 11; i++) {
        if(PlayerBus::ourPlayerAvailable(i)){
            float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
            if (distanceToBall < 0.3) {
                return true;
            }
        }
    }
    return false;
}

int Role_AdvancedMidfielder::playerWithPoss(bool ourPoss) {
    if (ourPoss == true) {
        for (quint8 i = 0; i < 11; i++) {
            if(PlayerBus::ourPlayerAvailable(i)){
                float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
                if(distanceToBall < 0.3){
                    return i;
                }
            }
        }
    } else {
        for (quint8 i = 0; i < 11; i++) {
            if(PlayerBus::theirPlayerAvailable(i)){
                float distanceToBall = PlayerBus::theirPlayer(i)->distanceTo(loc()->ball());
                if(distanceToBall < 0.3){
                    return i;
                }
            }
        }
    }
    //std::cout<<"BallPos_None"<<std::endl;
    return BALLPOSS_NONE;
}

void Role_AdvancedMidfielder::receiveAttackerID(int id) {
    _bh_re->setAttackerId(id);
    //printf("[CF] AttackerId: %i\n", id);
}
