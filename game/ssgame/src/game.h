#ifndef GAME_H
#define GAME_H

class Level;
class Object;

class Game
{
public:
    Game();
    ~Game();

    void update(float dt);
    void draw();
    void run();
    Level& level();

private:
    int m_numPlayers;
    int m_playerFocus;
    int m_numLevels;
    Level *m_levels;

    bool addLevel();
    bool loadLevel();
    bool addPlayer();

    Object *m_players;
    Level *m_currentLevel;
};

#endif // GAME_H

