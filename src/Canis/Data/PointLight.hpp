#pragma once
#include <glm/glm.hpp>

namespace Canis
{
    struct PointLight
    {
        glm::vec3 position;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        bool flicker;
        float constant;
        float linear;
        float quadratic;
    };
}