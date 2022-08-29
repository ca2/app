#include "framework.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/list.h"
#include "toolbar.h"
#include "base/user/menu/central.h"
#include "aura/user/user/style.h"
#include "core/platform/session.h"
#include "base/user/user/user.h"
#include "aura/message/user.h"
#include "base/user/user/tab.h"


#define TIMER_HOVER 321654


#define EXTRA_TEXT_CX 3
#define EXTRA_TEXT_CY 1

//#define ITEM_SEP_CX 2
//#define ITEM_SEP_CY 2
//#define TOOL_SEP_CX 8

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//#define ITEMHOVERCX 0
//#define ITEMHOVERCY 0
/*#define ITEMHOVERPADLEFT 2
#define ITEMHOVERPADTOP 2
#define ITEMHOVERPADRIGHT 2
#define ITEMHOVERPADBOTTOM 2*/
//#define ITEMPRESSCX 3
//#define ITEMPRESSCY 3
/*#define ITEMPRESSPADLEFT 2
#define ITEMPRESSPADTOP 2
#define ITEMPRESSPADRIGHT 2
#define ITEMPRESSPADBOTTOM 2*/
//#define IMAGE_SEP_CX 2
//#define PAD_CX 1
//#define PAD_CX 1


simple_toolbar::simple_toolbar()
{

   m_bClickDefaultMouseHandling = true;

   m_bStyleFlat = true;

   m_econtroltype = ::user::e_control_type_toolbar;

   m_iImageSpacing = -1;

   m_sizePress.set(0);

   m_sizeSpacing.set(-1);

   m_sizeSeparator.set(-1);

   m_rectangleBorder.set(-1);

   m_rectangleItemPad.set(-1);

   m_dFontSize = 1.0;

   // lakic
   m_sizeSpacing.cx = 8;

   m_rectangleItemPad.set(9, 9);

   m_rectangleBorder.set(9, 9);
   // end lakic

   //m_pitemCurrent = -1;

   //m_bTransparentBackground = true;

   m_sizeImage.cx = 16;
   m_sizeImage.cy = 15;

   m_sizeButton.cx = 23;
   m_sizeButton.cy = 22;

   m_bDelayedButtonLayout = true;



}


simple_toolbar::~simple_toolbar()
{

}


void simple_toolbar::install_message_routing(::channel * pchannel)
{

   ::user::toolbar::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_create       , pchannel, this, &simple_toolbar::on_message_create);
   //MESSAGE_LINK(e_message_mouse_move    , pchannel, this, &simple_toolbar::on_message_mouse_move);
   //MESSAGE_LINK(e_message_left_button_down  , pchannel, this, &simple_toolbar::on_message_left_button_down);
   //MESSAGE_LINK(e_message_left_button_up    , pchannel, this, &simple_toolbar::on_message_left_button_up);
   //MESSAGE_LINK(e_message_non_client_hittest    , pchannel, this, &simple_toolbar::_001OnNcHitTest);
   //MESSAGE_LINK(e_message_mouse_leave   , pchannel, this, &simple_toolbar::on_message_mouse_leave);

   //install_click_default_mouse_handling(pchannel);
   
}


//bool simple_toolbar::create(::user::interaction * puiParent, u32 uStyle, atom nID)
//{
//
//   return create_toolbar(puiParent, 0, uStyle, nID);
//
//}


//bool simple_toolbar::create_toolbar(::user::interaction * puiParent, u32 dwCtrlStyle, u32 uStyle, atom nID)
//{
//
//   ASSERT_VALID(puiParent);   // must have a parent
//   ASSERT(!((uStyle & CBRS_SIZE_FIXED) && (uStyle & CBRS_SIZE_DYNAMIC)));
//
//   //SetBorders(rectangleBorders);
//
//   // save the style
//   m_dwStyle = (uStyle & CBRS_ALL);
//   if (nID == __IDW_TOOLBAR)
//      m_dwStyle |= CBRS_HIDE_INPLACE;
//
//   uStyle &= ~CBRS_ALL;
//   uStyle |= CCS_NOPARENTALIGN | CCS_NOMOVEY | CCS_NODIVIDER | CCS_NORESIZE;
//   uStyle |= dwCtrlStyle & 0xffff;
//   m_dwCtrlStyle = dwCtrlStyle & (0xffff0000 | TBSTYLE_FLAT);
//
//   if (!::user::interaction::create_window(nullptr, nullptr, uStyle, puiParent, nID))
//   {
//
//      return false;
//
//   }
//
//   SetSizes(m_sizeButton, m_sizeImage);
//
//   return true;
//
//}


size_i32 simple_toolbar::CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz)
{

   u32 dwMode = bStretch ? LM_STRETCH : 0;

   dwMode |= bHorz ? LM_HORZ : 0;

   return CalcLayout(pgraphics, dwMode);

}


size_i32 simple_toolbar::CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics)
{

   ASSERT_VALID(this);

   ASSERT(is_window());

   ::count nCount;

   ::size_i32 sizeResult;

   nCount = m_useritema.get_count();

   if (nCount > 0)
   {

      ::rectangle_i32 rectangleItem;

      ::rectangle_i32 rectangleSize(0, 0, 0, 0);

      for (index i = 0; i < nCount; i++)
      {

         _001GetItemRect(i, rectangleItem);

         rectangleSize.unite(rectangleSize, rectangleItem);

      }

      sizeResult = rectangleSize.size();

   }

#ifdef WINDOWS_DESKTOP

   //if (GetStyle() & TBSTYLE_FLAT)
   if (m_bStyleFlat)
   {

      sizeResult.cy += 2;

   }

#else

   throw ::exception(todo);

#endif

   return sizeResult;

}


void simple_toolbar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   __pointer(::user::tab) ptab = get_typed_parent < ::user::tab >();

   if (ptab.is_set())
   {

   }

   //if (m_bDelayedButtonLayout)
   //{

   //   on_layout(pgraphics);

   //}

   ::rectangle_i32 rectangleClient;

   get_client_rect(rectangleClient);

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   auto pstyle = get_style(pgraphics);

   pgraphics->fill_rectangle(rectangleClient, get_color(pstyle, ::e_element_background));

   //::user::interaction::_001OnDraw(pgraphics);

   pgraphics->set(get_font(pstyle));

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   //auto iHover = _001GetHoverItem();

   //descriptor().set_control_type(::user::e_control_type_button);

//   select_user_schema();

   for (index iItem = 0; iItem < m_useritema.get_size(); iItem++)
   {

      //if (!::is_item(m_pitemHover, iItem))
      //{

         _001DrawItem(pgraphics, iItem);

      //}

   }

   //if (m_pitemHover->m_eelement == ::e_element_item)
   //{

   //   _001DrawItem(pgraphics, m_pitemHover);

   //}


}


//void simple_toolbar::SetTransparentBackground(bool bSet)
//{
//
//   m_bTransparentBackground = bSet;
//
//}


