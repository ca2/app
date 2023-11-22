#include "framework.h"
#include "button.h"
#include "item.h"
#include "menu.h"
#include "aura/user/user/calc_size.h"
#include "acme/constant/message.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/image/list.h"
#include "base/user/user/style.h"
#include "base/platform/session.h"
#include "base/user/user/user.h"
#include "base/user/menu/central.h"
#include "aura/message/user.h"


namespace user
{


   menu_button::menu_button()
   {

      m_econtroltype = e_control_type_menu_button;
      //m_erectMargin = rect_menu_item_margin;
      //m_erectBorder = rect_menu_item_border;
      //m_erectPadding = rect_menu_item_padding;
      //m_eintTextAlign = int_menu_item_draw_text_flags;

      m_flagNonClient.erase(::user::interaction::e_non_client_focus_rect);


   }


   menu_button::~menu_button()
   {

   }


   void menu_button::initialize_menu_interaction(menu_item* pitem)
   {

      //auto estatus = 
      
      button::initialize(pitem);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pmenuitem = pitem;

      //return estatus;

   }


   void menu_button::install_message_routing(::channel * pchannel)
   {

      ::user::button::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &menu_button::on_message_create);

   }


   //bool menu_button::create_interaction(::user::interaction *pparent, const ::atom & atom)
   //{

   //   if (!button::create_interaction(pparent, atom))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   void menu_button::_001OnDrawDefault(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();
      
      if(rectangleX.is_empty())
      {
       
         return;
         
      }

      if (m_atom == "separator")
      {

         _001OnButtonDrawBackground(pgraphics);

         //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         //pgraphics->fill_rectangle(rectangleX, _001GetButtonBackgroundColor());

         //auto ppen = __create < ::draw2d::pen > ();

         //ppen->create_solid(1.0, _001GetColor(color_button_text));

         //pgraphics->set(ppen);

         //pgraphics->set_current_point(rectangleX.left() + rectangleX.width() / 8, (rectangleX.top() + rectangleX.bottom()) / 2);

         ///pgraphics->line_to(rectangleX.right() - rectangleX.width() / 8, (rectangleX.top() + rectangleX.bottom()) / 2);

         return;

      }

      button::_001OnDraw(pgraphics);

      if (m_pmenuitem != nullptr && m_pmenuitem->m_bPopup)
      {

         auto pbrush = __create < ::draw2d::brush > ();

         pbrush->create_solid(argb(255, 0, 0, 0));

         auto ppen = __create < ::draw2d::pen > ();

         ppen->create_solid(1, rgb(0, 0, 0));
         pgraphics->set(ppen);
         pgraphics->set(pbrush);
         ::rectangle_i32 rectanglePopupArrow;
         rectanglePopupArrow.left() = rectangleX.right() - 9;
         rectanglePopupArrow.right() = rectangleX.right() - 4;
         rectanglePopupArrow.top() = ((rectangleX.top() + rectangleX.bottom()) / 2) - 4;
         rectanglePopupArrow.bottom() = ((rectangleX.top() + rectangleX.bottom()) / 2) + 4;
         point_f64_array pointa;
         pointa.add(point_i32(rectanglePopupArrow.left(), rectanglePopupArrow.bottom()));
         pointa.add(point_i32(rectanglePopupArrow.right(), (rectanglePopupArrow.bottom() + rectanglePopupArrow.top()) / 2));
         pointa.add(point_i32(rectanglePopupArrow.left(), rectanglePopupArrow.top()));
         pointa.add(point_i32(rectanglePopupArrow.left(), rectanglePopupArrow.bottom()));
         pgraphics->polygon(pointa);
      }

      _001DrawCheck(pgraphics);

   }


   ::color::color menu_button::_001GetButtonBackgroundColor()
   {

      auto colorBackground = ::user::button::_001GetButtonBackgroundColor();

      colorBackground.m_u8Opacity = 200;

      return colorBackground;

   }


   void menu_button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::pointer<::base::style>pbasestyle = get_style(pgraphics);

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
      
      ::user::button::on_layout(pgraphics);

