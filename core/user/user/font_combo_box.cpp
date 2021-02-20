#include "framework.h"
#include "core/user/user/_user.h"


namespace user
{


   font_combo_box::font_combo_box()
   {

      font_combo_box_common_construct();

   }


   void font_combo_box::font_combo_box_common_construct()
   {

      m_edatamode = data_mode_string;

      m_typeComboList = __type(::user::font_list);

      m_bEdit = false;

   }


   font_combo_box::~font_combo_box()
   {

   }


   void font_combo_box::install_message_routing(::channel * psender)
   {

      ::user::combo_box::install_message_routing(psender);

      MESSAGE_LINK(e_message_create, psender, this, &::user::font_combo_box::_001OnCreate);

   }


   void font_combo_box::_001OnCreate(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      //__throw(todo("style"));

      //::rectangle_f64 r(2, 2, 2, 2);

      //create_rect(::user::rect_edit_padding, r, ::draw2d::unit_pixel);

      defer_create_combo_list();

      __pointer(::user::font_list) plist = m_plist;

      plist->set_font_list_type(::write_text::font_list::type_single_column);

      set_need_layout();

      ::user::font_list& list = *m_plist.cast < ::user::font_list>();

      synchronization_lock synchronizationlock(list.mutex());

      for (auto& item : list.m_pfontlist->m_pitema->ptra())
      {

         if (item.is_set())
         {

            AddString(item->m_strName, item->m_strName);

         }

      }


   }


   void font_combo_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

   }


} //  namespace user



