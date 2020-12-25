#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif


#define SBPF_UPDATE 0x0001  // pending update of text
#define CX_PANE_BORDER 6    // 3 pixels on each side of each pane


namespace user
{

   __STATUSPANE* status_bar::_GetPanePtr(index nIndex)
   {

      return m_panea[nIndex];

   }


   status_bar::status_bar()
   {
      // setup default border/margin depending on type of system
      m_rectBorder.top = 2;
      m_rectBorder.left = 0;
      m_rectBorder.right = 0;
      m_rectBorder.bottom = 0;

      // minimum height set with SB_SETMINHEIGHT is cached
      m_nMinHeight = 0;
   }

   status_bar::~status_bar()
   {
      //   AllocElements(0, 0);    // destroys existing elements
   }

   void status_bar::install_message_routing(::channel * pchannel)
   {
      MESSAGE_LINK(e_message_nchittest, pchannel, this, &status_bar::_001OnNcHitTest);
      MESSAGE_LINK(e_message_nccalcsize, pchannel, this, &status_bar::_001OnNcCalcSize);
      MESSAGE_LINK(e_message_size, pchannel, this, &status_bar::_001OnSize);
      MESSAGE_LINK(e_message_window_position_changing, pchannel, this, &status_bar::_001OnWindowPosChanging);
#ifdef WINDOWS_DESKTOP
      MESSAGE_LINK(WM_SETTEXT, pchannel, this, &status_bar::_001OnSetText);
      MESSAGE_LINK(WM_GETTEXT, pchannel, this, &status_bar::_001OnGetText);
      MESSAGE_LINK(WM_GETTEXTLENGTH, pchannel, this, &status_bar::_001OnGetTextLength);
      MESSAGE_LINK(SB_SETMINHEIGHT, pchannel, this, &status_bar::_001OnSetMinHeight);
#endif
   }


   bool status_bar::create_window(::user::interaction * puiParent, u32 uStyle, id strId)
   {

      return create_window_ex(puiParent, 0, uStyle, strId);

   }

   bool status_bar::create_window_ex(::user::interaction * puiParent,u32 dwCtrlStyle,u32 uStyle, id strId)
   {

      ASSERT_VALID(puiParent);   // must have a parent


      // save the style (some of these style bits are aura API specific)
      m_dwStyle = (uStyle & CBRS_ALL);

      // translate aura API style bits to windows style bits
      uStyle &= ~CBRS_ALL;
      uStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;
#ifdef WINDOWS_DESKTOP
      if (puiParent->GetStyle() & WS_THICKFRAME)
         uStyle |= SBARS_SIZEGRIP;
#endif

      //return ::user::interaction::create_window(STATUSCLASSNAMEA, nullptr, uStyle, rect, puiParent, strId);
      return ::user::interaction::create_window("msctls_statusbar32",nullptr,uStyle,puiParent,strId);

   }

   bool status_bar::pre_create_window(::user::create_struct * pcreatestruct)
   {
      // in Win4, status bars do not have a border at all, since it is
      //  provided by the client area.
      if ((m_dwStyle & (CBRS_ALIGN_ANY|CBRS_BORDER_ANY)) == CBRS_BOTTOM)
         m_dwStyle &= ~(CBRS_BORDER_ANY|CBRS_BORDER_3D);

      return ::user::control_bar::pre_create_window(pcreatestruct);
   }

