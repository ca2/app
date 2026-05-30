//
//  menu_shared.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2021-02-08 <3TBS_!! Thomas Borregaard Soerensen
//
#pragma once


//#include "acme/prototype/prototype/matter.h"


namespace windowing
{


   class CLASS_DECL_AURA menu_item :
      virtual public matter
   {
   public:


      string            m_strParent;
      string            m_strMenu;
      e_status          m_estatus;


      menu_item();
      virtual ~menu_item();


      virtual void add_status(enum_status estatus);
      virtual void erase_status(enum_status estatus);

      inline i32_boolean is_checked() const { return m_estatus & e_status_checked; }
      inline i32_boolean should_set_checked() const { return m_estatus & e_status_set_checked; }

      inline i32_boolean is_disabled() const { return m_estatus & e_status_disabled; }
      inline i32_boolean should_set_disabled() const { return m_estatus & e_status_set_disabled; }

   };


} // namespace windowing



