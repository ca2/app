//
//  menu_shared.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 10/08/20.
//
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA menu :
      virtual public matter
   {
   public:


      enum enum_status
      {
         status_none = 0,
         status_checked = 1 << 0,
         status_disabled = 1 << 1,
         status_set_checked = 1 << 8,
         status_set_disabled = 1 << 9,
      };


      char_pointer const * m_ppszParent;
      char_pointer const * m_ppszMenu;
      char_pointer const * m_ppszId;
      pointer_array < menu_shared_item >         m_shareditema;
      ::i32 * m_statusa;
      ::i32                                       m_iCount;


      menu_shared();
      virtual ~menu_shared();


      void * find_item(const ::scoped_string & scopedstrParent, const ::scoped_string & scopedstrId);

      void on_idle_update();


   };


} // namespace windowing



