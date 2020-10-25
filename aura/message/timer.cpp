#include "framework.h"
#include "timer.h"


namespace message
{


   void timer::set(::user::primitive* pwnd, const ::id & id, WPARAM wparam, ::lparam lparam)
   {

      base::set(pwnd, id, wparam, lparam);

      m_uEvent = static_cast<UINT>(wparam);

   }


} // namespace message



