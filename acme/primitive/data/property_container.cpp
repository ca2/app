//
// Created by camilo on 2024-06-05 19:22 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "property_container.h"
#include "property_listener.h"


namespace data
{


   property_container::property_container()
   {


   }


   property_container::~property_container()
   {



   }


   bool property_container::set_property(const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   {

      if (!on_property_will_change(atoma, payload, actioncontext))
      {

         return false;

      }

      m_propertyset[atoma] = payload;

      on_property_changed(atoma, payload, actioncontext);

      return true;

   }


   ::payload property_container::get_property(const ::atom_array & atoma) const
   {

      return m_propertyset[atoma];

   }


   bool property_container::on_property_will_change(const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   {

      for (auto & propertywillchange : m_propertywillchangea)
      {

         if (!propertywillchange(this, atoma, payload, actioncontext))
         {

            return false;

         }

      }

      for (auto & plistener : m_propertylistenera)
      {

         if (!plistener->on_property_will_change(this, atoma, payload, actioncontext))
         {

            return false;

         }

      }

      return true;

   }


   void property_container::on_property_changed(const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   {

      for (auto & propertychanged : m_propertychangeda)
      {

         propertychanged(this, atoma, payload, actioncontext);

      }

      for (auto & plistener : m_propertylistenera)
      {

         plistener->on_property_changed(this, atoma, payload, actioncontext);

      }

   }


   ::comparable_array < property_will_change > & property_container::property_will_change()
   {

      return m_propertywillchangea;

   }


   ::comparable_array < property_changed > & property_container::property_changed()
   {

      return m_propertychangeda;

   }


} // namespace data