//void simple_toolbar::TransparentEraseNonClient(::draw2d::graphics_pointer & pgraphics)
//{
//
//
//
//   m_pimageDraft->get_graphics()->BitBlt(0, 0, 7, 7, pgraphics, 0, 0);
//
//   ::rectangle_i32 rectangleWindow;
//   get_window_rect(rectangleWindow);
//   rectangleWindow.offset(-rectangleWindow.top_left());
//   if (m_bTransparentBackground)
//   {
//      class imaging & imaging = psystem->imaging();
//      if (m_pitemHover)
//      {
//         imaging.color_blend(
//         pgraphics,
//         rectangleWindow.left,
//         rectangleWindow.top,
//         rectangleWindow.width(),
//         rectangleWindow.height(),
//         rgb(215, 215, 210),
//         220);
//      }
//      else
//      {
//         imaging.color_blend(
//         pgraphics,
//         rectangleWindow.left,
//         rectangleWindow.top,
//         rectangleWindow.width(),
//         rectangleWindow.height(),
//         rgb(215, 215, 210),
//         180);
//      }
//   }
//   else
//   {
//#ifdef WINDOWS_DESKTOP
//      pgraphics->fill_rectangle(rectangleWindow, psession->get_default_color(COLOR_3DFACE));
//#else
//      pgraphics->fill_rectangle(rectangleWindow, argb(255, 190, 184, 177));
//#endif
//   }
//
//   // Desenha chanfro
//   ::color32_t color32 = m_pimageDraft->GetPixel(0, 0);
//   pgraphics->SetPixel(0, 0, color32);
//   pgraphics->SetPixel(0, 1, m_pimageDraft->GetPixel(0, 1));
//   pgraphics->SetPixel(0, 2, m_pimageDraft->GetPixel(0, 2));
//   pgraphics->SetPixel(0, 3, m_pimageDraft->GetPixel(0, 3));
//   pgraphics->SetPixel(0, 4, m_pimageDraft->GetPixel(0, 4));
//   pgraphics->SetPixel(0, 5, m_pimageDraft->GetPixel(0, 5));
//   pgraphics->SetPixel(0, 6, m_pimageDraft->GetPixel(0, 6));
//   pgraphics->SetPixel(1, 0, m_pimageDraft->GetPixel(1, 0));
//   pgraphics->SetPixel(1, 1, m_pimageDraft->GetPixel(1, 1));
//   pgraphics->SetPixel(1, 2, m_pimageDraft->GetPixel(1, 2));
//   pgraphics->SetPixel(1, 3, m_pimageDraft->GetPixel(1, 3));
//   pgraphics->SetPixel(1, 4, m_pimageDraft->GetPixel(1, 4));
//   pgraphics->SetPixel(1, 5, m_pimageDraft->GetPixel(1, 5));
//   pgraphics->SetPixel(2, 0, m_pimageDraft->GetPixel(2, 0));
//   pgraphics->SetPixel(2, 1, m_pimageDraft->GetPixel(2, 1));
//   pgraphics->SetPixel(2, 2, m_pimageDraft->GetPixel(2, 2));
//   pgraphics->SetPixel(2, 3, m_pimageDraft->GetPixel(2, 3));
//   pgraphics->SetPixel(2, 4, m_pimageDraft->GetPixel(2, 4));
//   pgraphics->SetPixel(3, 0, m_pimageDraft->GetPixel(3, 0));
//   pgraphics->SetPixel(3, 1, m_pimageDraft->GetPixel(3, 1));
//   pgraphics->SetPixel(3, 2, m_pimageDraft->GetPixel(3, 2));
//   pgraphics->SetPixel(3, 3, m_pimageDraft->GetPixel(3, 3));
//   pgraphics->SetPixel(4, 0, m_pimageDraft->GetPixel(4, 0));
//   pgraphics->SetPixel(4, 1, m_pimageDraft->GetPixel(4, 1));
//   pgraphics->SetPixel(4, 2, m_pimageDraft->GetPixel(4, 2));
//   pgraphics->SetPixel(5, 0, m_pimageDraft->GetPixel(5, 0));
//   pgraphics->SetPixel(5, 1, m_pimageDraft->GetPixel(5, 1));
//   pgraphics->SetPixel(6, 0, m_pimageDraft->GetPixel(6, 0));
//
//
//   //pgraphics->BitBlt(0, 0, 7, 7, &m_dcDraft, 0, 0);
//
//   //
//
//   // draw borders in non-client area
//   DrawBorders(pgraphics, rectangleWindow);
//   /*   pgraphics->fill_rectangle(
//   rectangleWindow.left + 7, rectangleWindow.top,
//   rectangleWindow.right, rectangleWindow.top + 1,
//   rgb(128, 128, 123));*/
//
//   // erase parts not drawn
//   //pgraphics->IntersectClipRect(rectangleWindow);
//   //SendMessage(e_message_erase_background, (WPARAM)pgraphics->get_handle1());
//
//   // draw gripper in non-client area
//   DrawGripper(pgraphics, rectangleWindow);
//
//   //pgraphics->set_origin(pointContext);
//}


void simple_toolbar::on_message_create(::message::message * pmessage)
{

   if (pmessage->previous())
   {

      return;

   }
   
   //descriptor().m_econtroltype = ::user::e_control_type_toolbar;

   m_pimageDraft = m_pcontext->m_pauracontext->create_image({20,  20 });

}


//void simple_toolbar::on_command_probe(::user::interaction * puserinteraction, bool bDisableIfNoHndler)
//{
//
//   simple_tool_command state(this);
//
//   state.m_puiOther = (this);
//
//   state.m_iCount = _001GetItemCount();
//
//   for (state.m_iIndex = 0; state.m_iIndex < state.m_iCount; state.m_iIndex++)
//   {
//
//      if (m_useritema[state.m_iIndex]->m_atom != "separator")
//      {
//
//         state.m_atom = m_useritema[state.m_iIndex]->m_atom;
//
//         // allow reflections
//         //if (::user::interaction::on_command(0,
//         //   MAKELONG((index)CN_UPDATE_::message::command, e_message_command+WM_REFLECT_BASE),
//         //   &state, nullptr))
//         //   continue;
//
//         state.m_bEnableChanged = false;
//
//         // allow the toolbar itself to have update handlers
//         _001SendCommandProbe(&state);
//
//         if (state.m_bRet)
//         {
//
//            continue;
//
//         }
//
//         //if (!state.m_bEnableChanged)
//         //{
//         //
//         //   if (m_useritema[state.m_iIndex]->m_bEnableIfHasCommandHandler)
//         //   {
//
//         //      if (!state.m_bHasCommandHandler)
//         //      {
//
//         //         continue;
//
//
//         //      }
//
//         //   }
//
//         //}
//
//         // allow the owner to process the update
//         state.do_probe(puserinteraction);
//
//      }
//
//   }
//
//   // update the dialog controls added to the toolbar
//   update_dialog_controls(puserinteraction);
//
//}

#define CX_OVERLAP 0


