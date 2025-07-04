#include "Entities/Characters/Ghost.h"

namespace Entities {
    Ghost::Ghost():
        Enemy(Texture::Ghost, Constants::GHOST_WIDTH, Constants::GHOST_HEIGHT, EntityType::Ghost),
        soulDamage(evilness * 2),
        inRange(false),
        dtime(0.f),
        detection_range(480.f)
    {}

    Ghost::~Ghost() {}

    void Ghost::setSoulDamage(const int damage) {
        soulDamage = damage;
    }

    const int Ghost::getSoulDamage() const {
        return soulDamage;
    }

    void Ghost::setDistance(){
        if(sprite.getPosition().x > p1->getGlobalHitbox().left) {
            distanceFromPlayer = sprite.getPosition().x - p1->getGlobalHitbox().left;
        }
        else {
            distanceFromPlayer = p1->getGlobalHitbox().left - sprite.getPosition().x;
        }

        if (distanceFromPlayer < detection_range){
            inRange = true;
        }
        else {
            inRange = false;
        }
    }


    void Ghost::setPlayer(Player* p){
        p1 = p;
    }

    void Ghost::setDtime(const float dt) {
        dtime = dt;
    }

    void Ghost::setInRange(const bool inrg) {
        inRange = inrg;
    }

    void Ghost::setDirection(){
        if (inRange) {
            dx = speed/2;
            if(sprite.getPosition().x > p1->getGlobalHitbox().left){
                if(dx>0){
                    dx *= -1;
                }
            }
            else {
                if(dx<0){
                    dx *= -1;
                }
            }
        }
        else {
            dx = 0;
        }
    }

    void Ghost::jump(){
        dy += Constants::JUMP_SPEED;
    }

    void Ghost::changeDirectionOnPlatform() {}

    void Ghost::damage(Player* player) {
        player->setLife(player->getLife() - soulDamage);
    }

    void Ghost::save() {
        json data = Enemy::saveDataBuffer();
        data["soulDamage"] = soulDamage;
        data["dtime"] = dtime;
        data["inRange"] = inRange;
        buffer << data.dump(4) << ",\n";
        buffer.flush();
    }

    void Ghost::exec(){
        /*GAMBIARRA*/
        dy += Constants::GRAVITY;
        if (sprite.getGlobalBounds().left + dx < 0 || sprite.getGlobalBounds().left + sprite.getGlobalBounds().width + dx > Constants::MAP_WIDTH) {
           dx = -dx; // Reverse direction if hits borders
        }
        dtime += 0.5f;
        if (!isHurt) {
            sprite.setColor(sf::Color::White);
            if(dtime > 50.f && inRange){//Change logic after 
                jump(); 
                dtime = 0.f; // Reset dtime after shooting
            }
            setDistance();
            setDirection();
        }
        else {
            sprite.setColor(sf::Color::Red);
        }

        moveHitboxSprite(dx, dy);
    }
}