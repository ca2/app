#include "framework.h"
#include "statusbar.h"
#include "acme/constant/message.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"


#define SBPF_UPDATE 0x0001  // pending update of text
#define CX_PANE_BORDER 6    // 3 pixels on each side of each pane


namespace user
{

   __STATUSPANE* status_bar::_GetPanePtr(index nIndex)
   {

      return m_panecompositea[nIndex];

   }


   status_bar::status_bar()
   {
      // setup default border/margin depending on type of system
      m_rectangleBorder.top = 2;
      m_rectangleBorder.left = 0;
      m_rectangleBorder.right = 0;
      m_rectangleBorder.bottom = 0;

      // minimum height set with SB_SETMINHEIGHT is cached
      m_nMinHeight = 0;
   }

   status_bar::~status_bar()
   {
      //   AllocElements(0, 0);    // destroys existing elements
   }

   void status_bar::install_message_routing(::channel * pchannel)
   {
      MESSAGE_LINK(e_message_non_client_hit_test, pchannel, this, &status_bar::_001OnNcHitTest);
      MESSAGE_LINK(e_message_non_client_calc_size, pchannel, this, &status_bar::on_message_non_client_calculate_size);
      MESSAGE_LINK(e_message_size, pchannel, this, &status_bar::on_message_size);
      MESSAGE_LINK(e_message_window_position_changing, pchannel, this, &status_bar::_001OnWindowPosChanging);
//#ifdef WINDOWS_DESKTOP
//      MESSAGE_LINK(WM_SETTEXT, pchannel, this, &status_bar::_001OnSetText);
//      MESSAGE_LINK(WM_GETTEXT, pchannel, this, &status_bar::_001OnGetText);
//      MESSAGE_LINK(WM_GETTEXTLENGTH, pchannel, this, &status_bar::_001OnGetTextLength);
//      MESSAGE_LINK(SB_SETMINHEIGHT, pchannel, this, &status_bar::_001OnSetMinHeight);
//#endif
   }


   //bool status_bar::create_window(::user::interaction * puiParent, u32 uStyle, atom strId)
   //{

   //   return create_window_ex(puiParent, 0, uStyle, strId);

   //}

//   bool status_bar::create_window_ex(::user::interaction * puiParent,u32 dwCtrlStyle,u32 uStyle, atom strId)
//   {
//
//      ASSERT_VALID(puiParent);   // must have a parent
//
//
//      // save the style (some of these style bits are aura API specific)
//      m_dwStyle = (uStyle & CBRS_ALL);
//
//      // translate aura API style bits to windows style bits
//      uStyle &= ~CBRS_ALL;
//      uStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;
//#ifdef WINDOWS_DESKTOP
//      if (puiParent->GetStyle() & WS_THICKFRAME)
//         uStyle |= SBARS_SIZEGRIP;
//#endif
//
//      //return ::user::interaction::create_window(STATUSCLASSNAMEA, nullptr, uStyle, rectangle, puiParent, strId);
//      return ::user::interaction::create_window("msctls_statusbar32",nullptr,uStyle,puiParent,strId);
//
//   }

   bool status_bar::pre_create_window(::user::system * pusersystem)
   {
      // in Win4, status bars do not have a border at all, since it is
      //  provided by the client area.
      if ((m_dwStyle & (CBRS_ALIGN_ANY|CBRS_BORDER_ANY)) == CBRS_BOTTOM)
         m_dwStyle &= ~(CBRS_BORDER_ANY|CBRS_BORDER_3D);

      return ::user::control_bar::pre_create_window(pusersystem);
   }

