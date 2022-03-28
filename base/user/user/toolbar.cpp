#include "framework.h"
#include "aura/operating_system.h"
//#include "base/user/user/_user.h"
#include "aqua/xml.h"
//#include "acme/operating_system/_os.h"
//#include "acme/operating_system/cross.h"
#include "aura/operating_system/_user.h"
#include "toolbar.h"
#include "aura/graphics/draw2d/_draw2d.h"
#include "acme/timer.h"

#define CLR_TO_RGBQUAD(clr)     (rgb(::blue(clr), ::green(clr), ::red(clr)))

struct __COLORMAP
{
   // use u32 instead of RGBQUAD so we can compare two RGBQUADs easily
   u32 rgbqFrom;
   index iSysColorTo;
};

//static const __COLORMAP gen_SysColorMap[] =
//{
// mapping from color in DIB to system color
// { RGB_TO_RGBQUAD(0x00, 0x00, 0x00),  COLOR_BTNTEXT },       // black
//{ RGB_TO_RGBQUAD(0x80, 0x80, 0x80),  COLOR_BTNSHADOW },     // dark gray
//{ RGB_TO_RGBQUAD(0xC0, 0xC0, 0xC0),  COLOR_BTNFACE },       // bright gray
//{ RGB_TO_RGBQUAD(0xFF, 0xFF, 0xFF),  COLOR_BTNHIGHLIGHT }   // white
//};


class user_toolbar_command : public ::message::command        // class private to this file !
{
public: // re-implementations only

   user_toolbar_command(::object * pobject);
   void enable(bool bOn = true, const ::action_context & context = ::e_source_system) override;
   //   virtual void _001SetCheck(bool bCheck, const ::action_context & context = ::e_source_system);   // 0, 1 or 2 (indeterminate)
   void _001SetCheck(enum_check echeck, const ::action_context & context = ::e_source_system) override;   // 0, 1 or 2 (indeterminate)
//   virtual void SetRadio(bool bOn = true, const ::action_context & context = ::e_source_system);
   //void _001SetText(const ::string & pszText, const ::action_context & context = ::e_source_system) override;

};


namespace user
{


   toolbar::toolbar()
   {

      m_bSimpleLayout = true;

      // initialize state
      m_pStringMap = nullptr;

      m_bDelayedButtonLayout = true;

      // default image sizes
      m_sizeImage.cx = 16;
      m_sizeImage.cy = 15;

      // default button sizes
      m_sizeButton.cx = 23;
      m_sizeButton.cy = 22;

      // top and bottom borders are 1 larger than default for ease of grabbing
      m_rectangleBorder.top = 3;
      m_rectangleBorder.bottom = 3;
   }

   toolbar::~toolbar()
   {
//#ifdef WINDOWS_DESKTOP
//      ::DeleteObject((HGDIOBJ*)&m_hbmImageWell);
//#else
      //    throw ::exception(todo);
//#endif
      delete m_pStringMap;

      //m_nCount = 0;
   }


   void toolbar::install_message_routing(::channel * pchannel)
   {

      ::user::control_bar::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_non_client_hittest, pchannel, this, &toolbar::_001OnNcHitTest);
      MESSAGE_LINK(e_message_non_client_calcsize, pchannel, this, &toolbar::on_message_non_client_calculate_size);
      MESSAGE_LINK(e_message_create, pchannel, this, &toolbar::on_message_create);
//#ifdef WINDOWS_DESKTOP
//      MESSAGE_LINK(TB_SETBITMAPSIZE, pchannel, this, &toolbar::_001OnSetBitmapSize);
//      MESSAGE_LINK(TB_SETBUTTONSIZE, pchannel, this, &toolbar::_001OnSetButtonSize);
//      MESSAGE_LINK(WM_SETTINGCHANGE, pchannel, this, &toolbar::_001OnPreserveZeroBorderHelper);
//      MESSAGE_LINK(WM_SETFONT, pchannel, this, &toolbar::_001OnPreserveZeroBorderHelper);
//      MESSAGE_LINK(WM_SYSCOLORCHANGE, pchannel, this, &toolbar::_001OnSysColorChange);
//#endif

   }


   void toolbar::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_etimer == e_timer_hover)
      {

         auto pframewindow = get_parent_frame();

         on_command_probe(pframewindow, true);

      }

   }


   void toolbar::on_command_probe(::user::interaction * puserinteraction, bool bDisableIfNoHndler)
   {

      user_toolbar_command command(this);

      command.m_puiOther = (this);

      command.m_iCount = _001GetItemCount();

      for (command.m_iIndex = 0; command.m_iIndex < command.m_iCount; command.m_iIndex++)
      {

         if (m_useritema[command.m_iIndex]->m_atom != "separator")
         {

            command.m_atom = m_useritema[command.m_iIndex]->m_atom;

            // allow reflections
            //if (::user::interaction::on_command(0,
            //   MAKELONG((index)CN_UPDATE_::message::command, e_message_command+WM_REFLECT_BASE),
            //   &state, nullptr))
            //   continue;

            command.m_bEnableChanged = false;

            // allow the toolbar itself to have update handlers
            _001SendCommandProbe(&command);

            if (command.m_bRet)
            {

               continue;

            }

            //if (!state.m_bEnableChanged)
            //{
            //
            //   if (m_useritema[state.m_iIndex]->m_bEnableIfHasCommandHandler)
            //   {

            //      if (!state.m_bHasCommandHandler)
            //      {

            //         continue;


            //      }

            //   }

            //}

            // allow the owner to process the update
            command.do_probe(puserinteraction);

         }

      }

      // update the dialog controls added to the toolbar
      update_dialog_controls(puserinteraction);

   }



   //bool toolbar::create_interaction(::user::interaction * puiParent,u32 uStyle, ::atom atom)
   //{

   //   return create_toolbar(puiParent, 0, uStyle, atom);

   //}


//   bool toolbar::create_toolbar(::user::interaction * puiParent,u32 dwCtrlStyle,u32 uStyle, atom nID)
//   {
//
//      ASSERT_VALID(puiParent);   // must have a parent
//      ASSERT (!((uStyle & CBRS_SIZE_FIXED) && (uStyle & CBRS_SIZE_DYNAMIC)));
//
//      //SetBorders(rectangleBorders);
//
//      // save the style
//      m_dwStyle = (uStyle & CBRS_ALL);
//      if (nID == __IDW_TOOLBAR)
//         m_dwStyle |= CBRS_HIDE_INPLACE;
//
//      uStyle &= ~CBRS_ALL;
//      uStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;
//
//      m_dwCtrlStyle = dwCtrlStyle & (0xffff0000 | TBSTYLE_FLAT);
//
//
//
////         if(!::user::control_bar::create_interaction(TOOLBARCLASSNAMEA,nullptr,uStyle,nullptr,puiParent,nID))
//      //          return false;
//      if(!::user::control_bar::create_interaction("ToolbarWindow32",nullptr,uStyle, puiParent,nID))
//         return false;
//
//      // synchronization_object up the sizes
//      SetSizes(m_sizeButton, m_sizeImage);
//
//      // Note: Parent must resize itself for control bar to be resized
//
//      return true;
//   }


   __pointer(::user::interaction) toolbar::set_owner(__pointer(::user::interaction) pOwnerWnd)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT_VALID(this);
