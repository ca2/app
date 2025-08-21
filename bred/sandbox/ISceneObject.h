//
// Created by camilo on 2025-08-20.
//
// IGameObject.h
#pragma once
// #include "SceneFoundry/sandbox/_types.h"
// #include "bred/graphics3d/ISceneObject.h"
// //#include "SceneFoundry/sandbox/renderer_i.h"
// //#include "SceneFoundry/sandbox/model_i.h"
// //#include <memory>
// #include <optional>
#include <glm/glm.hpp>


namespace sandbox
{


    class ISceneObject  :
        virtual public ::particle
    {
    public:
        //    virtual ~IGameObject() = default;

        virtual ::sandbox::TransformComponent& getTransform() = 0;
        virtual IModel * getModel() const = 0;

        virtual glm::vec3 getColor() const { return glm::vec3(1.f); }
        virtual const ::sandbox::point_light_component  * getPointLight() const {return nullptr;}
        virtual long long getId() const { return 0; }

    };




} // namespace sandbox


