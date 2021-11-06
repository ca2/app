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
   virtual ~window_android();


   virtual bool update_buffer(const ::size_i32 & size, int iStride = -1) override;
   virtual void destroy_buffer() override;

   virtual bool update_window(::image * pimage) override;

};
