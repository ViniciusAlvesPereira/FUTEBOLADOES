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

#include "behaviour_sweeper.h"
#include <entity/player/playerbus.h>

QString Behaviour_Sweeper::name() {
    return "Behaviour_Sweeper";
}

Behaviour_Sweeper::Behaviour_Sweeper() {
}

void Behaviour_Sweeper::configure() {
    usesSkill(_skill_GoToLookTo = new Skill_GoToLookTo());
};

void Behaviour_Sweeper::run() {
    _skill_GoToLookTo->setAimPosition(loc()->ball());
    //printf("ID COM POSSE: %i\n", _id);
    float x = PlayerBus::ourPlayer(_id)->position().x();
    if (loc()->ourGoal().x() > 0.0) x = -x;
    x = -0.06 * x * x + 0.35 * x -1.45;  //Equação característica: y = -0.06x² + 0.35x - 1.45
    if (loc()->ourGoal().x() > 0.0) x = -x;
    Position sweeperPosition = Position(true, x, PlayerBus::ourPlayer(_id)->position().y() / 2, 0.0);
    _skill_GoToLookTo->setDesiredPosition(sweeperPosition);
}
