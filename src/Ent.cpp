#include "Ent.h"
#include "Managers/GraphicsManager.h"
#include <iostream>

int Ent::cont(0);
Manager::GraphicsManager* Ent::pGraphicsManager(nullptr);

Ent::Ent():
    id(0),
    sprite()
{
    std::cerr << "No Parameters in Ent Constructor" << std::endl;
}

Ent::Ent(const Texture::ID idTexture, const int width, const int height):
    id(cont++),
    sprite()
{   
    pGraphicsManager = Manager::GraphicsManager::getGraphicsManager();  //fix later
    setTexture(idTexture);
    sprite.setHitbox({0.f, 0.f, (float)width, (float)height});
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

Ent::~Ent() {}

const int Ent::getId() const {
    return id;
}

const sf::Sprite* Ent::getSprite() {
    return &sprite;
}

const sf::FloatRect Ent::getGlobalHitbox() const {
    return sprite.getGlobalHitbox();
}

void Ent::setTexture(Texture::ID id) {
    sf::Texture* pTexture = pGraphicsManager->getTexture(id);
    if (pTexture) {
        sprite.setTexture(*pTexture);
    }
}

void Ent::setSpritePosition(float x, float y) {
    sprite.setPosition(x, y);
    sprite.updateHitbox();
}

void Ent::setScale(sf::Vector2f scale) {
    sprite.setScale(scale);
    sprite.updateHitbox();
}

void Ent::draw() {
    pGraphicsManager->drawEnt(this);
}

void Ent::setGraphicsManager(Manager::GraphicsManager* pGM) {
    pGraphicsManager = pGM;
}