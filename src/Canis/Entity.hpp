#pragma once
#include <string>
#include "Model.hpp"
#include "Shader.hpp"
#include "Data/Transform.hpp"
#include "Data/GLTexture.hpp"
#include <deque>


namespace Canis
{
    class World;

    struct Entity
    {
        float lifeTime = 0.0f;
        bool active = true;
        std::string name;
        std::string tag;
        Transform transform;
        Model *model;
        Shader *shader;
        glm::vec3 color = glm::vec3(1.0f);
        GLTexture *albedo;
        std::deque<GLTexture> animationTextures;
        float animationSpeed;
        GLTexture *specular;
        void (*Update)(World &_world, Entity &_entity, float _deltaTime) = nullptr;
    };
}