   bool status_bar::SetIndicators(string_array & stra)
   {
      ASSERT_VALID(this);
      ASSERT(stra.get_count() >= 1);  // must be at least one of them
      //ASSERT(pIDArray == nullptr ||

      //      is_memory_segment_ok(pIDArray, sizeof(::u32) * nIDCount, false));

      ASSERT(is_window());

      // first allocate array for panes and copy initial data
      //   if (!AllocElements(nIDCount, sizeof(__STATUSPANE)))
      //      return false;
      //   ASSERT(nIDCount == m_panecompositea.get_count());

      // copy initial data from indicator array
      bool bResult = true;
      //if (pIDArray != nullptr)

      //{
//         HFONT hFont = (HFONT)send_message(WM_GETFONT);
      ::draw2d::graphics_pointer spgraphicsScreen(e_create, this);

      //throw ::exception(todo);
      /*         HGDIOBJ hOldFont = nullptr;
               if (hFont != nullptr)
                  hOldFont = spgraphicsScreen->set(hFont);*/

      __STATUSPANE* pSBP = _GetPanePtr(0);
      for (i32 i = 0; i < stra.get_count(); i++)
      {
         pSBP->m_atom = stra[i];
         pSBP->nFlags |= SBPF_UPDATE;
         if (pSBP->m_atom.has_char())
         {
            /* xxx            if (!pSBP->strText.load_string(pSBP->strId))
                        {
                           information(trace_category_appmsg, 0, "Warning: failed to load indicator string 0x%04X.\n",
                              pSBP->strId);
                           bResult = false;
                           break;
                        } */
            pSBP->cxText = (i32) (spgraphicsScreen->get_text_extent(pSBP->strText).cx());
            ASSERT(pSBP->cxText >= 0);
            if (!SetPaneText(i, pSBP->strText, false))
            {
               bResult = false;
               break;
            }
         }
         else
         {
            // no indicator (must access via index)
            // default to 1/4 the screen width (first pane is stretchy)
//#ifdef WINDOWS_DESKTOP
//            pSBP->cxText = ::GetSystemMetrics(SM_CXSCREEN)/4;
//            if (i == 0)
//               pSBP->nStyle |= (SBPS_STRETCH | SBPS_NOBORDERS);
//#else
//            throw ::exception(todo);
//#endif
         }
         ++pSBP;
      }
//         if (hOldFont != nullptr)
      //          spgraphicsScreen->set(hOldFont);
      //}
      UpdateAllPanes(true, true);

      return bResult;
   }

   /*
   bool status_bar::AllocElements(i32 nElements, i32 cbElement)
   {
      i32 i;

      // destruct old elements
      //__STATUSPANE* pSBP = _GetPanePtr(0);
      //for (i = 0; i < m_panecompositea.get_count(); i++)
      //{
      //   pSBP->strText.~string();
      //   ++pSBP;
      //}

      // allocate memory_new elements
      //if (!::user::control_bar::AllocElements(nElements, cbElement))
      //   return false;

      // construct memory_new elements
      pSBP = _GetPanePtr(0);
      for (i = 0; i < m_panecompositea.get_count(); i++)
      {
   #pragma push_macro("memory_new")
   
         memory_new( &pSBP->strText ) string;
   #pragma pop_macro("memory_new")
         ++pSBP;
      }*/
   /*   return true;
   }
   */

   void status_bar::CalcInsideRect(::draw2d::graphics_pointer & pgraphics, ::rectangle_i32& rectangle, bool bHorz)
   {

//      ASSERT_VALID(this);
//      ASSERT(is_window());
//      ASSERT(bHorz);  // vertical status bar not supported
//
//      // subtract standard ::user::control_bar borders
//      ::user::control_bar::CalcInsideRect(rectangle, bHorz);
//#ifdef WINDOWS_DESKTOP
//      // subtract size_i32 grip if present
//      if ((GetStyle() & SBARS_SIZEGRIP) && !get_parent()->layout().is_zoomed())
//      {
//         // get border metrics from common control
//         i32 rgBorders[3];
//         status_bar* pBar = (status_bar*)this;
//         pBar->default_window_procedure(SB_GETBORDERS, 0, (LPARAM)&rgBorders);
//
//         // size_i32 grip uses a border + size of scrollbar + cx border
//         rectangle.right -= rgBorders[0] + ::GetSystemMetrics(SM_CXVSCROLL) +
//                       ::GetSystemMetrics(SM_CXBORDER) * 2;
//      }
//#else
//      throw ::exception(todo);
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
//         ::rectangle_i32 rectangle;
//         window_rectangle(rectangle);
//         rectangle.offset(-rectangle.left, -rectangle.top);
//         CalcInsideRect(rectangle, true);
//         i32 rgBorders[3];
//
//         default_window_procedure(SB_GETBORDERS, 0, (LPARAM)&rgBorders);
//
//         // determine extra space for stretchy pane
//         i32 cxExtra = rectangle.width() + rgBorders[2];
//         i32 nStretchyCount = 0;
//         //__STATUSPANE* pSBP = _GetPanePtr(0);
//         for (i = 0; i < m_panecompositea.get_count(); i++)
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
//         rgRightsMem.allocate(m_panecompositea.get_count() * sizeof(i32));
//         i32* rgRights = (i32*)rgRightsMem.get_data();
//         i32 right = rgBorders[0];
//         //      pSBP = _GetPanePtr(0);
//         for (i = 0; i < m_panecompositea.get_count(); i++)
//         {
//            __STATUSPANE* pSBP = _GetPanePtr(i);
//            // determine size_i32 of the pane
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
//         // set memory_new right edges for all panes
//         default_window_procedure(SB_SETPARTS, (WPARAM) m_panecompositea.get_count(), (LPARAM)rgRights);
//
//      }
//
//      // update text in the status panes if specified
//      if (bUpdateText)
//      {
//         for (i = 0; i < m_panecompositea.get_count(); i++)
//         {
//            __STATUSPANE* pSBP = _GetPanePtr(i);
//            if (pSBP->nFlags & SBPF_UPDATE)
//               SetPaneText(i, pSBP->strText);
//            ++pSBP;
//         }
//      }
//#else
//      throw ::exception(todo);
//#endif
   }

#ifdef __CORE3_SEG
#pragma code_seg(__CORE3_SEG)
#endif

