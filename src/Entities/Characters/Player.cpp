#include "Entities/Characters/Player.h"
#include "Utility/Constants.h"

namespace Entities {
    Player::Player(Texture::ID id, const int width, const int height):
        Character(id, width, height, EntityType::Player),
        swordDamage(1),
        attack_radius(64.f)
    {
    }

    Player::Player():
        swordDamage(-1),
        attack_radius()
    {}

    Player::~Player() {}

    void Player::checkKeyboardInput() {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
            dx = 0;       }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dx = Constants::SPEED;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dx = Constants::SPEED * -1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && getOnGround()) {
            setDy(Constants::JUMP_SPEED);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash)) {
            attack();
        }
    }

    void Player::attack(){
        //Manager::CollisionManager::getCollisionManager();
    }

    sf::Vector2f Player::getPosition(){
        return sprite.getPosition();
    }

    void Player::save()
    {
    }

    void Player::exec()
    {
        if (!isHurt) {
            sprite.setColor(sf::Color::White);
            checkKeyboardInput();
        }
        else {
            sprite.setColor(sf::Color::Red);
        }
        dy += Constants::GRAVITY;
        if (dy > 20) {
            dy = 20;
        }
        moveHitboxSprite(dx, dy);
        if (!isHurt) {
            dx = 0;
        }

        setOnGround(false);

        // frame += 0.008f * time; // Animation speed
        // if (frame >= 8) {
        //     frame = 0;
        // }

        // /*animation*/
        // if (dx > 0) {
        //     sprite.setTextureRect(sf::IntRect(width * (int)frame, 0, width, height));
        // }
        // if (dx < 0) {
        //     sprite.setTextureRect(sf::IntRect(width * ((int)frame + 1), 0, -width, height));
        // }
    }
}