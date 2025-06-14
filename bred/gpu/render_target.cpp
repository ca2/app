// Created by camilo on 2025-06-12 12:38 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "renderer.h"
#include "render_target.h"


namespace gpu
{


   //class CLASS_DECL_BRED render_target :
   //   virtual public ::particle
   //{
   //public:


   render_target::render_target()
   {


   }


   render_target::~render_target()
   {


   }


   void render_target::initialize_render_target(::gpu::renderer* pgpurenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous)
   {

      m_pgpurenderer = pgpurenderer;
      m_size = size;
      m_prendertargetviewOld = previous;

   }


   void render_target::init()
   {


   }


   texture * render_target::current_texture()
   {

      auto iFrameIndex = m_pgpurenderer->get_frame_index();

      auto size = m_texturea.size();

      return m_texturea[iFrameIndex];

   }


   void render_target::on_before_begin_draw_frame(::draw2d_gpu::graphics* pgraphics)
   {


   }


   void render_target::on_after_end_draw_frame(::draw2d_gpu::graphics* pgraphics)
   {


   }


} // namespace gpu



