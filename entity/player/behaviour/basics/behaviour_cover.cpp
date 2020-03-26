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
    float y = -0.1 * x * x + 0.6 * x -1.8;
    Position coverPosition = Position(true, y, PlayerBus::ourPlayer(_id)->position().y() / 2, 0.0);
    _skill_GoToLookTo->setDesiredPosition(coverPosition);
}
