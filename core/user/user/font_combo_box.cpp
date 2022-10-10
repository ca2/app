#include "framework.h"
#include "aura/message/user.h"
#include "aura/graphics/write_text/font_list.h"
#include "aura/graphics/write_text/font_enumeration_item.h"
#include "font_list.h"
#include "font_combo_box.h"


namespace user
{


   font_combo_box::font_combo_box()
   {

      font_combo_box_common_construct();

   }


   void font_combo_box::font_combo_box_common_construct()
   {

      m_edatamode = data_mode_string;

      m_typeListBox = __type(::user::font_list);

      m_bEdit = false;

   }


   font_combo_box::~font_combo_box()
   {

   }


   void font_combo_box::install_message_routing(::channel * psender)
   {

      ::user::combo_box::install_message_routing(psender);

      MESSAGE_LINK(e_message_create, psender, this, &::user::font_combo_box::on_message_create);

   }


   void font_combo_box::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      //throw ::exception(todo("style"));

      //::rectangle_f64 r(2, 2, 2, 2);

      //create_rect(::user::rect_edit_padding, r, ::draw2d::e_unit_pixel);

      defer_create_list_box();

      ::pointer<::user::font_list>pfontlist = m_plistbox;

      pfontlist->set_font_list_type(::write_text::e_font_list_single_column);

   }


   void font_combo_box::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void font_combo_box::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_font_enumeration)
      {

         ::pointer<::user::font_list>pfontlist = m_plistbox;

         synchronous_lock synchronouslock(pfontlist->mutex());

         auto pfontenumerationitema = pfontlist->m_pfontlist->m_pfontenumerationitema;

         for (auto & item : pfontenumerationitema->ptra())
         {

            if (item.is_set())
            {

               add_string(item->m_strName, item->m_strName);

            }

         }

         set_need_redraw();

         post_redraw();

      }

      ::user::combo_box::handle(ptopic, pcontext);

   }



} //  namespace user



