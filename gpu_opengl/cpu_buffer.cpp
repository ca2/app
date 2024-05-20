#include "framework.h"
#include "cpu_buffer.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"


namespace opengl
{


   cpu_buffer::cpu_buffer()
   {

   }


   cpu_buffer::~cpu_buffer()
   {

   }


   void cpu_buffer::gpu_read()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_pixmap.nok())
      {

         return;

      }

      //m_pixmap.map();

      auto cx = m_pixmap.m_size.cx();

      auto cy = m_pixmap.m_size.cy();

      //auto sizeNeeded = cx * cy * 4;

      //m_pixmap.create(m_memory, sizeNeeded);
      
      auto data = m_memory.data();
      
#if defined(__APPLE__) || defined(ANDROID)

      if(data != nullptr)
      {
         glReadBuffer(GL_FRONT);

//if(0)
{
   glReadPixels(
                0, 0,
                cx, cy,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                data);
   
}
         
      }

      //m_pixmap.mult_alpha();
      information() << "after glReadPixels cx,cy : " << cx << ", " << cy;
      
      //::memory_set(m_pixmap.m_pimage32Raw, 127, cx * cy * 4);

#elif defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
      glReadBuffer(GL_FRONT);
      

      glReadPixels(
         0, 0,
         cx, cy,
         GL_BGRA,
         GL_UNSIGNED_BYTE,
         m_pixmap.m_pimage32Raw);
      
      //m_pixmap.mult_alpha();
      
#else
      glReadBuffer(GL_FRONT);
      

      glReadnPixels(
         0, 0,
         cx, cy,
         GL_BGRA,
         GL_UNSIGNED_BYTE,
         cx * cy * 4,
         data);

      int iError = glGetError();

      if(iError != 0)
      {

         printf("glReadnPixels error");

      }

      //::memory_set(m_pixmap.m_pimage32Raw, 127, cx * cy * 4);

#endif

      {

         auto dst = (::u8 *)data;
         auto size = cx * cy;

         while (size > 0)
         {
            dst[0] = u8_clip(((i32)dst[0] * (i32)dst[3]) / 255);
            dst[1] = u8_clip(((i32)dst[1] * (i32)dst[3]) / 255);
            dst[2] = u8_clip(((i32)dst[2] * (i32)dst[3]) / 255);
            dst += 4;
            size--;
         }

      }

      //::copy_image32(m_pixmap.m_pimage32,
      //   cx, cy,
      //   m_pixmap.m_iScan,
      //   (const ::image32_t*) data, cx * 4);

   }


   void cpu_buffer::gpu_write()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pixmap.nok())
      {

         return;

      }

 //     m_pixmap.map();
      //
//      glDrawPixels(
//         m_pixmap.m_size.cx(), m_pixmap.m_size.cy(),
//         GL_BGRA,
//         GL_UNSIGNED_BYTE,
//         m_pixmap.m_pimage32Raw);
      
      glTexImage2D(GL_TEXTURE_2D, 0, 0, 0,
                   m_pixmap.m_size.cx(), m_pixmap.m_size.cy(),
                   GL_RGBA, GL_UNSIGNED_BYTE,
                   m_pixmap.m_pimage32Raw);

   }


} // namespace opengl