   bool status_bar::SetIndicators(string_array & stra)
   {
      ASSERT_VALID(this);
      ASSERT(stra.get_count() >= 1);  // must be at least one of them
      //ASSERT(pIDArray == nullptr ||

      //      __is_valid_address(pIDArray, sizeof(::u32) * nIDCount, FALSE));

      ASSERT(is_window());

      // first allocate array for panes and copy initial data
      //   if (!AllocElements(nIDCount, sizeof(__STATUSPANE)))
      //      return FALSE;
      //   ASSERT(nIDCount == m_panea.get_count());

      // copy initial data from indicator array
      bool bResult = TRUE;
      //if (pIDArray != nullptr)

      //{
//         HFONT hFont = (HFONT)send_message(WM_GETFONT);
      ::draw2d::graphics_pointer spgraphicsScreen(e_create);

      //__throw(todo());
      /*         HGDIOBJ hOldFont = nullptr;
               if (hFont != nullptr)
                  hOldFont = spgraphicsScreen->set(hFont);*/

      __STATUSPANE* pSBP = _GetPanePtr(0);
      for (i32 i = 0; i < stra.get_count(); i++)
      {
         pSBP->m_id = stra[i];
         pSBP->nFlags |= SBPF_UPDATE;
         if (pSBP->m_id.has_char())
         {
            /* xxx            if (!pSBP->strText.load_string(pSBP->strId))
                        {
                           TRACE(trace_category_appmsg, 0, "Warning: failed to load indicator string 0x%04X.\n",
                              pSBP->strId);
                           bResult = FALSE;
                           break;
                        } */
            pSBP->cxText = (i32) (spgraphicsScreen->GetTextExtent(pSBP->strText).cx);
            ASSERT(pSBP->cxText >= 0);
            if (!SetPaneText(i, pSBP->strText, FALSE))
            {
               bResult = FALSE;
               break;
            }
         }
         else
         {
            // no indicator (must access via index)
            // default to 1/4 the screen width (first pane is stretchy)
#ifdef WINDOWS_DESKTOP
            pSBP->cxText = ::GetSystemMetrics(SM_CXSCREEN)/4;
            if (i == 0)
               pSBP->nStyle |= (SBPS_STRETCH | SBPS_NOBORDERS);
#else
            __throw(todo());
#endif
         }
         ++pSBP;
      }
//         if (hOldFont != nullptr)
      //          spgraphicsScreen->set(hOldFont);
      //}
      UpdateAllPanes(TRUE, TRUE);

      return bResult;
   }

   /*
   bool status_bar::AllocElements(i32 nElements, i32 cbElement)
   {
      i32 i;

      // destruct old elements
      //__STATUSPANE* pSBP = _GetPanePtr(0);
      //for (i = 0; i < m_panea.get_count(); i++)
      //{
      //   pSBP->strText.~string();
      //   ++pSBP;
      //}

      // allocate new elements
      //if (!::user::control_bar::AllocElements(nElements, cbElement))
      //   return FALSE;

      // construct new elements
      pSBP = _GetPanePtr(0);
      for (i = 0; i < m_panea.get_count(); i++)
      {
   #pragma push_macro("new")
   #undef new
         new( &pSBP->strText ) string;
   #pragma pop_macro("new")
         ++pSBP;
      }*/
   /*   return TRUE;
   }
   */

