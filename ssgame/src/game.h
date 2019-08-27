#ifndef GAME_H
#define GAME_H

#include "level.h"

//class Level;
class Object;

class Game
{
public:
    Game();
    ~Game();

    void update(float dt);
    void draw();
    void run();

    bool addLevel(int index);
    Level& level();

private:
    int m_numPlayers;
    int m_playerFocus;
    int m_numLevels;

    bool loadLevel();
    bool addPlayer();

    Object *m_players;
    int m_currentLevel;
    QList<Level> m_levels;
};

#endif // GAME_H

