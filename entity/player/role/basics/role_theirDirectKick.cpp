#include "role_theirDirectKick.h"

QString Role_TheirDirectKick::name(){
    return "Role_KickOff";
}

Role_TheirDirectKick::Role_TheirDirectKick()
{

}

void Role_TheirDirectKick::initializeBehaviours(){
    usesBehaviour(BHV_POSITIONING, _bh_psn = new Behaviour_Positioning());
}

void Role_TheirDirectKick::configure(){
    _theirKickOff = false;
}

void Role_TheirDirectKick::run(){
    //Nesse KickOff, encontra-se o posicionamento inicial dos jogadores
    switch (_order) {
    case AMF: {
        Position AMF_Pos = _bh_psn->getBestPosition(0);
        _bh_psn->setTimeOutPosition(AMF_Pos);
        break; }
    case CF: {
        Position CF_Pos = _bh_psn->getBestPosition(1);
        _bh_psn->setTimeOutPosition(CF_Pos);
        break; }
    case SS: {
        Position SS_Pos = _bh_psn->getBestPosition(2);
        _bh_psn->setTimeOutPosition(SS_Pos);
        break; }
    case DMF: {
        Position DMF_Pos = _bh_psn->getBestPosition(3);
        _bh_psn->setTimeOutPosition(DMF_Pos);
        break; }
    case DF: {
        Position DF_Pos = _bh_psn->getBestPosition(4);
        _bh_psn->setTimeOutPosition(DF_Pos);
        break; }
    }
    setBehaviour(BHV_POSITIONING);
}