   void status_bar::CalcInsideRect(::draw2d::graphics_pointer & pgraphics, ::rect& rect, bool bHorz)
   {

//      ASSERT_VALID(this);
//      ASSERT(is_window());
//      ASSERT(bHorz);  // vertical status bar not supported
//
//      // subtract standard ::user::control_bar borders
//      ::user::control_bar::CalcInsideRect(rect, bHorz);
//#ifdef WINDOWS_DESKTOP
//      // subtract size grip if present
//      if ((GetStyle() & SBARS_SIZEGRIP) && !GetParent()->layout().is_zoomed())
//      {
//         // get border metrics from common control
//         i32 rgBorders[3];
//         status_bar* pBar = (status_bar*)this;
//         pBar->default_window_procedure(SB_GETBORDERS, 0, (LPARAM)&rgBorders);
//
//         // size grip uses a border + size of scrollbar + cx border
//         rect.right -= rgBorders[0] + ::GetSystemMetrics(SM_CXVSCROLL) +
//                       ::GetSystemMetrics(SM_CXBORDER) * 2;
//      }
//#else
//      __throw(todo());
//#endif
   }
//
   void status_bar::UpdateAllPanes(bool bUpdateRects, bool bUpdateText)
   {
//      ASSERT_VALID(this);
//      ASSERT(is_window());
//
//#ifdef WINDOWS_DESKTOP
//
//      i32 i;
//
//      // update the status pane locations
//      if (bUpdateRects)
//      {
//
//         // get border information and client work area
//         ::rect rect;
//         get_window_rect(rect);
//         rect.offset(-rect.left, -rect.top);
//         CalcInsideRect(rect, TRUE);
//         i32 rgBorders[3];
//
//         default_window_procedure(SB_GETBORDERS, 0, (LPARAM)&rgBorders);
//
//         // determine extra space for stretchy pane
//         i32 cxExtra = rect.width() + rgBorders[2];
//         i32 nStretchyCount = 0;
//         //__STATUSPANE* pSBP = _GetPanePtr(0);
//         for (i = 0; i < m_panea.get_count(); i++)
//         {
//            __STATUSPANE* pSBP = _GetPanePtr(i);
//            if (pSBP->nStyle & SBPS_STRETCH)
//               ++nStretchyCount;
//            cxExtra -= (pSBP->cxText+CX_PANE_BORDER + rgBorders[2]);
//            //++pSBP;
//         }
//
//         // determine right edge of each pane
//         memory rgRightsMem;
//         rgRightsMem.allocate(m_panea.get_count() * sizeof(i32));
//         i32* rgRights = (i32*)rgRightsMem.get_data();
//         i32 right = rgBorders[0];
//         //      pSBP = _GetPanePtr(0);
//         for (i = 0; i < m_panea.get_count(); i++)
//         {
//            __STATUSPANE* pSBP = _GetPanePtr(i);
//            // determine size of the pane
//            ASSERT(pSBP->cxText >= 0);
//            right += pSBP->cxText+CX_PANE_BORDER;
//            if ((pSBP->nStyle & SBPS_STRETCH) && cxExtra > 0)
//            {
//               ASSERT(nStretchyCount != 0);
//               i32 cxAddExtra = cxExtra / nStretchyCount;
//               right += cxAddExtra;
//               --nStretchyCount;
//               cxExtra -= cxAddExtra;
//            }
//            rgRights[i] = right;
//
//            // next pane
//            ++pSBP;
//            right += rgBorders[2];
//         }
//
//         // set new right edges for all panes
//         default_window_procedure(SB_SETPARTS, (WPARAM) m_panea.get_count(), (LPARAM)rgRights);
//
//      }
//
//      // update text in the status panes if specified
//      if (bUpdateText)
//      {
//         for (i = 0; i < m_panea.get_count(); i++)
//         {
//            __STATUSPANE* pSBP = _GetPanePtr(i);
//            if (pSBP->nFlags & SBPF_UPDATE)
//               SetPaneText(i, pSBP->strText);
//            ++pSBP;
//         }
//      }
//#else
//      __throw(todo());
//#endif
   }

#ifdef __CORE3_SEG
#pragma code_seg(__CORE3_SEG)
#endif

   /////////////////////////////////////////////////////////////////////////////
   // status_bar attribute access

   i32 status_bar::CommandToIndex(id id)
   {
      ASSERT_VALID(this);

      if (m_panea.get_count() <= 0)
         return -1;

      for (i32 i = 0; i < m_panea.get_count(); i++)
      {
         __STATUSPANE* pSBP = _GetPanePtr(i);
         if (pSBP->m_id == id)
            return i;
      }

      return -1;
   }

   id status_bar::GetItemId(i32 nIndex)
   {
      ASSERT_VALID(this);
      return _GetPanePtr(nIndex)->m_id;
   }

   void status_bar::GetItemRect(i32 nIndex, RECT32 * prect)

   {
      ASSERT_VALID(this);
      ASSERT(is_window());

//#ifdef WINDOWS_DESKTOP
//      status_bar* pBar = (status_bar*)this;
//      if (!pBar->default_window_procedure(SB_GETRECT, nIndex, (LPARAM)prect))
//
//         ::SetRectEmpty(prect);
//
//#else
//      __throw(todo());
//#endif
   }
//
   ::u32 status_bar::GetPaneStyle(i32 nIndex)
   {
      return _GetPanePtr(nIndex)->nStyle;
   }
//
   void status_bar::SetPaneStyle(i32 nIndex, ::u32 nStyle)
   {
//      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
//      if (pSBP->nStyle != nStyle)
//      {
//         // if the pane is changing SBPS_STRETCH, then...
//         if ((pSBP->nStyle ^ nStyle) & SBPS_STRETCH)
//         {
//            // ... we need to re-on_layout the panes
//            pSBP->nStyle = nStyle;
//            UpdateAllPanes(TRUE, FALSE);
//         }
//
//         // use SetPaneText, since it updates the style and text
//         pSBP->nStyle = nStyle;
//         pSBP->nFlags |= SBPF_UPDATE;
//         SetPaneText(nIndex, pSBP->strText);
//      }
   }

