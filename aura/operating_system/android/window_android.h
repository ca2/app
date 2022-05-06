#pragma once


class CLASS_DECL_AURA window_android :
   public ::graphics::buffer
{
public:


   //cairo_t *                      m_cairoSource;
   //cairo_surface_t *              m_cairosurfaceSource;
   memory                           m_mem;
   size_i32                             m_size;


   window_android();
   ~window_android() override;


   bool update_buffer(const ::size_i32 & size, int iStride = -1) override;
   void destroy_buffer() override;

   bool update_screen(::image * pimage) override;


};
