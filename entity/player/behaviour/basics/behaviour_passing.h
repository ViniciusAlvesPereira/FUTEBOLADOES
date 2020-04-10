#ifndef BEHAVIOUR_PASSING_H
#define BEHAVIOUR_PASSING_H

#include <entity/player/behaviour/behaviour.h>
#include <entity/player/skills/skills_include.h>

class Behaviour_Passing : public Behaviour {
private:
    void configure();
    void run();

    //Parameters
    int _id;

    // Skills
    Skill_Kick *_skill_kick;

    // Functions
    int getBestPassOption(Position &watcher);

public:
    Behaviour_Passing();
    QString name();

    void setPlayerId (int id) { _id = id; }
};

#endif // BEHAVIOUR_PASSING_H