   void status_bar::GetPaneInfo(i32 nIndex, id & id, ::u32& nStyle,
                                i32& cxWidth)
   {
      ASSERT_VALID(this);

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      id = pSBP->m_id;
      nStyle = pSBP->nStyle;
      cxWidth = pSBP->cxText;
   }

   void status_bar::SetPaneInfo(i32 nIndex, id id, ::u32 nStyle, i32 cxWidth)
   {
      ASSERT_VALID(this);

      bool bChanged = FALSE;
      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      pSBP->m_id = id;
      if (pSBP->nStyle != nStyle)
      {
         if ((pSBP->nStyle ^ nStyle) & SBPS_STRETCH)
            bChanged = TRUE;
         else
         {
            pSBP->nStyle = nStyle;
            pSBP->nFlags |= SBPF_UPDATE;
            SetPaneText(nIndex, pSBP->strText);
         }
         pSBP->nStyle = nStyle;
      }
      if (cxWidth != pSBP->cxText)
      {
         // change width of one pane -> invalidate the entire status bar
         pSBP->cxText = cxWidth;
         bChanged = TRUE;
      }
      if (bChanged)
         UpdateAllPanes(TRUE, FALSE);
   }

   void status_bar::GetPaneText(i32 nIndex, string & s)
   {
      ASSERT_VALID(this);

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      s = pSBP->strText;
   }

   string status_bar::GetPaneText(i32 nIndex)
   {
      ASSERT_VALID(this);

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      return pSBP->strText;
   }

   bool status_bar::SetPaneText(i32 nIndex, const char * pszNewText, bool bUpdate)

   {
      ASSERT_VALID(this);
      ASSERT(is_window());

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);

      if (!(pSBP->nFlags & SBPF_UPDATE) &&
            ((pszNewText == nullptr && pSBP->strText.is_empty()) ||

             (pszNewText != nullptr && pSBP->strText.compare(pszNewText) == 0)))

      {
         // nothing to change
         return TRUE;
      }

      try
      {
         if (pszNewText != nullptr)

            pSBP->strText = pszNewText;

         else
            pSBP->strText.Empty();
      }
      catch(::exception::exception *)
      {
         // Note: DELETE_EXCEPTION(e) not required
         return FALSE;
      }


      if (!bUpdate)
      {
         // can't update now, wait until later
         pSBP->nFlags |= SBPF_UPDATE;
         return TRUE;
      }

      pSBP->nFlags &= ~SBPF_UPDATE;
//#ifdef WINDOWS_DESKTOP
//      default_window_procedure(SB_SETTEXT, ((::u16)pSBP->nStyle)|nIndex,
//                    (pSBP->nStyle & SBPS_DISABLED) ? 0 :
//                    (LPARAM)(const char *)pSBP->strText);
//#endif
//
      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // status_bar implementation

