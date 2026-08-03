// Created by camilo on 2026-07-30 22:40 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/graphics/image/pixmap.h"


namespace windowing
{


   class CLASS_DECL_AURA window_buffer : 
      virtual public ::particle
   {
   public:


      ::pixmap_pointer                          m_ppixmapWindowBuffer;
      ::pointer < ::windowing::window >         m_pwindow;

      //::pixmap_t m_pixmap;

      window_buffer();
      ~window_buffer() override;


      virtual void initialize_window_buffer(::windowing::window * pwindow);


      virtual void destroy_window_buffer();


      virtual bool _create_window_device_context(const ::i32_size & size, ::i32 iStride = -1);
      virtual void _destroy_window_device_context();


      virtual void present_window_buffer();


      virtual void buffer_lock_round_swap_key_buffers();


   };


} // namespace windowing



