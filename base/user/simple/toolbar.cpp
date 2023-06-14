#include "framework.h"
#include "toolbar.h"
#include "acme/constant/message.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/user/user/tool_item.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/draw2d/pen.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/message/user.h"
#include "aura/user/user/style.h"
#include "base/user/menu/central.h"
#include "base/user/user/user.h"
#include "base/user/user/tab.h"
#include "base/platform/session.h"


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
   m_sizeSpacing.cx() = 8;

   m_rectangleItemPad.set(9, 9);

   m_rectangleBorder.set(9, 9);
   // end lakic

   //m_ptoolitemCurrent = -1;

   //m_bTransparentBackground = true;

   m_sizeImage.cx() = 16;
   m_sizeImage.cy() = 15;

   m_sizeButton.cx() = 23;
   m_sizeButton.cy() = 22;

   m_bDelayedButtonLayout = true;



}


simple_toolbar::~simple_toolbar()
{

}


void simple_toolbar::install_message_routing(::channel * pchannel)
{

   ::user::toolbar::install_message_routing(pchannel);

   MESSAGE_LINK(MESSAGE_CREATE       , pchannel, this, &simple_toolbar::on_message_create);
   //MESSAGE_LINK(e_message_mouse_move    , pchannel, this, &simple_toolbar::on_message_mouse_move);
   //MESSAGE_LINK(e_message_left_button_down  , pchannel, this, &simple_toolbar::on_message_left_button_down);
   //MESSAGE_LINK(e_message_left_button_up    , pchannel, this, &simple_toolbar::on_message_left_button_up);
   //MESSAGE_LINK(e_message_non_client_hit_test    , pchannel, this, &simple_toolbar::_001OnNcHitTest);
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

   nCount = m_pitema->get_count();

   if (nCount > 0)
   {

      ::rectangle_i32 statusrectangleItem;

      ::rectangle_i32 rectangleSize(0, 0, 0, 0);

      for (index i = 0; i < nCount; i++)
      {

         statusrectangleItem = index_item_rectangle(i);

         rectangleSize.unite(rectangleSize, statusrectangleItem);

      }

      sizeResult = rectangleSize.size();

   }

#ifdef WINDOWS_DESKTOP

   //if (GetStyle() & TBSTYLE_FLAT)
   if (m_bStyleFlat)
   {

      sizeResult.cy() += 2;

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

   ::pointer<::user::tab>ptab = get_typed_parent < ::user::tab >();

   if (ptab.is_set())
   {

   }

   //if (m_bDelayedButtonLayout)
   //{

   //   on_layout(pgraphics);

   //}

   ::rectangle_i32 rectangleClient;

   client_rectangle(rectangleClient);

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   auto pstyle = get_style(pgraphics);

   pgraphics->fill_rectangle(rectangleClient, get_color(pstyle, ::e_element_background));

   //::user::interaction::_001OnDraw(pgraphics);

   pgraphics->set(get_font(pstyle));

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   //auto iHover = _001GetHoverItem();

   //descriptor().set_control_type(::user::e_control_type_button);

//   select_user_schema();

   for (index iItem = 0; iItem < m_pitema->get_size(); iItem++)
   {

      //if (!::is_item(m_ptoolitemHover, iItem))
      //{
      
      

         _001DrawItem(pgraphics, iItem);

      //}

   }

   //if (m_ptoolitemHover->m_eelement == ::e_element_item)
   //{

   //   _001DrawItem(pgraphics, m_ptoolitemHover);

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
//   window_rectangle(rectangleWindow);
//   rectangleWindow.offset(-rectangleWindow.top_left());
//   if (m_bTransparentBackground)
//   {
//      class imaging & imaging = psystem->imaging();
//      if (m_ptoolitemHover)
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

   auto iC = minimum(nCount, m_pitema->get_size());

   ::rectangle_i32 rectangleItemPad = get_item_pad();

   string str;

   bool bFirstInRow = true;

   int iRowStart = 0;

   int i;

   for (i = 0; i < iC; i++)
   {

      auto ptoolitem = index_tool_item(i);

      if (ptoolitem->is_hidden())
      {

         continue;

      }

      if (!bFirstInRow)
      {

         cur.x() += sSpacing.cx();

      }

      bFirstInRow = false;

      if (ptoolitem->m_estyle & e_tool_item_style_separator)
      {

         buttonx = sSeparator.cx();

         buttony = rectangleItemPad.top + rectangleItemPad.bottom; //  +sPress.cy();

      }
      else
      {

         if (ptoolitem->m_pimage->is_set())
         {

            buttonx = ptoolitem->m_pimage->width() + iImageSpacing + rectangleItemPad.left + rectangleItemPad.right;

            buttony = ptoolitem->m_pimage->height() + rectangleItemPad.top + rectangleItemPad.bottom;

         }
         else
         {

            buttonx = rectangleItemPad.left + rectangleItemPad.right;

            buttony = rectangleItemPad.top + rectangleItemPad.bottom;

         }

         size_f64 size;

         str = tool_item_text(i);

         size = pgraphics->get_text_extent(str);

         buttonx += (index) (size.cx() + EXTRA_TEXT_CX);

         buttony += (index) (size.cy() + EXTRA_TEXT_CY);

      }

      ptoolitem->m_rectangle.left = cur.x();

      ptoolitem->m_rectangle.right = (::i32) (cur.x() + buttonx);

      cur.x() += (::i32) buttonx; //  +sPress.cx();

      sizeResult.cx() = maximum(cur.x(), sizeResult.cx());

      cur.y() = (::i32) maximum(cur.y(), buttony);

      if (ptoolitem->m_estate & e_tool_item_state_wrap)
      {

         for (int j = iRowStart; j <= i; j++)
         {

            ptoolitem->m_rectangle.top = sizeResult.cy();

            ptoolitem->m_rectangle.bottom = sizeResult.cy() + cur.y();

         }

         if (sizeResult.cy() > rectangleBorder.top)
         {

            cur.y() += sSpacing.cy();

         }

         // cur.y() += sPress.cy();

         iRowStart = i + 1;

         sizeResult.cy() += cur.y();

         cur.x() = rectangleBorder.left;

         cur.y() = 0;

         if (ptoolitem->m_estyle & e_tool_item_style_separator)
         {

            sizeResult.cy() += sSeparator.cy();

         }

         bFirstInRow = true;

      }

   }

   for (int j = iRowStart; j < i; j++)
   {
      
      auto ptoolitemHere = index_tool_item(j);

      if (ptoolitemHere->is_hidden())
      {

         continue;

      }

      ptoolitemHere->m_rectangle.top = sizeResult.cy();

      ptoolitemHere->m_rectangle.bottom = sizeResult.cy() + cur.y();

   }

   // sizeResult.cy() += sPress.cy();

   sizeResult.cy() += cur.y();

   sizeResult.cx() += rectangleBorder.right;

   sizeResult.cy() += rectangleBorder.bottom;

   return sizeResult;

}


void simple_toolbar::_001DrawItem(::draw2d::graphics_pointer & pgraphics, index iItem)
{
   
   auto ptoolitem = index_tool_item(iItem);

   if (::is_null(ptoolitem) || ptoolitem->is_hidden())
   {

      return;

   }

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

   auto ptoolitem = index_tool_item(iItem);

   if (::is_null(ptoolitem) || ptoolitem->is_hidden())
   {

      return;

   }

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //::rectangle_i32 statusrectangleItem;

   //::rectangle_i32 rectangleImage;

   pgraphics->set_font(this, ::e_element_none);

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   auto estyle = tool_item_style(iItem);

   auto psession = acmesession()->m_pbasesession;

   auto puser = psession->user();

   auto pmenucentral = puser->menu();

   ::u32 uImage = pmenucentral->command_image(ptoolitem->m_atom);
   
   auto estate = tool_item_user_state(iItem);

   auto statusrectangleItem = index_element_rectangle(iItem, ::e_element_item, estate);

   auto statusrectangleImage = index_element_rectangle(iItem, ::e_element_image, estate);

   if (estyle & e_tool_item_style_separator)
   {

      ::rectangle_i32 rectangleSeparator;

      rectangleSeparator.left = (statusrectangleImage.left + statusrectangleImage.right) / 2 - 1;

      rectangleSeparator.right = rectangleSeparator.left + 2;

      rectangleSeparator.top = statusrectangleImage.top;

      rectangleSeparator.bottom = statusrectangleImage.bottom;

      pgraphics->draw_inset_3d_rectangle(rectangleSeparator, argb(255, 92, 92, 92), argb(255, 255, 255, 255), 1.0);

   }
   else
   {

      if (estate & ::user::e_state_hover)
      {

         if (estate & ::user::e_state_checked)
         {

            statusrectangleItem = index_element_rectangle(iItem, ::e_element_item, estate);

            statusrectangleImage = index_element_rectangle(iItem, ::e_element_image, estate);

            if ((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               pgraphics->fill_rectangle(statusrectangleItem, argb(208, 255, 255, 250));

               pgraphics->draw_inset_3d_rectangle(statusrectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255), 1.0);

            }

            if (uImage != 0xffffffffu)
            {

               if (!(estate & ::user::e_state_disabled))
               {

                  // button is enabled
                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, statusrectangleImage.top_left(), 0);

               }
               else
               {

                  // button is disabled
                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, statusrectangleImage.top_left(), 0);

               }

            }

         }
         else
         {

//            auto statusrectangleShadow = index_element_rectangle(iItem, ::e_element_item, estate);

            if ((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               auto ppen = __create < ::draw2d::pen > ();

               ppen->create_solid(1, argb(190, 92, 184, 92));

               auto pbrush = __create < ::draw2d::brush >();

               pbrush->create_solid(argb(123, 180, 184, 255));

               pgraphics->set(ppen);

               pgraphics->set(pbrush);

               pgraphics->rectangle(statusrectangleItem);

            }

            if (ptoolitem->m_pimage->is_set())
            {

               auto statusrectangle = index_element_rectangle(iItem, ::e_element_image, estate);

               image_source imagesource(ptoolitem->m_pimage);

               image_drawing_options imagedrawingoptions(statusrectangle);

               imagedrawingoptions.opacity(0.85);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }
            else if (uImage != 0xffffffffu)
            {

               auto statusrectangle = index_element_rectangle(iItem, ::e_element_image, estate);

               pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, statusrectangle.top_left(), 0);

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, statusrectangleImage.top_left(), 0);

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

            pgraphics->rectangle(statusrectangleItem);

         }

         if (ptoolitem->m_pimage->is_set())
         {

            auto statusrectangle = index_element_rectangle(iItem, ::e_element_image, estate);

            image_source imagesource(ptoolitem->m_pimage);

            image_drawing_options imagedrawingoptions(statusrectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pgraphics->draw(imagedrawing);

         }
         else if (uImage != 0xffffffff)
         {

            pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, statusrectangleImage.top_left(), 0);

         }

      }
      else
      {

         if (!(estate & ::user::e_state_disabled))
         {

            statusrectangleItem = index_element_rectangle(iItem, ::e_element_item, estate);

            pgraphics->fill_rectangle(statusrectangleItem, argb(190, 255, 255, 255));

         }

         if (estate & ::user::e_state_checked)
         {

            pgraphics->draw_inset_3d_rectangle(statusrectangleItem, argb(255, 127, 127, 127), argb(255, 255, 255, 255), 1.0);

         }

         if (ptoolitem->m_pimage->is_set())
         {

            auto statusrectangle = index_element_rectangle(iItem, ::e_element_image, estate);

            if(statusrectangle.ok())
            {

//            if(rectangle.width() > 10000)
               //          {

               //           output_debug_string("width > 10000");

               //         index_element_rectangle(iItem, rectangle, element_image);

               //    }

               image_source imagesource(ptoolitem->m_pimage);

               image_drawing_options imagedrawingoptions(statusrectangle);

               imagedrawingoptions.opacity(0.23);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }
         else if (uImage != 0xffffffff)
         {

            if (!(estate & ::user::e_state_disabled))
            {

               pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, statusrectangleImage.top_left(), 0);

            }
            else
            {

               pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, statusrectangleImage.top_left(), 0);

            }

         }

      }

   }

   if (ptoolitem->m_str.has_char())
   {

      pgraphics->set_font(this, ::e_element_none);

      m_dFontSize = pgraphics->m_pfont->m_dFontSize;

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

      auto statusrectangleText = index_element_rectangle(iItem, ::e_element_text, estate);

      if (statusrectangleText.ok() && statusrectangleText.right > 0)
      {

         pgraphics->_DrawText(ptoolitem->m_str, statusrectangleText, e_align_bottom_left, e_draw_text_no_prefix);

      }

   }

}


