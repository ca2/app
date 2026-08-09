// from aura/graphics/image/lock.h by Camilo on 2026-08-05 06:26 <3ThomasBorregaardSorensen!! Mummi!! Bilbo!!
// created by Camilo on 2025-06-01 01:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "lock.h"
#include "pixmap.h"


//#include "aura/graphics/image/aaa_buffer.h"


namespace image
{


   lock::lock(pixmap * ppixmap)
   {

      m_ppixmap = ppixmap;

   }


   lock::lock(lock && lock) :
      m_ppixmap(::transfer(lock.m_ppixmap))
   {

      lock.m_ppixmap = nullptr;

   }



   lock::~lock()
   {

      try
      {

         m_ppixmap->unlock();

      }
      catch (...)
      {


      }


   }


} // namespace image



