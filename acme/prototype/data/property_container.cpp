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


   void property_container::destroy()
   {

      m_propertyset.clear();
      m_propertylistenera.clear();
      m_propertywillchangea.clear();
      m_propertychangeda.clear();

      ::particle::destroy();

   }


   bool property_container::set_property(const ::atom_array & atoma, const ::payload & payload, const ::action_context & actioncontext)
   {

      property_change change{ this, atoma, payload, actioncontext };

      if (!on_property_will_change(change))
      {

         return false;

      }

      on_set_property(change);

      on_property_changed(change);

      return true;

   }


   ::payload property_container::get_property(const ::atom_array & atoma) const
   {

      return on_get_property(atoma);

   }


   void property_container::on_set_property(::data::property_change & change)
   {

      m_propertyset[change.m_atoma] = change.m_payload;

   }


   ::payload property_container::on_get_property(const ::atom_array & atoma) const
   {

      return m_propertyset[atoma];

   }



   bool property_container::on_property_will_change(::data::property_change & change)
   {

      for (auto & propertywillchange : m_propertywillchangea)
      {

         if (!propertywillchange(change))
         {

            return false;

         }

      }

      for (auto & plistener : m_propertylistenera)
      {

         if (!plistener->on_property_will_change(change))
         {

            return false;

         }

      }

      return true;

   }


   void property_container::on_property_changed(::data::property_change & change)
   {

      for (auto & propertychanged : m_propertychangeda)
      {

         propertychanged(change);

      }

      for (auto & plistener : m_propertylistenera)
      {

         plistener->on_property_changed(change);

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




