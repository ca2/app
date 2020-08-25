#include "framework.h"


#define TIMER_HOVER 321654

class simple_tool_command : public ::user::command        // class private to this file !
{
public: // re-implementations only

   simple_tool_command(::object * pobject);
   virtual void Enable(bool bOn = TRUE, const ::action_context & context = ::source_system);
   //   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void _001SetCheck(enum_check echeck, const ::action_context & context = ::source_system);   // 0, 1 or 2 (indeterminate)
//   virtual void SetRadio(bool bOn = TRUE, const ::action_context & context = ::source_system);
   virtual void SetText(const char * pszText, const ::action_context & context = ::source_system);

};

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

   m_iImageSpacing = -1;

   m_sizePress.set(0);

   m_sizeSpacing.set(-1);

   m_sizeSeparator.set(-1);

   m_rectBorder.set(-1);

   m_rectItemPad.set(-1);

   m_dFontSize = 1.0;

   // lakic
   m_sizeSpacing.cx = 8;

   m_rectItemPad.set(9, 9);

   m_rectBorder.set(9, 9);
   // end lakic

   m_itemCurrent = -1;

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

   IGUI_MSG_LINK(WM_CREATE       , pchannel, this, &simple_toolbar::_001OnCreate);
   //IGUI_MSG_LINK(WM_MOUSEMOVE    , pchannel, this, &simple_toolbar::_001OnMouseMove);
   //IGUI_MSG_LINK(WM_LBUTTONDOWN  , pchannel, this, &simple_toolbar::_001OnLButtonDown);
   //IGUI_MSG_LINK(WM_LBUTTONUP    , pchannel, this, &simple_toolbar::_001OnLButtonUp);
   //IGUI_MSG_LINK(WM_NCHITTEST    , pchannel, this, &simple_toolbar::_001OnNcHitTest);
   //IGUI_MSG_LINK(WM_MOUSELEAVE   , pchannel, this, &simple_toolbar::_001OnMouseLeave);

   install_simple_ui_default_mouse_handling(pchannel);
   
}


bool simple_toolbar::create(::user::interaction * puiParent, u32 uStyle, id nID)
{

   return create_toolbar(puiParent, 0, uStyle, nID);

}


bool simple_toolbar::create_toolbar(::user::interaction * puiParent, u32 dwCtrlStyle, u32 uStyle, id nID)
{

   ASSERT_VALID(puiParent);   // must have a parent
   ASSERT(!((uStyle & CBRS_SIZE_FIXED) && (uStyle & CBRS_SIZE_DYNAMIC)));

   //SetBorders(rectBorders);

   // save the style
   m_dwStyle = (uStyle & CBRS_ALL);
   if (nID == __IDW_TOOLBAR)
      m_dwStyle |= CBRS_HIDE_INPLACE;

   uStyle &= ~CBRS_ALL;
   uStyle |= CCS_NOPARENTALIGN | CCS_NOMOVEY | CCS_NODIVIDER | CCS_NORESIZE;
   uStyle |= dwCtrlStyle & 0xffff;
   m_dwCtrlStyle = dwCtrlStyle & (0xffff0000 | TBSTYLE_FLAT);

   if (!::user::interaction::create_window(nullptr, nullptr, uStyle, puiParent, nID))
   {

      return FALSE;

   }

   SetSizes(m_sizeButton, m_sizeImage);

   return true;

}


size simple_toolbar::CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz)
{

   u32 dwMode = bStretch ? LM_STRETCH : 0;

   dwMode |= bHorz ? LM_HORZ : 0;

   return CalcLayout(pgraphics, dwMode);

}


size simple_toolbar::CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics)
{

   ASSERT_VALID(this);

   ASSERT(is_window());

   ::count nCount;

   ::size sizeResult;

   nCount = m_itema.get_count();

   if (nCount > 0)
   {

      ::rect rectItem;

      ::rect rectSize(0, 0, 0, 0);

      for (index i = 0; i < nCount; i++)
      {

         _001GetItemRect(i, rectItem);

         rectSize.unite(rectSize, rectItem);

      }

      sizeResult = rectSize.size();

   }

#ifdef WINDOWS_DESKTOP

   if (GetStyle() & TBSTYLE_FLAT)
   {

      sizeResult.cy += 2;

   }

#else

   __throw(todo());

#endif

   return sizeResult;

}


void simple_toolbar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   __pointer(::user::tab) ptab = GetTypedParent < ::user::tab >();

   if (ptab.is_set())
   {

   }

   //if (m_bDelayedButtonLayout)
   //{

   //   on_layout(::draw2d::graphics_pointer & pgraphics);

   //}

   ::rect rectClient;

   get_client_rect(rectClient);

   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

   auto pstyle = get_style(pgraphics);

   pgraphics->fill_rect(rectClient, get_color(pstyle, ::user::element_background));

   //::user::interaction::_001OnDraw(pgraphics);

   pgraphics->set(get_font(pstyle));

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   //auto iHover = _001GetHoverItem();

   //descriptor().set_control_type(::user::control_type_button);

