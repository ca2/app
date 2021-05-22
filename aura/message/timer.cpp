#include "framework.h"
#include "timer.h"


namespace message
{


   void timer::set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam, const ::point_i32 & point)
   {

      ::user::message::set(oswindow, pwindow, id, wparam, lparam, point);

      m_uEvent = static_cast<::u32>(wparam);

   }


} // namespace message



