#include "framework.h"
#include "timer.h"


namespace message
{


   void timer::set(oswindow oswindow, ::user::primitive* pwnd, const ::id & id, WPARAM wparam, ::lparam lparam)
   {

      base::set(oswindow, pwnd, id, wparam, lparam);

      m_uEvent = static_cast<::u32>(wparam);

   }


} // namespace message