//   select_user_schema();

   for (index iItem = 0; iItem < m_itema.get_size(); iItem++)
   {

      if (m_itemHover != iItem)
      {

         _001DrawItem(pgraphics, iItem);

      }

   }

   if (m_itemHover)
   {

      _001DrawItem(pgraphics, m_itemHover);

   }


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
//   m_pimageDraft->get_graphics()->BitBlt(0, 0, 7, 7, pgraphics, 0, 0, SRCCOPY);
//
//   ::rect rectWindow;
//   get_window_rect(rectWindow);
//   rectWindow.offset(-rectWindow.top_left());
//   if (m_bTransparentBackground)
//   {
//      class imaging & imaging = System.imaging();
//      if (m_itemHover)
//      {
//         imaging.color_blend(
//         pgraphics,
//         rectWindow.left,
//         rectWindow.top,
//         rectWindow.width(),
//         rectWindow.height(),
//         RGB(215, 215, 210),
//         220);
//      }
//      else
//      {
//         imaging.color_blend(
//         pgraphics,
//         rectWindow.left,
//         rectWindow.top,
//         rectWindow.width(),
//         rectWindow.height(),
//         RGB(215, 215, 210),
//         180);
//      }
//   }
//   else
//   {
//#ifdef WINDOWS_DESKTOP
//      pgraphics->fill_rect(rectWindow, Session.get_default_color(COLOR_3DFACE));
//#else
//      pgraphics->fill_rect(rectWindow, ARGB(255, 190, 184, 177));
//#endif
//   }
//
//   // Desenha chanfro
//   COLORREF cr = m_pimageDraft->GetPixel(0, 0);
//   pgraphics->SetPixel(0, 0, cr);
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
//   //pgraphics->BitBlt(0, 0, 7, 7, &m_dcDraft, 0, 0, SRCCOPY);
//
//   //
//
//   // draw borders in non-client area
//   DrawBorders(pgraphics, rectWindow);
//   /*   pgraphics->fill_rect(
//   rectWindow.left + 7, rectWindow.top,
//   rectWindow.right, rectWindow.top + 1,
//   RGB(128, 128, 123));*/
//
//   // erase parts not drawn
//   //pgraphics->IntersectClipRect(rectWindow);
//   //SendMessage(WM_ERASEBKGND, (WPARAM)pgraphics->get_handle1());
//
//   // draw gripper in non-client area
//   DrawGripper(pgraphics, rectWindow);
//
//   //pgraphics->SetViewportOrg(pointViewport);
//}


void simple_toolbar::_001OnCreate(::message::message * pmessage)
{

   if (pmessage->previous())
      return;
   
   descriptor().m_econtroltype = ::user::control_type_toolbar;

   m_pimageDraft = create_image({20,  20 });

}


void simple_toolbar::on_command_probe(::user::frame_window * ptarget, bool bDisableIfNoHndler)
{

   simple_tool_command state(get_context_object());

   state.m_puiOther = (this);

   state.m_iCount = _001GetItemCount();

   for (state.m_iIndex = 0; state.m_iIndex < state.m_iCount; state.m_iIndex++)
   {

      if (m_itema[state.m_iIndex]->m_id != "separator")
      {

         state.m_id = m_itema[state.m_iIndex]->m_id;

         // allow reflections
         //if (::user::interaction::on_command(0,
         //   MAKELONG((index)CN_UPDATE_::user::command, WM_COMMAND+WM_REFLECT_BASE),
         //   &state, nullptr))
         //   continue;

         state.m_bEnableChanged = false;

         // allow the toolbar itself to have update handlers
         _001SendCommandProbe(&state);

         if (state.m_bRet)
         {

            continue;

         }

         //if (!state.m_bEnableChanged)
         //{
         //
         //   if (m_itema[state.m_iIndex]->m_bEnableIfHasCommandHandler)
         //   {

         //      if (!state.m_bHasCommandHandler)
         //      {

         //         continue;


         //      }

         //   }

         //}

         // allow the owner to process the update
         state.do_probe(ptarget);

      }

   }

   // update the dialog controls added to the toolbar
   update_dialog_controls(ptarget);

}

#define CX_OVERLAP 0


