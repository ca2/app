// Created by camilo on 2026-07-30 23:28 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "window_buffer.h"
#include "window.h"


namespace windowing
{
   

   window_buffer::window_buffer()
   {


   }

   
   window_buffer::~window_buffer()
   {


   }

   
   void window_buffer::initialize_window_buffer(::windowing::window * pwindow)
   {

      m_pwindow = pwindow;

   }


   void window_buffer::destroy_window_buffer()
   {

      m_ppixmapWindowBuffer.release();

   }


   bool window_buffer::_create_window_device_context(const ::i32_size & size, ::i32 iStride)
   {

      return false;

   }


   void window_buffer::_destroy_window_device_context()
   {



   }


   void window_buffer::present_window_buffer()
   {


   }


   void window_buffer::buffer_lock_round_swap_key_buffers()
   {


   }


} // namespace windowing