   size status_bar::CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool, bool bHorz)
   {
      ASSERT_VALID(this);
      ASSERT(is_window());

      // determinme size of font being used by the status bar
//      TEXTMETRICW tm;
      {
         // os independence
         ::exception::throw_not_implemented();
         /*      CClientDC spgraphics(nullptr);
               HFONT hFont = (HFONT)SendMessage(WM_GETFONT);
               HGDIOBJ hOldFont = nullptr;
               if (hFont != nullptr)
                  hOldFont = spgraphics->set(hFont);
               VERIFY(spgraphics->GetTextMetrics(&tm));
               if (hOldFont != nullptr)
                  spgraphics->set(hOldFont);*/
      }

      // get border information
      ::rect rect;

      CalcInsideRect(pgraphics, rect, bHorz);
      ::size size;
      size.cx =0;
      size.cy =0;

//#ifdef WINDOWS_DESKTOP
//      i32 rgBorders[3];
//      TEXTMETRICW tm;
//      DefWindowProc(SB_GETBORDERS, 0, (LPARAM)&rgBorders);
//
//      // determine size, including borders
//      size.cx = 32767;
//      size.cy = tm.tmHeight - tm.tmInternalLeading - 1
//         + rgBorders[1] * 2 + ::GetSystemMetrics(SM_CYBORDER) * 2
//         - rect.height();
//      if (size.cy < m_nMinHeight)
//         size.cy = m_nMinHeight;
//#endif

      return size;
   }


   void status_bar::_001OnNcHitTest(::message::message * pmessage)
   {
      //SCAST_PTR(::message::nchittest, pnchittest, pmessage);
      //::u32 nResult = (::u32)default_window_procedure();
      //if (nResult == HTBOTTOMRIGHT)
      //{
      //   pnchittest->set_lresult(HTBOTTOMRIGHT);
      //}
      //else
      //{

      //   pnchittest->set_lresult(HTCLIENT);

      //}

   }


   void status_bar::_001OnNcCalcSize(::message::message * pmessage)
   {
//
//#ifdef WINDOWS_DESKTOP
//
//      SCAST_PTR(::message::nc_calc_size, pnccalcsize, pmessage);
//
//      // calculate border space (will add to top/bottom, subtract from right/bottom)
//
//      ::rect rect;
//
//      ::user::control_bar::CalcInsideRect(rect, TRUE);
//      ASSERT(rect.top >= 2);
//
//      // adjust non-client area for border space
//      pnccalcsize->m_pparams->rgrc[0].left += rect.left;
//      pnccalcsize->m_pparams->rgrc[0].top += rect.top - 2;
//      pnccalcsize->m_pparams->rgrc[0].right += rect.right;
//      pnccalcsize->m_pparams->rgrc[0].bottom += rect.bottom;
//#else
//      __throw(todo());
//#endif
}
//
//
   void status_bar::OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle)
   {
//
//      if (((dwOldStyle & CBRS_BORDER_ANY) != (dwNewStyle & CBRS_BORDER_ANY)))
//      {
//
//         // recalc non-client area when border styles change
//         set_window_pos(zorder_none, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
//
//      }

   }

   /*void status_bar::OnNcPaint()
   {
      EraseNonClient();
   }*/

   // Derived class is responsible for implementing all of these handlers
   //  for owner/self draw controls.
#ifdef WINDOWS_DESKTOP
   void status_bar::DrawItem(LPDRAWITEMSTRUCT)
   {
      ASSERT(FALSE);
   }
