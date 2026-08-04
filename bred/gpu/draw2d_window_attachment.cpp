// Created by camilo on 2026-08-03 17:37 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "bred_approach.h"
#include "context.h"
#include "device.h"
#include "frame.h"
#include "frame_ephemeral.h"
#include "frame_storage.h"
#include "layer.h"
#include "renderer.h"
#include "render_target.h"
#include "draw2d_window_attachment.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/windowing/window.h"


#ifdef WINDOWS_DESKTOP
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#endif


namespace gpu
{


   draw2d_window_attachment::draw2d_window_attachment()
   {

      m_iCurrentImage = 0;

   }


   draw2d_window_attachment::~draw2d_window_attachment()
   {


   }


   void draw2d_window_attachment::initialize_window_attachment(::windowing::window * pwindow)
   {

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {
         //::direct2d::get() -> d2d1_factory1()->CreateHwndRenderTarget(rendertargetproperties,
           // hwndrendertargetproperties)
      }

      if (m_papplication->m_bGpu)
      {

         auto pgpuapproach = m_papplication->get_gpu_approach();

         //pgpuapproach->gpu_on_create_window(pwindow);

         ::string strType;

         strType = ::type(pwindow->m_pacmeuserinteraction).name();

         const_char_pointer pszType = strType.c_str();

         information("gpu::approach::gpu_on_create_window for type {}", pszType);

         auto pgpudevice = pgpuapproach->get_gpu_device(pwindow);

         m_pgpucontextWindow = pgpudevice->allocate_gpu_context();

         ::gpu::enum_output eoutput = ::gpu::e_output_none;

         if (m_papplication->m_gpu.m_bUseSwapChainWindow)
         {

            eoutput = ::gpu::e_output_swap_chain;

         }
         else
         {

            eoutput = ::gpu::e_output_gpu_buffer;

         }

         auto sizeWindow = pwindow->m_sizeWindow;

         ::gpu::enum_scene escene = ::gpu::e_scene_2d;

         m_pgpucontextWindow->create_window_gpu_context(pgpudevice, eoutput, escene, pwindow, sizeWindow);

         //::cast<::gpu_opengl::approach> papproach = m_papplication->get_gpu_approach();
         //_gpu_on_create_window(pacmewindowingwindow);
         //::draw2d_gpu::draw2d::on_create_window(pwindowParam);


         //void approach::_gpu_on_create_window(::acme::windowing::window * pwindowParam)
         //{

            #if defined(WINDOWS_DESKTOP)



            auto hwnd= ::as_HWND(pwindow->operating_system_window());

            //auto pHWND = pwin32window->_HWND();

            //opengl_on_create_window(hwnd, (HINSTANCE) ::system()->m_hinstanceThis);

            DWM_BLURBEHIND bb = { 0 };
            HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
            bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
            bb.hRgnBlur = hRgn;
            bb.fEnable = TRUE;
            DwmEnableBlurBehindWindow((HWND)hwnd, &bb);

            #endif

//         }

         //::cast < ::windowing_win32::window > pwindow = pwindowParam;

         // auto hwnd = pwindow->m_hwnd;

         // HRGN hRgn = CreateRectRgn(0, 0, -1, -1);
         // bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
         // bb.hRgnBlur = hRgn;
         // bb.fEnable = TRUE;
         // DwmEnableBlurBehindWindow(hwnd, &bb);


      }

   }



   ::gpu::context * draw2d_window_attachment::window_context()
   {

      return m_pgpucontextWindow;

      //if(!m_pgpucontextMainWindow)
      //{

      //   ::cast < ::user::interaction > puserinteractionMain = m_pacmeuserinteractionMain;

      //   auto pwindowMain = puserinteractionMain->window();

      //   m_pgpucontextMainWindow = create_window_context(pwindowMain);

      //}

      //return m_pgpucontextMainWindow;

   }