size_i32 simple_toolbar::CalcSize(::draw2d::graphics_pointer & pgraphics, index nCount)
{

   ASSERT(nCount > 0);

   pgraphics->set_font(this, ::e_element_none);

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   int iImageSpacing = get_image_spacing();

   ::rectangle_i32 rectangleBorder = get_bar_border();

   //size_i32 sPress = get_press_shift();

   auto sSpacing = get_item_spacing();

   auto sSeparator = get_separator_size();

   point_i32 cur(rectangleBorder.left, rectangleBorder.top);

   ::size_i32 sizeResult(rectangleBorder.left, rectangleBorder.top);

   index buttonx, buttony;

   auto iC = minimum(nCount, m_useritema.get_size());

   ::rectangle_i32 rectangleItemPad = get_item_pad();

   string str;

   bool bFirstInRow = true;

   int iRowStart = 0;

   int i;

   for (i = 0; i < iC; i++)
   {

      if (!bFirstInRow)
      {

         cur.x += sSpacing.cx;

      }

      bFirstInRow = false;

      ::user::toolbar_item & item = *::user::__toolbar_item(m_useritema[i]);

      //index cySep = item.m_iImage;

      if (item.m_estyle & e_toolbar_item_style_separator)
      {

         buttonx = sSeparator.cx;

         buttony = rectangleItemPad.top + rectangleItemPad.bottom; //  +sPress.cy;

      }
      else
      {

         if (item.m_pimage->is_set())
         {

            buttonx = item.m_pimage->width() + iImageSpacing + rectangleItemPad.left + rectangleItemPad.right;

            buttony = item.m_pimage->height() + rectangleItemPad.top + rectangleItemPad.bottom;

         }
         else
         {

            buttonx = rectangleItemPad.left + rectangleItemPad.right;

            buttony = rectangleItemPad.top + rectangleItemPad.bottom;

         }

         size_f64 size;

         GetButtonText(i, str);

         size = pgraphics->get_text_extent(str);

         buttonx += (index) (size.cx + EXTRA_TEXT_CX);

         buttony += (index) (size.cy + EXTRA_TEXT_CY);

      }

      if (item.m_estate & e_toolbar_item_state_hidden)
      {

         continue;

      }

      item.m_rectangle.left = cur.x;

      item.m_rectangle.right = (::i32) (cur.x + buttonx);

      cur.x += (::i32) buttonx; //  +sPress.cx;

      sizeResult.cx = maximum(cur.x, sizeResult.cx);

      cur.y = (::i32) maximum(cur.y, buttony);

      if (item.m_estate & e_toolbar_item_state_wrap)
      {

         for (int j = iRowStart; j <= i; j++)
         {

            item.m_rectangle.top = sizeResult.cy;

            item.m_rectangle.bottom = sizeResult.cy + cur.y;

         }

         if (sizeResult.cy > rectangleBorder.top)
         {

            cur.y += sSpacing.cy;

         }

         // cur.y += sPress.cy;

         iRowStart = i + 1;

         sizeResult.cy += cur.y;

         cur.x = rectangleBorder.left;

         cur.y = 0;

         if (item.m_estyle & e_toolbar_item_style_separator)
         {

            sizeResult.cy += sSeparator.cy;

         }

         bFirstInRow = true;

      }

   }

   for (int j = iRowStart; j < i; j++)
   {

      m_useritema[j]->m_rectangle.top = sizeResult.cy;

      m_useritema[j]->m_rectangle.bottom = sizeResult.cy + cur.y;

   }

   // sizeResult.cy += sPress.cy;

   sizeResult.cy += cur.y;

   sizeResult.cx += rectangleBorder.right;

   sizeResult.cy += rectangleBorder.bottom;

   return sizeResult;

}


void simple_toolbar::_001DrawItem(::draw2d::graphics_pointer & pgraphics, index iItem)
{

   auto pstyle = get_style(pgraphics);

   if(pstyle)
   {
   
      if (pstyle->_001DrawToolbarItem(pgraphics, iItem, this))
      {

         return;

      }

   }

   return _001DrawSimpleToolbarItem(pgraphics, iItem);


}


