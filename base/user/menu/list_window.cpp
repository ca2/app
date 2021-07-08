#include "framework.h"
#include "base/user/menu/_menu.h"


namespace user
{


   const i32 g_base_menu_indent = 11;


   menu_list_window::menu_list_window()
   {

      m_econtroltype = e_control_type_menu;
      m_bInline = true;
      m_bAutoDelete = true;
      m_bOwnItem = false;
      m_puiMenuNotify = nullptr;
      m_bAutoClose = true;
      m_bInline = true;

   }


   menu_list_window::menu_list_window(menu_item * pitem)
   {

      m_puiMenuNotify      = nullptr;
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

      MESSAGE_LINK(e_message_create, pchannel, this, &menu_list_window::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &menu_list_window::on_message_destroy);
      MESSAGE_LINK(e_message_close, pchannel, this, &menu_list_window::on_message_close);

   }


   void menu_list_window::on_message_create(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void menu_list_window::on_message_close(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void menu_list_window::on_message_destroy(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void menu_list_window::_001OnTimer(::timer * ptimer)
   {

      ::user::menu::_001OnTimer(ptimer);

   }


   void menu_list_window::calc_size(menu_item * pitemParent, ::draw2d::graphics_pointer & pgraphics, i32 & iMaxWidth, i32 & iMaxHeight)
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

      for(i32 i = 0; i < pitemParent->m_pmenuitema->get_size(); i++)
      {

         menu_item * pitem = pitemParent->m_pmenuitema->element_at(i);

         if(pitem->m_puserinteraction == nullptr)
         {

            continue;

         }

         pgraphics->set_font(pitem->m_puserinteraction, ::user::e_element_none);

         string strWindowText = pitem->m_puserinteraction->get_window_text();

         const char * pszWindowText = strWindowText.c_str();

         auto size = pgraphics->get_text_extent(strWindowText);

         size.cy = size.cy * 5 / 4;

         size.cx = size.cx * 5 / 4;

         size.cx += pitem->m_iLevel * g_base_menu_indent;

         if(pitem->IsPopup())
            size.cx += 12 + 16;

         if(size.cy > iMaxHeight)
            iMaxHeight = (i32) size.cy;

         if(size.cx > iMaxWidth)
            iMaxWidth = (i32)size.cx;

         calc_size(pitem, pgraphics, iMaxWidth, iMaxHeight);

      }

   }


   void menu_list_window::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (!m_bMenuOk)
      {

         return;

      }

      if(get_parent() == nullptr)
      {

         return;

      }

      __pointer(menu_item) pitem = get_menu_item();

      if(pitem == nullptr)
      {

         return;

      }

      ::rectangle_i32 rectangleClient;

      get_parent()->get_client_rect(rectangleClient);

      pgraphics->set_font(this, ::user::e_element_none);

      const ::size_i32 & size = pgraphics->get_text_extent("XXXMMMgggppp");

      i32 iMaxHeight = size.cy;

      i32 iMaxWidth = size.cx;

      m_dHeaderHeight = size.cy;

      calc_size(m_pmenuitem, pgraphics, iMaxWidth, iMaxHeight);

      m_dItemHeight = iMaxHeight * 3 / 2;

      m_size.cx = iMaxWidth * 7 / 4;

      m_size.cy = (::i32) (m_dHeaderHeight + pitem->m_iSeparatorCount * 3 + pitem->m_iFullHeightItemCount * m_dItemHeight + 4);

      ::rectangle_i32 rectangle(4, (::i32) m_dHeaderHeight + 4, m_size.cx - 8, 4);

      string str;

      layout_buttons(m_pmenuitem, iMaxWidth + 4, rectangle, rectangleClient);

      auto & puiClose = m_pitemClose->m_puserinteraction;

      if(puiClose->is_window())
      {

         puiClose->resize_to_fit(pgraphics);

         puiClose->move_to(m_size.cx - puiClose->width() - 2, 2);

      }

   }


   void menu_list_window::layout_buttons(menu_item * pitemParent, i32 iMaxWidth, RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectBound)
   {

      if (!m_bMenuOk)
      {

         return;

      }

      if(pitemParent->m_pmenuitema == nullptr)
      {

         return;

      }

      for(i32 i = 0; i < pitemParent->m_pmenuitema->get_size(); i++)
      {

         menu_item * pitem = pitemParent->m_pmenuitema->element_at(i);

         prectangle->bottom = (::i32) (prectangle->top + m_dItemHeight - 2);

         if(prectangle->bottom > rectBound.bottom)
         {

            prectangle->left += iMaxWidth + 16;

            prectangle->top = rectBound.top;

            prectangle->bottom = (::i32) (prectangle->top + m_dItemHeight - 2);

         }

         if (pitem->m_id != "separator" && pitem->m_puserinteraction != nullptr)
         {

            pitem->m_puserinteraction->set_dim(
            prectangle->left + pitem->m_iLevel * g_base_menu_indent,
            prectangle->top,
            iMaxWidth - pitem->m_iLevel * g_base_menu_indent,
            prectangle->bottom - prectangle->top);

            pitem->m_puserinteraction->display();

            layout_buttons(pitem, iMaxWidth, prectangle, rectBound);

         }

         prectangle->top = prectangle->bottom + 2;

      }

   }


   void menu_list_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

   }


} // namespace user