//      ASSERT(is_window());
//      default_window_procedure(TB_SETPARENT, (WPARAM)pOwnerWnd.m_p, 0);
//#else
//      throw ::exception(todo);
//
//#endif
      return ::user::control_bar::set_owner(pOwnerWnd);

   }


   void toolbar::SetSizes(const ::size_i32 & sizeButton, const ::size_i32 & sizeImage)
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

      //if (is_window())
      {
         // set the sizes via TB_SETBITMAPSIZE and TB_SETBUTTONSIZE
//#ifdef WINDOWS_DESKTOP
//         //VERIFY(send_message(TB_SETBITMAPSIZE, 0, MAKELONG(sizeImage.cx, sizeImage.cy)));
//         //VERIFY(send_message(TB_SETBUTTONSIZE, 0, MAKELONG(sizeButton.cx, sizeButton.cy)));
//#else
//         //throw ::exception(todo);
//#endif
         // Invalidate();   // just to be nice if called when toolbar is visible
      }
      //else
      {
         // just set our internal values for later
         m_sizeButton = sizeButton;
         m_sizeImage = sizeImage;
      }
   }


   void toolbar::SetHeight(index cyHeight)
   {

      ASSERT_VALID(this);

      index nHeight = cyHeight;
      if (m_dwStyle & CBRS_BORDER_TOP)
//         cyHeight -= afxData.cyBorder2;
         cyHeight -= 2;
      if (m_dwStyle & CBRS_BORDER_BOTTOM)
         //cyHeight -= afxData.cyBorder2;
         cyHeight -= 2;

      m_rectangleBorder.bottom = (::i32) ((cyHeight - m_sizeButton.cy) / 2);
      // if there is an extra pixel, m_rectangleBorder.top will get it
      m_rectangleBorder.top = (::i32) (cyHeight - m_sizeButton.cy - m_rectangleBorder.bottom);
      if (m_rectangleBorder.top < 0)
      {
         FORMATTED_TRACE("Warning: toolbar::SetHeight(%d) is smaller than button.",
               nHeight);
         m_rectangleBorder.bottom += m_rectangleBorder.top;
         m_rectangleBorder.top = 0;  // will clip at bottom
      }

      // recalculate the non-client region
      //set_window_position(zorder_none, 0, 0, 0, 0, SWP_DRAWFRAME|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
      Invalidate();   // just to be nice if called when toolbar is visible
   }


//#ifdef WINDOWS_DESKTOP
//
//   bool toolbar::from(HBITMAP hbmImageWell)
//   {
//      ASSERT_VALID(this);
//      ASSERT(hbmImageWell != nullptr);
//
//      // the caller must manage changing system colors
////      m_hInstImageWell = nullptr;
//      //    m_hRsrcImageWell = nullptr;
//
//      // tell common control toolbar about the new bitmap
//      return AddReplaceBitmap(hbmImageWell);
//   }
//
//   bool toolbar::AddReplaceBitmap(HBITMAP hbmImageWell)
//   {
//      bool bResult = false;
//
//      // need complete bitmap size_i32 to determine number of images
//      /*#ifdef WINDOWS_DESKTOP
//            BITMAP bitmap;
//            VERIFY(::GetObject(hbmImageWell, sizeof(BITMAP), &bitmap));
//
//            // add the bitmap to the common control toolbar
//            if (m_hbmImageWell == nullptr)
//            {
//               TBADDBITMAP addBitmap;
//               addBitmap.hInst = nullptr; // makes TBADDBITMAP::nID behave a HBITMAP
//               addBitmap.nID = (::u32)hbmImageWell;
//               bResult =  default_window_procedure(TB_ADDBITMAP,
//                  bitmap.bmWidth / m_sizeImage.cx, (LPARAM)&addBitmap) == 0;
//            }
//            else
//            {
//               TBREPLACEBITMAP replaceBitmap;
//               replaceBitmap.hInstOld = nullptr;
//               replaceBitmap.nIDOld = (::u32)m_hbmImageWell;
//               replaceBitmap.hInstNew = nullptr;
//               replaceBitmap.nIDNew = (::u32)hbmImageWell;
//               replaceBitmap.nButtons = bitmap.bmWidth / m_sizeImage.cx;
//               bResult = default_window_procedure(TB_REPLACEBITMAP, 0, (LPARAM)&replaceBitmap) != false;
//            }
//            // erase old bitmap, if present
//            if (bResult)
//            {
//               ::DeleteObject((HGDIOBJ*)&m_hbmImageWell);
//               m_hbmImageWell = hbmImageWell;
//            }
//      #else
//            throw ::exception(todo);
//      #endif*/
//      return bResult;
//   }
//
//#endif

   bool toolbar::SetButtons(const ::u32* pIDArray, index nIDCount)
   {

//#ifdef WINDOWS_DESKTOP
//
//      ASSERT_VALID(this);
//
//      ASSERT(nIDCount >= 1);  // must be at least one of them
//
//      ASSERT(pIDArray == nullptr || __is_valid_address(pIDArray, sizeof(::u32) * nIDCount, false));
//
//      // delete all existing buttons
//      index nCount = (index)default_window_procedure(TB_BUTTONCOUNT, 0, 0);
//      while (nCount--)
//         VERIFY(default_window_procedure(TB_DELETEBUTTON, 0, 0));
//
//      TBBUTTON button; __memset(&button, 0, sizeof(TBBUTTON));
//      button.iString = -1;
//      if (pIDArray != nullptr)
//
//      {
//         // add new buttons to the common control
//         index iImage = 0;
//         for (index i = 0; i < nIDCount; i++)
//         {
//            button.fsState = TBSTATE_ENABLED;
//            if ((button.idCommand = *pIDArray++) == 0)
//
//            {
//               // separator
//               button.fsStyle = TBSTYLE_SEP;
//               // width of separator includes 8 pixel overlap
//               if ((GetStyle() & TBSTYLE_FLAT))
//                  button.iBitmap = 6;
//               else
//                  button.iBitmap = 8;
//            }
//            else
//            {
//               // a command button with image
//               button.fsStyle = TBSTYLE_BUTTON;
//               button.iBitmap = (int) iImage++;
//            }
//            if (!default_window_procedure(TB_ADDBUTTONS, 1, (LPARAM)&button))
//               return false;
//         }
//      }
//      else
//      {
//         // add 'blank' buttons
//         button.fsState = TBSTATE_ENABLED;
//         for (index i = 0; i < nIDCount; i++)
//         {
//            ASSERT(button.fsStyle == TBSTYLE_BUTTON);
//            if (!default_window_procedure(TB_ADDBUTTONS, 1, (LPARAM)&button))
//               return false;
//         }
//      }
//      //   m_nCount = (index)default_window_procedure(TB_BUTTONCOUNT, 0, 0);
//      m_bDelayedButtonLayout = true;
//#else
//      throw ::exception(todo);
//#endif
      return true;
   }
/*

#ifdef WINDOWS_DESKTOP
*/

