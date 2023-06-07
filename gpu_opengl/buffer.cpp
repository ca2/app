#include "framework.h"
#include "buffer.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"


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

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pimage.nok())
      {

         return;

      }

      m_pimage->map();

      glReadBuffer(GL_FRONT);
      
      int cx = m_pimage->m_size.cx();

      int cy = m_pimage->m_size.cy();
      
#if defined(__APPLE__) || defined(ANDROID)
      
      glReadPixels(
         0, 0,
         cx, cy,
         GL_RGBA,
         GL_UNSIGNED_BYTE,
         m_pimage->m_pcolorrefRaw);
      
      //m_pimage->mult_alpha();
      
#else
      
      glReadnPixels(
         0, 0,
         cx, cy,
         GL_BGRA,
         GL_UNSIGNED_BYTE,
         cx * cy * 4,
         m_pimage->m_pcolorrefRaw);

      int iError = glGetError();

      if(iError != 0)
      {

         printf("glReadnPixels error");

      }

      memset(m_pimage->m_pcolorrefRaw, 127, cx * cy * 4 / 8);

#endif
      
      m_pimage->mult_alpha();

   }


   void buffer::gpu_write()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pimage.ok())
      {

         return;

      }

      m_pimage->map();

//      glDrawPixels(
//         m_pimage->m_size.cx(), m_pimage->m_size.cy(),
//         GL_BGRA,
//         GL_UNSIGNED_BYTE,
//         m_pimage->m_pcolorrefRaw);
      
      glTexImage2D(GL_TEXTURE_2D, 0, 0, 0,
                   m_pimage->m_size.cx(), m_pimage->m_size.cy(),
                   GL_RGBA, GL_UNSIGNED_BYTE,
                   m_pimage->m_pcolorrefRaw);

   }


} // namespace opengl



