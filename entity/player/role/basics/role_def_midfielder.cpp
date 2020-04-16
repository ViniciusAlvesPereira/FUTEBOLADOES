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