::status < ::rectangle_i32 > simple_toolbar::index_element_rectangle(index iItem, ::enum_element eelement, ::user::enum_state estate)
{

   if (iItem < 0 || iItem >= m_pitema->get_size())
   {

      return error_index_out_of_bounds;

   }

   ::rectangle_i32 rectangleItemPad = get_item_pad();

   int iImageSpacing = get_image_spacing();

   ::status < ::rectangle_i32 > rectangle;

   auto ptoolitem = index_tool_item(iItem);

   if (ptoolitem->is_hidden())
   {

      return error_failed;

   }

   if ((ptoolitem->m_estyle & e_tool_item_style_separator) != 0)
   {

      rectangle = ptoolitem->m_rectangle;

   }
   else
   {

      switch (eelement)
      {
         case ::e_element_item:

         rectangle = ptoolitem->m_rectangle;

         break;
      case ::e_element_image:

         if (ptoolitem->m_pimage->is_null() || ptoolitem->m_pimage->area() <= 0)
         {

            return error_failed;

         }

         rectangle = ptoolitem->m_rectangle;

         rectangle.left += rectangleItemPad.left;
         rectangle.bottom -= rectangleItemPad.bottom;
         rectangle.top = rectangle.bottom - ptoolitem->m_pimage->height();
         rectangle.right = rectangle.left + ptoolitem->m_pimage->width();

         break;
      case ::e_element_text:
      {

         rectangle = ptoolitem->m_rectangle;

         rectangle.left += rectangleItemPad.left;

         if (ptoolitem->m_pimage->is_set() && ptoolitem->m_pimage->area() > 0)
         {

            rectangle.left += ptoolitem->m_pimage->width();

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
         
         rectangle.offset(sPress.cx(), sPress.cy());
         
      }

   }
      
   rectangle.m_estatus = ::success;

   return rectangle;

}


void simple_toolbar::SetSizes(const ::size_i32 & sizeButton, const ::size_i32 & sizeImage)
{
   ASSERT_VALID(this);

   // sizes must be non-zero and positive
   ASSERT(sizeButton.cx() > 0 && sizeButton.cy() > 0);
   ASSERT(sizeImage.cx() > 0 && sizeImage.cy() > 0);

   // button must be big enough to hold image
   //   + 7 pixels on x
   //   + 6 pixels on y
   ASSERT(sizeButton.cx() >= sizeImage.cx() + 7);
   ASSERT(sizeButton.cy() >= sizeImage.cy() + 6);

   //   if (::IsWindow(get_handle()))
//   if (false)
//   {
//      // set the sizes via TB_SETBITMAPSIZE and TB_SETBUTTONSIZE
//#ifdef WINDOWS_DESKTOP
//      VERIFY(send_message(TB_SETBITMAPSIZE, 0, MAKELONG(sizeImage.cx(), sizeImage.cy())));
//      VERIFY(send_message(TB_SETBUTTONSIZE, 0, MAKELONG(sizeButton.cx(), sizeButton.cy())));
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


// tell common control toolbar about the memory_new bitmap
//   if (!AddReplaceBitmap(hbmImageWell))
//      return false;

// remember the resource handles so the bitmap can be recolored if necessary
m_hInstImageWell = hInstImageWell;
m_hRsrcImageWell = hRsrcImageWell;

_001DiscardImageList();

m_pimagelist = memory_new image_list();
m_bInternalImageList = true;

m_pimagelist->create(
   (char *) pszResourceName,

   m_sizeImage.cx(),
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

   auto rectangleClient = client_rectangle();

   if (rectangleClient.is_empty())
   {

      return;

   }

   auto pstyle = get_style(pgraphics);

   m_sizePress.cx() = get_int(pstyle, ::user::e_int_button_press_shift_cx, ::user::e_state_none, 2);

   m_sizePress.cy() = get_int(pstyle, ::user::e_int_button_press_shift_cy, ::user::e_state_none, 2);

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

      if (m_pitema->has_elements())
      {

         CalcSize(pgraphics, (index)(m_pitema->get_count()));

         for (index iItem = 0; iItem < m_pitema->get_count(); iItem++)
         {

            auto ptoolitem = index_tool_item(iItem);
            
            if(ptoolitem->is_hidden())
            {
               
               continue;
               
            }
            
            if (ptoolitem->should_wrap() || m_pitema->is_last_index(iItem))
            {

               int iTotalX = 0;

               for (index j = 0; j <= iItem; j++)
               {
                  
                  auto ptoolitemHere = index_tool_item(j);

                  if (ptoolitemHere->is_hidden())
                  {

                     continue;

                  }

                  iTotalX += ptoolitemHere->m_rectangle.width() + get_item_spacing().cx();

               }

               int offsetx = (rectangleClient.width() - iTotalX) / 2;

               for (index j = 0; j <= iItem; j++)
               {
                  
                  auto ptoolitemHere = index_tool_item(j);

                  if (ptoolitemHere->is_hidden())
                  {

                     continue;

                  }

                  ptoolitemHere->m_rectangle.offset(offsetx, 0);

               }

            }

         }

      }

   }
   
   ::rectangle_i32 rectangleSize;
   
   bool bFirstToolItemRectangle = true;
   
   for(index iItem = 0; iItem < tool_item_count(); iItem++)
   {
      
      auto ptoolitem = index_tool_item(iItem);
      
      if(ptoolitem->is_hidden())
      {
         
         continue;
         
      }
      
      if(bFirstToolItemRectangle)
      {
         
         bFirstToolItemRectangle = false;
         
         rectangleSize = ptoolitem->m_rectangle;
         
      }
      else
      {
         
         rectangleSize.unite(ptoolitem->m_rectangle);
         
      }
      
   }
   
   m_sizeBarDragScroll.cx() = rectangleSize.right + m_rectangleBorder.right;
   
   m_sizeBarDragScroll.cy() = rectangleSize.bottom + m_rectangleBorder.bottom;
      
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
//      if (m_ptoolitemHover)
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
//   m_ptoolitemCurrent = hit_test(pmouse);
//
//   if (m_ptoolitemCurrent)
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
//      if (item && item == m_ptoolitemCurrent)
//      {
//
//         m_ptoolitemCurrent = item; // update point_i32 and flags
//
//         on_click(m_ptoolitemCurrent);
//
//         pmouse->m_bRet = true;
//
//         pmouse->set_lresult(1);
//
//      }
//
//      ::pointer<::user::frame_window>pTarget = get_owner();
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
//         pTarget->send_message_to_descendants(e_message_idle_update_command_user_interface);
//
//      }
//
//      m_ptoolitemCurrent = -1;
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


::item_pointer simple_toolbar::on_hit_test(const ::point_i32 &point, ::user::e_zorder ezorder)
{

   return ::user::toolbar::on_hit_test(point, ezorder);

   //for (index iItem = 0; iItem < m_pitema->get_size(); iItem++)
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

   //window_rectangle(rectangleWindow);

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
//   if (m_ptoolitemHover != itemHover)
//   {
//
//      track_mouse_leave();
//
//      m_ptoolitemHover = itemHover;
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


bool simple_toolbar::on_click(::item * ptoolitem)
{

   ::pointer<::user::interaction>puserinteraction = get_owner();

   if (!::is_set(ptoolitem))
   {

      return false;

   }

   ::message::command command(ptoolitem->m_atom);

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


void simple_toolbar::_001SetImageList(::pointer<::image_list>imagelist)
{

   UNREFERENCED_PARAMETER(imagelist);

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

      m_pimagelistHue = memory_new ::image_list();

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

      m_pimagelistBlend = memory_new ::image_list();

   }

   psystem->imaging().Createcolor_blend_ImageList(
      m_pimagelistBlend,
      m_pimagelist,
      rgb(255, 255, 240),
      64
   );

   if(m_pimagelistHueLight == nullptr)
   {

      m_pimagelistHueLight = memory_new ::image_list();

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




//etool_item_state simple_toolbar::get_item_state(index iItem)
//{
//
//   return m_useritema[iItem]->m_estate;
//
//}
//
//
//bool simple_toolbar::set_item_state(index iItem, const etool_item_state & estate)
//{
//
//   return m_useritema[iItem]->m_estate;
//
//}


//enumeration < ::enum_tool_item_style > simple_toolbar::GetButtonStyle(index nIndex)
//{
//
//   ::pointer<::user::tool_item>ptoolitem = m_useritema[nIndex];
//
//   if (!ptoolitem)
//   {
//
//      return 0;
//
//   }
//
//   return MAKELONG(ptoolitem->m_fsStyle, ptoolitem->m_fsState);
//
//}
//
//
//void simple_toolbar::SetButtonStyle(index nIndex, ::u32 nStyle)
//{
//
//   ::pointer<::user::tool_item>ptoolitem = m_useritema[nIndex];
//
//   if (!ptoolitem)
//   {
//
//      return;
//
//   }
//
//   if (ptoolitem->m_fsStyle != (::u8)LOWORD(nStyle) || ptoolitem->m_fsState != (::u8)HIWORD(nStyle))
//   {
//
//      ptoolitem->m_fsStyle = (::u8)LOWORD(nStyle);
//
//      ptoolitem->m_fsState = (::u8)HIWORD(nStyle);
//
//      m_bDelayedButtonLayout = true;
//
//   }
//
//}


void simple_toolbar::on_message_non_client_calculate_size(::message::message * pmessage)
{

#if defined(WINDOWS_DESKTOP) //|| defined(LINUX)

   ::pointer<::message::nc_calc_size>pnccalcsize(pmessage);

   // calculate border space (will add to top/bottom, subtract from right/bottom)
   ::rectangle_i32 rectangle;

   bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;

   auto psystem = acmesystem()->m_paurasystem;

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
//   ::pointer<::message::nchittest>pnchittest(pmessage);
//
//   pnchittest->set_lresult(HTCLIENT);
//
//}


#define CX_OVERLAP  0


index simple_toolbar::WrapToolBar(::draw2d::graphics_pointer & pgraphics, index nCount, index nWidth)
{

   synchronous_lock synchronouslock(this->synchronization());

   ::count countNewlyWrapped = 0;

   ASSERT(nCount > 0);

   pgraphics->set_font(this, ::e_element_none);

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   int iImageSpacing = get_image_spacing();

   auto sizeSeparator = get_separator_size();

   auto sizeSpacing = get_item_spacing();

   //size_i32 sPress = get_press_shift();

   ::rectangle_i32 rectangleItemPad = get_item_pad();

   ::rectangle_i32 rectangleBorder = get_bar_border();

   index x = rectangleBorder.left;

   string str;

   auto count = minimum(nCount, m_pitema->get_count());

   bool bFirstInRow = true;

   for (index iItem = 0; iItem < count; iItem++)
   {

      auto ptoolitem = index_tool_item(iItem);

      if (ptoolitem->is_hidden())
      {

         continue;

      }

      ptoolitem->m_estate -= e_tool_item_state_wrap;

      str = ptoolitem->m_str;

      index greekdeltax, greekdeltaxNext;

      if (ptoolitem->m_estyle & e_tool_item_style_separator)
      {

         greekdeltax = sizeSeparator.cx();

         greekdeltaxNext = greekdeltax;

      }
      else
      {

         greekdeltax = rectangleItemPad.left;

         if (ptoolitem->m_pimage->is_set())
         {

            greekdeltax += ptoolitem->m_pimage->height();

         }

         if (str.has_char() && ptoolitem->m_pimage->is_set())
         {

            greekdeltax += iImageSpacing;

         }

         if (str.has_char())
         {

            size_f64 size = pgraphics->get_text_extent(str);

            greekdeltax = (index)  (size.cx() + EXTRA_TEXT_CX);

         }

         greekdeltax += rectangleItemPad.right; // +sPress.cx();

         greekdeltaxNext = greekdeltax - CX_OVERLAP;

      }

      bool bFound = false;

      if (x + greekdeltax > nWidth - rectangleBorder.right)
      {

         for (index iItemHere = iItem; iItemHere >= 0; iItemHere--)
         {
            
            auto ptoolitemHere = index_tool_item(iItemHere);

            if (ptoolitemHere->is_hidden())
            {

               continue;

            }
            
            if(ptoolitemHere->should_wrap())
            {
               
               break;
               
            }

            // find last separator that isn't hidden
            // and a custom control
            if (ptoolitemHere->is_custom_control()
                && !ptoolitemHere->is_hidden())
            {

               bFound = true;

               iItem = iItemHere;

               x = rectangleBorder.left;

               bFirstInRow = true;

               ptoolitemHere->set_should_wrap();

               countNewlyWrapped++;

               break;

            }

         }

         if (!bFound)
         {

            for (index iItemHere = iItem - 1; iItemHere >= 0; iItemHere--)
            {
               
               auto ptoolitemHere = index_tool_item(iItemHere);

               if (ptoolitemHere->is_hidden())
               {

                  continue;

               }
               
               if(ptoolitemHere->should_wrap())
               {
                  
                  break;
                  
               }

               // Never wrap anything that is hidden,
               // or custom controls
               if (ptoolitemHere->is_custom_control()                  || ptoolitemHere->is_separator())
               {

                  continue;

               }

               bFound = true;

               iItem = iItemHere;

               x = rectangleBorder.left;

               bFirstInRow = true;

               ptoolitemHere->set_should_wrap();

               countNewlyWrapped++;

               break;

            }

         }

      }

      if (!bFound)
      {

         if (!bFirstInRow)
         {

            x += sizeSpacing.cx();

         }

         bFirstInRow = false;

         x += greekdeltaxNext;

      }

   }

   return countNewlyWrapped + 1;

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

      WrapToolBar(pgraphics, nCount, size.cx());

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

      while (sizeMin.cx() < sizeMax.cx())
      {

         sizeMid.cx() = (sizeMin.cx() + sizeMax.cx()) / 2;

         WrapToolBar(pgraphics, nCount, sizeMid.cx());

         sizeMid = CalcSize(pgraphics, nCount);

         if (nLength < sizeMid.cy())
         {

            if (sizeMin == sizeMid)
            {

               WrapToolBar(pgraphics, nCount, sizeMax.cx());

               return;

            }

            sizeMin = sizeMid;

         }
         else if (nLength > sizeMid.cy())
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

   //::pointer<::user::tab>ptab = get_typed_parent < ::user::tab >();

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

   ::size_i32 sizeResult(0, 0);

   auto count = tool_item_count();

   if (count > 0)
   {

      if (!(m_dwStyle & CBRS_SIZE_FIXED))
      {

         bool bDynamic = (m_dwStyle & CBRS_SIZE_DYNAMIC) != 0;

         if (bDynamic && (dwMode & LM_MRUWIDTH))
         {

            SizeToolBar(pgraphics, count, m_nMRUWidth);

         }
         else if (bDynamic && (dwMode & LM_HORZDOCK))
         {

            SizeToolBar(pgraphics, count, 32767);

         }
         else if (bDynamic && (dwMode & LM_VERTDOCK))
         {

            SizeToolBar(pgraphics, count, 0);

         }
         else if (bDynamic && (nLength != -1))
         {

            ::rectangle_i32 rectangle;

            CalcInsideRect(pgraphics, rectangle, (dwMode & LM_HORZ) != 0);

            bool bVert = (dwMode & LM_LENGTHY) != 0;

            index nLen = nLength + (bVert ? rectangle.height() : rectangle.width());

            SizeToolBar(pgraphics, count, nLen, bVert);

         }
         else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
         {

            SizeToolBar(pgraphics, count, m_nMRUWidth);

         }
         else
         {

            SizeToolBar(pgraphics, count, (dwMode & LM_HORZ) ? 32767 : 0);

         }

      }

      sizeResult = CalcSize(pgraphics, count);

      if (dwMode & LM_COMMIT)
      {

         ___CONTROLPOS* pControl = nullptr;

         index nControlCount = 0;

         bool bIsDelayed = m_bDelayedButtonLayout;

         m_bDelayedButtonLayout = false;

         index i;

         for (i = 0; i < count; i++)
         {

            if (index_tool_item(i)->is_hidden())
            {

               continue;

            }

            if (index_tool_item(i)->is_separator())
            {

               nControlCount++;

            }

         }

         if (nControlCount > 0)
         {

            array < ___CONTROLPOS > controlposa;

            controlposa.set_size(nControlCount);

            nControlCount = 0;

            for (index i = 0; i < count; i++)
            {
               
               auto ptoolitem = index_tool_item(i);

               if (ptoolitem->is_hidden())
               {

                  continue;

               }

               if (ptoolitem->is_custom_control())
               {

                  pControl[nControlCount].nIndex = i;

                  pControl[nControlCount].strId = ptoolitem->m_atom;

                  auto statusrectangle = index_item_rectangle(i);

                  client_to_screen()(statusrectangle);

                  pControl[nControlCount].rectangleOldPos = statusrectangle;

                  nControlCount++;

               }

            }

         }

         string str;

         if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
         {

            m_nMRUWidth = sizeResult.cx();

         }

         for (i = 0; i < count; i++)
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
            //       str.length(),
            //       &size);
            //
            //    size.cx() += m_sizeButton.cx();
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
            // memory_set(&button, 0, sizeof(button));
            //
            // button.cbSize = sizeof(button);
            //
            // button.dwMask = TBIF_COMMAND | TBIF_SIZE;
            // button.cx() = size.cx();
            // button.m_atom = i;
            //
            // GetToolBarCtrl().SetButtonInfo(i, &button);

         }

         //for (i = 0; i < nCount; i++)
         {

            // TBBUTTONINFOW buttona;
            // memory_set(&buttona, 0, sizeof(buttona));
            // buttona.cbSize = sizeof(buttona);
            // buttona.dwMask =
            //    TBIF_COMMAND
            //    | TBIF_STYLE
            //    | TBIF_SIZE;
            // ::u32 uID = GetItemID(i);
            // GetToolBarCtrl().GetButtonInfo(uId, &buttona);
            // information("BUTTON.m_atom = %d\n", buttona.m_atom  );
            // information("BUTTON.m_fsStyle = %d\n", buttona.m_fsStyle  );
            // information("BUTTON.cx() = %d\n", buttona.cx() );

         }

         if (nControlCount > 0)
         {

            for (index i = 0; i < nControlCount; i++)
            {

               /* xxx

               ::pointer<::user::interaction>pwindow = get_child_by_id(pControl[i]->strId);

               if (pwindow != nullptr)
               {

               ::rectangle_i32 rectangle;

               pwindow->window_rectangle(&rectangle);

               const ::point_i32 & point = rectangle.top_left() - pControl[i]->rectangleOldPos.top_left();

               index_element_rectangle(pControl[i]->nIndex, &rectangle);

               point = rectangle.top_left() + point_i32;

               pwindow->set_window_position(0, point.x(), point.y(), 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);

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

      sizeResult.cy() -= rectangle.height();

      sizeResult.cx() -= rectangle.width();

      const ::size_i32 & size = ::user::control_bar::CalcFixedLayout(pgraphics, (dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZ) != 0);

      sizeResult.cx() = maximum(sizeResult.cx(), size.cx());

      sizeResult.cy() = maximum(sizeResult.cy(), size.cy());

   }

   return sizeResult;

}


//void simple_toolbar::GetButtonText(index i, string &str)
//{
//
//   if (i < 0 || i >= m_pitema->get_count())
//   {
//
//      str.empty();
//
//      return;
//
//   }
//
//   auto
//
//   str = index_tool_item(i)->m_str;
//
//}


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
//   ::pointer<::user::message>pusermessage(pmessage);
//
//   m_ptoolitemHover = ::e_element_none;
//
//   OnUpdateHover();
//
//   set_need_redraw();
//
//   pusermessage->set_lresult(0);
//
//}




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

   m_pitema->erase_all();

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

   if (s.cx() < 0)
   {

      s.cx() = 0;

   }
   if (s.cy() < 0)
   {

      s.cy() = 0;

   }

   return s;

}


size_i32 simple_toolbar::get_separator_size()
{

   ::size_i32 s;

   s = m_sizeSeparator;

   if (s.cx() < 0)
   {

      s.cx() = ::i32(m_dFontSize * 2 / 3);

   }

   if (s.cy() < 0)
   {

      s.cy() = ::i32(m_dFontSize * 2 / 3);

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




