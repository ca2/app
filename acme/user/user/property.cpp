// Created by camilo on 2024-06-06 20:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "control.h"
#include "acme/user/user/property.h"
#include "acme/prototype/data/property_container.h"
#include "acme/prototype/data/property.h"


namespace user
{
   property::property(::user::control * pusercontrol) :
      m_pusercontrol(pusercontrol)
   {

      

   }


   void property::set_data_property(::data::property & propertyTarget, const ::data::property & propertySource)
   {

      if (::is_set(propertyTarget.m_ppropertycontainer) && propertyTarget.m_ppropertycontainer != propertySource.m_ppropertycontainer)
      {

         propertyTarget.m_ppropertycontainer->m_propertylistenera.erase(m_pusercontrol);

         propertyTarget.m_ppropertycontainer = propertySource.m_ppropertycontainer;

      }

      propertyTarget.m_atom = propertySource.m_atom;

      if (::is_set(propertyTarget.m_ppropertycontainer) && propertyTarget.m_ppropertycontainer != propertySource.m_ppropertycontainer)
      {

         propertyTarget.m_ppropertycontainer->m_propertylistenera.add(m_pusercontrol);

      }

   }


} // namespace user



