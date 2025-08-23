#pragma once



//#include "graphics3d/device.h"
#include "bred/graphics3d/immersion_layer.h"
//#include "bred/graphics3d/window_input.h"
//#include "bred/graphics3d/renderer.h"
#include "bred/graphics3d/engine.h"
//#include "SceneFoundry/sandbox_game/player.h"
//#include "SceneFoundry/sandbox_game/scene.h"
//#include <iostream>
//#include <memory>

namespace prodevian
{


   class CLASS_DECL_BRED immersion :
      virtual public ::graphics3d::immersion_layer
   {
   public:


      //::pointer<::graphics3d::IScene> m_pscene;
      //::pointer<::graphics3d::IWindowInput> m_pwindowinput;
      ::pointer < graphics3d::asset_manager > m_passetmanager;


      immersion();
      ~immersion() override;


      //void initialize_immersion_layer(::graphics3d::IWindowInput * pinput, ::graphics3d::asset_manager & assets);

      void initialize_immersion_layer(::graphics3d::engine * pengine, ::graphics3d::asset_manager * passetmanager) override;

      void on_initialize_immersion_layer() override;
      //void onInit() override;
      //void onUpdate(float dt) override;

      //::graphics3d::IScene& getSceneInterface() override;

      virtual ::pointer < ::graphics3d::scene > create_main_scene();

      template < typename SCENE >
      ::pointer < SCENE> create_scene(const ::scoped_string& scopedstrName)
      {

         auto pscene = øcreate_new < SCENE>();

         pscene->m_strSceneName = scopedstrName;

         //pscene->initialize_scene(m_pengine);

         pscene->m_pengine = m_pengine;

         m_pengine->m_pimmersionlayer->add_scene(pscene);

         return pscene;

      }


   ///private:

   };


} // namespace sandbox_game


