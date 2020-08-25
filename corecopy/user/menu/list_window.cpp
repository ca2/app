#include "framework.h"


namespace user
{


   const i32 g_base_menu_indent = 11;


   menu_list_window::menu_list_window()
   {

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

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &menu_list_window::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &menu_list_window::_001OnDestroy);
      IGUI_MSG_LINK(WM_CLOSE, pchannel, this, &menu_list_window::_001OnClose);

   }


   void menu_list_window::_001OnCreate(::message::message * pmessage)
   {

      descriptor().set_control_type(control_type_menu);

      UNREFERENCED_PARAMETER(pmessage);

   }


   void menu_list_window::_001OnClose(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void menu_list_window::_001OnDestroy(::message::message * pmessage)
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

      if(pitemParent->m_spmenuitema == nullptr)
      {

         return;

      }

      for(i32 i = 0; i < pitemParent->m_spmenuitema->get_size(); i++)
      {

         menu_item * pitem = pitemParent->m_spmenuitema->element_at(i);

         if(pitem->m_puserinteraction == nullptr)
         {

            continue;

         }

         auto size = pgraphics->GetTextExtent(pitem->m_puserinteraction->get_window_text());

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

      if(GetParent() == nullptr)
      {

         return;

      }

      __pointer(menu_item) pitem = get_menu_item();

      if(pitem == nullptr)
      {

         return;

      }

      ::rect rectClient;

      GetParent()->get_client_rect(rectClient);

      pgraphics->set_font(this);

      const ::size & size = pgraphics->GetTextExtent("XXXMMM");

      i32 iMaxHeight = size.cy;

      i32 iMaxWidth = size.cx;

      m_iHeaderHeight = size.cy;

      calc_size(m_pmenuitemThis, pgraphics, iMaxWidth, iMaxHeight);

      m_iItemHeight = iMaxHeight + 6 + 2;

      m_size.cx = iMaxWidth + 4;

      m_size.cy = m_iHeaderHeight + pitem->m_iSeparatorCount * 3 + pitem->m_iFullHeightItemCount * m_iItemHeight + 4;

      ::rect rect(4, m_iHeaderHeight + 4, m_size.cx - 8, 4);

      string str;

      layout_buttons(m_pmenuitemThis, iMaxWidth + 4, rect, rectClient);

      auto & puiClose = m_pitemClose->m_puserinteraction;

      if(puiClose->is_window())
      {

         puiClose->resize_to_fit(pgraphics);

         puiClose->move_to(m_size.cx - puiClose->width() - 2, 2);

      }

   }


   void menu_list_window::layout_buttons(menu_item * pitemParent, i32 iMaxWidth, RECT * prect, const ::rect & rectBound)
   {

      if (!m_bMenuOk)
      {

         return;

      }

      if(pitemParent->m_spmenuitema == nullptr)
      {

         return;

      }

      for(i32 i = 0; i < pitemParent->m_spmenuitema->get_size(); i++)
      {

         menu_item * pitem = pitemParent->m_spmenuitema->element_at(i);

         prect->bottom = prect->top + m_iItemHeight - 2;

         if(prect->bottom > rectBound.bottom)
         {

            prect->left += iMaxWidth + 16;

            prect->top = rectBound.top;

            prect->bottom = prect->top + m_iItemHeight - 2;

         }

         if (pitem->m_id != "separator" && pitem->m_puserinteraction != nullptr)
         {

            pitem->m_puserinteraction->set_dim(
            prect->left + pitem->m_iLevel * g_base_menu_indent,
            prect->top,
            iMaxWidth - pitem->m_iLevel * g_base_menu_indent,
            prect->bottom - prect->top);

            pitem->m_puserinteraction->display();

            layout_buttons(pitem, iMaxWidth, prect, rectBound);

         }

         prect->top = prect->bottom + 2;


      }

   }


   void menu_list_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

   }


} // namespace user