//   void toolbar::_GetButton(::index nIndex, TBBUTTON* pButton) const
//   {
//
//      //toolbar* pBar = (toolbar*)this;
//
//      //VERIFY(pBar->default_window_procedure(TB_GETBUTTON, (WPARAM) nIndex, (LPARAM)pButton));
//
//      //// TBSTATE_ENABLED == e_toolbar_item_style_disabled so invert it
//
//      //pButton->fsState ^= TBSTATE_ENABLED;
//
//   }
//
//
//   void toolbar::_SetButton(::index nIndex, TBBUTTON* pButton)
//   {
//
//      // get original button state
//
////      TBBUTTON button;
////
////      VERIFY(default_window_procedure(TB_GETBUTTON, (WPARAM) nIndex, (LPARAM)&button));
////
////      // prepare for old/new button comparsion
////      button.bReserved[0] = 0;
////      button.bReserved[1] = 0;
////      // TBSTATE_ENABLED == e_toolbar_item_style_disabled so invert it
////      pButton->fsState ^= TBSTATE_ENABLED;
////      pButton->bReserved[0] = 0;
////      pButton->bReserved[1] = 0;
////
////      // nothing to do if they are the same
////      if (__memcmp(pButton, &button, sizeof(TBBUTTON)) != 0)
////      {
////         // don't redraw everything while setting the button
////         u32 uStyle = GetStyle();
////         ModifyStyle(WS_VISIBLE, 0);
////         VERIFY(default_window_procedure(TB_DELETEBUTTON, (WPARAM) nIndex, 0));
////         VERIFY(default_window_procedure(TB_INSERTBUTTON, (WPARAM) nIndex, (LPARAM)pButton));
////         ModifyStyle(0, uStyle & WS_VISIBLE);
////
////         // invalidate appropriate parts
////         if (((pButton->fsStyle ^ button.fsStyle) & TBSTYLE_SEP) ||
////               ((pButton->fsStyle & TBSTYLE_SEP) && pButton->iBitmap != button.iBitmap))
////         {
////            // changing a separator
////            Invalidate();
////         }
////         else
////         {
////
////            // invalidate just the button
////
////            ::rectangle_i32 rectangle;
////
////            if (default_window_procedure(TB_GETITEMRECT, (WPARAM)nIndex, (LPARAM)& rectangle))
////            {
////
////               InvalidateRect(rectangle);
////
////            }
////
////         }
////
////      }
////
////   }
////
////#endif
////
////   index toolbar::CommandToIndex(::u32 nIDFind)
////   {
////      ASSERT_VALID(this);
////      ASSERT(is_window());
////
////#ifdef WINDOWS_DESKTOP
////      toolbar* pBar = (toolbar*)this;
////      return (index)pBar->default_window_procedure(TB_COMMANDTOINDEX, nIDFind, 0);
////#else
////      throw ::exception(todo);
////#endif
//   }

   ::u32 toolbar::GetItemID(index nIndex)
   {
      ASSERT_VALID(this);
      ASSERT(is_window());

//#ifdef WINDOWS_DESKTOP
//      TBBUTTON button;
//      _GetButton(nIndex, &button);
//      return button.idCommand;
//#else
//      throw ::exception(todo);
//#endif
      return 0;
   }

   void toolbar::GetItemRect(index nIndex, RECTANGLE_I32 * prectangle)

   {
      ASSERT_VALID(this);
      ASSERT(is_window());

      // handle any delayed on_layout
      //if (m_bDelayedButtonLayout)
      //   ((toolbar*)this)->set_need_layout(pgraphics);

//      // now it is safe to get the item rectangle_i32
//#ifdef WINDOWS_DESKTOP
//      toolbar* pBar = (toolbar*)this;
//      if (!pBar->default_window_procedure(TB_GETITEMRECT, (WPARAM) nIndex, (LPARAM)prectangle))
//
//         ::SetRectEmpty(prectangle);
//
//#else
//      throw ::exception(todo);
//#endif
   }

   void toolbar::on_layout(::draw2d::graphics_pointer & pgraphics)
   {
      //ASSERT(m_bDelayedButtonLayout);

      //m_bDelayedButtonLayout = false;

      //bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
      //if(m_bSimpleLayout)
      //   CalcSimpleLayout();
      //else if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
      //   ((toolbar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH | LM_COMMIT);
      //else if (bHorz)
      //   ((toolbar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK | LM_COMMIT);
      //else
      //   ((toolbar*)this)->CalcDynamicLayout(0, LM_VERTDOCK | LM_COMMIT);
   }


   e_toolbar_item_style toolbar::get_item_style(index iIndex)
   {

      return m_useritema[iIndex].cast <toolbar_item>()->m_estyle;

   }


   void toolbar::set_item_style(index iIndex, const e_toolbar_item_style &estyle)
   {

      m_useritema[iIndex].cast <toolbar_item>()->m_estyle = estyle;

   }


