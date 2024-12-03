#pragma once


#include "graphics.h"


namespace graphics
{


   class CLASS_DECL_AURA buffer :
      virtual public graphics
   {
   public:


      int                           m_iGoodStride;
      ::image::image_pointer               m_pimageBuffer;

      bool                          m_bDibIsHostingBuffer;


      buffer();
      ~buffer() override;


      //virtual ::particle * get_draw_lock() override;
      bool _on_begin_draw(buffer_item * pbufferitem) override;
      virtual void update_screen() override;
      virtual bool buffer_lock_round_swap_key_buffers() override;


      virtual bool update_buffer(buffer_item * pitem) override;
      virtual void destroy_buffer() override;
      virtual ::int_size buffer_size();

//
      //virtual bool update_screen() override;
      virtual bool is_buffer_ok();
      ::image::image_pointer & get_buffer();

      //virtual ::image::image_pointer & get_screen_image() override;
      //virtual ::particle * get_screen_sync() override;


   };


} // namespace graphics



