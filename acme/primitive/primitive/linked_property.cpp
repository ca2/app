#include "framework.h"



void linked_property::notify_property_changed(const ::action_context & actioncontext) const
{

   if (::is_null(m_pproperty))
   {

      return;

   }

   if (::is_null(m_pobjectPropertyHolder))
   {

      return;

   }

   m_pobjectPropertyHolder->notify_property_changed(m_pproperty, actioncontext);

}



