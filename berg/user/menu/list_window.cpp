#include "framework.h"
#include "list_window.h"
#include "acme/constant/message.h"
#include "aura/graphics/draw2d/graphics.h"
#include "berg/user/menu/item.h"
#include "berg/user/menu/item_ptra.h"


namespace user
{


   const int g_base_menu_indent = 11;


   menu_list_window::menu_list_window()
   {

      m_econtroltype = e_control_type_menu;
      m_bInline = true;
      m_bAutoDelete = true;
      m_bOwnItem = false;
      m_bAutoClose = true;
      m_bInline = true;
      m_bExtendOnParentHostingArea = true;

   }


   menu_list_window::menu_list_window(::menu::item * pitem)
   {

      m_bAutoClose         = true;
      m_bAutoDelete        = true;
      m_bOwnItem           = false;
      m_bInline            = true;

   }


   menu_list_window::~menu_list_window()
   {

   }


   void menu_list_window::install_message_routing(::channel * pchannel)
   {

      menu::install_message_routing(pchannel);

      MESSAGE_LINK(::user::e_message_create, pchannel, this, &menu_list_window::on_message_create);
      MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &menu_list_window::on_message_destroy);
      MESSAGE_LINK(::user::e_message_close, pchannel, this, &menu_list_window::on_message_close);

   }


   void menu_list_window::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void menu_list_window::on_message_close(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void menu_list_window::on_message_destroy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void menu_list_window::on_timer(::timer * ptimer)
   {

      ::user::menu::on_timer(ptimer);

   }


   void menu_list_window::calc_size(::menu::item * pitemParent, ::draw2d::graphics_pointer & pgraphics, int & iMaxWidth, int & iMaxHeight)
   {

      if (!m_bMenuOk)
      {

         return;

      }

      if(pitemParent == nullptr)
      {

         return;

      }

      if(pitemParent->m_pmenuitema == nullptr)
      {

         return;

      }

      for(int i = 0; i < pitemParent->m_pmenuitema->get_size(); i++)
      {

         ::menu::item * pitem = pitemParent->m_pmenuitema->element_at(i);

         if(pitem->m_puserinteraction == nullptr)
         {

            continue;

         }

         pgraphics->set_font(pitem->m_puserinteraction, ::e_element_none);

         string strWindowText = pitem->m_puserinteraction->get_window_text();

         //const ::scoped_string & scopedstrWindowText = strWindowText.c_str();

         auto size = pgraphics->get_text_extent(strWindowText);

         size.cy() = size.cy() * 5 / 4;

         size.cx() = size.cx() * 5 / 4;

         size.cx() += pitem->m_iLevel * g_base_menu_indent;

         if(pitem->is_popup())
            size.cx() += 12 + 16;

         if(size.cy() > iMaxHeight)
            iMaxHeight = (int) size.cy();

         if(size.cx() > iMaxWidth)
            iMaxWidth = (int)size.cx();

         calc_size(pitem, pgraphics, iMaxWidth, iMaxHeight);

      }

   }


   void menu_list_window::layout_buttons(::menu::item * pitemParent, int iMaxWidth, ::int_rectangle * prectangle, const ::int_rectangle & rectangleBound)
   {

      if (!m_bMenuOk)
      {

         return;

      }

      if(pitemParent->m_pmenuitema == nullptr)
      {

         return;

      }

      for(int i = 0; i < pitemParent->m_pmenuitema->get_size(); i++)
      {

         ::menu::item * pitem = pitemParent->m_pmenuitema->element_at(i);

         prectangle->bottom() = (int) (prectangle->top() + m_dItemHeight * 1.2 - 2);

         if(prectangle->bottom() > rectangleBound.bottom())
         {

            prectangle->left() += iMaxWidth + 16;

            prectangle->top() = rectangleBound.top();

            prectangle->bottom() = (int) (prectangle->top() + m_dItemHeight - 2);

         }

         if (pitem->id() != "separator" && pitem->m_puserinteraction != nullptr)
         {
            
            auto rPlacement = ::int_rectangle_dimension(
                                                        prectangle->left() + pitem->m_iLevel * g_base_menu_indent,
                                                        prectangle->top(),
                                                        iMaxWidth - pitem->m_iLevel * g_base_menu_indent,
                                                        prectangle->bottom() - prectangle->top());

            pitem->m_puserinteraction->place(rPlacement);

            pitem->m_puserinteraction->display();

            layout_buttons(pitem, iMaxWidth, prectangle, rectangleBound);

         }

         prectangle->top() = prectangle->bottom() + 5;

      }

   }


   void menu_list_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

   }


   void menu_list_window::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {
      
      ::user::interaction::on_perform_top_down_layout(pgraphics);

      if (!m_bMenuOk)
      {

         return;

      }

      if(get_parent() == nullptr)
      {

         return;

      }

      ::pointer<::menu::item>pitem = get_menu_item();

      if(pitem == nullptr)
      {

         return;

      }

      ::int_rectangle rectangleX;
      
      ::string strType = ::type(get_parent());

//      auto rectangleParentX = get_parent()->rectangle(e_layout_layout);
      rectangleX = this->rectangle(e_layout_layout);

      pgraphics->set_font(this, ::e_element_none);

      const ::int_size & size = pgraphics->get_text_extent("XXXMMMgggppp");

      int iMaxHeight = size.cy();

      int iMaxWidth = size.cx();

      m_dHeaderHeight = size.cy();

      calc_size(m_pmenuitem, pgraphics, iMaxWidth, iMaxHeight);

      m_dItemHeight = iMaxHeight * 3 / 2;

      m_size.cx() = iMaxWidth * 7 / 4;

      m_size.cy() = (int) (m_dHeaderHeight + pitem->get_separator_item_count() * 3 + pitem->get_full_height_item_count() * m_dItemHeight + 4);

      ::int_rectangle rectangle(4, (int) m_dHeaderHeight + 4, m_size.cx() - 8, 4);

      string str;

      layout_buttons(m_pmenuitem, iMaxWidth + 4, &rectangle, rectangleX);

      if (m_pitemClose)
      {

         auto & puiClose = m_pitemClose->m_puserinteraction;

         if (puiClose->is_window())
         {

            puiClose->resize_to_fit(pgraphics);

            puiClose->set_position({ m_size.cx() - puiClose->width() - 2, 2 });

         }

      }

   }


} // namespace user



