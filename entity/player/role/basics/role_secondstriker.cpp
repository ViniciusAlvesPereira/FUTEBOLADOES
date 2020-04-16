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

#include "role_secondstriker.h"

QString Role_SecondStriker::name(){
    return "Role_SecondStriker";
}

Role_SecondStriker::Role_SecondStriker() {
}

void Role_SecondStriker::initializeBehaviours(){
    // Aqui são inseridos os behaviours possíveis de serem usados
    // na ordem: ID do behaviour, instanciação dele
    usesBehaviour(BHV_DONOTHING, _bh_dn = new Behaviour_DoNothing());
    usesBehaviour(BHV_MARKPLAYER, _bh_mkp = new Behaviour_MarkPlayer());
    usesBehaviour(BHV_MARKBALL, _bh_mkb = new Behaviour_MarkBall());
    usesBehaviour(BHV_FOLLOWBALL, _bh_flb = new Behaviour_FollowBall());
    usesBehaviour(BHV_ATTACKER, _bh_att = new Behaviour_Attacker());
    usesBehaviour(BHV_RECIEVER, _bh_rec = new Behaviour_Receiver());
}

void Role_SecondStriker::configure(){
    // Aqui são setados parametros que devem ser configurados
}

void Role_SecondStriker::run(){
    /*
     * Aqui devem ocorrer os sets de parametros de acordo com o behaviour
     * que estiver sendo executado, de preferencia declare todos os parametros
     * na classe da role, sete-os aqui e envie para o behaviour (usando as funções
     * set presentes neles)
    */

    if (ourTeamPossession()) {
        if (playerWithPoss() == 0){
            setBehaviour(BHV_ATTACKER);
        }else{
            setBehaviour(BHV_RECIEVER);
        }
    } else {
        int id = playerWithPoss();
        if (id == BALLPOSS_NONE || player()->distanceTo(PlayerBus::theirPlayer(1)->position()) < 0.5) {
            setBehaviour(BHV_MARKBALL);
        } else {
            _bh_mkp->setTargetID(2);
            setBehaviour(BHV_MARKPLAYER);
        }
    }

}

bool Role_SecondStriker::ourTeamPossession() {
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

int Role_SecondStriker::playerWithPoss() {
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

/*float Role_SecondStriker::menDistPlayer(){
    float dist, mendist = 1000;
    const QList<Player*> players = _players.values();
    QList<Player*>::const_iterator it;
    for(it = players.constBegin(); it != players.end(); it++){
        const Player* player = *it;
        dist =
    }

    return   ;
}*/
