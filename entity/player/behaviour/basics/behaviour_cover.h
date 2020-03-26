#ifndef BEHAVIOUR_COVER_H
#define BEHAVIOUR_COVER_H

#include <entity/player/behaviour/behaviour.h>
#include <entity/player/skills/skills_include.h>

class Behaviour_Cover : public Behaviour {
private:
    void configure();
    void run();
    int _state;

    // Skills
    Skill_GoToLookTo *_skill_GoToLookTo;

    // Parameters
    int _id;

    // Players
    QHash<quint8, Player*> _players;

    // Auxiliary functions
    bool ourTeamPossession();

public:
    Behaviour_Cover();
    QString name();

    void setIdOfPoss (int idWithPoss) { _id == idWithPoss; }
};

#endif // BEHAVIOUR_COVER_H