   /////////////////////////////////////////////////////////////////////////////
   // status_bar attribute access

   i32 status_bar::CommandToIndex(atom atom)
   {
      ASSERT_VALID(this);

      if (m_panecompositea.get_count() <= 0)
         return -1;

      for (i32 i = 0; i < m_panecompositea.get_count(); i++)
      {
         __STATUSPANE* pSBP = _GetPanePtr(i);
         if (pSBP->m_atom == atom)
            return i;
      }

      return -1;
   }

   atom status_bar::GetItemId(i32 nIndex)
   {
      ASSERT_VALID(this);
      return _GetPanePtr(nIndex)->m_atom;
   }

   void status_bar::GetItemRect(i32 nIndex, ::rectangle_i32 * prectangle)

   {
      ASSERT_VALID(this);
      ASSERT(is_window());

//#ifdef WINDOWS_DESKTOP
//      status_bar* pBar = (status_bar*)this;
//      if (!pBar->default_window_procedure(SB_GETRECT, nIndex, (LPARAM)prectangle))
//
//         ::SetRectEmpty(prectangle);
//
//#else
//      throw ::exception(todo);
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
//            UpdateAllPanes(true, false);
//         }
//
//         // use SetPaneText, since it updates the style and text
//         pSBP->nStyle = nStyle;
//         pSBP->nFlags |= SBPF_UPDATE;
//         SetPaneText(nIndex, pSBP->strText);
//      }
   }

   void status_bar::GetPaneInfo(i32 nIndex, atom & atom, ::u32& nStyle,
                                i32& cxWidth)
   {
      ASSERT_VALID(this);

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      atom = pSBP->m_atom;
      nStyle = pSBP->nStyle;
      cxWidth = pSBP->cxText;
   }


   void status_bar::SetPaneInfo(i32 nIndex, const ::atom & atom, ::u32 nStyle, i32 cxWidth)
   {

      ASSERT_VALID(this);

      bool bChanged = false;
      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      pSBP->m_atom = atom;
      if (pSBP->nStyle != nStyle)
      {
         if ((pSBP->nStyle ^ nStyle) & SBPS_STRETCH)
            bChanged = true;
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
         bChanged = true;
      }
      if (bChanged)
         UpdateAllPanes(true, false);
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

   bool status_bar::SetPaneText(i32 nIndex, const ::string & pszNewText, bool bUpdate)

   {
      ASSERT_VALID(this);
      ASSERT(is_window());

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);

      if (!(pSBP->nFlags & SBPF_UPDATE) &&
            ((!pszNewText && pSBP->strText.is_empty()) ||

             (pszNewText && pSBP->strText.equals(pszNewText))))

      {
         // nothing to change
         return true;
      }

      try
      {
         if (pszNewText)

            pSBP->strText = pszNewText;

         else
            pSBP->strText.empty();
      }
      catch(::exception *)
      {
         // Note: DELETE_EXCEPTION(e) not required
         return false;
      }


      if (!bUpdate)
      {
         // can't update now, wait until later
         pSBP->nFlags |= SBPF_UPDATE;
         return true;
      }

      pSBP->nFlags &= ~SBPF_UPDATE;
//#ifdef WINDOWS_DESKTOP
//      default_window_procedure(SB_SETTEXT, ((::u16)pSBP->nStyle)|nIndex,
//                    (pSBP->nStyle & SBPS_DISABLED) ? 0 :
//                    (LPARAM)(const ::string &)pSBP->strText);
//#endif
//
      return true;
   }

