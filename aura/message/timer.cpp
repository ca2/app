#include "framework.h"
#include "timer.h"


namespace message
{


   void timer::set(::user::primitive* pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam)
   {

      base::set(pwnd, uiMessage, wparam, lparam);

      m_uEvent = static_cast<UINT>(wparam);

   }


} // namespace message