size simple_toolbar::CalcSize(::draw2d::graphics_pointer & pgraphics, index nCount)
{

   ASSERT(nCount > 0);

   pgraphics->set_font(this);

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   int iImageSpacing = get_image_spacing();

   ::rect rectBorder = get_bar_border();

   //size sPress = get_press_shift();

   auto sSpacing = get_item_spacing();

   auto sSeparator = get_separator_size();

   point cur(rectBorder.left, rectBorder.top);

   ::size sizeResult(rectBorder.left, rectBorder.top);

   index buttonx, buttony;

   auto iC = MIN(nCount, m_itema.get_size());

   ::rect rectItemPad = get_item_pad();

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

      ::user::toolbar_item & item = m_itema(i);

      //index cySep = item.m_iImage;

      if (m_itema[i]->m_fsStyle & TBSTYLE_SEP)
      {

         buttonx = sSeparator.cx;

         buttony = rectItemPad.top + rectItemPad.bottom; //  +sPress.cy;

      }
      else
      {

         if (item.m_pimage->is_set())
         {

            buttonx = item.m_pimage->width() + iImageSpacing + rectItemPad.left + rectItemPad.right;

            buttony = item.m_pimage->height() + rectItemPad.top + rectItemPad.bottom;

         }
         else
         {

            buttonx = rectItemPad.left + rectItemPad.right;

            buttony = rectItemPad.top + rectItemPad.bottom;

         }

         sized size;

         GetButtonText(i, str);

         size = pgraphics->GetTextExtent(str);

         buttonx += (index) (size.cx + EXTRA_TEXT_CX);

         buttony += (index) (size.cy + EXTRA_TEXT_CY);

      }

      if (m_itema[i]->m_fsState & TBSTATE_HIDDEN)
      {

         continue;

      }

      m_itema[i]->m_rect.left = cur.x;

      m_itema[i]->m_rect.right = (LONG) (cur.x + buttonx);

      cur.x += (LONG) buttonx; //  +sPress.cx;

      sizeResult.cx = MAX(cur.x, sizeResult.cx);

      cur.y = (LONG) MAX(cur.y, buttony);

      if (m_itema[i]->m_fsState & TBSTATE_WRAP)
      {


         for (int j = iRowStart; j <= i; j++)
         {

            m_itema[i]->m_rect.top = sizeResult.cy;

            m_itema[i]->m_rect.bottom = sizeResult.cy + cur.y;

         }

         if (sizeResult.cy > rectBorder.top)
         {

            cur.y += sSpacing.cy;

         }

         // cur.y += sPress.cy;

         iRowStart = i + 1;

         sizeResult.cy += cur.y;

         cur.x = rectBorder.left;

         cur.y = 0;

         if (m_itema[i]->m_fsStyle & TBSTYLE_SEP)
         {

            sizeResult.cy += sSeparator.cy;

         }

         bFirstInRow = true;

      }

   }

   for (int j = iRowStart; j < i; j++)
   {

      m_itema[j]->m_rect.top = sizeResult.cy;

      m_itema[j]->m_rect.bottom = sizeResult.cy + cur.y;

   }

   // sizeResult.cy += sPress.cy;

   sizeResult.cy += cur.y;

   sizeResult.cx += rectBorder.right;

   sizeResult.cy += rectBorder.bottom;

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

   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

   ::rect rectItem;

   ::rect rectImage;

   pgraphics->set_font(this);

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   ::user::toolbar_item & item = m_itema(iItem);

   UINT nStyle = GetButtonStyle(iItem);

   //bool bHover = m_itemHover == iItem;

   __pointer(::user::menu_central) pmenucentral = User.menu();

   UINT uiImage = pmenucentral->command_image(item.m_id);
   
   ::user::estate estate = get_button_state((int)iItem);

//   e_element eelement = element_item;
//
//   e_element eelementImage = element_image;
//
//   e_element eelementText = element_text;
//
//   if ((nStyle & TBBS_SEPARATOR) == 0)
//   {
//
//      if ((nStyle & TBBS_DISABLED) == 0)
//      {
//
//         // item is enabled
//         if (m_itemCurrent)
//         {
//
//            if (m_itemCurrent == iItem)
//            {
//
//               if (bHover)
//               {
//
//                  eelement = element_item_press;
//
//                  eelementImage = element_image_press;
//
//                  eelementText = element_text_press;
//
//               }
//               else
//               {
//
//                  eelement = element_item_hover;
//
//                  eelementImage = element_image_hover;
//
//                  eelementText = element_text_hover;
//
//               }
//
//            }
//
//         }
//         else if (bHover)
//         {
//
//            eelement = element_item_hover;
//
//            eelementImage = element_image_hover;
//
//            eelementText = element_text_hover;
//
//         }
//
//      }
//      else
//      {
//
//         // item is disabled
//
//         eelement = element_item;
//
//         eelementImage = element_image;
//
//         eelementText = element_text;
//
//      }
//
//   }
//   else
//   {
//
//      eelement = element_item;
//
//      eelementImage = element_image;
//
//      eelementText = element_text;
//
//   }

