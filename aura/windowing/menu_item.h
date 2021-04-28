//
//  menu_shared.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2021-02-08 <3TBS_!! Thomas Borregaard Sørensen
//
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA menu_item :
      virtual public material_object
   {
   public:


      string            m_strParent;
      string            m_strMenu;
      e_status          m_estatus;


      menu_item();
      virtual ~menu_item();


      virtual void add_status(enum_status estatus);
      virtual void erase_status(enum_status estatus);

      inline bool is_checked() const { return m_estatus & e_status_checked; }
      inline bool should_set_checked() const { return m_estatus & e_status_set_checked; }

      inline bool is_disabled() const { return m_estatus & e_status_disabled; }
      inline bool should_set_disabled() const { return m_estatus & e_status_set_disabled; }

   };


} // namespace windowing



