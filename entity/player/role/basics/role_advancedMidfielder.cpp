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

bool Role_AdvancedMidfielder::ourTeamPossession() {
    for (quint8 i = 0; i < 6; i++) {
        if(PlayerBus::ourPlayerAvailable(i)){
            float distanceToBall = PlayerBus::ourPlayer(i)->distanceTo(loc()->ball());
            if (distanceToBall < 0.3) {
                return true;
            }
        }
    }
    return false;
}

bool Role_AdvancedMidfielder::ourPlayerPoss() {

    _ourPlayer = player()->playerId();
    float distanceToBall = PlayerBus::ourPlayer(_ourPlayer)->distanceTo(loc()->ball());
    if (distanceToBall < 0.3)
        return true;

    return false;

}

bool Role_AdvancedMidfielder:: nearestPlayer(){

    float _distMin[6];
    float _distActualPlayer;

    for(quint8 i = 0; i < 6; i++){
        if(PlayerBus::ourPlayerAvailable(i) && i != player()->playerId()){
            _distMin[i] = WR::Utils::distance(loc()->ball(), PlayerBus::ourPlayer(i)->position());
        }
        else{
            _distMin[i] = 100;
        }
    }

    _distActualPlayer = WR::Utils::distance(loc()->ball(), player()->position());

    for(int i = 0; i < 6; i++){
        if(_distActualPlayer > _distMin[i]){
            return false;
        }
    }
    return true;
}

void Role_AdvancedMidfielder::run(){
    /*
     * Aqui devem ocorrer os sets de parametros de acordo com o behaviour
     * que estiver sendo executado, de preferencia declare todos os parametros
     * na classe da role, sete-os aqui e envie para o behaviour (usando as funções
     * set presentes neles)
    */


    switch(getActualBehaviour()){

    case BHV_MARKBALL:{
        _actualState = getActualBehaviour();

        if(ourTeamPossession()){
            if(ourPlayerPoss()){
                setBehaviour(BHV_ATTACKER);
            }
            else{
                setBehaviour(BHV_RECEIVER);
            }
        }
    }
    break;

    case BHV_RECEIVER:{
        _actualState = getActualBehaviour();

        //_bh_re->setAttackerId(1);

        if(!ourTeamPossession() && nearestPlayer())
            setBehaviour(BHV_MARKBALL);

        if(ourPlayerPoss())
            setBehaviour(BHV_ATTACKER);

    }
    break;

    case BHV_ATTACKER:{
        _actualState = getActualBehaviour();
        emit sendAttackerID(player()->playerId());

        if(!ourTeamPossession()){
            setBehaviour(BHV_MARKBALL);
        }
        if(ourTeamPossession()){
            if(!ourPlayerPoss())
            setBehaviour(BHV_RECEIVER);
        }

    }
    break;

    case BHV_DONOTHING:{
        _actualState = getActualBehaviour();

    }
    break;

    }

    //Printar o behaviours atual
    if(_actualState != _beforeState){

        _actualPayer = player()->playerId();
        if(_actualState == BHV_MARKBALL){ std::cout<<"\n Behaviour MarkBall - PlayerId:"<< _actualPayer<<std::endl; }
        if(_actualState == BHV_RECEIVER){ std::cout<<"\n Behaviour Receiver - PlayerId:"<< _actualPayer<<std::endl; }
        if(_actualState == BHV_ATTACKER){ std::cout<<"\n Behaviour Attacker - PlayerId:"<< _actualPayer<<std::endl; }
        if(_actualState == BHV_DONOTHING){ std::cout<<"\n Behaviour Donothing - PlayerId:"<< _actualPayer<<std::endl; }
         _beforeState = _actualState;
    }
}

void Role_AdvancedMidfielder::receiveAttackerID(quint8 id) {
    _bh_re->setAttackerId(id);
    //printf("[CF] AttackerId: %i\n", id);
}
