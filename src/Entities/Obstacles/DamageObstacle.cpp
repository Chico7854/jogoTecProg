#include "Entities/Obstacles/DamageObstacle.h"

namespace Entities {
    DamageObstacle::DamageObstacle(const Texture::ID id, const int sprite_width, const int sprite_height, const EntityType type):
        Obstacle(id, sprite_width, sprite_height, type, false),
        damage(10)
    {}

    DamageObstacle::DamageObstacle(): damage(-1) {}

    DamageObstacle::~DamageObstacle() {}

    void DamageObstacle::damageCollision(Character* character) {
        const sf::FloatRect charCoordinates = character->getGlobalHitbox();
        const sf::FloatRect obstacleCoordinates = getGlobalHitbox();


        if (charCoordinates.intersects(obstacleCoordinates)) {
            const float middlePointPlayer = charCoordinates.left + (charCoordinates.width / 2);
            const float middlePointEntity = obstacleCoordinates.left + (obstacleCoordinates.width / 2);

            const float dy = Constants::JUMP_SPEED / 1.5;
            float dx = Constants::SPEED * 2;

            if (middlePointPlayer < middlePointEntity) {
                dx *= -1;
            }

            character->setDy(dy);
            character->setDx(dx);
            character->setIsHurt(true);
            character->moveHitboxSprite(dx, dy);
        }
    }

    void DamageObstacle::obstruct(Character* character) {
		if (character->getType() == EntityType::Player) {
            damageCollision(character);
        }
        else {
            sf::FloatRect intersectionRect;

            const sf::FloatRect charCoordinates = character->getGlobalHitbox();
            const sf::FloatRect obstacleCoordinates = getGlobalHitbox();

            if (charCoordinates.intersects(obstacleCoordinates, intersectionRect)) {
                float xOverlap = intersectionRect.width;
                float yOverlap = intersectionRect.height;

                /*Check vertical collision*/
                if (yOverlap <= xOverlap) {
                    if ((character->getDy() >= 0) && (charCoordinates.top < obstacleCoordinates.top)) {
                        yOverlap *= -1;
                        character->setOnGround(true);
                        character->setIsHurt(false);
                    }
                    character->moveHitboxSprite(0, yOverlap);
                    character->setDy(0.f);
                } 
                /*Horizontal collision*/
                else {
                    if (obstacleCoordinates.left > charCoordinates.left)
                        xOverlap *= -1;
                    character->moveHitboxSprite(xOverlap, 0);
                    if (character->getType() != EntityType::Player) {
                        character->setDx(character->getDx() * -1);
                    }
                }
            }
        }
	}
}