//   int iOffsetX = 0;
//
//   int iOffsetY = 0;

   _001GetElementRect(iItem, rectItem, ::user::element_item, estate);

   _001GetElementRect(iItem, rectImage, ::user::element_image, estate);

   if ((nStyle & TBBS_SEPARATOR) != 0)
   {

      ::rect rectSeparator;

      rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;

      rectSeparator.right = rectSeparator.left + 2;

      rectSeparator.top = rectImage.top;

      rectSeparator.bottom = rectImage.bottom;

      pgraphics->draw_3drect(rectSeparator, ARGB(255, 92, 92, 92), ARGB(255, 255, 255, 255));

   }
   else
   {

      if (estate & ::user::e_state_hover)
      {

         if (estate & ::user::e_state_checked)
         {

            _001GetElementRect(iItem, rectItem, ::user::element_item, estate);

            _001GetElementRect(iItem, rectImage,::user::element_image, estate);

            if ((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {
               System.imaging().color_blend(
               pgraphics,
               rectItem.left,
               rectItem.top,
               rectItem.width(),
               rectItem.height(),
               RGB(255, 255, 250), 208);

               pgraphics->draw_3drect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));

            }

            if (uiImage != 0xffffffffu)
            {

               if (!(estate & ::user::e_state_disabled))
               {

                  // button is enabled
                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

               }
               else
               {

                  // button is disabled
                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

               }

            }

         }
         else
         {

            ::rect rectShadow;

            _001GetElementRect(iItem, rectShadow, ::user::element_item, estate);

            if ((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1, ARGB(190, 92, 184, 92));

               ::draw2d::brush_pointer brush(e_create);

               brush->create_solid(ARGB(123, 180, 184, 255));

               pgraphics->set(pen);

               pgraphics->set(brush);

               pgraphics->rectangle(rectItem);

            }

            if (item.m_pimage->is_set())
            {

               ::rect rect;

               _001GetElementRect(iItem, rect, ::user::element_image, estate);

               System.imaging().color_blend(pgraphics, rect.top_left(), rect.size(), item.m_pimage->g(), nullptr, 0.85);

            }
            else if (uiImage != 0xffffffffu)
            {

               ::rect rect;

               _001GetElementRect(iItem, rect, ::user::element_image, estate);

               pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uiImage, rect.top_left(), 0);

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

            }

         }

      }
      else if (estate & ::user::e_state_pressed)
      {

         if ((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
         {

            ::draw2d::pen_pointer pen(e_create);

            pen->create_solid(1, ARGB(255, 92, 92, 92));

            ::draw2d::brush_pointer brush(e_create);

            brush->create_solid(ARGB(255, 255, 255, 255));

            pgraphics->set(pen);

            pgraphics->set(brush);

            pgraphics->rectangle(rectItem);

         }

         if (item.m_pimage->is_set())
         {

            ::rect rect;

            _001GetElementRect(iItem, rect, ::user::element_image, estate);

            System.imaging().color_blend(pgraphics, rect.top_left(), rect.size(), item.m_pimage->g(), nullptr, 1.0);

         }
         else if (uiImage != 0xffffffff)
         {

            pmenucentral->MenuV033GetImageList()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

         }

      }
      else
      {

         if (!(estate & ::user::e_state_disabled))
         {

            _001GetElementRect(iItem, rectItem, ::user::element_item, estate);

            pgraphics->fill_rect(rectItem, ARGB(190, 255, 255, 255));

         }

         if (estate & ::user::e_state_checked)
         {

            pgraphics->draw_3drect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));

         }

         if (item.m_pimage->is_set())
         {

            ::rect rect;

            if(_001GetElementRect(iItem, rect, ::user::element_image, estate))
            {

//            if(rect.width() > 10000)
               //          {

               //           output_debug_string("width > 10000");

               //         _001GetElementRect(iItem, rect, element_image);

               //    }

               System.imaging().color_blend(pgraphics, rect.top_left(), rect.size(), item.m_pimage->g(), nullptr, 0.23);

            }

         }
         else if (uiImage != 0xffffffff)
         {

            if (!(estate & ::user::e_state_disabled))
            {

               pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

            }
            else
            {

               pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

            }

         }

      }

   }

   if (item.m_str.has_char())
   {

      pgraphics->set_font(this);

      m_dFontSize = pgraphics->m_pfont->m_dFontSize;

      ::rect rectText;

      ::draw2d::brush_pointer brushText(e_create);

      if (!(estate & ::user::e_state_disabled))
      {

         brushText->create_solid(ARGB(255, 0, 0, 0));

      }
      else
      {

         brushText->create_solid(ARGB(255, 120, 120, 118));

      }

      pgraphics->set(brushText);

      if (_001GetElementRect(iItem, rectText, ::user::element_text, estate) && rectText.right > 0)
      {

         pgraphics->_DrawText(item.m_str, item.m_str.get_length(), rectText, DT_BOTTOM | DT_LEFT | DT_NOPREFIX);

      }

   }

}


bool simple_toolbar::_001GetElementRect(index iItem, RECT * prect, ::user::e_element eelement, ::user::estate estate)
{

   if (iItem < 0 || iItem >= m_itema.get_size())
   {

      return false;

   }

   ::rect rectItemPad = get_item_pad();

   int iImageSpacing = get_image_spacing();

   ::rect rect;

   ::user::toolbar_item & item = m_itema(iItem);

   if ((item.m_fsStyle & TBSTYLE_SEP) != 0)
   {

      rect = item.m_rect;

   }
   else
   {

      switch (eelement)
      {
         case ::user::element_item:

         rect = item.m_rect;

         break;
      case ::user::element_image:

         if (item.m_pimage->is_null() || item.m_pimage->area() <= 0)
         {

            return false;

         }

         rect = item.m_rect;

         rect.left += rectItemPad.left;
         rect.bottom -= rectItemPad.bottom;
         rect.top = rect.bottom - item.m_pimage->height();
         rect.right = rect.left + item.m_pimage->width();

         break;
      case ::user::element_text:
      {

         rect = item.m_rect;

         rect.left += rectItemPad.left;

         if (item.m_pimage->is_set() && item.m_pimage->area() > 0)
         {

            rect.left += item.m_pimage->width();

            rect.left += iImageSpacing;

         }

         rect.top += rectItemPad.top;
         rect.right -= (rectItemPad.right);
         rect.bottom -= (rectItemPad.bottom);
         break;

      }
            
         default:
            break;
            
      }
            
      if(estate & ::user::e_state_pressed)
      {
         
         ::size sPress = get_press_shift();
         
         rect.offset(sPress.cx, sPress.cy);
         
      }

   }
      
   *prect = rect;

   return true;

}


void simple_toolbar::SetSizes(const ::size & sizeButton, const ::size & sizeImage)
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
//      //__throw(todo());
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
bool simple_toolbar::LoadBitmap(const char * pszResourceName)

