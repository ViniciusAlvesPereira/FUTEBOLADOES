#ifndef BEHAVIOUR_PASSING_H
#define BEHAVIOUR_PASSING_H

#include <entity/player/behaviour/behaviour.h>
#include <entity/player/skills/skills_include.h>

class Behaviour_Passing : public Behaviour {
private:
    void configure();
    void run();
    int _state;

    //Parameters
    int _id;

    // Skills
    Skill_GoToLookTo *_skill_goToLookTo;
    Skill_Kick *_skill_kick;

    // Transitions
    enum{
        STATE_GOTO,
        STATE_KICK
    };

    // Functions
    int getBestPassOption(Position &watcher);

    // Players
    QHash<quint8, Player*> _players;

public:
    Behaviour_Passing();
    QString name();

    void setPlayerId(int id) { _id = id; }
};
#endif // BEHAVIOUR_PASSING_H
