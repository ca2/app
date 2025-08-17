// Created by camilo on 2022-03-15 08:08 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "impact_creator.h"
#include "impact_kit.h"


namespace user
{


   void impact_kit::add_impact_item(const ::atom & atom, const ::scoped_string & scopedstrTitle, ::user::impact_creator * pimpactcreator)
   {

      auto pitem = øcreate_new < item >();

      pitem->id() = atom;

      pitem->m_strName = scopedstrTitle;

      pitem->m_pimpactcreator = pimpactcreator;

      m_itema.add(pitem);

   }


} // namespace user




