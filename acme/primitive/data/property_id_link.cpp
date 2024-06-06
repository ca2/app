#include "framework.h"
#include "property_container.h"
#include "property_link.h"
//#include "acme/primitive/primitive/property_object.h"

/*
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
*/

/*

property_link::property_link(::property_container * ppropertycontainer, const ::atom & atom):
   m_ppropertycontainer(ppropertycontainer),
   m_atom(atom)
{

if(m_ppropertycontainer)
{
   m_ppropertycontainer->m_propertylistenera.add(this);

   }

}


property_link::property_link(const property_link & propertylink) :
m_ppropertycontainer(propertylink.m_ppropertycontainer),
m_atom(propertylink.m_atom)
{

if(m_ppropertycontainer)
{
   m_ppropertycontainer->m_propertylistenera.add(this);

   }

}


property_link::~property_link()
{

if(::is_set(m_ppropertycontainer))
{
m_ppropertycontainer->m_propertylistenera.erase(this);

}

}

bool property_link::set_property(const ::payload & payload, const ::action_context & actioncontext)
{

   return m_ppropertycontainer->set_property(m_atom, payload, actioncontext);

}


::payload property_link::get_property() const
{

   return m_ppropertycontainer->get_property(m_atom);

}

*/