#include "framework.h"
#include "_.h"


namespace opengl
{


   buffer::buffer()
   {

   }


   buffer::~buffer()
   {

   }


   void buffer::gpu_read()
   {

      if (!::is_ok(m_pimage))
      {

         return;

      }

      glReadBuffer(GL_BACK);
      
      int cx = m_pimage->m_size.cx;

      int cy = m_pimage->m_size.cy;
      
#ifdef __APPLE__
      
      glReadPixels(
         0, 0,
         cx, cy,
         GL_RGBA,
         GL_UNSIGNED_BYTE,
         m_pimage->m_pcolorrefRaw);
      
      //m_pimage->mult_alpha();
      
#else
      
      glReadPixels(
         0, 0,
         cx, cy,
         GL_BGRA,
         GL_UNSIGNED_BYTE,
         m_pimage->m_pcolorrefRaw);

#endif
      
      m_pimage->mult_alpha();

   }


   void buffer::gpu_write()
   {

      if (!::is_ok(m_pimage))
      {

         return;

      }

      glDrawPixels(
         m_pimage->m_size.cx, m_pimage->m_size.cy,
         GL_BGRA, 
         GL_UNSIGNED_BYTE,
         m_pimage->m_pcolorrefRaw);

   }


} // namespace opengl