void simple_toolbar::_001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem)
{

   __pointer(::user::toolbar_item) pitem = m_useritema[iItem];

   if (::is_null(pitem))
   {

      return;

   }


   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   ::rectangle_i32 rectangleItem;

   ::rectangle_i32 rectangleImage;

   pgraphics->set_font(this, ::e_element_none);

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   auto estyle = get_item_style(iItem);

   __pointer(::core::session) psession = get_session();

   auto puser = psession->user();

   __pointer(::user::menu_central) pmenucentral = puser->menu();

   ::u32 uImage = pmenucentral->command_image(pitem->m_atom);
   
   auto estate = get_item_user_state(iItem);

   _001GetElementRect(iItem, rectangleItem, ::e_element_item, estate);

   _001GetElementRect(iItem, rectangleImage, ::e_element_image, estate);

   if (estyle & e_toolbar_item_style_separator)
   {

      ::rectangle_i32 rectangleSeparator;

      rectangleSeparator.left = (rectangleImage.left + rectangleImage.right) / 2 - 1;

      rectangleSeparator.right = rectangleSeparator.left + 2;

      rectangleSeparator.top = rectangleImage.top;

      rectangleSeparator.bottom = rectangleImage.bottom;

      pgraphics->draw_inset_3d_rectangle(rectangleSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255));

   }
   else
   {

      if (estate & ::user::e_state_hover)
      {

         if (estate & ::user::e_state_checked)
         {

            _001GetElementRect(iItem, rectangleItem, ::e_element_item, estate);

            _001GetElementRect(iItem, rectangleImage,::e_element_image, estate);

            if ((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               pgraphics->fill_rectangle(rectangleItem, argb(208, 255, 255, 250));

               pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

            }

            if (uImage != 0xffffffffu)
            {

               if (!(estate & ::user::e_state_disabled))
               {

                  // button is enabled
                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

               }
               else
               {

                  // button is disabled
                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

               }

            }

         }
         else
         {

            ::rectangle_i32 rectangleShadow;

            _001GetElementRect(iItem, rectangleShadow, ::e_element_item, estate);

            if ((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               auto ppen = __create < ::draw2d::pen > ();

               ppen->create_solid(1, argb(190, 92, 184, 92));

               auto pbrush = __create < ::draw2d::brush >();

               pbrush->create_solid(argb(123, 180, 184, 255));

               pgraphics->set(ppen);

               pgraphics->set(pbrush);

               pgraphics->rectangle(rectangleItem);

            }

            if (pitem->m_pimage->is_set())
            {

               ::rectangle_i32 rectangle;

               _001GetElementRect(iItem, rectangle, ::e_element_image, estate);

               image_source imagesource(pitem->m_pimage);

               image_drawing_options imagedrawingoptions(rectangle);

               imagedrawingoptions.opacity(0.85);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffffu)
            {

               ::rectangle_i32 rectangle;

               _001GetElementRect(iItem, rectangle, ::e_element_image, estate);

               pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, rectangle.top_left(), 0);

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

            }

         }

      }
      else if (estate & ::user::e_state_pressed)
      {

         if ((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
         {

            auto ppen = __create < ::draw2d::pen > ();

            ppen->create_solid(1, argb(255, 92, 92, 92));

            auto pbrush = __create < ::draw2d::brush >();

            pbrush->create_solid(argb(255, 255, 255, 255));

            pgraphics->set(ppen);

            pgraphics->set(pbrush);

            pgraphics->rectangle(rectangleItem);

         }

         if (pitem->m_pimage->is_set())
         {

            ::rectangle_i32 rectangle;

            _001GetElementRect(iItem, rectangle, ::e_element_image, estate);

            image_source imagesource(pitem->m_pimage);

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }
         else if (uImage != 0xffffffff)
         {

            pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

         }

      }
      else
      {

         if (!(estate & ::user::e_state_disabled))
         {

            _001GetElementRect(iItem, rectangleItem, ::e_element_item, estate);

            pgraphics->fill_rectangle(rectangleItem, argb(190, 255, 255, 255));

         }

         if (estate & ::user::e_state_checked)
         {

            pgraphics->draw_inset_3d_rectangle(rectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255));

         }

         if (pitem->m_pimage->is_set())
         {

            ::rectangle_i32 rectangle;

            if(_001GetElementRect(iItem, rectangle, ::e_element_image, estate))
            {

//            if(rectangle.width() > 10000)
               //          {

               //           output_debug_string("width > 10000");

               //         _001GetElementRect(iItem, rectangle, element_image);

               //    }

               image_source imagesource(pitem->m_pimage);

               image_drawing_options imagedrawingoptions(rectangle);

               imagedrawingoptions.opacity(0.23);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }
         else if (uImage != 0xffffffff)
         {

            if (!(estate & ::user::e_state_disabled))
            {

               pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

            }
            else
            {

               pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectangleImage.top_left(), 0);

            }

         }

      }

   }

   if (pitem->m_str.has_char())
   {

      pgraphics->set_font(this, ::e_element_none);

      m_dFontSize = pgraphics->m_pfont->m_dFontSize;

      ::rectangle_i32 rectangleText;

      auto pbrushText = __create < ::draw2d::brush > ();

      if (!(estate & ::user::e_state_disabled))
      {

         pbrushText->create_solid(argb(255, 0, 0, 0));

      }
      else
      {

         pbrushText->create_solid(argb(255, 120, 120, 118));

      }

      pgraphics->set(pbrushText);

      if (_001GetElementRect(iItem, rectangleText, ::e_element_text, estate) && rectangleText.right > 0)
      {

         pgraphics->_DrawText(pitem->m_str, rectangleText, e_align_bottom_left, e_draw_text_no_prefix);

      }

   }

}


bool simple_toolbar::_001GetElementRect(index iItem, RECTANGLE_I32 * prectangle, ::enum_element eelement, ::user::enum_state estate)
{

   if (iItem < 0 || iItem >= m_useritema.get_size())
   {

      return false;

   }

   ::rectangle_i32 rectangleItemPad = get_item_pad();

   int iImageSpacing = get_image_spacing();

   ::rectangle_i32 rectangle;

   ::user::toolbar_item & item = *::user::__toolbar_item(m_useritema[iItem]);

   if ((item.m_estyle & e_toolbar_item_style_separator) != 0)
   {

      rectangle = item.m_rectangle;

   }
   else
   {

      switch (eelement)
      {
         case ::e_element_item:

         rectangle = item.m_rectangle;

         break;
      case ::e_element_image:

         if (item.m_pimage->is_null() || item.m_pimage->area() <= 0)
         {

            return false;

         }

         rectangle = item.m_rectangle;

         rectangle.left += rectangleItemPad.left;
         rectangle.bottom -= rectangleItemPad.bottom;
         rectangle.top = rectangle.bottom - item.m_pimage->height();
         rectangle.right = rectangle.left + item.m_pimage->width();

         break;
      case ::e_element_text:
      {

         rectangle = item.m_rectangle;

         rectangle.left += rectangleItemPad.left;

         if (item.m_pimage->is_set() && item.m_pimage->area() > 0)
         {

            rectangle.left += item.m_pimage->width();

            rectangle.left += iImageSpacing;

         }

         rectangle.top += rectangleItemPad.top;
         rectangle.right -= (rectangleItemPad.right);
         rectangle.bottom -= (rectangleItemPad.bottom);
         break;

      }
            
         default:
            break;
            
      }
            
      if(estate & ::user::e_state_pressed)
      {
         
         ::size_i32 sPress = get_press_shift();
         
         rectangle.offset(sPress.cx, sPress.cy);
         
      }

   }
      
   *prectangle = rectangle;

   return true;

}


void simple_toolbar::SetSizes(const ::size_i32 & sizeButton, const ::size_i32 & sizeImage)
{
   ASSERT_VALID(this);

   // sizes must be non-zero and positive
   ASSERT(sizeButton.cx > 0 && sizeButton.cy > 0);
   ASSERT(sizeImage.cx > 0 && sizeImage.cy > 0);

   // button must be big enough to hold image
   //   + 7 pixels on x
   //   + 6 pixels on y
   ASSERT(sizeButton.cx >= sizeImage.cx + 7);
   ASSERT(sizeButton.cy >= sizeImage.cy + 6);

   //   if (::IsWindow(get_handle()))
//   if (false)
//   {
//      // set the sizes via TB_SETBITMAPSIZE and TB_SETBUTTONSIZE
//#ifdef WINDOWS_DESKTOP
//      VERIFY(send_message(TB_SETBITMAPSIZE, 0, MAKELONG(sizeImage.cx, sizeImage.cy)));
//      VERIFY(send_message(TB_SETBUTTONSIZE, 0, MAKELONG(sizeButton.cx, sizeButton.cy)));
//#else
//      //throw ::exception(todo);
//#endif
//
//      Invalidate();   // just to be nice if called when toolbar is visible
//   }
//   else
   {
      // just set our internal values for later
      m_sizeButton = sizeButton;
      m_sizeImage = sizeImage;
   }
}

/*
bool simple_toolbar::LoadBitmap(const ::string & pszResourceName)

{
ASSERT_VALID(this);
ASSERT(pszResourceName != nullptr);


// determine location of the bitmap in resource fork
HINSTANCE hInstImageWell = ::aura::FindResourceHandle(pszResourceName, RT_BITMAP);

HRSRC hRsrcImageWell = ::FindResource(hInstImageWell, pszResourceName, RT_BITMAP);

if (hRsrcImageWell == nullptr)
return false;

// load the bitmap
HBITMAP hbmImageWell;
//   hbmImageWell = ::aura::LoadSysColorBitmap(hInstImageWell, hRsrcImageWell);
::draw2d::memory_graphics pgraphics(this);;
hbmImageWell = imaging::LoadSysColorBitmap(pgraphics, hInstImageWell, hRsrcImageWell);


// tell common control toolbar about the new bitmap
//   if (!AddReplaceBitmap(hbmImageWell))
//      return false;

// remember the resource handles so the bitmap can be recolored if necessary
m_hInstImageWell = hInstImageWell;
m_hRsrcImageWell = hRsrcImageWell;

_001DiscardImageList();

m_pimagelist = new image_list();
m_bInternalImageList = true;

m_pimagelist->create(
   (char *) pszResourceName,

   m_sizeImage.cx,
   1,
   rgb(192, 192, 192)
   );

_001OnImageListAttrib();

*/

/*
return true;
}
*/

void simple_toolbar::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   auto rectangleClient = get_client_rect();

   if (rectangleClient.is_empty())
   {

      return;

   }

   auto pstyle = get_style(pgraphics);

   m_sizePress.cx = get_int(pstyle, ::user::e_int_button_press_shift_cx, ::user::e_state_none, 2);

   m_sizePress.cy = get_int(pstyle, ::user::e_int_button_press_shift_cy, ::user::e_state_none, 2);

   //m_bDelayedButtonLayout = false;

   bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;

   if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
   {

      CalcDynamicLayout(pgraphics, 0, LM_HORZ | LM_MRUWIDTH | LM_COMMIT);

   }
   else if (bHorz)
   {

      CalcDynamicLayout(pgraphics, 0, LM_HORZ | LM_HORZDOCK | LM_COMMIT);

   }
   else
   {

      CalcDynamicLayout(pgraphics, 0, LM_VERTDOCK | LM_COMMIT);

   }

   if (m_dwCtrlStyle & TBSTYLE_ALIGN_CENTER)
   {

      output_debug_string("please_center_align");

      if (m_useritema.has_elements())
      {

         CalcSize(pgraphics, (index)(m_useritema.get_count()));

         for (index i = 0; i < m_useritema.get_count(); i++)
         {

            auto pitem = ::user::__toolbar_item(m_useritema[i]);

            if (pitem->m_estate & e_toolbar_item_state_wrap || i == m_useritema.get_upper_bound())
            {

               int iTotalX = 0;

               for (index j = 0; j <= i; j++)
               {

                  iTotalX += m_useritema[j]->m_rectangle.width() + get_item_spacing().cx;

               }

               int offsetx = (rectangleClient.width() - iTotalX) / 2;

               for (index j = 0; j <= i; j++)
               {

                  m_useritema[j]->m_rectangle.offset(offsetx, 0);

               }

            }

         }

      }

   }

}


