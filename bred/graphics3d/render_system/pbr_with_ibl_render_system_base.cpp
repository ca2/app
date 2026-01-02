#include "framework.h"
#include "pbr_with_ibl_render_system_base.h"
#include "bred/gpu/context.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/renderer.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/types.h"


namespace graphics3d
{



   pbr_with_ibl_render_system_base::pbr_with_ibl_render_system_base()
   {


   }


   pbr_with_ibl_render_system_base::~pbr_with_ibl_render_system_base() 
   {


   }



      ::graphics3d::scene_renderable *pbr_with_ibl_render_system_base::current_scene_renderable() 
      {
         
         return m_pscenerenderableCurrent; 
      
      }




   void pbr_with_ibl_render_system_base::on_prepare(::gpu::context *pgpucontext)
   {


   }


   void pbr_with_ibl_render_system_base::on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
   {


   }


} // namespace graphics3d



