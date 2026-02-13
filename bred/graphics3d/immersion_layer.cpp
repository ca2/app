//
// Created by camilo on 2025-08-22 06:48 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "asset_manager.h"
#include "engine.h"
#include "immersion_layer.h"
#include "scene_base.h"


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


   void immersion_layer::add_scene(::graphics3d::scene_base* pscene)
   {

      m_mapScene[pscene->m_strSceneName] = pscene;

   }


   void immersion_layer::set_current_scene(::graphics3d::scene_base* pscene)
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



   ::pointer < ::graphics3d::scene_base > immersion_layer::create_main_scene()
   {

      return {};


   }


   void immersion_layer::load_camera(const ::property_set & set)
   {

      auto pos = set.get("position", ::float_array_base{0.f, 0.f, 0.f});
      auto rot = set.get("rotation", ::float_array_base{0.f, 0.f});

      m_initialCameraPosition = {pos[0], pos[1], pos[2]};
      m_rotationInitialCamera.set(::degrees(rot[0]), ::degrees(rot[1]));

      m_pscene->m_bInitialCameraLoaded = true;

      information("Camera position: ({}, {}, {}), rotation (deg): ({}, {}, {})", pos[0], pos[1], pos[2], rot[0], rot[1],
                  rot[2]);


   }


   ::pointer<::graphics3d::camera> immersion_layer::allocate_camera()
   {

      auto pcamera = øcreate<::graphics3d::camera>();

      return pcamera;

   }


   void immersion_layer::on_initial_camera_load()
   {

         //{
      auto pcameraLoaded = this->allocate_camera();

         //auto pcameraLoaded = øcreate_new<SandboxCamera>();

         // pcameraLoaded->initialize_SandboxCamera(::floating_sequence3(0.f, 0.f, 3.f));

         pcameraLoaded->m_pengine = m_pengine;

         //         // ::floating_sequence3 camera = ::floating_sequence3(0.0f, 1.0f *m_pengine->m_fYScale, 3.0f);
         //::floating_sequence3 camera = ::floating_sequence3(0.0f, 1.0f, 3.0f);
         //::floating_sequence3 target = ::floating_sequence3(0.0f, 0.0f, 0.0f); // Look at origin
         //// ::floating_sequence3 direction = glm::normalize(target - cameraPos);
         //// camera camera{ ::floating_sequence3(0.0f, 2.0f, -15.0f), -90.0f, 0.0f };
         // auto pcameraDefault = øcreate<SandboxCamera>();
         // pcameraDefault->m_pengine = m_pimmersionlayer->m_pengine;

         // pcamera->m_pimpact = m_pimpact;


         // pcameraDefault->m_pengine = m_pimmersionlayer->m_pengine;

         // pcameraLoaded->m_position = m_initialCameraPosition;

         // pcameraLoaded->m_pitch = m_initialCameraRotation.x;

         // pcameraLoaded->m_yaw = m_initialCameraRotation.y;
         pcameraLoaded->initialize_camera(m_initialCameraPosition, m_rotationInitialCamera);

         m_pscene->set_default_camera(pcameraLoaded);

      //}


   }


   void immersion_layer::on_pre_update_camera()
   {


   }


} // namespace graphics3d