#endif


   bool status_bar::OnChildNotify(::message::base * pbase)
   {



#ifdef WINDOWS_DESKTOP

      if (pbase->m_id != WM_DRAWITEM)
      {

         return ::user::interaction::OnChildNotify(pbase);

      }

      DrawItem(pbase->m_lparam.cast < DRAWITEMSTRUCT >());

#endif

      return true;

   }


   /*void status_bar::OnPaint()
   {
      UpdateAllPanes(FALSE, TRUE);

      default_window_procedure();
   }
   */

   void status_bar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

      UpdateAllPanes(FALSE, TRUE);

      //default_window_procedure();

   }


   void status_bar::_001OnSize(::message::message * pmessage)
   {
      ASSERT_VALID(this);
      ASSERT(is_window());

      pmessage->previous();

      // need to adjust pane right edges (because of stretchy pane)
      UpdateAllPanes(TRUE, FALSE);
   }

   void status_bar::_001OnWindowPosChanging(::message::message * pmessage)
   {
#ifdef WINDOWS_DESKTOP
      SCAST_PTR(::message::window_pos, pwindowpos, pmessage);
      // not necessary to invalidate the borders
      u32 uStyle = m_dwStyle;
      m_dwStyle &= ~(CBRS_BORDER_ANY);
      // trans   ::user::control_bar::OnWindowPosChanging(pwindowpos->m_pwindowpos);
      pwindowpos->previous();
      m_dwStyle = uStyle;
#else
      __throw(todo());
#endif
   }

   void status_bar::_001OnSetText(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);
      ASSERT_VALID(this);
      ASSERT(is_window());

      i32 nIndex = CommandToIndex(nullptr);
      if (nIndex < 0)
      {
         pbase->m_lresult = -1;
         pbase->m_bRet = true;
         return;
      }
      pbase->m_lresult = SetPaneText(nIndex, (const char *)pbase->m_lparam.m_lparam) ? 0 : -1;
      pbase->m_bRet = true;
   }


   void status_bar::_001OnGetText(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      ASSERT_VALID(this);

      ASSERT(is_window());

      index nMaxLen = (index) pbase->m_wparam;

      if (nMaxLen == 0)
      {

         // nothing copied

         pbase->m_lresult = 0;

         pbase->m_bRet = true;

         return;

      }

      char * pszDest = (char *) pbase->m_lparam.m_lparam;

      index nLen = 0;

      i32 nIndex = CommandToIndex(nullptr); // use pane with ID zero

      if (nIndex >= 0)
      {

         __STATUSPANE* pSBP = _GetPanePtr(nIndex);

         nLen = pSBP->strText.get_length();

         if (nLen > nMaxLen)
         {

            nLen = nMaxLen - 1; // number of characters to copy (less term.)

         }

         ::memcpy_dup(pszDest, (const char *)pSBP->strText, nLen*sizeof(char));

      }

      pszDest[nLen] = '\0';

      pbase->m_lresult = (nLen + 1);      // number of bytes copied

      pbase->m_bRet = true;

   }


   void status_bar::_001OnGetTextLength(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);

      ASSERT_VALID(this);
      ASSERT(is_window());

      index nLen = 0;

      index nIndex = CommandToIndex(0); // use pane with ID zero

      if (nIndex >= 0)
      {

         __STATUSPANE * pSBP = _GetPanePtr(nIndex);

         nLen = pSBP->strText.get_length();

      }

      pbase->m_lresult = nLen;

      pbase->m_bRet = true;

   }


   void status_bar::_001OnSetMinHeight(::message::message * pmessage)
   {

      //SCAST_PTR(::message::base, pbase, pmessage);

      //LRESULT lResult = default_window_procedure();

      //m_nMinHeight = (i32)pbase->m_wparam;

      //pbase->set_lresult(lResult);

   }


   /////////////////////////////////////////////////////////////////////////////
   // status_bar idle update through status_command class

   class status_command :
      virtual public ::user::command,
      virtual public ::user::check,
      virtual public ::user::text
   {
   public:


      status_command(::layered * pobjectContext);

      virtual void enable(bool bOn);
      virtual void _001SetCheck(::enum_check echeck, const ::action_context & context) override;
      virtual void _001SetText(const string & strText, const ::action_context & context) override;

      virtual void delete_this() override;


   };


   status_command::status_command(::layered * pobjectContext) :
      ::user::command(pobjectContext)
   {

   }


   void status_command::enable(bool bOn)
   {
      m_bEnableChanged = TRUE;
      __pointer(status_bar) pStatusBar = m_puiOther;
      ASSERT(pStatusBar != nullptr);
      ASSERT_KINDOF(status_bar, pStatusBar);
      ASSERT(m_iIndex < m_iCount);

      ::u32 nNewStyle = pStatusBar->GetPaneStyle((i32) m_iIndex) & ~SBPS_DISABLED;
      if (!bOn)
         nNewStyle |= SBPS_DISABLED;
      pStatusBar->SetPaneStyle((i32) m_iIndex, nNewStyle);
   }

   void status_command::_001SetCheck(::enum_check echeck, const ::action_context & context) // "checking" will pop out the text
   {

#ifdef WINDOWS_DESKTOP

      __pointer(status_bar) pStatusBar = m_puiOther;

      ASSERT(pStatusBar != nullptr);

      ASSERT_KINDOF(status_bar, pStatusBar);

      ASSERT(m_iIndex < m_iCount);

      ::u32 nNewStyle = pStatusBar->GetPaneStyle((i32) m_iIndex) & ~SBPS_POPOUT;

      if (echeck != ::check_unchecked)
      {

         nNewStyle |= SBPS_POPOUT;

      }

      pStatusBar->SetPaneStyle((i32) m_iIndex, nNewStyle);

#else

      __throw(todo());

#endif

   }

   void status_command::_001SetText(const string & strText, const ::action_context & context)
   {

      __pointer(status_bar) pStatusBar = m_puiOther;

      ASSERT(pStatusBar != nullptr);

      ASSERT_KINDOF(status_bar, pStatusBar);

      ASSERT(m_iIndex < m_iCount);

      pStatusBar->SetPaneText((i32) m_iIndex, strText);

   }


   void status_command::delete_this()
   {

      ::user::command::delete_this();

   }

   void status_bar::on_command_probe(::user::frame_window * ptarget, bool bDisableIfNoHndler)
   {
      
      status_command state(get_context_object());

      state.m_puiOther = this;
      state.m_iCount = (::u32)m_panea.get_count();
      for (state.m_iIndex = 0; state.m_iIndex < state.m_iCount; state.m_iIndex++)
      {
         state.m_id = _GetPanePtr((i32) state.m_iIndex)->m_id;

         // allow the statusbar itself to have update handlers
         ::user::interaction::on_command_probe(&state);

         if (state.m_bRet)
         {

            continue;

         }

         // allow target (owner) to handle the remaining updates
         state.do_probe(ptarget);

      }

      // update the dialog controls added to the status bar
      update_dialog_controls(ptarget);

   }


   /////////////////////////////////////////////////////////////////////////////
   // status_bar diagnostics


   void status_bar::assert_valid() const
   {
      ::user::control_bar::assert_valid();
   }

   void status_bar::dump(dump_context & dumpcontext) const
   {
      ::user::control_bar::dump(dumpcontext);

      if (dumpcontext.GetDepth() > 0)
      {
         for (i32 i = 0; i < m_panea.get_count(); i++)
         {
            __STATUSPANE * ppane = ((status_bar *) this)->_GetPanePtr(i);
            dumpcontext << "\nstatus pane[" << i << "] = {";
            dumpcontext << "\n\tnID = " << (const char *) ppane->m_id;
            dumpcontext << "\n\tnStyle = " << ppane->nStyle;
            dumpcontext << "\n\tcxText = " << ppane->cxText;
            dumpcontext << "\n\tstrText = " << ppane->strText;
            dumpcontext << "\n\t}";
         }
      }
      dumpcontext << "\n";
   }


