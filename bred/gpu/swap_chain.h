// Created by camilo on 2025-06-10 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/windowing/window.h"
#include "bred/gpu/context_pointer.h"


namespace gpu
{


   class CLASS_DECL_BRED swap_chain :
      virtual public ::acme::windowing::gpu_context_render_frame
   {
   public:


      ::collection::index                                m_iSwapSeed;
      ::collection::index                                m_iCurrentSwapSerial;
      bool                                               m_bWindowInitialized;
      bool                                               m_bSwapChainInitialized;

      ::gpu::context_pointer                       m_pgpucontext;
      ::pointer < ::gpu::renderer >                      m_pgpurenderer;
      ::pointer < ::windowing::window >                  m_pwindowSwapChain;
      ::i32                                                m_iSwapChainIndex;

      ::pointer < ::pointer_array < ::gpu::texture > >   m_ptextureaSwapChain;
      ::i32                                                m_iCurrentSwapChainFrame;
      ::i32                                                m_iCurrentSwapChainImage;
      ::pointer_array<::gpu::semaphore>                  m_gpusemaphoreaWait;

      
      struct frame_sync
      {
         // VkFence                                m_vkfenceInFlight = VK_NULL_HANDLE;
         // VkSemaphore                            m_vksemaphoreImageAvailable = VK_NULL_HANDLE;
         // VkSemaphore                            m_vksemaphoreRenderFinished = VK_NULL_HANDLE;
         ::pointer<::gpu::fence> m_pgpufenceInFlight;
         ::pointer<::gpu::semaphore> m_pgpusemaphoreImageAvailable;
         ::pointer<::gpu::semaphore> m_pgpusemaphoreRenderFinished;
         ::pointer<::gpu::command_buffer> m_pcommandbufferLastSwapChainPresentation;
      };

      ::array_base<frame_sync> m_framesynca;


      swap_chain();
      ~swap_chain() override;


      virtual void on_new_frame();


      virtual void create_images();

      virtual void defer_check_swap_chain();

      virtual void on_new_swap_chain();

      virtual void initialize_swap_chain_window(::gpu::context * pcontext, ::acme::windowing::window* pwindow);
      virtual void initialize_gpu_swap_chain(::gpu::renderer * pgpurenderer);

      //virtual void endDraw(::gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* prendererSrc);
      //virtual void present(::gpu::texture * pgputexture);
      virtual void present(::gpu::texture * pgputexture, ::gpu::command_buffer * pgpucommandbuffer);
      virtual void set_present_state(::gpu::command_buffer *pgpucommandbuffer);
      virtual void swap_buffers();
      virtual ::i32 swap_chain_frame_index();
      virtual ::i32 swap_chain_image_index();
      virtual ::i32 swap_chain_frame_count();
      virtual ::gpu::texture* current_swap_chain_texture();

      void on_gpu_context_render_frame(::i32 w, ::i32 h) override;

            virtual bool create_frame_sync(frame_sync &frame);
      virtual void destroy_frame_sync(frame_sync &frame);

      virtual frame_sync &frame(::collection::index iFrameIndex);


   };


} // namespace gpu



