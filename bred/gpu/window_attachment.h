// Created by camilo on 2026-08-03 17:33 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/prototype/prototype/pool.h"
#include "apex/gpu/window_attachment.h"
#include "bred/gpu/context_pointer.h"
#include "bred/gpu/post_frame_context_registry.h"



namespace gpu
{


   class CLASS_DECL_BRED window_attachment :
      virtual public ::apex::gpu::window_attachment
   {
   public:


      //::collection::index                                m_iCurrentFrame3 = 0;
      //::collection::index                                m_iCurrentImage = -1;
      //::collection::index                                m_iFrameSerial2 = -1;
      //::collection::count                                m_iFrameCount = 3;



      ::i32                                              m_iLayer;
      ::i32                                              m_iLayerCount;
      //::pointer < layer > m_playerComposing;
      //::array<::comptr<ID3D12Resource>>   m_resourceaSnapshot;
      ::pointer < ::pointer_array < ::gpu::layer > >     m_pgpulayera;



      ::pointer_array < ::gpu::frame_storage >           m_framestoragea;
      ::pointer_array < ::gpu::frame_ephemeral >         m_frameephemerala;
      ::pointer < ::gpu::frame_ephemeral >               m_pframeephemeralStrict;
//      ::pointer < ::gpu::texture >                       m_pgputextureOutput;
      ::pointer_array<::gpu::frame>                      m_framea;

      ::pointer < ::gpu::render_target >                 m_pgpurendertargetRender;
      ::procedure_array                                  m_procedureaOnTopFrameEnd;
      ::pointer_array < pool_group >                     m_poolgroupaFrame;
      ::pointer_array < ::pointer_array < ::particle > > m_particleaFrame;

      ::pointer< ::gpu::context >                        m_pgpucontextWindow;
      ::gpu::context_pointer                             m_pgpucontextDraw2d;
      ::pointer<::gpu::context>                          m_pgpucontextWork;
      using post_frame_context_registry_t =
         ::gpu::post_frame_context_registry<
         ::pointer<::gpu::context>,
         ::pointer<::gpu::layer>>;
      ::pointer < ::graphics3d::engine >                 m_pgraphics3dengine;
      post_frame_context_registry_t                      m_postframecontextregistry;


      class ::time                                       m_timeLast5s;



      window_attachment();
      ~window_attachment() override;


      void initialize_gpu_window_attachment(::acme::windowing::window * pacmewindowingwindow) override;

      virtual ::gpu::render_target * render_target();
      virtual void set_render_target(::gpu::render_target * pgpurendertargetTarget);
      virtual void do_output(::gpu::texture_site * pgputexturesite);

      virtual void present();

      //virtual ::i32 get_frame_index3();
      //virtual ::i32 get_image_index();
      //virtual ::i32 get_frame_count();
      //virtual void restart_frame_counter();
      //virtual bool is_starting_frame()const;




      virtual void start_frame();
      virtual void end_frame();
      virtual void register_frame_context(::gpu::context * pcontext, ::gpu::layer * player);
      virtual void dispatch_post_frame_contexts();

      virtual void on_start_frame();
      virtual void on_end_frame();


      virtual ::gpu::layer * get_previous_layer(::gpu::layer * pgpulayer);


      virtual ::gpu::frame_storage * current_frame_storage();
      virtual ::gpu::frame_ephemeral * current_frame_ephemeral();

      
      static window_attachment * get(::gpu::render_target * pgpurendertarget);
      static window_attachment * get(::gpu::renderer * pgpurenderer);
      static window_attachment * get(::gpu::context * pgpucontext);
      static window_attachment * get(::acme::user::interaction * pacmeuserinteraction);
      static window_attachment * get(::acme::windowing::window * pacmewindowingwindow);


      virtual ::gpu::context * window_context();
      virtual ::gpu::context * draw2d_context();
      virtual ::pointer<::gpu::context> create_work_context();
      virtual ::gpu::context * work_context();


      virtual pool_group * frame_pool_group(::i32 iFrameIndex);
      virtual ::pointer_array<::particle> * frame_particle_array(::i32 iFrameIndex);
      virtual ::gpu::frame * current_frame();

      virtual void start_stacking_layers();
      //virtual void layer_start(renderer * pgpurenderer, const ::i32_rectangle & rectangleHost);
      virtual layer * create_gpu_layer(renderer * pgpurenderer);
      virtual void layer_end();
      virtual layer * current_layer();
      //virtual void layer_merge(context* pcontextTarget);


   };


} // namespace draw2d_direct2d



