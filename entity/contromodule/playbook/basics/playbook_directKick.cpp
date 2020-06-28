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

#include "playbook_directKick.h"

QString Playbook_DirectKick::name() {
    return "Playbook_KickOff";
}

Playbook_DirectKick::Playbook_DirectKick() {
}

int Playbook_DirectKick::maxNumPlayer() {
    return INT_MAX;
}

void Playbook_DirectKick::configure(int numPlayers) {
    _theirDirectKick = false;

    if(!_theirDirectKick){
        /* usesRole(_rl_gk = new Role_GoalKeeper());
        usesRole(_rl_df = new Role_Defender());
        usesRole(_rl_dmf = new Role_Def_Midfielder());
        //usesRole(_rl_amf = new Role_AdvancedMidfielder());
        usesRole(_rl_ss = new Role_SecondStriker());
        usesRole(_rl_cf = new Role_CentreForward());*/

        for (int i = 0; i < numPlayers-2; i++) {
            usesRole(_rl_ko = new Role_KickOff);
            _rl_KickOff.push_back(_rl_ko);
        }

        //New Role
        //usesRole(_rl_ka = new Role_KickerAtk());
        usesRole(_rl_gk = new Role_GoalKeeper());
        usesRole(_rl_amf = new Role_AdvancedMidfielder());
    }
    else{
        for (int i = 0; i < numPlayers-1; i++) {
            usesRole(_rl_tdk = new Role_TheirDirectKick);
            _rl_TheirDirect.push_back(_rl_tdk);
        }
        usesRole(_rl_gk = new Role_GoalKeeper());
    }
}

void Playbook_DirectKick::run(int numPlayers) {

    if(!_theirDirectKick){
        /*for(int i = 0; i < numPlayers; i++) {
            quint8 playerId = dist()->getPlayer();

            if (i == numPlayers - 5) {
                setPlayerRole(playerId, _rl_cf);
            }
            if (i == numPlayers - 4) {
                setPlayerRole(playerId, _rl_ss);
            }
            if (i == numPlayers - 3) {
                setPlayerRole(playerId, _rl_dmf);
            }
            if (i == numPlayers - 2) {
                setPlayerRole(playerId, _rl_df);
            }
            if (i == numPlayers - 1) {
                setPlayerRole(playerId, _rl_gk);
            }
            //Jogador que vai inicar a partida
            if (i == numPlayers - 6) {
                setPlayerRole(playerId, _rl_ka);
            }
        }*/
        for(quint8 i = 0; i < numPlayers-2; i++) {
           // quint8 playerId = dist()->getPlayer();

            _rl_KickOff[i]->setOrder(i);
            setPlayerRole(i, _rl_KickOff[i]);
        }
        setPlayerRole(numPlayers-3, _rl_gk);
        setPlayerRole(numPlayers-2, _rl_amf);
        setPlayerRole(numPlayers-1, _rl_ko);

   }
   else{
        for(quint8 i = 0; i < numPlayers-1; i++) {
           // quint8 playerId = dist()->getPlayer();

            _rl_TheirDirect[i]->setOrder(i);
            setPlayerRole(i, _rl_TheirDirect[i]);
        }
        setPlayerRole(numPlayers, _rl_gk);
    }
}