//      if (m_puserstyle == nullptr)
//      {
//
//         if (m_pmenuitem != nullptr)
//         {
//
//            ::pointer<::user::menu>pinteraction = m_pmenuitem->m_pmenuitem;
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

      //if (m_atom != "separator")
      {

         ::user::button::_001OnNcDraw(pgraphics);

      }

   }


   void menu_button::_001DrawCheck(::draw2d::graphics_pointer & pgraphics)
   {

      ::u32 uImage = 0xffffffffu;

      if(m_pmenuitem != nullptr)
      {

         auto psession = get_session();

         auto puser = psession->baseuser();

         if (puser)
         {

            auto pmenu = puser->menu();

            if (pmenu)
            {

               uImage = pmenu->command_image(m_pmenuitem->m_atom);

            }

         }

      }

      if(uImage != 0xffffffffu)
      {

         ::rectangle_i32 rectangleImage = m_rectangleCheckBox;
         ::rectangle_i32 rectangleImageBorder = rectangleImage;
         rectangleImageBorder.inflate(2, 2);
         ::image_list::info ii;
         ::pointer<image_list>pimagelist;

         auto psession = get_session();

         auto puser = psession->baseuser();

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

            ::rectangle_i32 & rectangleImageInfo(ii.m_rectangle);
            rectangleImage.offset(1, 1);
            rectangleImage.top() = rectangleImage.bottom() - rectangleImageInfo.height();
            rectangleImage.right() = rectangleImage.left() + rectangleImageInfo.width();

            if (echeck() == ::e_check_checked)
            {

               pgraphics->fill_rectangle(rectangleImageBorder, rgb(127, 127, 127));

               //auto psession = get_session();

               auto pstyle = get_style(pgraphics);

               auto colorDarkShadow = pstyle->get_color(this, ::e_element_dark_shadow);

               auto colorHilite = pstyle->get_color(this, ::e_element_hilite);

               pgraphics->draw_inset_3d_rectangle(rectangleImageBorder, colorDarkShadow, colorHilite, 1.0);

            }

            pimagelist->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

         }

      }
      else
      {

         auto pstyle = get_style(pgraphics);

         if (pstyle)
         {

            pstyle->draw_check(this, get_echeck(), m_rectangleCheckBox, pgraphics);

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

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->previous();


   }


   bool menu_button::keyboard_focus_is_focusable()
   {

      return false;

   }


   ::size_f64 menu_button::get_preferred_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto size = button::get_preferred_size(pgraphics);

//      if (m_estockicon != e_stock_icon_none)
//      {
//
//         pcalcsize->m_size.cx() = 24;
//
//         pcalcsize->m_size.cy() = 24;
//
//
//         return;
//
//      }
//
//      auto pstyle = get_style(pcalcsize->m_pgraphics);
//
//      pcalcsize->m_pgraphics->set_font(this, ::e_element_none);
//
//      string strButtonText;
//
//      strButtonText = get_window_text();
//
//      bool bSeparator = false;
//
//      if (strButtonText.is_empty())
//      {
//
//         strButtonText = "separator";
//
//         bSeparator = true;
//
//      }
//
//      auto size = pcalcsize->m_pgraphics->get_text_extent(strButtonText);
//
//      if (bSeparator)
//      {
//
//         size.cy() /= 2;
//
//      }
//
//      auto rectangleMargin = get_margin(pstyle);
//
//      auto rectangleBorder = get_border(pstyle);
//
//      auto rectanglePadding = get_padding(pstyle);
//
//      size.cx() += rectangleMargin.left() + rectangleBorder.left() + rectanglePadding.left();
//
//      size.cx() += rectangleMargin.right();435
//
//      size.cx() += m_pmenuitem->m_pmenu->m_dCheckBoxSize;
//
//      size.cx() += rectanglePadding.left();

      if (m_pmenuitem->is_popup())
      {

         auto pstyle = get_style(pgraphics);

         auto rectanglePadding = get_padding(pstyle);

         size.cx() += rectanglePadding.left();

         size.cx() += m_pmenuitem->m_pmenu->m_dCheckBoxSize;

      }

//      size.cx() += rectangleMargin.right() + rectangleBorder.right() + rectanglePadding.right();
//
//      size.cy() += rectangleMargin.top() + rectangleBorder.top() + rectanglePadding.top();
//
//      size.cy() += rectangleMargin.bottom() + rectangleBorder.bottom() + rectanglePadding.bottom();
//
//      pcalcsize->m_size = size;

      return size;

   }


   bool menu_button::on_click(::item * pitem)
   {

      if (get_parent()->on_click(m_pmenuitem))
      {

         return true;

      }

      return false;

   }


} // namespace user



