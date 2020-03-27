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
    float x = PlayerBus::ourPlayer(_id)->position().x();
    if (loc()->ourGoal().x() > 0) x = -x;
    float y = -0.1 * x * x + 0.6 * x -1.8;  //Equação característica: y = -0.1x² + 0.6x - 1.8
    if (loc()->ourGoal().x() > 0) y = -y;
    Position sweeperPosition = Position(true, y, PlayerBus::ourPlayer(_id)->position().y() / 2, 0.0);
    _skill_GoToLookTo->setDesiredPosition(sweeperPosition);
}