//void simple_toolbar::on_message_mouse_move(::message::message * pmessage)
//{
//
//   auto pmouse = pmessage->m_union.m_pmouse;
//
//   ::point_i32 point = pmouse->m_point;
//
//   screen_to_client()(point);
//
//   if (m_bDockTrack)
//   {
//
//      pmessage->previous();
//
//   }
//   else
//   {
//
//      _001Hover(point);
//
//      if (m_pitemHover)
//      {
//
//         pmouse->m_bRet = true;
//
//         pmouse->set_lresult(1);
//
//      }
//
//      pmessage->previous();
//
//   }
//
//}


//void simple_toolbar::on_message_left_button_down(::message::message * pmessage)
//{
//
//   auto pmouse = pmessage->m_union.m_pmouse;
//
//   auto point = screen_to_client(pmouse->m_point);
//
//   m_pitemCurrent = hit_test(pmouse);
//
//   if (m_pitemCurrent)
//   {
//
//      pmouse->m_bRet = true;
//
//      pmouse->set_lresult(1);
//
//   }
//
//   set_need_redraw();
//
//   pmessage->previous();
//
//}
//
//
//void simple_toolbar::on_message_left_button_up(::message::message * pmessage)
//{
//
//   auto pmouse = pmessage->m_union.m_pmouse;
//
//   auto point = pmouse->m_point;
//
//   screen_to_client()(point);
//
//   if (m_bDockTrack)
//   {
//
//      pmessage->previous();
//
//   }
//   else
//   {
//
//      auto item = hit_test(pmouse);
//
//      if (item && item == m_pitemCurrent)
//      {
//
//         m_pitemCurrent = item; // update point_i32 and flags
//
//         on_click(m_pitemCurrent);
//
//         pmouse->m_bRet = true;
//
//         pmouse->set_lresult(1);
//
//      }
//
//      __pointer(::user::frame_window) pTarget = get_owner();
//
//      if (pTarget == nullptr)
//      {
//
//         pTarget = get_parent_frame();
//
//      }
//
//      if (pTarget != nullptr)
//      {
//
//         pTarget->send_message_to_descendants(WM_IDLEUPDATECMDUI);
//
//      }
//
//      m_pitemCurrent = -1;
//
//      set_need_redraw();
//
//      if (pmessage->m_bRet)
//      {
//
//         return;
//
//      }
//
//      pmessage->previous();
//
//   }
//
//}


::item_pointer simple_toolbar::on_hit_test(const ::point_i32 &point)
{

   return ::user::toolbar::on_hit_test(point);

   //for (index iItem = 0; iItem < m_useritema.get_size(); iItem++)
   //{

   //   if (m_useritema[iItem]->m_rectangle.contains(point))
   //   {

   //      //item = ::item( ::e_element_item, iItem );

   //      return m_useritema[iItem];

   //   }

   //}

   //auto psession = get_session();

   //if (has_mouse_capture())
   //{

   //   //item = ::e_element_none;

   //   return nullptr;

   //}

   //::rectangle_i32 rectangleWindow;

   //get_window_rect(rectangleWindow);

   //screen_to_client(rectangleWindow);

   //if (rectangleWindow.contains(point))
   //{

   //   //item = ::e_element_none;

   //   return nullptr;

   //}
   //else
   //{

   //   //item = ::e_element_none;

   //   return nullptr;

   //}

}


//void simple_toolbar::_001Hover(const ::point_i32 & point, bool bRedraw)
//{
//
//   auto itemHover = hit_test(pmouse);
//
//   if (m_pitemHover != itemHover)
//   {
//
//      track_mouse_leave();
//
//      m_pitemHover = itemHover;
//
//      OnUpdateHover();
//
//      //      if(m_iHover < -1)
//      //    {
//      //     KillTimer(TIMER_HOVER);
//      //      }
//      //    else
//      //  {
//      //   SetTimer(TIMER_HOVER, 50, nullptr);
//      //}
//
//      if (bRedraw)
//      {
//
//         set_need_redraw();
//
//      }
//
//   }
//
//}


//void simple_toolbar::_001Hover(bool bRedraw)
//{
//
//   auto point = psession->get_cursor_position();
//
//   screen_to_client()(point);
//
//   _001Hover(point, bRedraw);
//
//}


void simple_toolbar::_001OnTimer(::timer * ptimer)
{

   ::user::toolbar::_001OnTimer(ptimer);

//   if (ptimer->m_uEvent == TIMER_HOVER)
//   {
//
//      _001Hover();
//
//   }

   // trans ::user::control_bar::OnTimer(ptimer->m_uEvent);

}


bool simple_toolbar::on_click(::item * pitem)
{

   __pointer(::user::interaction) puserinteraction = get_owner();

   if (!::is_set(pitem))
   {

      return false;

   }

   ::message::command command(pitem->m_atom);

   puserinteraction->_001SendCommand(&command);

   return command.m_bRet;

}


void simple_toolbar::_001DiscardImageList()
{

   /*

   if(m_bInternalImageList)
   {

      if(m_pimagelist != nullptr)
      {

         delete m_pimagelist;

         m_pimagelist = nullptr;

      }

   }
   else
   {

      m_pimagelist = nullptr;

   }
   */

}


