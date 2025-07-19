// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 04:11 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "context.h"
#include "engine.h"
#include "scene.h"
#include "acme/parallelization/synchronous_lock.h"
#include "bred/gpu/context.h"
#include "aura/platform/application.h"
#include "bred/user/user/graphics3d.h"


namespace graphics3d
{


   scene::scene()
   {

      m_bInitialized = false;
      m_bLoadedScene = false;

   }


   scene::~scene()
   {


   }


   void scene::on_initialize_scene()
   {

      defer_create_synchronization();

   }


   void scene::initialize_scene(::graphics3d::engine * pengine)
   {

      m_pengine = pengine;

      on_initialize_scene();

   }


   ::gpu::properties & scene::global_ubo()
   {

      return m_propertiesGlobalUbo;

   }


   ::pointer < ::graphics3d::camera > scene::get_default_camera()
   {

      return {};

   }

   
   void scene::defer_load_scene(::gpu::context* pgpucontext)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (!m_bInitialized)
      {

         m_bInitialized = true;

         initialize_scene(pgpucontext->m_pengine);

      }

      if (!m_bLoadedScene)
      {

         on_load_scene(pgpucontext);

         m_bLoadedScene = true;

      }

   }


   void scene::on_load_scene(::gpu::context* pgpucontext)
   {


   }


   void scene::add_object(::graphics3d::scene_object *pobject)
   {

      m_mapObjects[pobject->m_iId] = pobject;

   }


   void scene::on_update_global_ubo(::gpu::context* pgpucontext)
   {



   }


   void scene::on_render(::gpu::context * pgpucontext)
   {


   }


   model<::graphics3d::Vertex> scene::create_tinyobjloader_model(const ::file::path& path)
   {

      auto pmodel = m_pengine->create_tinyobjloader_model(path);

      return pmodel;

   }


   scene_object & scene::tinyobjloader_object(const ::file::path& path)
   {
      
      auto pmodel = create_tinyobjloader_model(path);
      
      auto pobject = __øcreate < ::graphics3d::scene_object>();

      add_object(pobject);

      pobject->m_pmodel = pmodel;

      pobject->m_strPath = path;

      return *pobject;

   }


} // namespace graphics3d