   /////////////////////////////////////////////////////////////////////////////
   // status_bar implementation

   size_i32 status_bar::CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool, bool bHorz)
   {
      ASSERT_VALID(this);
      ASSERT(is_window());

      // determinme size_i32 of font being used by the status bar
//      TEXTMETRICW tm;
      {
         // os independence
         throw ::interface_only();
         /*      CClientDC spgraphics(nullptr);
               HFONT hFont = (HFONT)SendMessage(WM_GETFONT);
               HGDIOBJ hOldFont = nullptr;
               if (hFont != nullptr)
                  hOldFont = spgraphics->set(hFont);
               VERIFY(spgraphics->GetTextMetrics(&tm));
               if (hOldFont != nullptr)
                  spgraphics->set(hOldFont);*/
      }

//      // get border information
//      ::rectangle_i32 rectangle;
//
//      CalcInsideRect(pgraphics, rectangle, bHorz);
//      ::size_i32 size;
//      size.cx() =0;
//      size.cy() =0;
//
////#ifdef WINDOWS_DESKTOP
////      i32 rgBorders[3];
////      TEXTMETRICW tm;
////      DefWindowProc(SB_GETBORDERS, 0, (LPARAM)&rgBorders);
////
////      // determine size, including borders
////      size.cx() = 32767;
////      size.cy() = tm.tmHeight - tm.tmInternalLeading - 1
////         + rgBorders[1] * 2 + ::GetSystemMetrics(SM_CYBORDER) * 2
////         - rectangle.height();
////      if (size.cy() < m_nMinHeight)
////         size.cy() = m_nMinHeight;
////#endif

      //return size;
   }


   void status_bar::_001OnNcHitTest(::message::message * pmessage)
   {
      //::pointer<::message::nchittest>pnchittest(pmessage);
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


   void status_bar::on_message_non_client_calculate_size(::message::message * pmessage)
   {
//
//#ifdef WINDOWS_DESKTOP
//
//      ::pointer<::message::nc_calc_size>pnccalcsize(pmessage);
//
//      // calculate border space (will add to top/bottom, subtract from right/bottom)
//
//      ::rectangle_i32 rectangle;
//
//      ::user::control_bar::CalcInsideRect(rectangle, true);
//      ASSERT(rectangle.top >= 2);
//
//      // adjust non-client area for border space
//      pnccalcsize->m_pparams->rgrc[0].left += rectangle.left;
//      pnccalcsize->m_pparams->rgrc[0].top += rectangle.top - 2;
//      pnccalcsize->m_pparams->rgrc[0].right += rectangle.right;
//      pnccalcsize->m_pparams->rgrc[0].bottom += rectangle.bottom;
//#else
//      throw ::exception(todo);
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
//         set_window_position(zorder_none, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
//
//      }

   }

   /*void status_bar::OnNcPaint()
   {
      EraseNonClient();
   }*/

   // Derived class is responsible for implementing all of these handlers
   //  for owner/self draw controls.
//#ifdef WINDOWS_DESKTOP
//   void status_bar::DrawItem(LPDRAWITEMSTRUCT)
//   {
//      ASSERT(false);
//   }
//#endif


   bool status_bar::OnChildNotify(::message::message * pmessage)
   {



//#ifdef WINDOWS_DESKTOP
//
//      if (pmessage->m_atom != WM_DRAWITEM)
//      {
//
//         return ::user::interaction::OnChildNotify(pmessage);
//
//      }
//
//      DrawItem(pmessage->m_lparam.cast < DRAWITEMSTRUCT >());
//
//#endif

      return true;

   }


   /*void status_bar::OnPaint()
   {
      UpdateAllPanes(false, true);

      default_window_procedure();
   }
   */

   void status_bar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

      UpdateAllPanes(false, true);

      //default_window_procedure();

   }


   void status_bar::on_message_size(::message::message * pmessage)
   {
      ASSERT_VALID(this);
      ASSERT(is_window());

      pmessage->previous();

      // need to adjust pane right edges (because of stretchy pane)
      UpdateAllPanes(true, false);
   }

   void status_bar::_001OnWindowPosChanging(::message::message * pmessage)
   {
#ifdef WINDOWS_DESKTOP
      ::pointer<::message::window_pos>pwindowpos(pmessage);
      // not necessary to invalidate the borders
      u32 uStyle = m_dwStyle;
      m_dwStyle &= ~(CBRS_BORDER_ANY);
      // trans   ::user::control_bar::OnWindowPosChanging(pwindowpos->m_pwindowpos);
      pwindowpos->previous();
      m_dwStyle = uStyle;
#else
      throw ::exception(todo);
#endif
   }


   void status_bar::_001OnSetText(::message::message * pmessage)
   {

      ASSERT_VALID(this);
      ASSERT(is_window());

      i32 nIndex = CommandToIndex(nullptr);
      if (nIndex < 0)
      {
         pmessage->m_lresult = -1;
         pmessage->m_bRet = true;
         return;
      }
      pmessage->m_lresult = SetPaneText(nIndex, (const char *)pmessage->m_lparam.m_lparam) ? 0 : -1;
      pmessage->m_bRet = true;
   }


   void status_bar::_001OnGetText(::message::message * pmessage)
   {

      ASSERT_VALID(this);

      ASSERT(is_window());

      index nMaxLen = (index) pmessage->m_wparam;

      if (nMaxLen == 0)
      {

         // nothing copied

         pmessage->m_lresult = 0;

         pmessage->m_bRet = true;

         return;

      }

      char * pszDest = (char *) pmessage->m_lparam.m_lparam;

      index nLen = 0;

      i32 nIndex = CommandToIndex(nullptr); // use pane with ID zero

      if (nIndex >= 0)
      {

         __STATUSPANE* pSBP = _GetPanePtr(nIndex);

         nLen = pSBP->strText.length();

         if (nLen > nMaxLen)
         {

            nLen = nMaxLen - 1; // number of characters to copy (less term.)

         }

         ::memory_copy(pszDest, (const ::string &)pSBP->strText, nLen*sizeof(char));

      }

      pszDest[nLen] = '\0';

      pmessage->m_lresult = (nLen + 1);      // number of bytes copied

      pmessage->m_bRet = true;

   }


   void status_bar::_001OnGetTextLength(::message::message * pmessage)
   {

      ASSERT_VALID(this);

      ASSERT(is_window());

      index nLen = 0;

      index nIndex = CommandToIndex(0); // use pane with ID zero

      if (nIndex >= 0)
      {

         __STATUSPANE * pSBP = _GetPanePtr(nIndex);

         nLen = pSBP->strText.length();

      }

      pmessage->m_lresult = nLen;

      pmessage->m_bRet = true;

   }


   void status_bar::_001OnSetMinHeight(::message::message * pmessage)
   {

      //::pointer<::message::message>pmessage(pmessage);

      //LRESULT lResult = default_window_procedure();

      //m_nMinHeight = (i32)pmessage->m_wparam;

      //pmessage->set_lresult(lResult);

   }


   /////////////////////////////////////////////////////////////////////////////
   // status_bar idle update through status_command class

   class status_command :
      virtual public ::message::command,
      virtual public ::user::check,
      virtual public ::user::text
   {
   public:


      status_command(::particle * pparticle);

      virtual void enable(bool bOn);
      void _001SetCheck(const ::e_check & echeck, const ::action_context & context) override;
      void _001SetText(const ::string & strText, const ::action_context & context) override;

      void delete_this() override;


   };


   status_command::status_command(::particle * pparticle)
   {

      initialize(pparticle);

   }


   void status_command::enable(bool bOn)
   {
      m_bEnableChanged = true;
      ::pointer<status_bar>pStatusBar = m_puiOther;
      ASSERT(pStatusBar != nullptr);
      ASSERT_KINDOF(status_bar, pStatusBar);
      ASSERT(m_iIndex < m_iCount);

      ::u32 nNewStyle = pStatusBar->GetPaneStyle((i32) m_iIndex) & ~SBPS_DISABLED;
      if (!bOn)
         nNewStyle |= SBPS_DISABLED;
      pStatusBar->SetPaneStyle((i32) m_iIndex, nNewStyle);
   }


   void status_command::_001SetCheck(const ::e_check & echeck, const ::action_context & context) // "checking" will pop out the text
   {

#ifdef WINDOWS_DESKTOP

      ::pointer<status_bar>pStatusBar = m_puiOther;

      ASSERT(pStatusBar != nullptr);

      ASSERT_KINDOF(status_bar, pStatusBar);

      ASSERT(m_iIndex < m_iCount);

      //::u32 nNewStyle = pStatusBar->GetPaneStyle((i32) m_iIndex) & ~SBPS_POPOUT;
      ::u32 nNewStyle = pStatusBar->GetPaneStyle((i32)m_iIndex);

      if (echeck != ::e_check_unchecked)
      {

         //nNewStyle |= SBPS_POPOUT;

      }

      pStatusBar->SetPaneStyle((i32) m_iIndex, nNewStyle);

#else

      throw ::exception(todo);

#endif

   }

   void status_command::_001SetText(const ::string & strText, const ::action_context & context)
   {

      ::pointer<status_bar>pStatusBar = m_puiOther;

      ASSERT(pStatusBar != nullptr);

      ASSERT_KINDOF(status_bar, pStatusBar);

      ASSERT(m_iIndex < m_iCount);

      pStatusBar->SetPaneText((i32) m_iIndex, strText);

   }


   void status_command::delete_this()
   {

      ::message::command::delete_this();

   }


   void status_bar::on_command_probe(::user::interaction * puserinteraction, bool bDisableIfNoHndler)
   {
      
      status_command command(this);

      command.m_puiOther = this;
      command.m_iCount = (::u32)m_panecompositea.get_count();
      for (command.m_iIndex = 0; command.m_iIndex < command.m_iCount; command.m_iIndex++)
      {
         command.m_atom = _GetPanePtr((i32) command.m_iIndex)->m_atom;

         // allow the statusbar itself to have update handlers
         ::user::interaction::on_command_probe(&command);

         if (command.m_bRet)
         {

            continue;

         }

         // allow target (owner) to handle the remaining updates
         command.do_probe(puserinteraction);

      }

      // update the dialog controls added to the status bar
      update_dialog_controls(puserinteraction);

   }


   ///////////////////////////////////////////////////////////////////////////////
   //// status_bar diagnostics


   //void status_bar::assert_ok() const
   //{
   //   ::user::control_bar::assert_ok();
   //}

   //void status_bar::dump(dump_context & dumpcontext) const
   //{
   //   ::user::control_bar::dump(dumpcontext);

   //   //if (dumpcontext.GetDepth() > 0)
   //   //{
   //   //   for (i32 i = 0; i < m_panecompositea.get_count(); i++)
   //   //   {
   //   //      __STATUSPANE * ppane = ((status_bar *) this)->_GetPanePtr(i);
   //   //      dumpcontext << "\nstatus pane[" << i << "] = {";
   //   //      dumpcontext << "\n\tnID = " << (const ::string &) ppane->m_atom;
   //   //      dumpcontext << "\n\tnStyle = " << ppane->nStyle;
   //   //      dumpcontext << "\n\tcxText = " << ppane->cxText;
   //   //      dumpcontext << "\n\tstrText = " << ppane->strText;
   //   //      dumpcontext << "\n\t}";
   //   //   }
   //   //}
   //   //dumpcontext << "\n";
   //}


