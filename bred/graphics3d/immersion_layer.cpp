//
// Created by camilo on 2025-08-22 06:48 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "immersion_layer.h"
#include "scene.h"
#include "bred/graphics3d/engine.h"


namespace graphics3d
{


   immersion_layer::immersion_layer()
   {


   }


   immersion_layer::~immersion_layer()
   {


   }



   void immersion_layer::initialize_immersion_layer(::graphics3d::engine * pengine)
   {

      m_pengine = pengine;

      øconstruct_new(m_passetmanager);

      m_passetmanager->initialize_asset_manager(m_pengine);

   }


   void immersion_layer::on_initialize_immersion_layer()
   {


   }


   void immersion_layer::add_scene(::graphics3d::scene* pscene)
   {

      m_mapScene[pscene->m_strSceneName] = pscene;

   }


   void immersion_layer::set_current_scene(::graphics3d::scene* pscene)
   {

      m_pscene = pscene;

   }


   ::graphics3d::camera * immersion_layer::camera()
   {

      return m_pcamera;

   }


   ::graphics3d::asset_manager * immersion_layer::asset_manager()
   {

      return m_passetmanager;

   }



   ::pointer < ::graphics3d::scene > immersion_layer::create_main_scene()
   {

      return {};


   }


   void immersion_layer::load_camera(const ::property_set & set)
   {


   }


   void immersion_layer::on_initial_camera_load()
   {


   }


   void immersion_layer::on_pre_update_camera()
   {


   }


} // namespace graphics3d



