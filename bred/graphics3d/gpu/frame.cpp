// Created by camilo on 2025-05-19 22:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "command_buffer.h"
#include "context.h"
#include "frame.h"
#include "render_target.h"
#include "renderer.h"


namespace gpu
{


   frame::frame()
   {

   }


   frame::~frame()
   {


   }


   void frame::initialize_frame()
   {

   }


   ::gpu::context* frame::gpu_context()
   {

      return m_pgpucommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext;

   }


   thread_local ::gpu::frame* t_pgpuframe;


   void set_current_frame(::gpu::frame* pgpuframe)
   {

      t_pgpuframe = pgpuframe;


   }
   ::gpu::frame* current_frame()
   {

      return t_pgpuframe;

   }


}  // namespace gpu


