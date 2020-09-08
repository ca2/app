#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/menu/_menu.h"
#endif


namespace user
{


   menu_button::menu_button(menu_item * pitem):
      object(pitem->get_context_application()),
      ::user::menu_interaction(pitem)
   {

      //m_erectMargin = rect_menu_item_margin;
      //m_erectBorder = rect_menu_item_border;
      //m_erectPadding = rect_menu_item_padding;
      //m_eintTextAlign = int_menu_item_draw_text_flags;

      m_flagNonClient.remove(::user::interaction::non_client_focus_rect);


   }


   menu_button::~menu_button()
   {

   }


   void menu_button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &menu_button::_001OnCreate);

   }


   bool menu_button::create_window(::user::interaction *pparent, const ::id & id)
   {

      if (!button::create_window(pparent, id))
      {

         return false;

      }

      return true;

   }


   void menu_button::_001OnDrawDefault(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if (m_id == "separator")
      {

         _001OnButtonDrawBackground(pgraphics);

         //pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         //pgraphics->fill_rect(rectClient, _001GetButtonBackgroundColor());

         //::draw2d::pen_pointer pen(e_create);

         //pen->create_solid(1.0, _001GetColor(color_button_text));

         //pgraphics->set(pen);

         //pgraphics->move_to(rectClient.left + rectClient.width() / 8, (rectClient.top + rectClient.bottom) / 2);

         ///pgraphics->line_to(rectClient.right - rectClient.width() / 8, (rectClient.top + rectClient.bottom) / 2);

         return;

      }

      button::_001OnDraw(pgraphics);

      if (m_pmenuitem != nullptr && m_pmenuitem->m_bPopup)
      {

         ::draw2d::brush_pointer br(e_create);

         br->create_solid(ARGB(255, 0, 0, 0));

         ::draw2d::pen_pointer pen(e_create);

         pen->create_solid(1, RGB(0, 0, 0));
         pgraphics->set(pen);
         pgraphics->set(br);
         ::rect rectPopupArrow;
         rectPopupArrow.left = rectClient.right - 9;
         rectPopupArrow.right = rectClient.right - 4;
         rectPopupArrow.top = ((rectClient.top + rectClient.bottom) / 2) - 4;
         rectPopupArrow.bottom = ((rectClient.top + rectClient.bottom) / 2) + 4;
         point_array pointa;
         pointa.add(point(rectPopupArrow.left, rectPopupArrow.bottom));
         pointa.add(point(rectPopupArrow.right, (rectPopupArrow.bottom + rectPopupArrow.top) / 2));
         pointa.add(point(rectPopupArrow.left, rectPopupArrow.top));
         pointa.add(point(rectPopupArrow.left, rectPopupArrow.bottom));
         pgraphics->polygon(pointa);
      }

      _001DrawCheck(pgraphics);

   }


   COLORREF menu_button::_001GetButtonBackgroundColor()
   {

      COLORREF crBackground = ::user::button::_001GetButtonBackgroundColor();

      crBackground &= 0x00ffffff;

      crBackground = crBackground | ARGB(200, 0, 0, 0);

      return crBackground;

   }


   void menu_button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __pointer(::base::style) pbasestyle = get_style(pgraphics);

      if (pbasestyle)
      {

         if (pbasestyle->_001OnDrawMenuInteraction(pgraphics, this))
         {

            return;

         }

      }

      _001OnDrawDefault(pgraphics);

   }


   void menu_button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

//      if (m_puserstyle == nullptr)
//      {
//
//         if (m_pmenuitem != nullptr)
//         {
//
//            __pointer(::user::menu) pinteraction = m_pmenuitem->m_pmenuitem;
//
//            if (pinteraction.is_set() && pinteraction->m_puserinteractionParent != nullptr)
//            {
//
//               m_puserstyle = pinteraction->m_puserinteractionParent;
//
//            }
//
//         }
//
//      }

   }

   void menu_button::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //if (m_id != "separator")
      {

         //::user::button::_001OnNcDraw(pgraphics);

      }

   }

   void menu_button::_001DrawCheck(::draw2d::graphics_pointer & pgraphics)
   {

      UINT uiImage = 0xffffffffu;

      if(m_pmenuitem != nullptr)
      {

         uiImage = User.menu()->command_image(m_pmenuitem->m_id);

      }

      if(uiImage != 0xffffffffu)
      {



         ::rect rectImage = m_rectCheckBox;
         ::rect rectImageBorder = rectImage;
         rectImageBorder.inflate(2, 2);
         ::image_list::info ii;
         __pointer(image_list) pimagelist;
         if(!is_window_enabled())
         {
            pimagelist = User.menu()->MenuV033GetImageListHueLight();
         }
         else
         {
            pimagelist = User.menu()->MenuV033GetImageList();
         }

         pimagelist->get_image_info(uiImage, &ii);

         ::rect & rectImageInfo(ii.m_rect);
         rectImage.offset(1, 1);
         rectImage.top     = rectImage.bottom - rectImageInfo.height();
         rectImage.right   = rectImage.left + rectImageInfo.width();

         if(echeck() == ::check_checked)
         {

            pgraphics->fill_rect(rectImageBorder, RGB(127, 127, 127));

            pgraphics->draw_3drect(rectImageBorder, Session.get_default_color(COLOR_3DSHADOW), Session.get_default_color(COLOR_3DHILIGHT));

         }

         pimagelist->draw(pgraphics, uiImage, rectImage.top_left(), 0);

      }
      else
      {

         auto pstyle = get_style(pgraphics);

         pstyle->draw_check(get_echeck(), m_rectCheckBox, pgraphics);

      }

   }


   void menu_button::_001OnCreate(::message::message * pmessage)
   {

      descriptor().set_control_type(control_type_menu_button);

      pmessage->previous();

   }


   void menu_button::_001OnMouseMove(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      pmouse->previous();


   }


   bool menu_button::keyboard_focus_is_focusable()
   {

      return false;


   }


   void menu_button::on_calc_size(calc_size * pcalcsize)
   {

      auto pstyle = get_style(pcalcsize->m_pgraphics);

      __pointer(::draw2d::font) pfont = get_font(pstyle);

      pcalcsize->m_pgraphics->set(pfont);

      //select(pcalcsize->m_pgraphics);

      string strButtonText;

      strButtonText = get_window_text();

      bool bSeparator = false;

      if (strButtonText.is_empty())
      {

         strButtonText = "separator";

         bSeparator = true;

      }

      auto size = pcalcsize->m_pgraphics->GetTextExtent(strButtonText);

      if (bSeparator)
      {

         size.cy /= 2;

      }

      ::rect rectMargin = get_margin(pstyle);

      ::rect rectBorder = get_border(pstyle);

      ::rect rectPadding = get_padding(pstyle);

      size.cx += rectMargin.left + rectBorder.left + rectPadding.left;

      size.cx += rectMargin.right;

      size.cx += m_pmenuitem->m_pmenu->m_iCheckBoxSize;

      size.cx += rectPadding.left;

      if (m_pmenuitem->IsPopup())
      {

         size.cx += rectPadding.left;

         size.cx += m_pmenuitem->m_pmenu->m_iCheckBoxSize;

      }

      size.cx += rectMargin.right + rectBorder.right + rectPadding.right;

      size.cy += rectMargin.top + rectBorder.top + rectPadding.top;

      size.cy += rectMargin.bottom + rectBorder.bottom + rectPadding.bottom;

      pcalcsize->m_size = size;

   }



} // namespace user
