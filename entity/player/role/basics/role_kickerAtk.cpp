#include "role_kickerAtk.h"

#include<entity/player/role/role.h>

QString Role_KickerAtk::name(){
    return "Role_KickerAtk";
}
Role_KickerAtk::Role_KickerAtk()
{

}

void Role_KickerAtk::initializeBehaviours(){
    usesBehaviour(BHV_POSITIONING, _bh_psn = new Behaviour_Positioning());
    usesBehaviour(BHV_ATTACKER, _bh_atk = new Behaviour_Attacker());
}

void Role_KickerAtk::configure(){
    _theirDirectKick = false;
    _gameStop = true;
    _gameStart = false;
}


void Role_KickerAtk::run(){

    if(_gameStop) {setBehaviour(BHV_POSITIONING);}

    switch (getActualBehaviour()) {
    case BHV_POSITIONING: {
        _kickerPos = loc()->ball();
        _bh_psn->setTimeOutPosition(_kickerPos);

        float distancia = PlayerBus::ourPlayer(_playerId)->distanceTo(loc()->ball());

        if(PlayerBus::ourPlayer(_playerId)->distanceTo(loc()->ball()) < 0.2){
            setBehaviour(BHV_DONOTHING);
        }


    break;
    }

    case BHV_DONOTHING: {
        if(_gameStart){
            setBehaviour(BHV_ATTACKER);
            _gameStop = false;
        }
    }

    break;

    case BHV_ATTACKER: {

    }

    break; }

}
