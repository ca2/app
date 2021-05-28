#include "framework.h"
#include "base/user/menu/_menu.h"


namespace user
{


   menu_button::menu_button()
   {

      m_econtroltype = e_control_type_menu_button;
      //m_erectMargin = rect_menu_item_margin;
      //m_erectBorder = rect_menu_item_border;
      //m_erectPadding = rect_menu_item_padding;
      //m_eintTextAlign = int_menu_item_draw_text_flags;

      m_flagNonClient.erase(::user::interaction::non_client_focus_rect);


   }


   menu_button::~menu_button()
   {

   }


   ::e_status menu_button::initialize_menu_interaction(menu_item* pitem)
   {

      auto estatus = button::initialize(pitem);

      if (!estatus)
      {

         return estatus;

      }

      m_pmenuitem = pitem;

      return estatus;

   }


   void menu_button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &menu_button::on_message_create);

   }


   //bool menu_button::create_interaction(::user::interaction *pparent, const ::id & id)
   //{

   //   if (!button::create_interaction(pparent, id))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   void menu_button::_001OnDrawDefault(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      if (m_id == "separator")
      {

         _001OnButtonDrawBackground(pgraphics);

         //pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         //pgraphics->fill_rectangle(rectClient, _001GetButtonBackgroundColor());

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

         br->create_solid(argb(255, 0, 0, 0));

         ::draw2d::pen_pointer pen(e_create);

         pen->create_solid(1, rgb(0, 0, 0));
         pgraphics->set(pen);
         pgraphics->set(br);
         ::rectangle_i32 rectPopupArrow;
         rectPopupArrow.left = rectClient.right - 9;
         rectPopupArrow.right = rectClient.right - 4;
         rectPopupArrow.top = ((rectClient.top + rectClient.bottom) / 2) - 4;
         rectPopupArrow.bottom = ((rectClient.top + rectClient.bottom) / 2) + 4;
         point_f64_array pointa;
         pointa.add(point_i32(rectPopupArrow.left, rectPopupArrow.bottom));
         pointa.add(point_i32(rectPopupArrow.right, (rectPopupArrow.bottom + rectPopupArrow.top) / 2));
         pointa.add(point_i32(rectPopupArrow.left, rectPopupArrow.top));
         pointa.add(point_i32(rectPopupArrow.left, rectPopupArrow.bottom));
         pgraphics->polygon(pointa);
      }

      _001DrawCheck(pgraphics);

   }


   color32_t menu_button::_001GetButtonBackgroundColor()
   {

      color32_t crBackground = ::user::button::_001GetButtonBackgroundColor();

      crBackground &= 0x00ffffff;

      crBackground = crBackground | argb(200, 0, 0, 0);

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

      ::u32 uImage = 0xffffffffu;

      if(m_pmenuitem != nullptr)
      {

         auto psession = get_session();

         auto puser = psession->user();

         if (puser)
         {

            auto pmenu = puser->menu();

            if (pmenu)
            {

               uImage = pmenu->command_image(m_pmenuitem->m_id);

            }

         }

      }

      if(uImage != 0xffffffffu)
      {

         ::rectangle_i32 rectImage = m_rectCheckBox;
         ::rectangle_i32 rectImageBorder = rectImage;
         rectImageBorder.inflate(2, 2);
         ::image_list::info ii;
         __pointer(image_list) pimagelist;

         auto psession = get_session();

         auto puser = psession->user();

         if (puser)
         {

            auto pmenu = puser->menu();

            if (pmenu)
            {

               if (!is_window_enabled())
               {

                  pimagelist = pmenu->MenuV033GetImageListHueLight();

               }
               else
               {

                  pimagelist = pmenu->MenuV033GetImageList();

               }

            }

         }

         if (pimagelist)
         {

            pimagelist->get_image_info(uImage, &ii);

            ::rectangle_i32 & rectImageInfo(ii.m_rectangle);
            rectImage.offset(1, 1);
            rectImage.top = rectImage.bottom - rectImageInfo.height();
            rectImage.right = rectImage.left + rectImageInfo.width();

            if (echeck() == ::check_checked)
            {

               pgraphics->fill_rectangle(rectImageBorder, rgb(127, 127, 127));

               //auto psession = get_session();

               auto pstyle = get_style(pgraphics);

               auto colorDarkShadow = pstyle->get_color(this, ::user::e_element_dark_shadow);

               auto colorHilite = pstyle->get_color(this, ::user::e_element_hilite);

               pgraphics->draw_3drect(rectImageBorder, colorDarkShadow, colorHilite);

            }

            pimagelist->draw(pgraphics, uImage, rectImage.top_left(), 0);

         }

      }
      else
      {

         auto pstyle = get_style(pgraphics);

         if (pstyle)
         {

            pstyle->draw_check(this, get_echeck(), m_rectCheckBox, pgraphics);

         }

      }

   }


   void menu_button::on_message_create(::message::message * pmessage)
   {

      //descriptor().set_control_type(e_control_type_menu_button);

      pmessage->previous();

   }


   void menu_button::on_message_mouse_move(::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      pmouse->previous();


   }


   bool menu_button::keyboard_focus_is_focusable() const
   {

      return false;

   }


   void menu_button::on_calc_size(calc_size * pcalcsize)
   {

      auto pstyle = get_style(pcalcsize->m_pgraphics);

      pcalcsize->m_pgraphics->set_font(this, ::user::e_element_none);

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

      auto rectMargin = get_margin(pstyle);

      auto rectBorder = get_border(pstyle);

      auto rectPadding = get_padding(pstyle);

      size.cx += rectMargin.left + rectBorder.left + rectPadding.left;

      size.cx += rectMargin.right;

      size.cx += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      size.cx += rectPadding.left;

      if (m_pmenuitem->IsPopup())
      {

         size.cx += rectPadding.left;

         size.cx += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      }

      size.cx += rectMargin.right + rectBorder.right + rectPadding.right;

      size.cy += rectMargin.top + rectBorder.top + rectPadding.top;

      size.cy += rectMargin.bottom + rectBorder.bottom + rectPadding.bottom;

      pcalcsize->m_size = size;

   }


} // namespace user