#define CX_OVERLAP  0


   ::e_toolbar_item_state toolbar::get_item_state(::index iItem)
   {

      __pointer(::user::toolbar_item) pitem = m_useritema[iItem];

      auto & estate = pitem->m_estate;

      auto & estyle = pitem->m_estyle;

      if (!(estyle & e_toolbar_item_style_separator))
      {

         bool bEnabled = !(estyle & e_toolbar_item_style_disabled);

         estate.set(e_toolbar_item_state_enabled, bEnabled);

         bool bPressed = ::is_element(m_pitemPressed, ::e_element_item) && ::is_item(m_pitemPressed, iItem);

         estate.set(e_toolbar_item_state_pressed, bPressed);

         bool bHover = ::is_element(m_pitemHover, ::e_element_item) && ::is_item(m_pitemHover, iItem);

         estate.set(e_toolbar_item_state_hover, bHover);

      }

      return estate;

   }


   ::user::enum_state toolbar::get_item_user_state(index iIndex)
   {

      auto eitemstate = get_item_state(iIndex);

      ::user::e_state estate = e_state_none;

      if(eitemstate & e_toolbar_item_state_checked)
      {

         estate += ::user::e_state_checked;

      }

      if(eitemstate & e_toolbar_item_state_pressed)
      {

         estate += ::user::e_state_pressed;

      }

      if (eitemstate & e_toolbar_item_state_hover)
      {

         estate += ::user::e_state_hover;

      }

      if(!(eitemstate & e_toolbar_item_state_enabled))
      {

         estate += ::user::e_state_disabled;

      }

      return estate;

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   ::size_i32 toolbar::CalcSize(TBBUTTON * pData, index nCount)
//   {
//
//      //ASSERT(pData != nullptr && nCount > 0);
//
//      //point_i32 cur(0,0);
//
//      //::size_i32 sizeResult(0,0);
//
//      //u32 dwExtendedStyle = (u32) default_window_procedure(TB_GETEXTENDEDSTYLE, 0, 0);
//
//      //for (index i = 0; i < nCount; i++)
//      //{
//      //   //WINBUG: The IE4 version of COMCTL32.DLL calculates the separation
//      //   //  on a TBSTYLE_WRAP button as 100% of the value in iBitmap compared
//      //   //  to the other versions which calculate it at 2/3 of that value.
//      //   //  This is actually a bug which should be fixed in IE 4.01, so we
//      //   //  only do the 100% calculation specifically for IE4.
//      //   index cySep = pData[i].iBitmap;
//      //   if (!(GetStyle() & TBSTYLE_FLAT))
//      //      cySep = cySep * 2 / 3;
//
//      //   if (pData[i].fsState & e_toolbar_button_hidden)
//      //      continue;
//
//      //   index cx = m_sizeButton.cx;
//      //   if (pData[i].fsStyle & TBSTYLE_SEP)
//      //   {
//      //      // a separator represents either a height or width
//      //      if (pData[i].fsState & TBSTATE_WRAP)
//      //         sizeResult.cy = (::i32) maximum(cur.y + m_sizeButton.cy + cySep, sizeResult.cy);
//      //      else
//      //         sizeResult.cx = maximum(cur.x + pData[i].iBitmap, sizeResult.cx);
//      //   }
//      //   else
//      //   {
//      //      // check for dropdown style, but only if the buttons are being drawn
//      //      if ((pData[i].fsStyle & TBSTYLE_DROPDOWN) &&
//      //            (dwExtendedStyle & TBSTYLE_EX_DRAWDDARROWS))
//      //      {
//      //         // add size_i32 of drop down
//      //         cx += 2;
//      //      }
//      //      sizeResult.cx = maximum(cur.x + cx, sizeResult.cx);
//      //      sizeResult.cy = maximum(cur.y + m_sizeButton.cy, sizeResult.cy);
//      //   }
//
//      //   if (pData[i].fsStyle & TBSTYLE_SEP)
//      //      cur.x += pData[i].iBitmap;
//      //   else
//      //      cur.x += cx - CX_OVERLAP;
//
//      //   if (pData[i].fsState & TBSTATE_WRAP)
//      //   {
//      //      cur.x = 0;
//      //      cur.y += m_sizeButton.cy;
//      //      if (pData[i].fsStyle & TBSTYLE_SEP)
//      //         cur.y += cySep;
//      //   }
//      //}
//      //return sizeResult;
//      return { 0,0 };
//   }
//
//   index toolbar::WrapToolBar(TBBUTTON* pData, index nCount, index nWidth)
//   {
//
//   //   ASSERT(pData != nullptr && nCount > 0);
//
//   //   auto pgraphics = create_memory_graphics();
//
//   //   index nResult = 0;
//   //   index x = 0;
//   //   string str;
//   //   for (index i = 0; i < nCount; i++)
//   //   {
//   //      pData[i].fsState &= ~TBSTATE_WRAP;
//
//   //      if (pData[i].fsState & e_toolbar_button_hidden)
//   //         continue;
//   //      GetButtonText(i, str);
//   //      index dx, dxNext;
//   //      if (pData[i].fsStyle & TBSTYLE_SEP)
//   //      {
//   //         dx = pData[i].iBitmap;
//   //         dxNext = dx;
//   //      }
//   //      else if (!str.is_empty())
//   //      {
//   //         dx = m_sizeButton.cx;
//   //         string str;
//   //         str = ::str::international::utf8_to_unicode(str);
//   //         //         str = (const unichar *) pData[i].iString;
//   //         ::size_i32 size;
//   //         ::GetTextExtentPoint32U(
//   //         (HDC)pgraphics->get_os_data(),
//   //         str,
//   //         (index) str.get_length(),
//   //         &size);
//   //         dx += size.cx;
//   //         dxNext = dx - CX_OVERLAP;
//   //      }
//   //      else
//   //      {
//   //         dx = m_sizeButton.cx;
//   //         dxNext = dx - CX_OVERLAP;
//   //      }
//
//   //      if (x + dx > nWidth)
//   //      {
//   //         bool bFound = false;
//   //         for (index j = i; j >= 0  &&  !(pData[j].fsState & TBSTATE_WRAP); j--)
//   //         {
//   //            // find last separator that isn't hidden
//   //            // a separator that has a command ID is not
//   //            // a separator, but a custom control.
//   //            if ((pData[j].fsStyle & TBSTYLE_SEP) &&
//   //                  (pData[j].idCommand == 0) &&
//   //                  !(pData[j].fsState & e_toolbar_button_hidden))
//   //            {
//   //               bFound = true; i = j; x = 0;
//   //               pData[j].fsState |= TBSTATE_WRAP;
//   //               nResult++;
//   //               break;
//   //            }
//   //         }
//   //         if (!bFound)
//   //         {
//   //            for (index j = i - 1; j >= 0 && !(pData[j].fsState & TBSTATE_WRAP); j--)
//   //            {
//   //               // Never wrap anything that is hidden,
//   //               // or any custom controls
//   //               if ((pData[j].fsState & e_toolbar_button_hidden) ||
//   //                     ((pData[j].fsStyle & TBSTYLE_SEP) &&
//   //                      (pData[j].idCommand != 0)))
//   //                  continue;
//
//   //               bFound = true; i = j; x = 0;
//   //               pData[j].fsState |= TBSTATE_WRAP;
//   //               nResult++;
//   //               break;
//   //            }
//   //            if (!bFound)
//   //               x += dxNext;
//   //         }
//   //      }
//   //      else
//   //         x += dxNext;
//   //   }
//
//   //   return nResult + 1;
//      return -1;
//   }
//
//   void  toolbar::SizeToolBar(TBBUTTON* pData, index nCount, index nLength, bool bVert)
//   {
//   //   ASSERT(pData != nullptr && nCount > 0);
//
//   //   if (!bVert)
//   //   {
//   //      index nMin, nMax, nTarget, nCurrent, nMid;
//
//   //      // Wrap ToolBar as specified
//   //      nMax = nLength;
//   //      nTarget = WrapToolBar(pData, nCount, nMax);
//
//   //      // Wrap ToolBar vertically
//   //      nMin = 0;
//   //      nCurrent = WrapToolBar(pData, nCount, nMin);
//
//   //      if (nCurrent != nTarget)
//   //      {
//   //         while (nMin < nMax)
//   //         {
//   //            nMid = (nMin + nMax) / 2;
//   //            nCurrent = WrapToolBar(pData, nCount, nMid);
//
//   //            if (nCurrent == nTarget)
//   //               nMax = nMid;
//   //            else
//   //            {
//   //               if (nMin == nMid)
//   //               {
//   //                  WrapToolBar(pData, nCount, nMax);
//   //                  break;
//   //               }
//   //               nMin = nMid;
//   //            }
//   //         }
//   //      }
//   //      const ::size_i32 & size = CalcSize(pData, nCount);
//   //      WrapToolBar(pData, nCount, size.cx);
//   //   }
//   //   else
//   //   {
//
//   //      ::size_i32 sizeMax;
//   //
//   //      ::size_i32 sizeMin;
//   //
//   //      ::size_i32 sizeMid;
//
//   //      // Wrap ToolBar vertically
//   //      WrapToolBar(pData, nCount, 0);
//   //      sizeMin = CalcSize(pData, nCount);
//
//   //      // Wrap ToolBar horizontally
//   //      WrapToolBar(pData, nCount, 32767);
//   //      sizeMax = CalcSize(pData, nCount);
//
//   //      while (sizeMin.cx < sizeMax.cx)
//   //      {
//   //         sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
//   //         WrapToolBar(pData, nCount, sizeMid.cx);
//   //         sizeMid = CalcSize(pData, nCount);
//
//   //         if (nLength < sizeMid.cy)
//   //         {
//   //            if (sizeMin == sizeMid)
//   //            {
//   //               WrapToolBar(pData, nCount, sizeMax.cx);
//   //               return;
//   //            }
//   //            sizeMin = sizeMid;
//   //         }
//   //         else if (nLength > sizeMid.cy)
//   //            sizeMax = sizeMid;
//   //         else
//   //            return;
//   //      }
//   //   }
//   }
//#endif
   struct ___CONTROLPOS
   {
      index nIndex, nID;
      ::rectangle_i32 rectangleOldPos;
   };


   size_i32 toolbar::CalcLayout(::draw2d::graphics_pointer & pgraphics, u32 dwMode, index nLength)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT_VALID(this);
//      ASSERT(is_window());
//      if (dwMode & LM_HORZDOCK)
//         ASSERT(dwMode & LM_HORZ);
//
//      index nCount;
//
//      TBBUTTON * pData = nullptr;
//
//      ::size_i32 sizeResult(0,0);
//
//      //BLOCK: Load Buttons
//      {
//         nCount = (index) default_window_procedure(TB_BUTTONCOUNT, 0, 0);
//         if (nCount != 0)
//         {
//            index i;
//            pData = new TBBUTTON[nCount];
//            for (i = 0; i < nCount; i++)
//               _GetButton(i, &pData[i]);
//         }
//      }
//
//      if (nCount > 0)
//      {
//         if (!(m_dwStyle & CBRS_SIZE_FIXED))
//         {
//            bool bDynamic = (m_dwStyle & CBRS_SIZE_DYNAMIC) != 0;
//
//            if (bDynamic && (dwMode & LM_MRUWIDTH))
//            {
//
//               SizeToolBar(pData, nCount, m_nMRUWidth);
//
//            }
//            else if (bDynamic && (dwMode & LM_HORZDOCK))
//            {
//
//               SizeToolBar(pData, nCount, 32767);
//
//            }
//            else if (bDynamic && (dwMode & LM_VERTDOCK))
//            {
//
//               SizeToolBar(pData, nCount, 0);
//
//            }
//            else if (bDynamic && (nLength != -1))
//            {
//
//               ::rectangle_i32 rectangle;
//
//               CalcInsideRect(rectangle, (dwMode & LM_HORZ) != 0);
//
//               bool bVert = (dwMode & LM_LENGTHY) != 0;
//
//               index nLen = nLength + (bVert ? rectangle.height() : rectangle.width());
//
//               SizeToolBar(pData, nCount, nLen, bVert);
//
//            }
//            else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
//            {
//
//               SizeToolBar(pData, nCount, m_nMRUWidth);
//
//            }
//            else
//            {
//
//               SizeToolBar(pData, nCount, (dwMode & LM_HORZ) ? 32767 : 0);
//
//            }
//
//         }
//
//         sizeResult = CalcSize(pData, nCount);
//
//         if (dwMode & LM_COMMIT)
//         {
//
//            ___CONTROLPOS* pControl = nullptr;
//
//            index nControlCount = 0;
//
//            bool bIsDelayed = m_bDelayedButtonLayout;
//
//            m_bDelayedButtonLayout = false;
//
//            index i;
//
//            for (i = 0; i < nCount; i++)
//            {
//
//               if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
//               {
//
//                  nControlCount++;
//
//               }
//
//            }
//
//            if (nControlCount > 0)
//            {
//
//               ap(___CONTROLPOS) pControl(new_array, nControlCount);
//
//               nControlCount = 0;
//
//               for(index i = 0; i < nCount; i++)
//               {
//
//                  if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
//                  {
//
//                     pControl[nControlCount].nIndex = i;
//
//                     pControl[nControlCount].nID = pData[i].idCommand;
//
//                     ::rectangle_i32 rectangle;
//
//                     GetItemRect(i, &rectangle);
//
//                     client_to_screen(&rectangle);
//
//                     pControl[nControlCount].rectangleOldPos = rectangle;
//
//                     nControlCount++;
//
//                  }
//
//               }
//
//            }
//
//            string str;
//
//            if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
//            {
//
//               m_nMRUWidth = sizeResult.cx;
//
//            }
//
//            for (i = 0; i < nCount; i++)
//            {
//
//               _SetButton(i, &pData[i]);
//
//            }
//
//            for (i = 0; i < nCount; i++)
//            {
//
//               TBBUTTONINFOW buttona;
//
//               __memset(&buttona, 0, sizeof(buttona));
//
//               buttona.cbSize = sizeof(buttona);
//
//               buttona.dwMask = TBIF_COMMAND | TBIF_STYLE | TBIF_SIZE;
//
//               ::u32 uID = GetItemID(i);
//
//               GetToolBarCtrl().GetButtonInfo(uId, &buttona);
//
//               FORMATTED_TRACE("BUTTON.idCommand = %d\n", buttona.idCommand);
//
//               FORMATTED_TRACE("BUTTON.fsStyle = %d\n", buttona.fsStyle);
//
//               FORMATTED_TRACE("BUTTON.cx = %d\n", buttona.cx );
//
//            }
//
//            if (nControlCount > 0)
//            {
//
//               for (index i = 0; i < nControlCount; i++)
//               {
//
//                  __pointer(::user::interaction) pwindow = get_child_by_id(pControl[i].nID);
//
//                  if (pwindow != nullptr)
//                  {
//
//                     auto rectangle = pwindow->get_window_rect();
//
//                     auto size = rectangle.origin() - pControl[i].rectangleOldPos.top_left();
//
//                     GetItemRect(pControl[i].nIndex, &rectangle);
//
//                     auto point = rectangle.origin() + size;
//
//                     pwindow->set_window_position(zorder_none, point.x, point.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
//
//                  }
//
//               }
//
//               delete[] pControl;
//
//            }
//            m_bDelayedButtonLayout = bIsDelayed;
//         }
//         delete[] pData;
//      }
//
//      //BLOCK: Adjust Margins
//      {
//
//         ::rectangle_i32 rectangle;
//
//         CalcInsideRect(rectangle, (dwMode & LM_HORZ) != 0);
//         sizeResult.cy -= rectangle.height();
//         sizeResult.cx -= rectangle.width();
//
//         const ::size_i32 & size = ::user::control_bar::CalcFixedLayout((dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZ) != 0);
//         sizeResult.cx = maximum(sizeResult.cx, size.cx);
//         sizeResult.cy = maximum(sizeResult.cy, size.cy);
//      }
//      return sizeResult;
//#else
//      throw ::exception(todo);
//#endif

return { 0,0 };
   }


   size_i32 toolbar::CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz)
   {

      u32 dwMode = bStretch ? LM_STRETCH : 0;

      dwMode |= bHorz ? LM_HORZ : 0;

      return CalcLayout(pgraphics, dwMode);

   }


   size_i32 toolbar::CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, index nLength, u32 dwMode)
   {

      if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
            ((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
      {

         return CalcFixedLayout(pgraphics, (dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZDOCK) != 0);

      }

      return CalcLayout(pgraphics, dwMode, nLength);

   }


   void toolbar::GetButtonInfo(index nIndex, ::u32& nID, ::u32& nStyle, index& iImage)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT_VALID(this);
//      ASSERT(is_window());
//
//      TBBUTTON button;
//      _GetButton(nIndex, &button);
//      nID = button.idCommand;
//      nStyle = MAKELONG(button.fsStyle, button.fsState);
//      iImage = button.iBitmap;
//#else
//      throw ::exception(todo);
//#endif
   }

   void toolbar::SetButtonInfo(index nIndex, ::u32 nID, ::u32 nStyle, index iImage)
   {
      ASSERT_VALID(this);
//#ifdef WINDOWS_DESKTOP
//      TBBUTTON button;
//      _GetButton(nIndex, &button);
//      TBBUTTON save;
//      ::memcpy_dup(&save, &button, sizeof(save));
//      button.idCommand = nID;
//      button.iBitmap = iImage;
//      button.fsStyle = (byte)LOWORD(nStyle);
//      button.fsState = (byte)HIWORD(nStyle);
//      if (__memcmp(&save, &button, sizeof(save)) != 0)
//      {
//         _SetButton(nIndex, &button);
//         m_bDelayedButtonLayout = true;
//      }
//#else
//      throw ::exception(todo);
//#endif

   }


   bool toolbar::SetButtonText(index nIndex, const ::string & pszText)

   {
      
      throw todo;
//      // attempt to lookup string index in map
//      iptr nString = -1;
//      void * p;
//      string wstrText(pszText);
//
//      if (m_pStringMap != nullptr && m_pStringMap->lookup(wstrText, p))
//         nString = (iptr)p;
//
//      // add new string if not already in map
//      if (nString == -1)
//      {
//         // initialize map if necessary
//         if (m_pStringMap == nullptr)
//            m_pStringMap = new string_to_ptr;
//
//         string str;
//         str = pszText;
//
//         // add new string to toolbar list
//         string strTemp(str);
//         throw ::interface_only();
//         // xxx nString = (index)default_window_procedure(TB_ADDSTRINGW, 0, (LPARAM)(const ::string &)(const unichar *)strTemp);
//         if (nString == -1)
//            return false;
//
//         // cache string away in string map
//         m_pStringMap->set_at(wstrText, (void *)nString);
//
//         ASSERT(m_pStringMap->lookup(wstrText, p));
//
//      }


      // machine the toolbar button description

      //   TBBUTTONINFOW button;
      //   __memset(&button, 0, sizeof(button));
      //   button.cbSize = sizeof(button);
      //   ::u32 uID = GetItemID(nIndex);
      //   button.pszText = (unichar *) (const unichar *) wstrText;
      //   button.cchText = wstrText.get_length();
      //   button.dwMask |= TBIF_TEXT;
      //   GetToolBarCtrl().SetButtonInfo(uId, &button);

      //   string str;
      //   GetButtonText(nIndex, str);
//#ifdef WINDOWS_DESKTOP
//      TBBUTTON button;
//      _GetButton(nIndex, &button);
//      button.iString = nString;
//      _SetButton(nIndex, &button);
//      string str;
//      GetButtonText(nIndex, str);
//#else
//      throw ::exception(todo);
//#endif

      return true;
   }

   string toolbar::GetButtonText(index nIndex) const
   {
      string strResult;
      GetButtonText(nIndex, strResult);
      return strResult;
   }

   void toolbar::GetButtonText(index nIndex, string & rWString) const
   {
//#ifdef WINDOWS_DESKTOP
//      if (m_pStringMap != nullptr)
//      {
//
//         // get button information (need button.iString)
//         TBBUTTON button;
//
//         _GetButton(nIndex, &button);
//
//         // look in map for matching iString
//         POSITION pos = m_pStringMap->get_start_position();
//
//         string str;
//
//         void * p;
//
//         while (pos)
//         {
//
//            m_pStringMap->get_next_assoc(pos, str, p);
//
//            if ((INT_PTR)p == button.iString)
//            {
//
//               rWString = str;
//
//               return;
//
//            }
//
//         }
//
//      }
//      rWString.Empty();
//#else
//      throw ::exception(todo);
//#endif
   }


   /*
   bool toolbar::OnEraseBkgnd(::draw2d::graphics *)
   {
      return (bool)default_window_procedure();
   }
   */


   void toolbar::_001OnNcHitTest(::message::message * pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      //pusermessage->m_lresult = HTCLIENT;

      pusermessage->m_bRet = true;

   }


   void toolbar::on_message_non_client_calculate_size(::message::message * pmessage)
   {

#ifdef WINDOWS_DESKTOP

      __pointer(::message::nc_calc_size) pnccalcsize(pmessage);

      // calculate border space (will add to top/bottom, subtract from right/bottom)

      ::rectangle_i32 rectangle;

      bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      ::user::control_bar::CalcInsideRect(pgraphics, rectangle, bHorz);

      NCCALCSIZE_PARAMS * pparams = (NCCALCSIZE_PARAMS *)pnccalcsize->m_pNCCALCSIZE_PARAMS;
      // adjust non-client area for border space
      pparams->rgrc[0].left += rectangle.left;
      pparams->rgrc[0].top += rectangle.top;
      // previous versions of COMCTL32.DLL had a built-in 2 pixel border
      pparams->rgrc[0].right += rectangle.right;
      pparams->rgrc[0].bottom += rectangle.bottom;
#else
      throw ::exception(todo);
#endif
   }

   void toolbar::OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle)
   {
      // a dynamically resizeable toolbar can not have the CBRS_FLOAT_MULTI
      ASSERT(!((dwNewStyle & CBRS_SIZE_DYNAMIC) &&
               (m_dwDockStyle & CBRS_FLOAT_MULTI)));

      // a toolbar can not be both dynamic and fixed in size_i32
      ASSERT (!((dwNewStyle & CBRS_SIZE_FIXED) &&
                (dwNewStyle & CBRS_SIZE_DYNAMIC)));

      // CBRS_SIZE_DYNAMIC can not be disabled once it has been enabled
      ASSERT (((dwOldStyle & CBRS_SIZE_DYNAMIC) == 0) ||
              ((dwNewStyle & CBRS_SIZE_DYNAMIC) != 0));

      if (((dwOldStyle & CBRS_BORDER_ANY) != (dwNewStyle & CBRS_BORDER_ANY)))
      {
         // recalc non-client area when border styles machine
         //set_window_position(zorder_none, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
      }
      m_bDelayedButtonLayout = true;
   }

   /*
   void toolbar::OnNcPaint()
   {
      return;
      EraseNonClient();
   }
   */

   void toolbar::_001OnWindowPosChanging(::message::message * pmessage)
   {
#ifdef WINDOWS_DESKTOP
      __pointer(::message::window_pos) pwindowpos(pmessage);
      // not necessary to invalidate the borders
      u32 uStyle = m_dwStyle;
      m_dwStyle &= ~(CBRS_BORDER_ANY);
      //::user::control_bar::OnWindowPosChanging(pwindowpos->m_pwindowpos);
      pmessage->previous();
      m_dwStyle = uStyle;

      // If we can resize while floating
      if (uStyle & CBRS_SIZE_DYNAMIC)
      {
         // And we are resizing
         WINDOWPOS * pWINDOWPOS = (WINDOWPOS *)pwindowpos->m_pWINDOWPOS;
         if (pWINDOWPOS->flags & SWP_NOSIZE)
         {

            return;

         }

         // Then redraw the buttons
         Invalidate();
      }
#else
      throw ::exception(todo);
#endif
   }

   /*
   void toolbar::OnPaint()
   {
      if (m_bDelayedButtonLayout)
         on_layout(pgraphics);

      default_window_procedure();
   }
   */


   void toolbar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

      //if (m_bDelayedButtonLayout)
      //{

      //   on_layout(pgraphics);

      //}

      //default_window_procedure();

   }


   void toolbar::on_message_create(::message::message * pmessage)
   {

      set_timer(e_timer_hover, 333_ms);

   }


   void toolbar::_001OnSetButtonSize(::message::message * pmessage)
   {

      //__pointer(::user::message) pusermessage(pmessage);

      //pusermessage->m_lresult = OnSetSizeHelper(m_sizeButton, pusermessage.m_lparam);

   }


   void toolbar::_001OnSetBitmapSize(::message::message * pmessage)
   {

      //__pointer(::user::message) pusermessage(pmessage);

      //pusermessage->m_lresult = OnSetSizeHelper(m_sizeImage, pusermessage.m_lparam);

   }


