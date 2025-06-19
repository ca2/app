// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-18 04:03 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/platform/app_consumer.h"
#include "bred/gpu/properties.h"
#include "bred/graphics3d/scene_object.h"


namespace graphics3d
{


   class CLASS_DECL_BRED scene :
      virtual public ::app_consumer < ::aura::application >
   {
   public:


      ::pointer < ::graphics3d::engine >     m_pengine;
      ::pointer < ::user::graphics3d >       m_pusergraphics3d;
      ::string                               m_strName;
      scene_object::map				            m_mapObjects;
      bool                                   m_bInitialized;
      bool                                   m_bLoadedScene;
      ::gpu::properties                      m_propertiesGlobalUbo;


      scene();
      ~scene() override;


      virtual void on_initialize_scene();
      virtual void initialize_scene(::graphics3d::engine * pengine);


      virtual ::gpu::properties & global_ubo();


      virtual ::pointer < ::graphics3d::camera > get_default_camera();

      virtual void defer_load_scene(::gpu::context* pgpucontext);

      virtual void on_load_scene(::gpu::context* pgpucontext);


      //virtual void handle_mouse_move(int x, int y);

      //virtual ::pointer<model> createModelFromFile(::cube::context* pgpucontext, const ::file::path& path);

      virtual void on_update_global_ubo(::gpu::context* pgpucontext);

      virtual void on_render(::gpu::context * pgpucontext);


      virtual ::pointer<::graphics3d::model> create_tinyobjloader_model(const ::file::path& path);
      virtual scene_object & tinyobjloader_object(const ::file::path& path);

      virtual void add_object(::graphics3d::scene_object* pobject);


   };


} // namespace graphics3d



