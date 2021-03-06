#ifndef SWORDFISH_H
#define SWORDFISH_H

#include "Fish.h"
class Swordfish:public Fish
{
public:
    enum State {DELAY,PREPARE,SHOOT,SHOOT_END};
    
    Swordfish(const sf::Vector2f& pos=sf::Vector2f(),const sf::Vector2f& dir=sf::Vector2f(1.0f,0.0f),float delay=0);
    Swordfish(const Swordfish&)=delete;
    
    Swordfish& operator=(const Swordfish&)=delete;
    
    void init();
    State getState() const;
    sf::Vector2f getCenter() const;
    float getAttackRadius() const;
    
    virtual void attacked() override;
    virtual void update(float deltaTime) override;
    virtual void updateShape() override;
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const override;
    
    sf::RectangleShape _body;
    sf::RectangleShape _attackLine;
    
    float _timer;
    float _delay;
    State _state;
    sf::Vector2f _oriPos;
    sf::Vector2f _dir;
    float _speed;
    static const float PREPARE_TIME,SHOOT_TIME,SIZE,SHOOT_SPEED;
};
#endif
