// created by Camilo on 2025-06-01 01:55 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/graphics/image/buffer.h"


namespace image
{


   class CLASS_DECL_AURA lock
   {
   public:


      ::image::buffer *              m_pbuffer;


      lock(buffer* pbuffer)
      {

         m_pbuffer = pbuffer;

      }


      ~lock()
      {

         m_pbuffer->unlock();

      }

      int width() const
      {

         return m_pbuffer->width();

      }

      int height() const
      {

         return m_pbuffer->height();

      }

      int scan() const
      {

         return m_pbuffer->m_iScan;

      }


      image32_t * data()
      {

         return m_pbuffer->data();

      }


   };




} // namespace image



