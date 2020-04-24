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

#ifndef BEHAVIOUR_COVER_H
#define BEHAVIOUR_COVER_H

#include <entity/player/behaviour/behaviour.h>
#include <entity/player/skills/skills_include.h>

class Behaviour_Cover : public Behaviour {
private:
    void configure();
    void run();

    // Skills
    Skill_GoToLookTo *_skill_GoToLookTo;

    // Parameters
    int _id;
    float _a, _b, _c;

public:
    Behaviour_Cover();
    QString name();

    void setIdOfPoss (int idWithPoss) { _id = idWithPoss; }
    void setACoeficient (float a) { _a = a; }
    void setBCoeficient (float b) { _b = b; }
    void setCCoeficient (float c) { _c = c; }
};

#endif // BEHAVIOUR_COVER_H
