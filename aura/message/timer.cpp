#include "framework.h"
#include "timer.h"


namespace message
{


   void timer::set(oswindow oswindow, ::layered * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      base::set(oswindow, pwindow, id, wparam, lparam);

      m_uEvent = static_cast<::u32>(wparam);

   }


} // namespace message



