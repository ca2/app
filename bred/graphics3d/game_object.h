// IGameObject.h
#pragma once


#include "bred/graphics3d/scene_object.h"



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


