#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include "Ent.h"
#include "Utility/Texture.h"
#include "Utility/Font.h"

namespace Manager {
    class GraphicsManager {
        private:
            sf::RenderWindow window;
            std::list<Texture::Texture> listTextures;
            Font::Font pixelify;
            sf::View camera_view;
            void windowSetup();

            static GraphicsManager* pSelf;
            GraphicsManager();            

        public:
            ~GraphicsManager();
            static GraphicsManager* getGraphicsManager();

            sf::RenderWindow* getWindow();

            const bool isWindowOpen() const;
            void clearWindow();
            void displayWindow();
            void closeWindow();
            void drawEnt(Ent* ent);
            void draw(sf::Drawable &drawable);

            /*Textures*/
            void loadTexture(Texture::ID id, std::string path);
            void loadAllTextures();
            sf::Texture* getTexture(Texture::ID id);

            sf::Font* getFont(Font::ID id);

            /*View*/
            void setView(const sf::View& view);
            void setViewCenter(float x);
            const float getViewPositionX() const;
            void resetView();
    };
}