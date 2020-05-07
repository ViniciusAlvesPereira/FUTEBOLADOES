#include "role_goalKeeper.h"

QString Role_GoalKeeper::name(){
    return "Role_GoalKeeper";
}

Role_GoalKeeper::Role_GoalKeeper() {
}

void Role_GoalKeeper::initializeBehaviours(){
    // Aqui são inseridos os behaviours possíveis de serem usados
    // na ordem: ID do behaviour, instanciação dele
    usesBehaviour(BHV_DONOTHING, _bh_dn = new Behaviour_DoNothing());
    usesBehaviour(BHV_PASSING, _bh_pg = new Behaviour_Passing());
    usesBehaviour(BHV_PENALTYGK, _bh_pgk = new Behaviour_Penalty_GK());
    usesBehaviour(BHV_GOALKEEPER, _bh_gk = new Behaviour_Goalkeeper());
}

void Role_GoalKeeper::configure(){
    // Aqui são setados parametros que devem ser configurados
    _actualState = BHV_GOALKEEPER;
    _beforeState = 200;
    setBehaviour(BHV_GOALKEEPER);
    state_Penalty = false;
    _actualPlayer = player()->playerId();
}

bool Role_GoalKeeper::ourPlayerPoss() {

    quint8 _ourPlayer = player()->playerId();
    float distanceToBall = PlayerBus::ourPlayer(_ourPlayer)->distanceTo(loc()->ball());

    if (distanceToBall < 0.3)
        return true;

    return false;

}

void Role_GoalKeeper::run(){
    /*
     * Aqui devem ocorrer os sets de parametros de acordo com o behaviour
     * que estiver sendo executado, de preferencia declare todos os parametros
     * na classe da role, sete-os aqui e envie para o behaviour (usando as funções
     * set presentes neles)
    */

    switch(getActualBehaviour()){
    case BHV_GOALKEEPER:{

        _actualState = getActualBehaviour();
        //Definir State Penalty
        if(state_Penalty)
           setBehaviour(BHV_PENALTYGK);
        else{
           if(loc()->isInsideOurArea(loc()->ball(), 1.0))
               setBehaviour(BHV_PASSING);
        }
    }
    break;

    case BHV_PASSING:{

        _actualState = getActualBehaviour();
        if(!(loc()->isInsideOurArea(loc()->ball(), 1.0)))
            setBehaviour(BHV_GOALKEEPER);

    }
    break;

    case BHV_PENALTYGK:{

        _actualState = getActualBehaviour();
        if(loc()->isInsideOurArea(loc()->ball(), 1.0))
            setBehaviour(BHV_PASSING);
        else
            setBehaviour(BHV_GOALKEEPER);
    }
    break;

    case BHV_DONOTHING:{

        _actualState = getActualBehaviour();

    }
    break;
    }

    //Printar o behaviours atual
    if(_actualState != _beforeState){

        if(_actualState == BHV_GOALKEEPER){ std::cout<<"\n Behaviour GoalKeeper - PlayerId:"<< _actualPlayer<<std::endl; }
        if(_actualState == BHV_PASSING){ std::cout<<"\n Behaviour Passing - PlayerId:"<< _actualPlayer<<std::endl; }
        if(_actualState == BHV_PENALTYGK){ std::cout<<"\n Behaviour PenaltyGK - PlayerId:"<< _actualPlayer<<std::endl; }
        if(_actualState == BHV_DONOTHING){ std::cout<<"\n Behaviour Donothing - PlayerId:"<< _actualPlayer<<std::endl; }
         _beforeState = _actualState;
    }

}