{
ASSERT_VALID(this);
ASSERT(pszResourceName != nullptr);


// determine location of the bitmap in resource fork
HINSTANCE hInstImageWell = ::aura::FindResourceHandle(pszResourceName, RT_BITMAP);

HRSRC hRsrcImageWell = ::FindResource(hInstImageWell, pszResourceName, RT_BITMAP);

if (hRsrcImageWell == nullptr)
return FALSE;

// load the bitmap
HBITMAP hbmImageWell;
//   hbmImageWell = ::aura::LoadSysColorBitmap(hInstImageWell, hRsrcImageWell);
::draw2d::memory_graphics pgraphics(this);;
hbmImageWell = imaging::LoadSysColorBitmap(pgraphics, hInstImageWell, hRsrcImageWell);


// tell common control toolbar about the new bitmap
//   if (!AddReplaceBitmap(hbmImageWell))
//      return FALSE;

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
   RGB(192, 192, 192)
   );

_001OnImageListAttrib();

*/

/*
return TRUE;
}
*/

void simple_toolbar::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   auto rectClient = get_client_rect();

   if (rectClient.is_empty())
   {

      return;

   }

   auto pstyle = get_style(pgraphics);

   m_sizePress.cx = get_int(pstyle, ::user::int_button_press_shift_cx, 2);

   m_sizePress.cy = get_int(pstyle, ::user::int_button_press_shift_cy, 2);

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

      if (m_itema.has_elements())
      {

         CalcSize(pgraphics, (index)(m_itema.get_count()));

         for (index i = 0; i < m_itema.get_count(); i++)
         {

            if (m_itema[i]->m_fsStyle & TBSTATE_WRAP || i == m_itema.get_upper_bound())
            {

               int iTotalX = 0;

               for (index j = 0; j <= i; j++)
               {

                  iTotalX += m_itema[j]->m_rect.width() + get_item_spacing().cx;

               }

               int offsetx = (rectClient.width() - iTotalX) / 2;

               for (index j = 0; j <= i; j++)
               {

                  m_itema[j]->m_rect.offset(offsetx, 0);

               }

            }

         }

      }

   }

}


//void simple_toolbar::_001OnMouseMove(::message::message * pmessage)
//{
//
//   SCAST_PTR(::message::mouse, pmouse, pmessage);
//
//   ::point point = pmouse->m_point;
//
//   _001ScreenToClient(point);
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
//      if (m_itemHover)
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


//void simple_toolbar::_001OnLButtonDown(::message::message * pmessage)
//{
//
//   SCAST_PTR(::message::mouse, pmouse, pmessage);
//
//   auto point = screen_to_client(pmouse->m_point);
//
//   m_itemCurrent = hit_test(pmouse);
//
//   if (m_itemCurrent)
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
//void simple_toolbar::_001OnLButtonUp(::message::message * pmessage)
//{
//
//   SCAST_PTR(::message::mouse, pmouse, pmessage);
//
//   auto point = pmouse->m_point;
//
//   _001ScreenToClient(point);
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
//      if (item && item == m_itemCurrent)
//      {
//
//         m_itemCurrent = item; // update point and flags
//
//         on_click(m_itemCurrent);
//
//         pmouse->m_bRet = true;
//
//         pmouse->set_lresult(1);
//
//      }
//
//      __pointer(::user::frame_window) pTarget = GetOwner();
//
//      if (pTarget == nullptr)
//      {
//
//         pTarget = GetParentFrame();
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
//      m_itemCurrent = -1;
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


void simple_toolbar::on_hit_test(::user::item & item)
{

   for (index iItem = 0; iItem < m_itema.get_size(); iItem++)
   {

      if (m_itema[iItem]->m_rect.contains(item.m_pointHitTest))
      {

         item = {::user::element_item, iItem};

         return;

      }

   }

   if (Session.GetCapture() == this)
   {

      item = ::user::element_none;

      return;

   }

   ::rect rectWindow;

   get_window_rect(rectWindow);

   _001ScreenToClient(rectWindow);

   if (rectWindow.contains(item.m_pointHitTest))
   {

      item = ::user::element_none;

      return;

   }
   else
   {

      item = ::user::element_none;

      return;

   }

}


//void simple_toolbar::_001Hover(const ::point & point, bool bRedraw)
//{
//
//   auto itemHover = hit_test(pmouse);
//
//   if (m_itemHover != itemHover)
//   {
//
//      track_mouse_leave();
//
//      m_itemHover = itemHover;
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
//   auto point = Session.get_cursor_pos();
//
//   _001ScreenToClient(point);
//
//   _001Hover(point, bRedraw);
//
//}


void simple_toolbar::_001OnTimer(::timer * ptimer)
{

   ::user::toolbar::_001OnTimer(ptimer);

//   if (ptimer->m_nIDEvent == TIMER_HOVER)
//   {
//
//      _001Hover();
//
//   }

   // trans ::user::control_bar::OnTimer(ptimer->m_nIDEvent);

}


