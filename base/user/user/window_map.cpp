#include "framework.h"


namespace user
{


   window_map::window_map()
   {

   }


   window_map::~window_map()
   {

   }


   ::user::primitive * window_map::get(oswindow oswindow)
   {

      ::user::primitive * puibase;

      if (!m_map.lookup(oswindow, puibase))
      {

         return nullptr;

      }

      return puibase;

   }


   void window_map::set(oswindow oswindow, const ::user::primitive * puibase)
   {

      m_map.set_at(oswindow, (::user::primitive *) puibase);

   }


} // namespace user