//   LRESULT toolbar::OnSetSizeHelper(::size_i32& size, LPARAM lParam)
//   {
//      //WINBUG: The IE4 version of COMCTL32.DLL supports a zero border, but
//      //  only if TBSTYLE_TRANSPARENT is on during the the TB_SETBITMAPSIZE
//      //  and/or TB_SETBUTTONSIZE messages.  In order to enable this feature
//      //  all the time (so we get consistent border behavior, dependent only
//      //  on the version of COMCTL32.DLL) we turn on TBSTYLE_TRANSPARENT
//      //  whenever these messages go through.  It would be nice that in a
//      //  future version, the system toolbar would just allow you to set
//      //  the top and left borders to anything you please.
//      LRESULT lResult = 0;
//
////#ifdef WINDOWS_DESKTOP
////      bool bModify = false;
////      u32 uStyle = GetStyle();
////      bModify = ModifyStyle(0, TBSTYLE_TRANSPARENT|TBSTYLE_FLAT);
////
////      lResult = default_window_procedure();
////      if (lResult)
////         size = (u32) lParam;
////
////      if (bModify)
////         set_window_long(GWL_STYLE, uStyle);
////#else
////      throw ::exception(todo);
////#endif
////      return lResult;
//
//      return 0;
//   }
////
////
   void toolbar::_001OnPreserveZeroBorderHelper(::message::message * pmessage)
   {
//
//      LRESULT lResult = 0;
//
//      __pointer(::user::message) pusermessage(pmessage);
//
//#ifdef LRESULT
//
//      bool bModify = false;
//      u32 uStyle = 0;
//      uStyle = GetStyle();
//      bModify = ModifyStyle(0, TBSTYLE_TRANSPARENT|TBSTYLE_FLAT);
//
//      lResult = default_window_procedure();
//
//      if (bModify)
//         SetWindowLong(GWL_STYLE, uStyle);
//#else
//      //throw ::exception(todo);
//#endif

//      pusermessage->set_lresult(lResult);

   //   return  0;
   }


   void toolbar::_001OnSysColorChange(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      // re-color bitmap for toolbar
//      if (m_hInstImageWell != nullptr && m_hbmImageWell != nullptr)
      {
         // trans      HBITMAP hbmNew;
         /*      hbmNew = ::aura::LoadSysColorBitmap(m_hInstImageWell, m_hRsrcImageWell);
               if (hbmNew != nullptr)
                  AddReplaceBitmap(hbmNew);*/
      }
   }

   /*
   void toolbar::OnUpdateCmdUI(__pointer(::user::frame_window) pTarget, bool bDisableIfNoHndler)
   {
      tool_command state;
      state.m_pOther = this;

      state.m_iCount = (::u32)default_window_procedure(TB_BUTTONCOUNT, 0, 0);
      for (state.m_iIndex = 0; state.m_iIndex < state.m_iCount; state.m_iIndex++)
      {
         // get buttons state
         TBBUTTON button;
         _GetButton(state.m_iIndex, &button);
         state.m_atom = button.idCommand;

         // ignore separators
         if (!(button.fsStyle & TBSTYLE_SEP))
         {
            // allow reflections
            if (::user::interaction::on_command(0,
               MAKELONG((index)CN_UPDATE_::message::command, e_message_command+WM_REFLECT_BASE),
               &state, nullptr))
               continue;

            // allow the toolbar itself to have update handlers
            if (::user::interaction::on_command(state.m_nID, CN_UPDATE_::message::command, &state, nullptr))
               continue;

            // allow the owner to process the update
            state.DoUpdate(pTarget, bDisableIfNoHndler);
         }
      }

      // update the dialog controls added to the toolbar
      UpdateDialogControls(pTarget, bDisableIfNoHndler);
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // toolbar diagnostics


   void toolbar::assert_ok() const
   {
      // Note: ::user::control_bar::assert_ok is not called because it checks for
      //  m_nCount and m_pData to be in synchronization_object, which they are not in toolbar.

      /*      ASSERT(m_hbmImageWell == nullptr ||
               (afxData.bWin95 || ::GetObjectType(m_hbmImageWell) == OBJ_BITMAP));

            if (m_hInstImageWell != nullptr && m_hbmImageWell != nullptr)
               ASSERT(m_hRsrcImageWell != nullptr);*/
   }

   void toolbar::dump(dump_context & dumpcontext) const
   {
      ::user::control_bar::dump(dumpcontext);

//      dumpcontext << "m_hbmImageWell = " << (::u32)m_hbmImageWell;
//      dumpcontext << "\nm_hInstImageWell = " << (::u32)m_hInstImageWell;
//      dumpcontext << "\nm_hRsrcImageWell = " << (::u32)m_hRsrcImageWell;
      dumpcontext << "\nm_sizeButton = " << m_sizeButton;
      dumpcontext << "\nm_sizeImage = " << m_sizeImage;

//      if (dumpcontext.GetDepth() > 0)
//      {
//#ifdef WINDOWS_DESKTOP
//         toolbar* pBar = (toolbar*)this;
//         LRESULT nCount = pBar->default_window_procedure(TB_BUTTONCOUNT, 0, 0);
//         for (index i = 0; i < nCount; i++)
//         {
//            TBBUTTON button;
//            _GetButton(i, &button);
//            dumpcontext << "\ntoolbar button[" << i << "] = {";
//            dumpcontext << "\n\tnID = " << button.idCommand;
//            dumpcontext << "\n\tnStyle = " << MAKELONG(button.fsStyle, button.fsState);
//            if (button.fsStyle & TBSTYLE_SEP)
//               dumpcontext << "\n\tiImage (separator width) = " << button.iBitmap;
//            else
//               dumpcontext <<"\n\tiImage (bitmap image index) = " << button.iBitmap;
//            dumpcontext << "\n}";
//         }
//#else
//         throw ::exception(todo);
//
//#endif
//      }

      dumpcontext << "\n";
   }


   // IMPLEMENT_DYNAMIC(toolbar, ::user::control_bar)

   /////////////////////////////////////////////////////////////////////////////


   size_i32 toolbar::CalcSimpleLayout(::draw2d::graphics_pointer& pgraphics)
   {

      ASSERT_VALID(this);
      ASSERT(is_window());

      ::size_i32 sizeResult(0,0);

//#ifdef WINDOWS_DESKTOP
//      index nCount;
//      TBBUTTON* pData = nullptr;
//
//      //BLOCK: Load Buttons
//      {
//         nCount =(index)  default_window_procedure(TB_BUTTONCOUNT, 0, 0);
//         if (nCount != 0)
//         {
//            index i;
//            pData = new TBBUTTON[nCount];
//            for (i = 0; i < nCount; i++)
//               _GetButton(i, &pData[i]);
//         }
//      }
//      if (nCount > 0)
//      {
//         index i;
//         for (i = 0; i < nCount; i++)
//         {
//            pData[i].fsState &= ~TBSTATE_WRAP;
//         }
//         for (i = 0; i < nCount; i++)
//         {
//            _SetButton(i, &pData[i]);
//         }
//         for (i = 0; i < nCount; i++)
//            _GetButton(i, &pData[i]);
//         for (i = 0; i < nCount; i++)
//         {
//            if(pData[i].fsState & TBSTATE_WRAP)
//               ASSERT(false);
//         }
//         ::rectangle_i32 rectangleItem;
//         ::rectangle_i32 rectangleSize(0, 0, 0, 0);
//         for (i = 0; i < nCount; i++)
//         {
//            GetItemRect(i, rectangleItem);
//            rectangleSize.unite(rectangleSize, rectangleItem);
//         }
//         sizeResult = rectangleSize.size();
//
//         delete[] pData;
//      }
//
//      if(GetStyle() & TBSTYLE_FLAT)
//      {
//         sizeResult.cy += 2;
//      }
//
//#else
//
//      throw ::exception(todo);
//
//#endif
//
//      return sizeResult;

      return { 0, 0 };

   }


   size_i32 toolbar::SimpleLayout(::draw2d::graphics_pointer& pgraphics)
   {

      const ::size_i32 & size = CalcSimpleLayout(pgraphics);

      /*set_window_position(
      e_zorder_top,
      0, 0,
      size.cx, size.cy,
      SWP_SHOWWINDOW
      | SWP_NOMOVE);*/
      return size;
   }


   toolbar_control& toolbar::GetToolBarCtrl() const
   { return *(toolbar_control*)this; }
   /*bool toolbar::LoadToolBar(::u32 nIDResource)
      { return LoadToolBar(MAKEINTRESOURCE(nIDResource)); }
   bool toolbar::LoadBitmap(::u32 nIDResource)
      { return LoadBitmap(MAKEINTRESOURCE(nIDResource)); }*/

   index toolbar::_001GetItemCount()
   {

      return (index)m_useritema.get_size();

   }


   bool toolbar::_001GetItemRect(index iItem,RECTANGLE_I32 * prectangle)
   {

      //// handle any delayed on_layout
      //if(m_bDelayedButtonLayout)
      //   on_layout(pgraphics);

      if(iItem >= 0 && iItem < m_useritema.get_size())
      {

         *prectangle = m_useritema[iItem]->m_rectangle;


         return true;

      }
      else
      {

         return false;

      }

   }


   bool toolbar::_001GetElementRect(index iItem,RECTANGLE_I32 * prectangle,enum_element eelement, ::user::enum_state estate)
   {

      return false;

   }


   ::user::toolbar_item * toolbar::_001GetItem(index iItem)
   {

      if(iItem < 0 || iItem >= m_useritema.get_size())
      {

         return nullptr;

      }

      return m_useritema[iItem].cast <toolbar_item>();

   }


   bool toolbar::_001SetItem(index iItem,::user::toolbar_item *pitem)
   {

      if(iItem < 0 || iItem >= m_useritema.get_size())
      {

         return false;

      }

      m_useritema[iItem] = pitem;

      return true;

   }


   bool toolbar::LoadXmlToolBar(const ::string & pszXml)

   {

      synchronous_lock synchronouslock(mutex());

      m_useritema.erase_all();

      auto pxmldocument = __create_new < xml::document >();

      if (!pxmldocument->load(pszXml))

      {

         return false;

      }

      auto & children = pxmldocument->root()->children();

      __pointer(::user::toolbar_item) pitem;

      //auto papp = get_app();

      for(index iItem = 0; iItem < children.get_size(); iItem++)
      {

         auto pchild = children.element_at(iItem)->get_xml_node();

         if(pchild->get_name() == "button")
         {

            pitem = __new(::user::toolbar_item);

            pitem->m_iItem = m_useritema.get_size();

            auto pattribute = pchild->find_attribute("id");

            pitem->m_atom = pattribute->string();

            pitem->m_str = pchild->get_value();

            if(pchild->attribute("image").has_char())
            {

               auto pcontext = m_pcontext->m_pauracontext;

               auto pcontextimage = pcontext->context_image();

               pitem->m_pimage = pcontextimage->load_image(pchild->attribute("image"), { .cache = false });

            }

            if(pchild->attribute("enable_if_has_command_handler").has_char())
            {

               pitem->m_bEnableIfHasCommandHandler = pchild->attribute("enable_if_has_command_handler").string().compare_ci("true") == 0;

            }

            pitem->m_estyle -= e_toolbar_item_style_separator;

            m_useritema.add(pitem);

         }
         else if(pchild->get_name() == "separator")
         {

            pitem = __new(::user::toolbar_item);

            pitem->m_iItem = m_useritema.get_size();

            pitem->m_atom = "separator";

            pitem->m_str = "";

            pitem->m_estyle |= e_toolbar_item_style_separator;

            m_useritema.add(pitem);

         }

      }

      return true;

   }


   void toolbar::set_item_state(index iIndex, const e_toolbar_item_state &estate)
   {

      m_useritema[iIndex].cast <toolbar_item>()->m_estate = estate;

   }


   toolbar_item::toolbar_item()
   {

      m_data[0]                     = this;
      m_eelement                    = e_element_item;
      m_iImage                      = -1;
      m_estate                      = e_toolbar_item_state_none;
      m_estyle                      = e_toolbar_item_style_none;
      m_bEnableIfHasCommandHandler  = true;


   }

   toolbar_item::~toolbar_item()
   {


   }


