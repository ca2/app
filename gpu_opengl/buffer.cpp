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

      auto cx = m_pimage->m_size.cx();

      auto cy = m_pimage->m_size.cy();
      
      auto data = m_pimage->m_pimage32Raw;
      
      
      
#if defined(__APPLE__) || defined(ANDROID)

      if(data != nullptr)
      {
         glReadBuffer(GL_FRONT);


         glReadPixels(
                      0, 0,
                      cx, cy,
                      GL_RGBA,
                      GL_UNSIGNED_BYTE,
                      data);
         
      }

      //m_pimage->mult_alpha();

#elif defined(LINUX)
      glReadBuffer(GL_FRONT);
      

      glReadPixels(
         0, 0,
         cx, cy,
         GL_BGRA,
         GL_UNSIGNED_BYTE,
         m_pimage->m_pimage32Raw);
      
      //m_pimage->mult_alpha();
      
#else
      glReadBuffer(GL_FRONT);
      

      glReadnPixels(
         0, 0,
         cx, cy,
         GL_BGRA,
         GL_UNSIGNED_BYTE,
         cx * cy * 4,
         m_pimage->m_pimage32Raw);

      int iError = glGetError();

      if(iError != 0)
      {

         printf("glReadnPixels error");

      }

      //memset(m_pimage->m_pimage32Raw, 127, cx * cy * 4 / 8);

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
//         m_pimage->m_pimage32Raw);
      
      glTexImage2D(GL_TEXTURE_2D, 0, 0, 0,
                   m_pimage->m_size.cx(), m_pimage->m_size.cy(),
                   GL_RGBA, GL_UNSIGNED_BYTE,
                   m_pimage->m_pimage32Raw);

   }


} // namespace opengl



