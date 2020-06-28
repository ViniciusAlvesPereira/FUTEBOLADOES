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

#include "behaviour_positioning.h"

QString Behaviour_Positioning::name() {
    return "Behaviour_Positioning";
}

Behaviour_Positioning::Behaviour_Positioning() {
    _skill_GoToLookTo = NULL;
    _desiredPosition = Position(true, 0.0, 0.0, 0.0);
}

void Behaviour_Positioning::configure() {
    usesSkill(_skill_GoToLookTo = new Skill_GoToLookTo());
};

void Behaviour_Positioning::run() {
    _skill_GoToLookTo->setDesiredPosition(_desiredPosition);
    _skill_GoToLookTo->setAimPosition(loc()->ball());
    //_skill_GoToLookTo->setOffsetToBall(0.0);
}

Position Behaviour_Positioning::getBestPosition(int quadrant){

    int _quadrant;
    Position ball;

    _quadrant = quadrant;

    return ball;
}