void simple_toolbar::_001SetImageList(__pointer(::image_list) imagelist)
{

   __UNREFERENCED_PARAMETER(imagelist);

   /*

   m_pimagelist = imagelist;

   m_bInternalImageList = false;

   _001OnImageListAttrib();

   */

}


void simple_toolbar::_001OnImageListAttrib()
{

   /*

   if(m_pimagelistHue == nullptr)
   {

      m_pimagelistHue = new ::image_list();

   }

   ::draw2d::graphics_pointer spgraphics(e_create);

   spgraphics->CreateDC("DISPLAY", nullptr, nullptr, nullptr);

   psystem->imaging().CreateHueImageList(
      &spgraphics,
      m_pimagelistHue,
      m_pimagelist,
      rgb(192, 192, 180),
      0.50
   );

   if(m_pimagelistBlend == nullptr)
   {

      m_pimagelistBlend = new ::image_list();

   }

   psystem->imaging().Createcolor_blend_ImageList(
      m_pimagelistBlend,
      m_pimagelist,
      rgb(255, 255, 240),
      64
   );

   if(m_pimagelistHueLight == nullptr)
   {

      m_pimagelistHueLight = new ::image_list();

   }

   psystem->imaging().CreateHueImageList(
      &spgraphics,
      m_pimagelistHueLight,
      m_pimagelist,
      rgb(220, 220, 215),
      0.50
      );

   */

}




//etoolbar_item_state simple_toolbar::get_item_state(index iItem)
//{
//
//   return m_useritema[iItem]->m_estate;
//
//}
//
//
//bool simple_toolbar::set_item_state(index iItem, const etoolbar_item_state & estate)
//{
//
//   return m_useritema[iItem]->m_estate;
//
//}


//enumeration < ::enum_toolbar_item_style > simple_toolbar::GetButtonStyle(index nIndex)
//{
//
//   __pointer(::user::toolbar_item) pitem = m_useritema[nIndex];
//
//   if (!pitem)
//   {
//
//      return 0;
//
//   }
//
//   return MAKELONG(pitem->m_fsStyle, pitem->m_fsState);
//
//}
//
//
//void simple_toolbar::SetButtonStyle(index nIndex, ::u32 nStyle)
//{
//
//   __pointer(::user::toolbar_item) pitem = m_useritema[nIndex];
//
//   if (!pitem)
//   {
//
//      return;
//
//   }
//
//   if (pitem->m_fsStyle != (byte)LOWORD(nStyle) || pitem->m_fsState != (byte)HIWORD(nStyle))
//   {
//
//      pitem->m_fsStyle = (byte)LOWORD(nStyle);
//
//      pitem->m_fsState = (byte)HIWORD(nStyle);
//
//      m_bDelayedButtonLayout = true;
//
//   }
//
//}


void simple_toolbar::on_message_non_client_calculate_size(::message::message * pmessage)
{

#if defined(WINDOWS_DESKTOP) //|| defined(LINUX)

   __pointer(::message::nc_calc_size) pnccalcsize(pmessage);

   // calculate border space (will add to top/bottom, subtract from right/bottom)
   ::rectangle_i32 rectangle;

   bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;

   auto psystem = m_psystem->m_paurasystem;

   auto pdraw2d = psystem->draw2d();

   auto pgraphics = pdraw2d->create_memory_graphics(this);

   ::user::control_bar::CalcInsideRect(pgraphics, rectangle, bHorz);

   throw ::exception(todo);

   //auto pparams = (NCCALCSIZE_PARAMS *)pnccalcsize->m_pNCCALCSIZE_PARAMS;

   //// adjust non-client area for border space
   //pparams->rgrc[0].left += rectangle.left;

   //pparams->rgrc[0].top += rectangle.top;

   //pparams->rgrc[0].right += rectangle.right;

   //pparams->rgrc[0].bottom += rectangle.bottom;

#else

   throw ::exception(todo);

#endif

}


//void simple_toolbar::_001OnNcHitTest(::message::message * pmessage)
//{
//
//   __pointer(::message::nchittest) pnchittest(pmessage);
//
//   pnchittest->set_lresult(HTCLIENT);
//
//}


#define CX_OVERLAP  0


index simple_toolbar::WrapToolBar(::draw2d::graphics_pointer & pgraphics, index nCount, index nWidth)
{

   synchronous_lock synchronouslock(mutex());

   index nResult = 0;

   ASSERT(nCount > 0);

   pgraphics->set_font(this, ::e_element_none);

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   int iImageSpacing = get_image_spacing();

   auto sSeparator = get_separator_size();

   auto sSpacing = get_item_spacing();

   //size_i32 sPress = get_press_shift();

   ::rectangle_i32 rectangleItemPad = get_item_pad();

   ::rectangle_i32 rectangleBorder = get_bar_border();

   index x = rectangleBorder.left;

   string str;

   auto iC = minimum(nCount, m_useritema.get_count());

   bool bFirstInRow = true;

   for (index i = 0; i < iC; i++)
   {

      auto pitem = ::user::__toolbar_item(m_useritema[i]);

      pitem->m_estate -= e_toolbar_item_state_wrap;

      if (pitem->m_estate & e_toolbar_item_state_hidden)
      {

         continue;

      }

      GetButtonText(i, str);

      index dx, dxNext;

      if (pitem->m_estyle & e_toolbar_item_style_separator)
      {

         dx = sSeparator.cx;

         dxNext = dx;

      }
      else
      {

         dx = rectangleItemPad.left;

         if (pitem->m_pimage->is_set())
         {

            dx += pitem->m_pimage->height();

         }

         if (str.has_char() && pitem->m_pimage->is_set())
         {

            dx += iImageSpacing;

         }

         if (str.has_char())
         {

            size_f64 size = pgraphics->get_text_extent(str);

            dx = (index)  (size.cx + EXTRA_TEXT_CX);

         }

         dx += rectangleItemPad.right; // +sPress.cx;

         dxNext = dx - CX_OVERLAP;

      }

      bool bFound = false;

      if (x + dx > nWidth - rectangleBorder.right)
      {

         for (index j = i; j >= 0 && !(::user::__toolbar_item(m_useritema[j])->m_estate & e_toolbar_item_state_wrap); j--)
         {

            // find last separator that isn't hidden
            // a separator that has a command ID is not
            // a separator, but a custom control.
            if ((::user::__toolbar_item(m_useritema[j])->m_estyle & e_toolbar_item_style_separator) &&
                  (::user::__toolbar_item(m_useritema[j])->m_atom == "separator") &&
                  !(::user::__toolbar_item(m_useritema[j])->m_estate & e_toolbar_item_state_hidden))
            {

               bFound = true;

               i = j;

               x = rectangleBorder.left;

               bFirstInRow = true;

               ::user::__toolbar_item(m_useritema[j])->m_estate |= e_toolbar_item_state_wrap;

               nResult++;

               break;

            }

         }

         if (!bFound)
         {

            for (index j = i - 1; j >= 0 && !(::user::__toolbar_item(m_useritema[j])->m_estate & e_toolbar_item_state_wrap); j--)
            {

               // Never wrap anything that is hidden,
               // or any custom controls
               if ((::user::__toolbar_item(m_useritema[j])->m_estate & e_toolbar_item_state_hidden) ||
                     ((::user::__toolbar_item(m_useritema[j])->m_estyle & e_toolbar_item_style_separator) &&
                      (::user::__toolbar_item(m_useritema[j])->m_atom != "separator")))
               {

                  continue;

               }

               bFound = true;

               i = j;

               x = rectangleBorder.left;

               bFirstInRow = true;

               ::user::__toolbar_item(m_useritema[j])->m_estate |= e_toolbar_item_state_wrap;

               nResult++;

               break;

            }

         }

      }

      if (!bFound)
      {

         if (!bFirstInRow)
         {

            x += sSpacing.cx;

         }

         bFirstInRow = false;

         x += dxNext;

      }

   }

   return nResult + 1;

}


