//
// Changed to a generic scene_object. Scene_object now becomes
// scene_renderable that will be based on scene_object.
// by camilo 2025-09-29 10:37 <3ThomasBorregaardSorensen!!
//
// Created by camilo on 2025-08-20.
//
// IGameObject.h
#pragma once
// #include "SceneFoundry/graphics3d/_types.h"
// #include "bred/graphics3d/scene_object.h"
// //#include "SceneFoundry/graphics3d/renderer_i.h"
// //#include "SceneFoundry/graphics3d/model_i.h"
// //#include <memory>
// #include <optional>
//
#include "bred/gpu/context_object.h"


namespace graphics3d
{


   class CLASS_DECL_BRED scene_object :
      virtual public ::gpu::context_object
   {
   public:


      ::pointer < ::graphics3d::scene_base >      m_pscene;
      //::graphics3d::transform                m_transform;
      //long long                              m_llId;
      //enum_render_system m_erendersystem;
      //::pointer<::graphics3d::renderable>    m_prenderable;
      //::color::color                         m_color;
      //::string                               m_strName;
      //::string                               m_strModel;
      //bool m_bIsOBJ{ false };
      //      ::graphics3d::point_light_component m_pointlight;

      //::string m_cubemapTextureName;
      //long long m_llId;
      //bool m_bIsSkybox = false;
      //::string m_strRenderablePath;


      scene_object();
      ~scene_object() override;


      virtual void initialize_scene_object(::graphics3d::scene_base * pscene);


      //virtual ::graphics3d::transform &transform();


      //virtual ::graphics3d::renderable *renderable();

      //virtual void set_renderable(::graphics3d::renderable * prenderable);


      //virtual void on_update(float deltaTime);

      //virtual ::color::color color();
      //virtual long long getId();


      //virtual void translate(const floating_sequence3 & floating_sequence3);
      //virtual void scale(const floating_sequence3 & floating_sequence3);


   };


} // namespace graphics3d
