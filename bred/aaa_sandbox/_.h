#pragma once


// #include "bred/_.h"
//
// #if defined(_sandbox_project)
// #define CLASS_DECL_SANDBOX  CLASS_DECL_EXPORT
// #else
// #define CLASS_DECL_SANDBOX  CLASS_DECL_IMPORT
// #endif


namespace graphics3d
{


    class ICamera;
    class IGameObject;
    class IRenderer;
    class IProvider;
    class IModel;
    class IAssetProvider;
    class IEntity;
    class IFrame;
    class render_system;
    class scene_object;
   class scene;
    class IWindowInput;


    using scene_object_map = ::map < long long, ::pointer < scene_object > >;


} // namespace graphics3d


#include "bred/graphics3d/_constant.h"
#include "bred/graphics3d/_types.h"



