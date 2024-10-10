// Creating by camilo with 
// property* system on 2024-06-06 21:20 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/prototype/data/property_container.h"
#include "acme/prototype/data/property.h"
//#include "acme/prototype/prototype/property_object.h"


namespace data
{


   property::property(::data::property_container * ppropertycontainer, const ::atom & atom) :
      m_ppropertycontainer(ppropertycontainer),
      m_atom(atom)
   {


   }

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


   property::property(const property & property) :
      m_ppropertycontainer(property.m_ppropertycontainer),
      m_atom(property.m_atom)
   {

   }


   property::~property()
   {


   }


   void property::initialize_data_property(const ::data::property & propertySource)
   {

      //if (::is_set(m_ppropertycontainer) && m_ppropertycontainer != propertySource.m_ppropertycontainer)
      //{

         //propertyTarget.m_ppropertycontainer->m_propertylistenera.erase(m_pusercontrol);

      m_ppropertycontainer = propertySource.m_ppropertycontainer;

      //}

      m_atom = propertySource.m_atom;

      //if (::is_set(m_ppropertycontainer) && m_ppropertycontainer != propertySource.m_ppropertycontainer)
      //{

      //   propertyTarget.m_ppropertycontainer->m_propertylistenera.add(m_pusercontrol);

      //}

   }



   ::comparable_array < property_will_change > & property::property_will_change() const
   {

      return m_ppropertycontainer->m_propertywillchangea;

   }


   ::comparable_array < property_changed > & property::property_changed() const
   {

      return m_ppropertycontainer->m_propertychangeda;

   }


   bool property::operator &&(const ::atom_array & atoma) const
   {

      if (atoma.is_empty())
      {

         return false;

      }

      if (atoma.first() != m_atom)
      {

         return false;

      }

      return true;

   }


   bool property::operator &&(::data::property_change & change) const
   {

      if (m_ppropertycontainer != change.m_ppropertycontainer)
      {

         return false;

      }

      if (!(*this && change.m_atoma))
      {

         return false;

      }

      return true;

   }


   bool property::set_property(const ::payload & payload, const ::action_context & actioncontext) const
   {

      return m_ppropertycontainer->set_property({ m_atom }, payload, actioncontext);

   }


   ::atom_array property::get_key(const ::atom_array & atomaSuffix) const
   {

      if (atomaSuffix.is_empty())
      {

         return { m_atom };

      }

      ::atom_array atoma;

      atoma.add(m_atom);

      atoma.append(atomaSuffix);

      return ::transfer(atoma);

   }


   bool property::set_property(const ::atom_array & atomaSuffix, const ::payload & payload, const ::action_context & actioncontext) const
   {

      return m_ppropertycontainer->set_property(get_key(atomaSuffix), payload, actioncontext);

   }


   ::payload property::get_property(const ::atom_array & atomaSuffix) const
   {


      return m_ppropertycontainer->get_property(get_key(atomaSuffix));

   }


   bool property::operator == (const property & property) const
   {

      if (m_ppropertycontainer != property.m_ppropertycontainer)
      {

         return false;

      }

      if (m_atom != property.m_atom)
      {

         return false;

      }

      return true;

   }


} // namespace data



