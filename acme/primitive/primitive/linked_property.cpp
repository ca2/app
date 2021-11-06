#include "framework.h"



void linked_property::notify_property_changed(const ::action_context & actioncontext) const
{

   if (::is_null(m_pproperty))
   {

      return;

   }

   if (::is_null(m_ppropertyobject))
   {

      return;

   }

   m_ppropertyobject->notify_property_changed(m_pproperty, actioncontext);

}



