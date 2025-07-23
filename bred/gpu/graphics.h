// Created by camilo on 2025-05-31 15:27 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/constant/gpu.h"
#include "aura/graphics/draw2d/graphics.h"
#include "bred/gpu/compositor.h"
#include "bred/gpu/context.h"
#include "bred/gpu/device.h"




namespace gpu
{


   class CLASS_DECL_BRED graphics :
      virtual public ::draw2d::graphics,
      virtual public ::gpu::compositor
   {
   public:


      //::pointer < ::gpu::context >           m_pgpucontextDraw2d;
      //::gpu::enum_output                     m_eoutputOnEndDraw;
      //::pointer < ::gpu::context >           m_pgpucontextOutput;
      //::pointer < ::gpu::frame >             m_pgpuframe;
      ::geometry2d::matrix                   m_m1;
      //::pointer < ::draw2d_gpu::end_draw >   m_penddraw;
      ::pointer < ::gpu::shader >               m_pshaderSourceRectangle;
      ::pointer < ::gpu::shader >               m_pshaderBlendRectangle;
      ::pool <::gpu::model_buffer >             m_poolmodelbufferRectangle;
      ::pool <::gpu::model_buffer >             m_poolmodelbufferCharacter;
      ::pool <::gpu::model_buffer >             m_poolmodelbufferLine;
      //int                                       m_iContextHeight;
      ::pointer < ::gpu::shader >         m_pgpushaderTextOut;

      graphics();
      ~graphics() override;


      void initialize(::particle* pparticle) override;
      bool _is_ok() const override;
      
      void on_begin_draw() override;
      void on_end_draw() override;
      void gpu_layer_on_before_end_render() override;

      void on_set_gpu_context() override;


      void update_matrix() override;

      //void start_gpu_layer() override;
      //void end_gpu_layer() override;


      //virtual ::gpu::renderer* end_draw_renderer_output();


      //virtual void create_end_draw();


      // returns true if it is new
     
      ::double_size total_size() override;

         //auto& pmodelbuffer = m_pmodelbufferRectangle;

      //void defer_yield_gpu_context() override;

      //::gpu::context* gpu_context() override;

      //void set_hint_window_output() override;
      virtual ::gpu::shader* rectangle_shader();

      void thread_select() override;

      void _set(const ::geometry2d::matrix& matrix);

      void do_on_context(const ::procedure& procedure) override;

      //template < typename TYPE >
      //void push_on_end_top_frame(::pointer_array < TYPE >& a, const ::pointer < TYPE > & p)
      //{

      //   m_pgpucontextCompositor->m_pgpudevice->m_procedureaOnTopFrameEnd.add(
      //      [this, &a, p]()
      //      {

      //         _synchronous_lock synchronouslock(this->synchronization());

      //         a.add(p);

      //         //      vkDestroyBuffer(logicalDevice, pmodel->m_vertexBuffer, nullptr);
      //         //      vkFreeMemory(logicalDevice, pmodel->m_vertexMemory, nullptr);

      //      });

      //}
 
      ///void create_offscreen_graphics_for_swap_chain_blitting(::user::interaction* puserinteraction, const ::int_size& size = {}) override;
      void create_for_window_draw2d(::user::interaction * puserinteraction, const ::int_size& size) override;
      virtual void defer_create_swap_chain(::user::interaction* puserinteraction);


      virtual void bind_draw2d_compositor(::gpu::layer * player);
      virtual void defer_soft_unbind_draw2d_compositor(::gpu::layer* player);


      virtual void _fill_quad(const ::double_point points[4], const ::color::color& color);

      void fill_rectangle(const ::double_rectangle& rectangle, const ::color::color& color);


      using ::draw2d::graphics::get_text_extent;
      double_size get_text_extent(const ::scoped_string& scopedstr) override;

      void text_out(double x, double yParam, const ::scoped_string& scopedstr) override;


      virtual ::typeface::face* get_face(::write_text::font* pfont);


   };


} // namespace gpu



