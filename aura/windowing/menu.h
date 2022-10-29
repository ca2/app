//
//  menu_shared.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 10/08/20.
//
#pragma once


#include "menu_item.h"
#include "acme/primitive/collection/pointer_array.h"


namespace windowing
{


   class CLASS_DECL_AURA menu :
      virtual public matter
   {
   public:


      string                              m_strParent;
      string                              m_strMenu;
      pointer_array < menu_item >         m_itema;


      menu();
      ~menu() override;


      menu_item * find_item(const ::string & pszParent, const ::string & pszId);

      void on_idle_update();

      void on_idle(::channel * pchannel);

   };


} // namespace windowing



