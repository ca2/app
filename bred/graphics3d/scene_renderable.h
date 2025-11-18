//
// Created by camilo on 2025-09-29 10:34 <3ThomasBorregaardSorensen!!
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
#include "bred/graphics3d/renderable.h"
#include "bred/graphics3d/scene_object.h"


namespace graphics3d
{


   class CLASS_DECL_BRED scene_renderable :
      virtual public ::graphics3d::scene_object,
      virtual public ::graphics3d::renderable
   {
   public:


      ::graphics3d::transform m_transform;
      long long m_llId;
      enum_render_system m_erendersystem;
      ::pointer<::graphics3d::renderable> m_prenderable;
      ::color::color m_color;
      //::string m_strName;
      ::string m_strModel;
      // bool m_bIsOBJ{ false };
      //       ::graphics3d::point_light_component m_pointlight;

      //::string m_cubemapTextureName;
      // long long m_llId;
      // bool m_bIsSkybox = false;
      ::string m_strRenderablePath;


      scene_renderable();
      ~scene_renderable() override;


      virtual void initialize_scene_renderable(::graphics3d::scene_base *pscene);


      virtual ::graphics3d::transform &transform();


      virtual ::graphics3d::renderable *renderable();

      virtual void set_renderable(::graphics3d::renderable *prenderable);


      virtual void on_update(float deltaTime);

      virtual ::color::color color();
      virtual long long getId();


      virtual void translate(const ::floating_sequence3 &floating_sequence3);
      virtual void scale(const ::floating_sequence3 &floating_sequence3);
   };


} // namespace graphics3d