#ifdef __INIT_SEG
#pragma code_seg(__INIT_SEG)
#endif

   // IMPLEMENT_DYNAMIC(status_bar, ::user::control_bar)

   /////////////////////////////////////////////////////////////////////////////


   __STATUSPANE & __STATUSPANE::operator = (const __STATUSPANE & pane)
   {
      if(&pane == this)
         return *this;
      m_id = pane.m_id;        // IDC of indicator: 0 => normal text area
      cxText = pane.cxText;     // width of string area in pixels
      //   on both sides there is a 3 pixel gap and
      //   a one pixel border, making a pane 6 pixels wider
      nStyle = pane.nStyle;     // style flags (SBPS_*)
      nFlags = pane.nFlags;     // state flags (SBPF_*)
      strText = pane.strText;    // text in the pane

      return *this;
   }

   __STATUSPANE::__STATUSPANE()
   {
   }

   __STATUSPANE::__STATUSPANE(const __STATUSPANE & pane)
   {
      operator =(pane);
   }


   void status_bar::SetPaneInfo(i32 nIndex, i32 iId, ::u32 nStyle, i32 cxWidth)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(iId);
      UNREFERENCED_PARAMETER(nStyle);
      UNREFERENCED_PARAMETER(cxWidth);
      //SetPaneInfo(nIndex, iId, nStyle, cxWidth);
   }

   void status_bar::SetPaneInfo(i32 nIndex, const char * pszId, ::u32 nStyle, i32 cxWidth)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(pszId);
      UNREFERENCED_PARAMETER(nStyle);
      UNREFERENCED_PARAMETER(cxWidth);
      //SetPaneInfo(nIndex, pszId, nStyle, cxWidth);
   }

} // namespace user
