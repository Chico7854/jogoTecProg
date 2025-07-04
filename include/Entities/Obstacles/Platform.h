#pragma once
#include "Obstacle.h"
#include "Entities/Characters/Character.h"

#include "Utility/Texture.h"

namespace Entities {
    class Platform : public Obstacle
    {
    private:
        float magicalForce;

    public:
        Platform();
        virtual ~Platform();

        void setMagicalForce(const float mf);
        const float getMagicalForce() const;

        void obstruct(Entities::Character* character) override;
        void save() override;
        void exec() override {}
    };
}