   ::gpu::context * draw2d_window_attachment::draw2d_context()
   {

      if (!m_pgpucontextDraw2d)
      {

         constructø(m_pgpucontextDraw2d);

         m_pgpucontextDraw2d->m_etype = ::gpu::context::e_type_draw2d;

         m_pgpucontextDraw2d->m_eoutput = ::gpu::e_output_gpu_buffer;

         m_pgpucontextDraw2d->m_pgpudevice = m_pgpucontextWindow->m_pgpudevice;

         auto pacmeuserinteractionMain = m_papplication->main_acme_user_interaction();

         ::cast < ::user::interaction > puserinteraction = pacmeuserinteractionMain;

         if (!m_pgpucontextDraw2d->m_itask
            && puserinteraction->m_pacmewindowingwindow)
         {

            m_pgpucontextDraw2d->branch_synchronously();

            m_pgpucontextDraw2d->sendø() << [this, puserinteraction]()
               {

                  auto pinteraction = (::user::interaction *)puserinteraction.m_p;

                  auto eoutput = m_pgpucontextDraw2d->m_eoutput;

                  auto pwindow = pinteraction->window();

                  auto size = pwindow->get_window_rectangle().size();

                  //<<<<<<< HEAD
                  //                  m_pgpucontextMainDraw2d->create_draw2d_context(
                  //=======
                  m_pgpucontextDraw2d->create_draw2d_gpu_context(
//>>>>>>> origin/main
m_pgpucontextWindow->m_pgpudevice,
pwindow,
size
);

                  //m_pgpucontextMainDraw2d->initialize_gpu_context(
                  //   this,
                  //   eoutput,
                  //   pwindow,
                  //   size
                  //);

               };

         }

      }

      return m_pgpucontextDraw2d;

   }


   ::pointer<::gpu::context> draw2d_window_attachment::create_work_context()
   {

      auto pgpucontext = createø<::gpu::context>();

      pgpucontext->m_etype = ::gpu::context::e_type_generic;

      pgpucontext->m_eoutput = ::gpu::e_output_none;

      pgpucontext->m_escene = ::gpu::e_scene_3d;

      pgpucontext->m_pgpudevice = m_pgpucontextWindow->m_pgpudevice;

      auto pacmeuserinteractionMain = m_papplication->main_acme_user_interaction();

      ::cast<::user::interaction> puserinteraction = pacmeuserinteractionMain;

      if (!pgpucontext->m_itask && puserinteraction->m_pacmewindowingwindow)
      {

         pgpucontext->branch_synchronously();

         pgpucontext->sendø() << [this, puserinteraction, pgpucontext]()
            {

               auto pinteraction = (::user::interaction *)puserinteraction.m_p;

               auto eoutput = pgpucontext->m_eoutput;

               auto escene = pgpucontext->m_escene;

               auto pwindow = pinteraction->window();

               auto size = pwindow->get_window_rectangle().size();

               pgpucontext->create_gpu_context(m_pgpucontextWindow->m_pgpudevice, eoutput, escene, pwindow, size);

            };

      }

      return pgpucontext;

   }


   ::gpu::context * draw2d_window_attachment::work_context()
   {

      if (!m_pgpucontextWork)
      {

         m_pgpucontextWork = create_work_context();

      }

      return m_pgpucontextWork;

   }

   ::gpu::frame * draw2d_window_attachment::current_frame()
   {

      _synchronous_lock lock(this->synchronization());

      auto iFrameIndex = get_frame_index3();

      auto & pframe = m_framea.atø(iFrameIndex);

      if (defer_construct_newø(pframe))
      {

         pframe->initialize_gpu_frame();

      }

      return pframe;


   }


   void draw2d_window_attachment::register_frame_context(::gpu::context * pcontext, ::gpu::layer * player)
   {

      _synchronous_lock lock(this->synchronization());

      m_postframecontextregistry.register_context(pcontext, player);

   }


   void draw2d_window_attachment::dispatch_post_frame_contexts()
   {

      post_frame_context_registry_t::entry_array entrya;
      ::pointer<::gpu::context> pcontextMain;

      {

         _synchronous_lock lock(this->synchronization());

         entrya = m_postframecontextregistry.take_entries();
         pcontextMain = m_pgpucontextWindow;

      }

      post_frame_context_registry_t::dispatch(
         std::move(entrya),
         pcontextMain,
         []()
         {

            return ::pointer<::gpu::layer>(::gpu::current_layer());

         },
         [](const ::pointer<::gpu::layer> & player)
         {

            ::gpu::set_current_layer(player);

         },
         [](const ::pointer<::gpu::context> & pcontext)
         {

            pcontext->on_end_frame();

         });

   }


   frame_storage * draw2d_window_attachment::current_frame_storage()
   {

      return m_framestoragea.atø(m_iCurrentFrame3);

   }