//   index toolbar::_001GetHoverItem()
//   {
//
//      return -1;
//
//   }
//
//
} // namespace user






/////////////////////////////////////////////////////////////////////////////
// simple_toolbar idle update through simple_tool_command class

user_toolbar_command::user_toolbar_command(::object * pobject)
{

   initialize(pobject);

}


void user_toolbar_command::enable(bool bEnable, const ::action_context & context)
{

   m_bEnableChanged = true;

   __pointer(::user::toolbar) pToolBar = m_puiOther;

   auto estateNew = pToolBar->get_item_state(m_iIndex) - e_toolbar_item_state_enabled;

   auto estyleNew = pToolBar->get_item_style(m_iIndex) - e_toolbar_item_style_disabled;

   if (bEnable)
   {

      estateNew |= e_toolbar_item_state_enabled;

   }
   else
   {

      estyleNew |= e_toolbar_item_style_disabled;

   }

   pToolBar->set_item_state((index)m_iIndex, estateNew);

   pToolBar->set_item_style((index)m_iIndex, estyleNew);

}


void user_toolbar_command::_001SetCheck(enum_check echeck, const ::action_context & context)
{

   // 0=>off, 1=>on, 2=>indeterminate

   ASSERT(echeck == e_check_checked || echeck == e_check_unchecked || echeck == e_check_tristate);

   __pointer(::user::toolbar) pToolBar = m_puiOther;

   ASSERT(pToolBar != nullptr);

   ASSERT(m_iIndex < m_iCount);

   auto estateNew = pToolBar->get_item_state(m_iIndex);

   estateNew -= e_toolbar_item_state_checked;

   estateNew -= e_toolbar_item_state_indeterminate;

   if (echeck == e_check_checked)
   {

      estateNew |= e_toolbar_item_state_checked;

   }
   else if (echeck == e_check_tristate)
   {

      estateNew |= e_toolbar_item_state_indeterminate;

   }

   auto estyle = pToolBar->get_item_style(m_iIndex);

   if (estyle & e_toolbar_item_style_separator)
   {

      throw ::exception(::error_failed);

   }

   pToolBar->set_item_state((index)m_iIndex, estateNew);

   pToolBar->set_item_style((index)m_iIndex, estyle | e_toolbar_item_style_checkbox);

}


//void user_toolbar_command::SetText(const ::string &, const ::action_context & context)
//{
//
//   // ignore it
//
//}


