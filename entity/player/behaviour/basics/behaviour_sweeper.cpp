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
