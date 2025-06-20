#pragma once
#include <fstream>
#include <string>

#include "Ent.h"
#include "States/State.h"
#include "Entities/EntityList.h"
#include "Entities/Characters/Youkai.h"
#include "Entities/Characters/Cannonhead.h"
#include "Entities/Characters/Ghost.h"
#include "Managers/CollisionManager.h"
#include "Managers/EventManager.h"
#include "States/StateStack.h"
#include "States/Menus/PausedState.h"

namespace States {
    class Stage : public Ent, public States::State{
        protected:
            List::EntityList* pEntityList;
            Manager::CollisionManager* pCollisionManager;
            Entities::Player* player;
            std::string mapPath;
            const int maxEnemies;
            int numberOfYoukais;
            bool isPaused;

        public:
            Stage(const Texture::ID background, const std::string path, 
                  const float sprite_width, const float sprite_height);
            virtual ~Stage();

            void setEntityList();
            const Entities::Player* getPlayer() const;
            void exec();

            void setIsPaused(bool isP);
        protected:
            void createYoukai(const float x, const float y);
            void createPlatform(const float x, const float y);
            void createBlock(const float x, const float y);
            void createPlayer();
            
            void updateView();

            virtual void createEnemies() = 0;
            virtual void createObstacles() = 0;
            virtual void createMap();

            void drawBackground();

            void pauseGame();
            void keyPressed(const sf::Keyboard::Key key);
    };
}