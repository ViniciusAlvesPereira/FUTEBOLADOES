#ifndef BEHAVIOUR_SWEEPER_H
#define BEHAVIOUR_SWEEPER_H

#include <entity/player/behaviour/behaviour.h>
#include <entity/player/skills/skills_include.h>

class Behaviour_Sweeper : public Behaviour {
private:
    void configure();
    void run();

    // Skills
    Skill_GoToLookTo *_skill_GoToLookTo;

    // Parameters
    int _id;

public:
    Behaviour_Sweeper();
    QString name();

    void setIdOfPoss (int idWithPoss) { _id = idWithPoss; }
};

#endif // BEHAVIOUR_SWEEPER_H