   ::gpu::frame_ephemeral * draw2d_window_attachment::current_frame_ephemeral()
   {

      return m_frameephemerala.atø(m_iCurrentFrame3);

   }




   void draw2d_window_attachment::on_start_frame()
   {

   }


   void draw2d_window_attachment::on_end_frame()
   {

      {

         _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         auto procedureaOnTopFrameEnd = ::transfer(m_procedureaOnTopFrameEnd);

         for (auto & procedure : procedureaOnTopFrameEnd)
         {

            procedure();
         }
      }

      auto pframestorage = current_frame_storage();

      if (::is_set(pframestorage))
      {

         try
         {

            pframestorage->on_end_frame();
         }
         catch (...)
         {
         }
      }

      if (m_timeLast5s.elapsed() > 5_s)
      {

         m_timeLast5s.Now();

         m_papplication->post(
            [this]()
            {
               m_pgpucontextWindow->m_pgpudevice->manage_retired_objects();
            });
      }
   }



   void draw2d_window_attachment::start_stacking_layers()
   {

      m_iLayerCount = 0;

   }


   layer * draw2d_window_attachment::create_gpu_layer(renderer * pgpurenderer)
   {

      m_iLayer = m_iLayerCount;
      m_iLayerCount++;

      defer_construct_newø(m_pgpulayera);

      auto & player = m_pgpulayera->element_at_grow(m_iLayer);

      defer_constructø(player);

      auto iFrameIndex = get_frame_index3();

      player->initialize_gpu_layer(pgpurenderer, iFrameIndex, m_iLayer);

      pgpurenderer->defer_update_renderer();

      //if (pgpurenderer->m_pgpurendertarget)
      //{

      //   player->m_pgputextureSource = pgpurenderer->m_pgpurendertarget->current_texture();

      //}

      return player;

   }


   void draw2d_window_attachment::layer_end()
   {

      auto & layera = *m_pgpulayera;

      auto & player = layera[m_iLayer];

      player->layer_end();
      //player->take_snapshot();

      //return pgpulayer->texture()->m_pgpurenderer->m_pgpucontext->rectangle();

   }


   layer * draw2d_window_attachment::current_layer()
   {

      if (m_iLayer < 0 || m_iLayer >= m_pgpulayera->get_count())
      {

         throw ::exception(error_wrong_state);

      }

      auto & layera = *m_pgpulayera;

      auto & player = layera[m_iLayer];

      return player;

   }

   void draw2d_window_attachment::start_frame()
   {

      {

         _synchronous_lock lock(this->synchronization());

         m_postframecontextregistry.clear();

      }

      start_stacking_layers();

      m_iFrameSerial2++;

      m_pgpucontextWindow->on_new_frame();

      // m_iCurrentFrame3 = (m_iCurrentFrame3 + 1) % iFrameCount;

      auto & pframestorage = m_framestoragea.atø(m_iCurrentFrame3);

      if (!pframestorage)
      {

         constructø(pframestorage);

         pframestorage->initialize_gpu_frame_storage(m_pgpucontextWindow->m_pgpudevice);

      }

      pframestorage->m_iBuffer = 0;

      pframestorage->m_iBufferOffset = 0;

      auto & pframeephemeral = m_frameephemerala.atø(m_iCurrentFrame3);

      constructø(pframeephemeral);

      _synchronous_lock lock(this->synchronization());

      auto pframe = current_frame();

      pframe->start_frame();

   }


   bool draw2d_window_attachment::is_starting_frame()const
   {

      return m_iFrameSerial2 == m_iCurrentFrame3;

   }


   void draw2d_window_attachment::restart_frame_counter()
   {

      if (this->get_frame_count() > 1)
      {

         m_iCurrentFrame3 = 0;
         m_iFrameSerial2 = -1;

         //m_pgpurenderer->m_prenderstate->on_happening(e_happening_reset_frame_counter);

      }

   }




   ::i32 draw2d_window_attachment::get_frame_index3()
   {

      auto iFrameCount = this->get_frame_count();

      if (iFrameCount > 1)
      {

         return (::i32)(m_iCurrentFrame3 % iFrameCount);

      }
      else
      {

         return 0;

      }

   }


   ::i32 draw2d_window_attachment::get_image_index()
   {

      if (this->get_frame_count() > 1)
      {

         return (::i32)m_iCurrentImage;
      }
      else
      {

         return 0;
      }

   }


