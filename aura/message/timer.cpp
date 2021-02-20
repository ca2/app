#include "framework.h"
#include "timer.h"


namespace message
{


   void timer::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam);

      m_uEvent = static_cast<::u32>(wparam);

   }


} // namespace message



