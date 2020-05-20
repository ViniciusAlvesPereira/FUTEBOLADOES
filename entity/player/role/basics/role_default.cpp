/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#include "role_default.h"

QString Role_Default::name(){
    return "Role_Default";
}

Role_Default::Role_Default() {
}

void Role_Default::initializeBehaviours(){
    // Aqui são inseridos os behaviours possíveis de serem usados
    // na ordem: ID do behaviour, instanciação dele
    usesBehaviour(BHV_DONOTHING, _bh_dn = new Behaviour_DoNothing());
    usesBehaviour(BHV_BALLRECEPTOR, _bh_brp = new Behaviour_BallReceptor());
}

void Role_Default::configure(){
    _isPassComing = false;
}

void Role_Default::run(){
    /*
     * Aqui devem ocorrer os sets de parametros de acordo com o behaviour
     * que estiver sendo executado, de preferencia declare todos os parametros
     * na classe da role, sete-os aqui e envie para o behaviour (usando as funções
     * set presentes neles)
    */

    //switch(getActualBehaviour()){
    //case BHV_DONOTHING:{
        //if(player()->position().x() >= 0)
    if (_isPassComing) setBehaviour(BHV_BALLRECEPTOR);
    else setBehaviour(BHV_DONOTHING);
    //}
    //break;
    //case BHV_BARRIER:{
    //    if(player()->position().x() < 0) setBehaviour(BHV_DONOTHING);
    //}
    //break;
    //}


}

void Role_Default::receivePassId(int passId) {
    if (passId == player()->playerId()) {
        _isPassComing = true;
        std::cout << "[Default] Aqui!\n";
    } else _isPassComing = false;
}