void  simple_toolbar::SizeToolBar(::draw2d::graphics_pointer& pgraphics, index nCount, index nLength, bool bVert)
{

   ASSERT(nCount > 0);

   if (!bVert)
   {

      index nMin, nMax, nTarget, nCurrent, nMid;

      // Wrap ToolBar as specified
      nMax = nLength;

      nTarget = WrapToolBar(pgraphics, nCount, nMax);

      // Wrap ToolBar vertically
      nMin = 0;

      nCurrent = WrapToolBar(pgraphics, nCount, nMin);

      if (nCurrent != nTarget)
      {
         while (nMin < nMax)
         {

            nMid = (nMin + nMax) / 2;

            nCurrent = WrapToolBar(pgraphics, nCount, nMid);

            if (nCurrent == nTarget)
            {

               nMax = nMid;

            }
            else
            {
               if (nMin == nMid)
               {

                  WrapToolBar(pgraphics, nCount, nMax);

                  break;

               }

               nMin = nMid;

            }

         }

      }

      const ::size_i32 & size = CalcSize(pgraphics, nCount);

      WrapToolBar(pgraphics, nCount, size.cx);

      CalcSize(pgraphics, nCount);

   }
   else
   {

      ::size_i32 sizeMax, sizeMin, sizeMid;

      // Wrap ToolBar vertically
      WrapToolBar(pgraphics, nCount, 0);

      sizeMin = CalcSize(pgraphics, nCount);

      // Wrap ToolBar horizontally
      WrapToolBar(pgraphics, nCount, 32767);

      sizeMax = CalcSize(pgraphics, nCount);

      while (sizeMin.cx < sizeMax.cx)
      {

         sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;

         WrapToolBar(pgraphics, nCount, sizeMid.cx);

         sizeMid = CalcSize(pgraphics, nCount);

         if (nLength < sizeMid.cy)
         {

            if (sizeMin == sizeMid)
            {

               WrapToolBar(pgraphics, nCount, sizeMax.cx);

               return;

            }

            sizeMin = sizeMid;

         }
         else if (nLength > sizeMid.cy)
         {

            sizeMax = sizeMid;

         }
         else
         {

            return;

         }

      }

   }

}


struct ___CONTROLPOS
{
   index nIndex;
   string strId;
   ::rectangle_i32 rectangleOldPos;
};


size_i32 simple_toolbar::CalcLayout(::draw2d::graphics_pointer & pgraphics, u32 dwMode, index nLength)
{

   //__pointer(::user::tab) ptab = GetTypedParent < ::user::tab >();

   //if (ptab.is_set())
   //{

   //   if (!ptab->m_bShowTabs)
   //   {

   //      return size_i32(0, 0);

   //   }

   //}

   ASSERT_VALID(this);

   if (!is_window())
   {

      return ::size_i32(0, 0);

   }

   if (dwMode & LM_HORZDOCK)
   {

      ASSERT(dwMode & LM_HORZ);

   }

   index nCount;

   ::size_i32 sizeResult(0, 0);

   nCount = _001GetItemCount();

   if (nCount > 0)
   {

      if (!(m_dwStyle & CBRS_SIZE_FIXED))
      {

         bool bDynamic = (m_dwStyle & CBRS_SIZE_DYNAMIC) != 0;

         if (bDynamic && (dwMode & LM_MRUWIDTH))
         {

            SizeToolBar(pgraphics, nCount, m_nMRUWidth);

         }
         else if (bDynamic && (dwMode & LM_HORZDOCK))
         {

            SizeToolBar(pgraphics, nCount, 32767);

         }
         else if (bDynamic && (dwMode & LM_VERTDOCK))
         {

            SizeToolBar(pgraphics, nCount, 0);

         }
         else if (bDynamic && (nLength != -1))
         {

            ::rectangle_i32 rectangle;

            CalcInsideRect(pgraphics, rectangle, (dwMode & LM_HORZ) != 0);

            bool bVert = (dwMode & LM_LENGTHY) != 0;

            index nLen = nLength + (bVert ? rectangle.height() : rectangle.width());

            SizeToolBar(pgraphics, nCount, nLen, bVert);

         }
         else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
         {

            SizeToolBar(pgraphics, nCount, m_nMRUWidth);

         }
         else
         {

            SizeToolBar(pgraphics, nCount, (dwMode & LM_HORZ) ? 32767 : 0);

         }

      }

      sizeResult = CalcSize(pgraphics, nCount);

      if (dwMode & LM_COMMIT)
      {

         ___CONTROLPOS* pControl = nullptr;

         index nControlCount = 0;

         bool bIsDelayed = m_bDelayedButtonLayout;

         m_bDelayedButtonLayout = false;

         index i;

         for (i = 0; i < nCount; i++)
         {

            if ((::user::__toolbar_item(m_useritema[i])->m_estyle & e_toolbar_item_style_separator) && (m_useritema[i]->m_atom != "separator"))
            {

               nControlCount++;

            }

         }

         if (nControlCount > 0)
         {

            ap(___CONTROLPOS) pControl(new_array, nControlCount);

            nControlCount = 0;

            for (index i = 0; i < nCount; i++)
            {

               if ((::user::__toolbar_item(m_useritema[i])->m_estyle & e_toolbar_item_style_separator) && (m_useritema[i]->m_atom != "separator"))
               {

                  pControl[nControlCount].nIndex = i;

                  pControl[nControlCount].strId = m_useritema[i]->m_atom;

                  ::rectangle_i32 rectangle;

                  _001GetItemRect(i, &rectangle);

                  client_to_screen()(rectangle);

                  pControl[nControlCount].rectangleOldPos = rectangle;

                  nControlCount++;

               }

            }

         }

         string str;

         if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
         {

            m_nMRUWidth = sizeResult.cx;

         }

         for (i = 0; i < nCount; i++)
         {

            // _SetButton(i, &m_useritema[i]);
            //
            // GetButtonText(i, str);
            //
            // ::size_i32 size;
            //
            // if(!str.is_empty())
            // {
            //
            //    ::GetTextExtentPointW(
            //       (HDC)pgraphics->get_os_data(),
            //       str,
            //       str.get_length(),
            //       &size);
            //
            //    size.cx += m_sizeButton.cx;
            //
            // }
            // else
            // {
            //
            //    size = m_sizeImage;
            //
            // }
            //
            // TBBUTTONINFOW button;
            //
            // __memset(&button, 0, sizeof(button));
            //
            // button.cbSize = sizeof(button);
            //
            // button.dwMask = TBIF_COMMAND | TBIF_SIZE;
            // button.cx = size.cx;
            // button.m_atom = i;
            //
            // GetToolBarCtrl().SetButtonInfo(i, &button);

         }

         //for (i = 0; i < nCount; i++)
         {

            // TBBUTTONINFOW buttona;
            // __memset(&buttona, 0, sizeof(buttona));
            // buttona.cbSize = sizeof(buttona);
            // buttona.dwMask =
            //    TBIF_COMMAND
            //    | TBIF_STYLE
            //    | TBIF_SIZE;
            // ::u32 uID = GetItemID(i);
            // GetToolBarCtrl().GetButtonInfo(uId, &buttona);
            // FORMATTED_TRACE("BUTTON.m_atom = %d\n", buttona.m_atom  );
            // FORMATTED_TRACE("BUTTON.m_fsStyle = %d\n", buttona.m_fsStyle  );
            // FORMATTED_TRACE("BUTTON.cx = %d\n", buttona.cx );

         }

         if (nControlCount > 0)
         {

            for (index i = 0; i < nControlCount; i++)
            {

               /* xxx

               __pointer(::user::interaction) pwindow = get_child_by_id(pControl[i]->strId);

               if (pwindow != nullptr)
               {

               ::rectangle_i32 rectangle;

               pwindow->get_window_rect(&rectangle);

               const ::point_i32 & point = rectangle.top_left() - pControl[i]->rectangleOldPos.top_left();

               _001GetElementRect(pControl[i]->nIndex, &rectangle);

               point = rectangle.top_left() + point_i32;

               pwindow->set_window_position(0, point.x, point.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);

               }*/

            }

            delete[] pControl;

         }

         m_bDelayedButtonLayout = bIsDelayed != 0;

      }

      //delete[] m_useritema;

   }

   //BLOCK: Adjust Margins
   {

      ::rectangle_i32 rectangle;

      CalcInsideRect(pgraphics, rectangle, (dwMode & LM_HORZ) != 0);

      sizeResult.cy -= rectangle.height();

      sizeResult.cx -= rectangle.width();

      const ::size_i32 & size = ::user::control_bar::CalcFixedLayout(pgraphics, (dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZ) != 0);

      sizeResult.cx = maximum(sizeResult.cx, size.cx);

      sizeResult.cy = maximum(sizeResult.cy, size.cy);

   }

   return sizeResult;

}


