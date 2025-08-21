// IGameObject.h
#pragma once
#include "bred/graphics3d/_types.h"
#include "bred/graphics3d/scene_object.h"
//#include "SceneFoundry/graphics3d/renderer_i.h"
//#include "SceneFoundry/graphics3d/model_i.h"
//#include <memory>
//#include <optional>



namespace graphics3d
{


    class IGameObject  :
        virtual public scene_object
    {
    public:
        //    virtual ~IGameObject() = default;

        virtual void onInit() {}


    };




} // namespace graphics3d


