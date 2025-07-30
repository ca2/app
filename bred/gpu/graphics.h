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


      ::geometry2d::matrix                   m_m1;
      ::pointer < ::gpu::shader >               m_pshaderSourceRectangle;
      ::pointer < ::gpu::shader >               m_pshaderBlendRectangle;
      map < ::draw2d::enum_model, ::pool <::gpu::model_buffer > >   m_mapModelBufferPool;
      ::pointer < ::gpu::shader >         m_pgpushaderTextOut;
      ::pointer < ::gpu::model_buffer >         m_pmodelbufferTextOutDummy;

      pool_group* m_ppoolgroupFrame;

      graphics();
      ~graphics() override;


      void initialize(::particle* pparticle) override;
      bool _is_ok() const override;
      
      void on_begin_draw() override;
      void on_end_draw() override;
      virtual void on_new_frame();
      void gpu_layer_on_before_end_render() override;

      void on_set_gpu_context() override;


      void on_gpu_context_placement_change(const ::int_rectangle & rectanglePlacement) override;

      virtual ::pool <::gpu::model_buffer >& model_buffer_pool(::draw2d::enum_model epool);
      virtual ::gpu::model_buffer * model_buffer(::draw2d::enum_model epool);
      void update_matrix() override;

      virtual ::geometry2d::matrix context_matrix();
      virtual ::geometry2d::matrix context_scale_matrix();


      template < primitive_point POINT >
      POINT& __transform(POINT& p)
      {
         
         m_m1.transform(p);
         
         p.y() = m_pgpucontextCompositor2->m_rectangle.height() - p.y();
         
         return p;

      }


      template < primitive_array POINT_ARRAY >
      POINT_ARRAY& __transform(POINT_ARRAY& a)
      {
         
         for (auto& p : a)__transform(p);

         return a;

      }


      template < primitive_point POINT >
      POINT& context_scale(POINT& p)
      {

         context_scale_matrix().transform(p);

         return p;

      }


      template < primitive_point POINT >
      POINT& context_transform(POINT& p)
      {
         
         context_matrix().transform(p);
         
         return p;

      }


      template < primitive_array POINT_ARRAY >
      POINT_ARRAY& context_transform(POINT_ARRAY& a)
      {

         for (auto& p : a)context_transform(p);

         return a;

      }

    
      ::double_size total_size() override;

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


      using ::draw2d::graphics::get_text_metrics;
      void get_text_metrics(::write_text::text_metric* pmetrics) override;


      void text_out(double x, double yParam, const ::scoped_string& scopedstr) override;


      virtual ::typeface::face* get_face(::write_text::font* pfont);


   };


} // namespace gpu