void simple_toolbar::GetButtonText(index i, string &str)
{

   if (i < 0 || i >= m_useritema.get_count())
   {

      str.Empty();

      return;

   }

   if (m_useritema[i].is_null())
   {

      str.Empty();

      return;

   }

   str = ::user::__toolbar_item(m_useritema[i])->m_str;

}


void simple_toolbar::OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle)
{

   // a dynamically resizeable toolbar can not have the CBRS_FLOAT_MULTI
   ASSERT(!((dwNewStyle & CBRS_SIZE_DYNAMIC) && (m_dwDockStyle & CBRS_FLOAT_MULTI)));

   // a toolbar can not be both dynamic and fixed in size_i32
   ASSERT(!((dwNewStyle & CBRS_SIZE_FIXED) && (dwNewStyle & CBRS_SIZE_DYNAMIC)));

   // CBRS_SIZE_DYNAMIC can not be disabled once it has been enabled
   ASSERT(((dwOldStyle & CBRS_SIZE_DYNAMIC) == 0) || ((dwNewStyle & CBRS_SIZE_DYNAMIC) != 0));

   if (((dwOldStyle & CBRS_BORDER_ANY) != (dwNewStyle & CBRS_BORDER_ANY)))
   {

      // recalc non-client area when border styles change
      //set_window_position(zorder_none, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

   }

   m_bDelayedButtonLayout = true;

}


size_i32 simple_toolbar::CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, ::i32 nLength, u32 dwMode)
{

   if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
         ((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
   {

      return CalcFixedLayout(pgraphics, (dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZDOCK) != 0);

   }

   return CalcLayout(pgraphics, dwMode, nLength);

}


//void simple_toolbar::on_message_mouse_leave(::message::message * pmessage)
//{
//
//   __pointer(::user::message) pusermessage(pmessage);
//
//   m_pitemHover = ::e_element_none;
//
//   OnUpdateHover();
//
//   set_need_redraw();
//
//   pusermessage->set_lresult(0);
//
//}


void simple_toolbar::SetItemImage(index iItem, index iImage)
{

   ::user::__toolbar_item(m_useritema[iItem])->m_iImage = iImage;

}

//
//void simple_toolbar::OnUpdateHover()
//{
//
//}


//index simple_toolbar::_001GetHoverItem()
//{
//
//   return m_iHover;
//
//}


void simple_toolbar::RemoveAllTools()
{

   m_useritema.erase_all();

}


rectangle_i32 simple_toolbar::get_item_pad()
{

   auto rectangle = m_rectangleItemPad;

   if (rectangle.left < 0)
   {

      rectangle.left = (::i32)(m_dFontSize / 3);

   }

   if (rectangle.right < 0)
   {

      rectangle.right = (::i32) (m_dFontSize / 3);

   }

   if (rectangle.top < 0)
   {

      rectangle.top = (::i32) (m_dFontSize / 3);

   }

   if (rectangle.bottom < 0)
   {

      rectangle.bottom = (::i32) (m_dFontSize / 3);

   }

   return rectangle;

}


rectangle_i32 simple_toolbar::get_bar_border()
{

   auto rectangle = m_rectangleBorder;

   if (rectangle.left < 0)
   {

      rectangle.left = (::i32) (m_dFontSize / 3);

   }
   if (rectangle.right < 0)
   {

      rectangle.right = (::i32) (m_dFontSize / 3);

   }
   if (rectangle.top < 0)
   {

      rectangle.top = (::i32) (m_dFontSize / 3);

   }
   if (rectangle.bottom < 0)
   {

      rectangle.bottom = (::i32)(m_dFontSize / 3);

   }

   return rectangle;

}


size_i32 simple_toolbar::get_press_shift()
{

   return m_sizePress;

}


size_i32 simple_toolbar::get_item_spacing()
{

   ::size_i32 s;

   s = m_sizeSpacing;

   if (s.cx < 0)
   {

      s.cx = 0;

   }
   if (s.cy < 0)
   {

      s.cy = 0;

   }

   return s;

}


size_i32 simple_toolbar::get_separator_size()
{

   ::size_i32 s;

   s = m_sizeSeparator;

   if (s.cx < 0)
   {

      s.cx = ::i32(m_dFontSize * 2 / 3);

   }

   if (s.cy < 0)
   {

      s.cy = ::i32(m_dFontSize * 2 / 3);

   }

   return s;

}



int simple_toolbar::get_image_spacing()
{

   int i;

   i = m_iImageSpacing;

   if (i < 0)
   {

      i = (int)(m_dFontSize / 4);

   }

   return i;

}