bool simple_toolbar::on_click(const ::user::item & item)
{

   __pointer(::user::interaction) pwnd = GetOwner();

   if (!item)
   {

      return false;

   }

   ::user::command command(m_itema[item]->m_id);

   pwnd->_001SendCommand(&command);

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


void simple_toolbar::_001SetImageList(__pointer(image_list) imagelist)
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

      m_pimagelistHue = new image_list();

   }

   ::draw2d::graphics_pointer spgraphics(e_create);

   spgraphics->CreateDC("DISPLAY", nullptr, nullptr, nullptr);

   System.imaging().CreateHueImageList(
      &spgraphics,
      m_pimagelistHue,
      m_pimagelist,
      RGB(192, 192, 180),
      0.50
   );

   if(m_pimagelistBlend == nullptr)
   {

      m_pimagelistBlend = new image_list();

   }

   System.imaging().Createcolor_blend_ImageList(
      m_pimagelistBlend,
      m_pimagelist,
      RGB(255, 255, 240),
      64
   );

   if(m_pimagelistHueLight == nullptr)
   {

      m_pimagelistHueLight = new image_list();

   }

   System.imaging().CreateHueImageList(
      &spgraphics,
      m_pimagelistHueLight,
      m_pimagelist,
      RGB(220, 220, 215),
      0.50
      );

   */

}


/////////////////////////////////////////////////////////////////////////////
// simple_toolbar idle update through simple_tool_command class

simple_tool_command::simple_tool_command(::object * pobject) :
   ::user::command(pobject)
{

}


void simple_tool_command::Enable(bool bOn, const ::action_context & context)
{

   m_bEnableChanged = TRUE;

   __pointer(simple_toolbar) pToolBar = m_puiOther;

   ASSERT(pToolBar != nullptr);

   //   ASSERT_KINDOF(simple_toolbar, pToolBar);

   ASSERT(m_iIndex < m_iCount);

   UINT nNewStyle = pToolBar->GetButtonStyle((index)m_iIndex) & ~TBBS_DISABLED;

   if (!bOn)
   {

      nNewStyle |= TBBS_DISABLED;

      // WINBUG: If a button is currently pressed and then is disabled
      // COMCTL32.DLL does not unpress the button, even after the mouse
      // button goes up!  We work around this bug by forcing TBBS_PRESSED
      // off when a button is disabled.
      nNewStyle &= ~TBBS_PRESSED;

   }

   ASSERT(!(nNewStyle & TBBS_SEPARATOR));

   pToolBar->SetButtonStyle((index)m_iIndex, nNewStyle);

}


void simple_tool_command::_001SetCheck(enum_check echeck, const ::action_context & context)
{

   // 0=>off, 1=>on, 2=>indeterminate

   ASSERT(echeck == check_checked || echeck == check_unchecked || echeck == check_tristate);

   __pointer(simple_toolbar) pToolBar = m_puiOther;

   ASSERT(pToolBar != nullptr);

   ASSERT_KINDOF(simple_toolbar, pToolBar);

   ASSERT(m_iIndex < m_iCount);

   UINT nNewStyle = pToolBar->GetButtonStyle((index)m_iIndex) & ~(TBBS_CHECKED | TBBS_INDETERMINATE);

   if (echeck == check_checked)
   {

      nNewStyle |= TBBS_CHECKED;

   }
   else if (echeck == check_tristate)
   {

      nNewStyle |= TBBS_INDETERMINATE;

   }

   ASSERT(!(nNewStyle & TBBS_SEPARATOR));

   pToolBar->SetButtonStyle((index)m_iIndex, nNewStyle | TBBS_CHECKBOX);

}


void simple_tool_command::SetText(const char *, const ::action_context & context)
{

   // ignore it

}


index simple_toolbar::GetItemStyle(index iItem)
{

   return m_itema[iItem]->m_fsStyle;

}


bool simple_toolbar::SetItemStyle(index iItem, BYTE bStyle)
{

   UNREFERENCED_PARAMETER(iItem);

   UNREFERENCED_PARAMETER(bStyle);

   return false;

}


UINT simple_toolbar::GetButtonStyle(index nIndex)
{

   __pointer(::user::toolbar_item) pitem = m_itema[nIndex];

   if (!pitem)
   {

      return 0;

   }

   return MAKELONG(pitem->m_fsStyle, pitem->m_fsState);

}


void simple_toolbar::SetButtonStyle(index nIndex, UINT nStyle)
{

   __pointer(::user::toolbar_item) pitem = m_itema[nIndex];

   if (!pitem)
   {

      return;

   }

   if (pitem->m_fsStyle != (BYTE)LOWORD(nStyle) || pitem->m_fsState != (BYTE)HIWORD(nStyle))
   {

      pitem->m_fsStyle = (BYTE)LOWORD(nStyle);

      pitem->m_fsState = (BYTE)HIWORD(nStyle);

      m_bDelayedButtonLayout = TRUE;

   }

}


void simple_toolbar::_001OnNcCalcSize(::message::message * pmessage)
{

#if defined(WINDOWS_DESKTOP) //|| defined(LINUX)

   SCAST_PTR(::message::nc_calc_size, pnccalcsize, pmessage);

   // calculate border space (will add to top/bottom, subtract from right/bottom)
   ::rect rect;

   bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;

   auto pgraphics = ::draw2d::create_memory_graphics();

   ::user::control_bar::CalcInsideRect(pgraphics, rect, bHorz);

   // adjust non-client area for border space
   pnccalcsize->m_pparams->rgrc[0].left += rect.left;

   pnccalcsize->m_pparams->rgrc[0].top += rect.top;

   pnccalcsize->m_pparams->rgrc[0].right += rect.right;

   pnccalcsize->m_pparams->rgrc[0].bottom += rect.bottom;

#else

   __throw(todo());

#endif

}


//void simple_toolbar::_001OnNcHitTest(::message::message * pmessage)
//{
//
//   SCAST_PTR(::message::nchittest, pnchittest, pmessage);
//
//   pnchittest->set_lresult(HTCLIENT);
//
//}


