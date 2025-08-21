//
// Created by camilo on 2025-08-20 06:20 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace sandbox
{


    struct point_light_component
    {

        float lightIntensity = 1.0f;

    };

    struct CLASS_DECL_BRED TransformComponent
    {
        //TransformComponent() = default;
        glm::vec3 translation{};
        glm::vec3 scale{ 1.f };
        glm::vec3 rotation{};

        glm::mat4 mat4() const;
        glm::mat3 normalMatrix() const;

    };


} // namespace sandbox



