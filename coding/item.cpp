//
// Created by camilo on 06/03/23.
//
#include "framework.h"
#include "group.h"
#include "item.h"


namespace coding
{


   item::item()
   {

      m_pgroup = nullptr;
      m_iIntegrate = -1;

   }


   item::~item()
   {


   }


   ::string item::get_integrate_item_name() const
   {

      ::string strIntegrateItemName;

      strIntegrateItemName = m_strName1;

      if (m_strRelease.has_character())
      {

         if (strIntegrateItemName.has_character())
         {

            strIntegrateItemName += " ";

         }

         strIntegrateItemName += m_strRelease;

      }

      return strIntegrateItemName;

   }


   void item::integrate()
   {
      m_pgroup->call_integrate(this);
   }


} // namespace integration_integration



