// Created by camilo on 2024-06-06 20:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "control.h"
#include "acme/primitive/data/property_container.h"
#include "acme/primitive/data/property_link.h"


namespace user
{

   void control::initialize_property_link(property_link & propertylinkTarget, const property_link & propertylinkSource)
   {

      if (propertylinkTarget.m_ppropertycontainer)
      {

         propertylinkTarget.m_ppropertycontainer->m_propertylistenera.erase(this);

      }

      propertylinkTarget.m_ppropertycontainer = propertylinkSource.m_ppropertycontainer;
      propertylinkTarget.m_atom = propertylinkSource.m_atom;

      if (propertylinkTarget.m_ppropertycontainer)
      {

         propertylinkTarget.m_ppropertycontainer->m_propertylistenera.add(this);

      }


   }


} // namespace user