#define CX_OVERLAP  0


index simple_toolbar::WrapToolBar(::draw2d::graphics_pointer & pgraphics, index nCount, index nWidth)
{

   sync_lock sl(mutex());

   index nResult = 0;

   ASSERT(nCount > 0);

   pgraphics->set_font(this);

   m_dFontSize = pgraphics->m_pfont->m_dFontSize;

   int iImageSpacing = get_image_spacing();

   auto sSeparator = get_separator_size();

   auto sSpacing = get_item_spacing();

   //size sPress = get_press_shift();

   ::rect rectItemPad = get_item_pad();

   ::rect rectBorder = get_bar_border();

   index x = rectBorder.left;

   string str;

   auto iC = MIN(nCount, m_itema.get_count());

   bool bFirstInRow = true;

   for (index i = 0; i < iC; i++)
   {

      m_itema[i]->m_fsState &= ~TBSTATE_WRAP;

      if (m_itema[i]->m_fsState & TBSTATE_HIDDEN)
         continue;

      GetButtonText(i, str);

      index dx, dxNext;

      if (m_itema[i]->m_fsStyle & TBSTYLE_SEP)
      {

         dx = sSeparator.cx;

         dxNext = dx;

      }
      else
      {

         dx = rectItemPad.left;

         if (m_itema[i]->m_pimage->is_set())
         {

            dx += m_itema[i]->m_pimage->height();

         }

         if (str.has_char() && m_itema[i]->m_pimage->is_set())
         {

            dx += iImageSpacing;

         }

         if (str.has_char())
         {

            sized size = pgraphics->GetTextExtent(str);

            dx = (index)  (size.cx + EXTRA_TEXT_CX);

         }

         dx += rectItemPad.right; // +sPress.cx;

         dxNext = dx - CX_OVERLAP;

      }

      bool bFound = FALSE;

      if (x + dx > nWidth - rectBorder.right)
      {

         for (index j = i; j >= 0 && !(m_itema[j]->m_fsState & TBSTATE_WRAP); j--)
         {

            // find last separator that isn't hidden
            // a separator that has a command ID is not
            // a separator, but a custom control.
            if ((m_itema[j]->m_fsStyle & TBSTYLE_SEP) &&
                  (m_itema[j]->m_id == "separator") &&
                  !(m_itema[j]->m_fsState & TBSTATE_HIDDEN))
            {

               bFound = TRUE;

               i = j;

               x = rectBorder.left;

               bFirstInRow = true;

               m_itema[j]->m_fsState |= TBSTATE_WRAP;

               nResult++;

               break;

            }

         }

         if (!bFound)
         {

            for (index j = i - 1; j >= 0 && !(m_itema[j]->m_fsState & TBSTATE_WRAP); j--)
            {

               // Never wrap anything that is hidden,
               // or any custom controls
               if ((m_itema[j]->m_fsState & TBSTATE_HIDDEN) ||
                     ((m_itema[j]->m_fsStyle & TBSTYLE_SEP) &&
                      (m_itema[j]->m_id != "separator")))
               {

                  continue;

               }

               bFound = TRUE;

               i = j;

               x = rectBorder.left;

               bFirstInRow = true;

               m_itema[j]->m_fsState |= TBSTATE_WRAP;

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

      const ::size & size = CalcSize(pgraphics, nCount);

      WrapToolBar(pgraphics, nCount, size.cx);

      CalcSize(pgraphics, nCount);

   }
   else
   {

      ::size sizeMax, sizeMin, sizeMid;

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
   ::rect rectOldPos;
};


size simple_toolbar::CalcLayout(::draw2d::graphics_pointer & pgraphics, u32 dwMode, index nLength)
{

   //__pointer(::user::tab) ptab = GetTypedParent < ::user::tab >();

   //if (ptab.is_set())
   //{

   //   if (!ptab->m_bShowTabs)
   //   {

   //      return size(0, 0);

   //   }

   //}

   ASSERT_VALID(this);

   if (!is_window())
   {

      return ::size(0, 0);

   }

   if (dwMode & LM_HORZDOCK)
   {

      ASSERT(dwMode & LM_HORZ);

   }

   index nCount;

   ::size sizeResult(0, 0);

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

            ::rect rect;

            CalcInsideRect(pgraphics, rect, (dwMode & LM_HORZ) != 0);

            bool bVert = (dwMode & LM_LENGTHY) != 0;

            index nLen = nLength + (bVert ? rect.height() : rect.width());

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

         m_bDelayedButtonLayout = FALSE;

         index i;

         for (i = 0; i < nCount; i++)
         {

            if ((m_itema[i]->m_fsStyle & TBSTYLE_SEP) && (m_itema[i]->m_id != "separator"))
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

               if ((m_itema[i]->m_fsStyle & TBSTYLE_SEP) && (m_itema[i]->m_id != "separator"))
               {

                  pControl[nControlCount].nIndex = i;

                  pControl[nControlCount].strId = m_itema[i]->m_id;

                  ::rect rect;

                  _001GetItemRect(i, &rect);

                  _001ClientToScreen(rect);

                  pControl[nControlCount].rectOldPos = rect;

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

            // _SetButton(i, &m_itema[i]);
            //
            // GetButtonText(i, str);
            //
            // ::size size;
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
            // button.m_id = i;
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
            // UINT uiID = GetItemID(i);
            // GetToolBarCtrl().GetButtonInfo(uiID, &buttona);
            // TRACE("BUTTON.m_id = %d\n", buttona.m_id  );
            // TRACE("BUTTON.m_fsStyle = %d\n", buttona.m_fsStyle  );
            // TRACE("BUTTON.cx = %d\n", buttona.cx );

         }

         if (nControlCount > 0)
         {

            for (index i = 0; i < nControlCount; i++)
            {

               /* xxx

               __pointer(::user::interaction) pwindow = get_child_by_id(pControl[i]->strId);

               if (pwindow != nullptr)
               {

               ::rect rect;

               pwindow->get_window_rect(&rect);

               const ::point & point = rect.top_left() - pControl[i]->rectOldPos.top_left();

               _001GetElementRect(pControl[i]->nIndex, &rect);

               point = rect.top_left() + point;

               pwindow->set_window_pos(0, point.x, point.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);

               }*/

            }

            delete[] pControl;

         }

         m_bDelayedButtonLayout = bIsDelayed != 0;

      }

      //delete[] m_itema;

   }

   //BLOCK: Adjust Margins
   {

      ::rect rect;

      CalcInsideRect(pgraphics, rect, (dwMode & LM_HORZ) != 0);

      sizeResult.cy -= rect.height();

      sizeResult.cx -= rect.width();

      const ::size & size = ::user::control_bar::CalcFixedLayout(pgraphics, (dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZ) != 0);

      sizeResult.cx = MAX(sizeResult.cx, size.cx);

      sizeResult.cy = MAX(sizeResult.cy, size.cy);

   }

   return sizeResult;

}


void simple_toolbar::GetButtonText(index i, string &str)
{

   if (i < 0 || i >= m_itema.get_count())
   {

      str.Empty();

      return;

   }

   if (m_itema[i].is_null())
   {

      str.Empty();

      return;

   }

   str = m_itema[i]->m_str;

}


void simple_toolbar::OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle)
{

   // a dynamically resizeable toolbar can not have the CBRS_FLOAT_MULTI
   ASSERT(!((dwNewStyle & CBRS_SIZE_DYNAMIC) && (m_dwDockStyle & CBRS_FLOAT_MULTI)));

   // a toolbar can not be both dynamic and fixed in size
   ASSERT(!((dwNewStyle & CBRS_SIZE_FIXED) && (dwNewStyle & CBRS_SIZE_DYNAMIC)));

   // CBRS_SIZE_DYNAMIC can not be disabled once it has been enabled
   ASSERT(((dwOldStyle & CBRS_SIZE_DYNAMIC) == 0) || ((dwNewStyle & CBRS_SIZE_DYNAMIC) != 0));

   if (((dwOldStyle & CBRS_BORDER_ANY) != (dwNewStyle & CBRS_BORDER_ANY)))
   {

      // recalc non-client area when border styles change
      //set_window_pos(zorder_none, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

   }

   m_bDelayedButtonLayout = TRUE;

}


size simple_toolbar::CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, index nLength, u32 dwMode)
{

   if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
         ((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
   {

      return CalcFixedLayout(pgraphics, (dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZDOCK) != 0);

   }

   return CalcLayout(pgraphics, dwMode, nLength);

}


//void simple_toolbar::_001OnMouseLeave(::message::message * pmessage)
//{
//
//   SCAST_PTR(::message::base, pbase, pmessage);
//
//   m_itemHover = ::user::element_none;
//
//   OnUpdateHover();
//
//   set_need_redraw();
//
//   pbase->set_lresult(0);
//
//}


void simple_toolbar::SetItemImage(index iItem, index iImage)
{

   m_itema[iItem]->m_iImage = iImage;

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

   m_itema.remove_all();

}


rect simple_toolbar::get_item_pad()
{

   auto rect = m_rectItemPad;

   if (rect.left < 0)
   {

      rect.left = (LONG)(m_dFontSize / 3);

   }

   if (rect.right < 0)
   {

      rect.right = (LONG) (m_dFontSize / 3);

   }

   if (rect.top < 0)
   {

      rect.top = (LONG) (m_dFontSize / 3);

   }

   if (rect.bottom < 0)
   {

      rect.bottom = (LONG) (m_dFontSize / 3);

   }

   return rect;

}


rect simple_toolbar::get_bar_border()
{

   auto rect = m_rectBorder;

   if (rect.left < 0)
   {

      rect.left = (LONG) (m_dFontSize / 3);

   }
   if (rect.right < 0)
   {

      rect.right = (LONG) (m_dFontSize / 3);

   }
   if (rect.top < 0)
   {

      rect.top = (LONG) (m_dFontSize / 3);

   }
   if (rect.bottom < 0)
   {

      rect.bottom = (LONG)(m_dFontSize / 3);

   }

   return rect;

}


size simple_toolbar::get_press_shift()
{

   return m_sizePress;

}


size simple_toolbar::get_item_spacing()
{

   ::size s;

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


size simple_toolbar::get_separator_size()
{

   ::size s;

   s = m_sizeSeparator;

   if (s.cx < 0)
   {

      s.cx = LONG(m_dFontSize * 2 / 3);

   }

   if (s.cy < 0)
   {

      s.cy = LONG(m_dFontSize * 2 / 3);

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


