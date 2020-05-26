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

#include "behaviour_ballreceptor.h"

QString Behaviour_BallReceptor::name() {
    return "Behaviour_BallReceptor";
}

Behaviour_BallReceptor::Behaviour_BallReceptor() {
}

void Behaviour_BallReceptor::configure() {
    //usesSkill(_sk_rotateto = new Skill_RotateTo());
    usesSkill(_sk_gotolookto = new Skill_GoToLookTo());
};

void Behaviour_BallReceptor::run() {
    //std::cout << "Suga-me!\n";
    const Position velocity(true, loc()->ballVelocity().x(), loc()->ballVelocity().y(), 0.0);
    float horizontalDistance = PlayerBus::ourPlayer(_id)->position().x() - loc()->ball().x();
    float verticalDistance = PlayerBus::ourPlayer(_id)->position().y() - loc()->ball().y();

    //Orthogonal Projection
    float fon = (horizontalDistance * velocity.x() + verticalDistance * velocity.y()) / (pow(horizontalDistance, 2) + pow(verticalDistance, 2));
    Position desiredPosition(true, loc()->ball().x() + fon * velocity.x(), loc()->ball().y() + fon * velocity.y(), 0.0);

    _sk_gotolookto->setDesiredPosition(desiredPosition);
    _sk_gotolookto->setAimPosition(loc()->ball());
}
