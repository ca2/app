//
//  menu_shared.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 10/08/20.
//
#pragma once


#include "menu_item.h"
//#include "acme/prototype/collection/pointer_array.h"


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


      menu_item * find_item(const ::scoped_string & scopedstrParent, const ::scoped_string & scopedstrId);

      void on_idle_update();

      void on_idle(::channel * pchannel);

   };


} // namespace windowing



