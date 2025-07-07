// Refactoring device_lock by camilo by 2021-09-08 16:25 BRT <3ThomasBS__!!
#include "framework.h"
#include "device_lock.h"
#include "draw2d.h"


namespace draw2d
{


   device_lock::device_lock(::particle* pparticle) :
      m_pparticle(pparticle)
   {

      m_bLocked = pparticle->system()->m_pdraw2d->lock_device();

   }


   device_lock::~device_lock()
   {

      if (m_bLocked)
      {
       
         m_pparticle->system()->m_pdraw2d->unlock_device();

      }

   }


} // namespace draw2d



