#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player() = default;
    virtual ~Player() = default;
    
private:
    int mHealth;
    float mAttackPercentage;
};

#endif // PLAYER_H