#pragma once


#include "bred/_.h"
#include "SceneFoundry/sandbox_engine/_.h"


#if defined(_SceneFoundry_sandbox_game_project)
#define CLASS_DECL_APP_GRAPHICS3D_CONTINUUM  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_GRAPHICS3D_CONTINUUM  CLASS_DECL_IMPORT
#endif


namespace app_graphics3d_continuum
{

   class application;
   class pane_impact;
   class document;
   class impact;


   class main_scene;
   class simple_render_system;
   class point_light_system;


   class game_object;


   class game_layer;

   class GlobalUbo;


} // namespace flag






