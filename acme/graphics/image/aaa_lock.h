// from aura/graphics/image/lock.h by Camilo on 2026-08-05 06:26 <3ThomasBorregaardSorensen!! Mummi!! Bilbo!!
// created by Camilo on 2025-06-01 01:55 <3ThomasBorregaardSorensen!!
#pragma once


//#include "aura/graphics/image/aaa_buffer.h"


namespace image
{


   class CLASS_DECL_ACME lock :
      public pixmap_t
   {
   public:


      ::pixmap * m_ppixmap;


      lock(pixmap * ppixmap);

      lock(const lock & lock) = delete;

      lock(lock && lock);
      
      ~lock();


      pixmap * operator ->() { return m_ppixmap; }

   };


} // namespace image




