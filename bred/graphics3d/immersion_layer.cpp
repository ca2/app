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



   void immersion_layer::initialize_immersion_layer(::graphics3d::engine * pengine, ::graphics3d::asset_manager * passetmanager)
   {


      m_pengine = pengine;
      m_passetmanager = passetmanager;

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


   ::pointer < ::graphics3d::scene > immersion_layer::create_main_scene()
   {

      return {};


   }


} // namespace graphics3d



