#include "framework.h"
#include "aura/operating_system.h"



namespace draw2d
{


   device_lock::device_lock(::user::interaction * pinteraction)
   {

#ifdef _UWP

      __pointer(::aura::system) psystem = m_psystem;

      m_D2DMultithread = pdraw2d->direct2d()->m_d2dMultithread.Get();

      m_D2DMultithread->Enter();

#endif

   }


   device_lock::~device_lock()
   {

#ifdef _UWP

      m_D2DMultithread->Leave();

#endif

   }


} // namespace draw2d



