// Created by camilo on 2025-05-16 22:45 <3ThomasBorregaardSorensen!!
#pragma once


#include "_constant.h"


namespace graphics3d
{


   class container;


   class engine;

   class engine;

   //template<typename TYPE>
   //class model;



   template<typename VERTEX>
   class model_instance;
   //class context;

   class scene;
   class scene_object;

   class input;
   class camera;

   class render_system;
   //class shader;

   //class simple_render_system;
   //class point_light_system;

   //class renderer;
   class asset_manager;

   class scene;
   class frame;
   class skybox;
   class renderable;

   class immersion_layer;
   class point_light;


   using scene_object_map = ::string_map<::pointer<scene_object>>;
   using skybox_map = ::string_map<::pointer<skybox>>;

   
   class gltf_render_system;
   class wavefront_obj_render_system;
   class point_light_render_system;
   class scene_render_system;
   class skybox_ibl_render_system;
   class skybox_render_system;


} // namespace graphics3d


#include "_types.h"
