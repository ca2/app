// ICamera.h
#pragma once

#include <glm/glm.hpp>


namespace graphics3d
{
    class ICamera :
        virtual public ::particle
    {
    public:
        //virtual ~ICamera() = default;

        virtual void updateView() {};

        virtual void updateProjection(float aspectRatio, float nearZ = 0.1f, float farZ = 100.f) = 0;

        virtual glm::mat4 getViewMatrix() const = 0;

        virtual glm::mat4 getProjectionMatrix() const = 0;

        virtual glm::vec3 getPosition() const = 0;

        virtual glm::mat4 getInverseViewMatrix() const = 0;
    };
} // namespace graphics3d

