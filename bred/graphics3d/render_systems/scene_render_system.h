// Changed by camilo on 2025-12-06 21:36 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/graphics3d/render_systems/pbr_with_ibl_render_system.h"


namespace graphics3d
{


   class CLASS_DECL_BRED scene_render_system : 
      virtual public ::graphics3d::pbr_with_ibl_render_system
   {
   public:


      scene_render_system();
      ~scene_render_system();


      void on_prepare(::gpu::context *pgpucontext) override;

      void on_render(::gpu::context *pgpucontext, ::graphics3d::scene_base *pscene) override;


   };


} // namespace graphics3d