#ifdef __INIT_SEG
#pragma code_seg(__INIT_SEG)
#endif

   // IMPLEMENT_DYNAMIC(status_bar, ::user::control_bar)

   /////////////////////////////////////////////////////////////////////////////


   __STATUSPANE & __STATUSPANE::operator = (const __STATUSPANE & pane)
   {
      if(&pane == this)
         return *this;
      m_atom = pane.m_atom;        // IDC of indicator: 0 => normal text area
      cxText = pane.cxText;     // width of string area in pixels
      //   on both sides there is a 3 pixel gap and
      //   a one pixel border, making a pane 6 pixels wider
      nStyle = pane.nStyle;     // style flags (SBPS_*)
      nFlags = pane.nFlags;     // command flags (SBPF_*)
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


   //void status_bar::SetPaneInfo(i32 nIndex, i32 iId, ::u32 nStyle, i32 cxWidth)
   //{
   //   __UNREFERENCED_PARAMETER(nIndex);
   //   __UNREFERENCED_PARAMETER(iId);
   //   __UNREFERENCED_PARAMETER(nStyle);
   //   __UNREFERENCED_PARAMETER(cxWidth);
   //   //SetPaneInfo(nIndex, iId, nStyle, cxWidth);
   //}

   //void status_bar::SetPaneInfo(i32 nIndex, const ::string & pszId, ::u32 nStyle, i32 cxWidth)
   //{
   //   __UNREFERENCED_PARAMETER(nIndex);
   //   __UNREFERENCED_PARAMETER(pszId);
   //   __UNREFERENCED_PARAMETER(nStyle);
   //   __UNREFERENCED_PARAMETER(cxWidth);
   //   //SetPaneInfo(nIndex, pszId, nStyle, cxWidth);
   //}

} // namespace user
