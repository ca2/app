#pragma once


#include "graphics.h"


namespace graphics
{


   class CLASS_DECL_AURA double_buffer :
      virtual public graphics
   {
   public:


      int                           m_iGoodStride;
      //::image_pointer               m_imageaBuffer[2];
      //::pointer_array < ::mutex >   m_mutexa;
      //bool                          m_bSingleBufferMode;


      bool                          m_bDibIsHostingBuffer;


      int                           m_iCurrentBuffer;


      double_buffer();
      ~double_buffer() override;


      void initialize_graphics_graphics(::user::interaction_impl * pimpl) override;


      bool is_single_buffer_mode() const override;


      bool buffer_lock_round_swap_key_buffers() override;

      // synchronous_lock buffer synchronization first...
      buffer_item * get_buffer_item() override;
      //::particle * get_buffer_sync() override;
      //::image_pointer & get_buffer_image() override;

      // synchronous_lock screen synchronization first...
      buffer_item * get_screen_item() override;
      //virtual ::particle * get_screen_sync() override;
      //virtual ::image_pointer & get_screen_image() override;


      ::collection::index get_buffer_index() const;
      ::collection::index get_screen_index() const;

      using graphics::update_screen;
      bool update_screen() override;

      //::particle * get_draw_lock() override;
      bool _on_begin_draw(buffer_item * pbufferitem) override;


      void destroy_buffer() override;


   };


} // namespace graphics



