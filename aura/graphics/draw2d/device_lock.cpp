#include "framework.h"
#include "aura/operating_system.h"
#include "aura/user/_user.h"
#include "aura/node/_node.h"
#ifdef _UWP
#include "aura/os/windows_common/draw2d_direct2d_global.h"
#endif


namespace draw2d
{


   device_lock::device_lock(::user::interaction * pinteraction)
   {

#ifdef _UWP

      m_D2DMultithread = System.draw2d().direct2d()->m_d2dMultithread.Get();

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