   ::i32 draw2d_window_attachment::get_frame_count()
   {

      return (::i32)m_iFrameCount;

   }




   pool_group * draw2d_window_attachment::frame_pool_group(::i32 iFrameIndex)
   {

      auto & ppoolgroupFrame = m_poolgroupaFrame.element_at_grow(iFrameIndex);

      defer_construct_newø(ppoolgroupFrame);

      ppoolgroupFrame->m_pallocator = this;

      return ppoolgroupFrame;

   }


   ::pointer_array<::particle > * draw2d_window_attachment::frame_particle_array(::i32 iFrameIndex)
   {

      auto & pparticleaFrame = m_particleaFrame.element_at_grow(iFrameIndex);

      if (!pparticleaFrame)
      {

         construct_newø(pparticleaFrame);

      }

      return pparticleaFrame;

   }



   ::gpu::layer * draw2d_window_attachment::get_previous_layer(::gpu::layer * pgpulayer)
   {

      if (!m_pgpulayera)
      {

         return nullptr;

      }

      auto iFind = m_pgpulayera->find_first(pgpulayer);

      if (iFind <= 0)
      {

         return nullptr;

      }

      for (::i32 i = (::i32)iFind - 1; i >= 0; i--)
      {

         if (m_pgpulayera->element_at(i)->m_pgpurenderer == pgpulayer->m_pgpurenderer)
         {

            return m_pgpulayera->element_at(i);

         }

      }

      return nullptr;

   }



   void draw2d_window_attachment::end_frame()
   {

      on_end_frame();

      {

         _synchronous_lock lock(this->synchronization());

         auto pframe = current_frame();

         pframe->end_frame();

      }

      dispatch_post_frame_contexts();

   }


   draw2d_window_attachment * draw2d_window_attachment::get(::gpu::render_target * pgpurendertarget)
   {

      if (::is_null(pgpurendertarget))
      {

         return nullptr;

      }

      auto pgpurenderer = pgpurendertarget->m_pgpurenderer;

      if (::is_null(pgpurenderer))
      {

         return nullptr;

      }

      return ::gpu::draw2d_window_attachment::get(pgpurenderer);

   }


   draw2d_window_attachment * draw2d_window_attachment::get(::gpu::renderer * pgpurenderer)
   {

      if (::is_null(pgpurenderer))
      {

         return nullptr;

      }

      auto pgpucontext = pgpurenderer->m_pgpucontext;

      if (::is_null(pgpucontext))
      {

         return nullptr;

      }

      return ::gpu::draw2d_window_attachment::get(pgpucontext);

   }


   draw2d_window_attachment * draw2d_window_attachment::get(::gpu::context * pgpucontext)
   {

      if (::is_null(pgpucontext))
      {

         return nullptr;

      }

      auto pacmeuserinteractionAffinity = pgpucontext->m_pacmeuserinteractionAffinity;

      if (::is_null(pacmeuserinteractionAffinity))
      {

         return nullptr;

      }

      return ::gpu::draw2d_window_attachment::get(pacmeuserinteractionAffinity);

   }


   ::gpu::draw2d_window_attachment * draw2d_window_attachment::get(::acme::user::interaction * pacmeuserinteraction)
   {

      if (::is_null(pacmeuserinteraction))
      {

         return nullptr;

      }

      auto pacmewindowingwindow = pacmeuserinteraction->acme_windowing_window();

      if (::is_null(pacmewindowingwindow))
      {

         return nullptr;

      }

      return ::gpu::draw2d_window_attachment::get(pacmewindowingwindow);

   }


   ::gpu::draw2d_window_attachment * draw2d_window_attachment::get(::acme::windowing::window * pacmewindowingwindow)
   {

      if (::is_null(pacmewindowingwindow))
      {

         return nullptr;

      }

      ::cast < ::windowing::window > pwindow = pacmewindowingwindow;

      if (!pwindow)
      {

         return nullptr;

      }

      ::cast< ::gpu::draw2d_window_attachment > pgpudraw2dwindowattachment = pwindow->m_pdraw2dwindowattachment;

      if (!pgpudraw2dwindowattachment)
      {

         return nullptr;

      }

      return pgpudraw2dwindowattachment;

   }


} // namespace draw2d_direct2d



