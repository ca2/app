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
//#include <glm/glm.hpp>


namespace graphics3d
{


   class CLASS_DECL_BRED scene_object :
      virtual public ::particle
   {
   public:


      ::graphics3d::transform       m_transform;
      long long                           m_llId;
      ::pointer<::graphics3d::IModel>        m_pmodel;
      ::color::color                      m_color;
      //bool m_bIsOBJ{ false };
      //      ::graphics3d::point_light_component m_pointlight;

      ::string m_cubemapTextureName;
      //long long m_llId;
      bool m_bIsSkybox = false;


      scene_object();
      ~scene_object() override;

      virtual ::graphics3d::transform &transform();


      virtual IModel *model();

      virtual void set_model(IModel *);


      virtual void on_update(float deltaTime);

      virtual ::color::color color();
      virtual long long getId();

   };


} // namespace graphics3d
