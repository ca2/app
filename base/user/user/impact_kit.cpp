// Created by camilo on 2022-03-15 08:08 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "impact_creator.h"
#include "impact_kit.h"


namespace user
{


   void impact_kit::add_impact_item(const ::atom & atom, const ::string & strTitle, ::user::impact_creator * pimpactcreator)
   {

      auto pitem = __create_new < item >();

      pitem->m_atom = atom;

      pitem->m_strName = strTitle;

      pitem->m_pimpactcreator = pimpactcreator;

      m_itema.add(pitem);

   }


} // namespace user




