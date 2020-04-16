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

#include "behaviour_cover.h"
#include <entity/player/playerbus.h>

QString Behaviour_Cover::name() {
    return "Behaviour_Cover";
}

Behaviour_Cover::Behaviour_Cover() {
}

void Behaviour_Cover::configure() {
    usesSkill(_skill_GoToLookTo = new Skill_GoToLookTo());
};

void Behaviour_Cover::run() {
    _skill_GoToLookTo->setAimPosition(loc()->ball());
    float x = PlayerBus::ourPlayer(_id)->position().x();
    if (loc()->ourGoal().x() > 0) x = -x;
    x = -0.13 * x * x + 0.7 * x - 0.1;    //Equação característica: y = -0.13x² + 0.7x - 0.1
    if (loc()->ourGoal().x() > 0) x = -x;
    Position coverPosition = Position(true, x, PlayerBus::ourPlayer(_id)->position().y() / 2, 0.0);
    _skill_GoToLookTo->setDesiredPosition(coverPosition);
}
