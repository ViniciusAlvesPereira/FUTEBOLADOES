#include "role_def_midfielder.h"

QString Role_Def_Midfielder::name(){
    return "Role_Def_Midfielder";
}

Role_Def_Midfielder::Role_Def_Midfielder() {
}

void Role_Def_Midfielder::initializeBehaviours(){
    // Aqui são inseridos os behaviours possíveis de serem usados
    // na ordem: ID do behaviour, instanciação dele
    usesBehaviour(BHV_ATTACKER, _bh_atk = new Behaviour_Attacker());
    //usesBehaviour(BHV_BARRIER, _bh_def = new Behaviour_Attacker());
}

void Role_Def_Midfielder::configure(){
    // Aqui são setados parametros que devem ser configurados
}

void Role_Def_Midfielder::run(){
    /*
     * Aqui devem ocorrer os sets de parametros de acordo com o behaviour
     * que estiver sendo executado, de preferencia declare todos os parametros
     * na classe da role, sete-os aqui e envie para o behaviour (usando as funções
     * set presentes neles)
    */

    //switch(getActualBehaviour()){
    //case BHV_DONOTHING:{
        //if(player()->position().x() >= 0)
    setBehaviour(BHV_ATTACKER);
    //}
    //break;
    //case BHV_BARRIER:{
    //    if(player()->position().x() < 0) setBehaviour(BHV_DONOTHING);
    //}
    //break;
    //}

}
