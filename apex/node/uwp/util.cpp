#include "framework.h"
//#include "uwp.h"
//#include <malloc.h>


// interesting function
/*bool CLASS_DECL_APEX __custom_log_font(::u32 nIDS, LOGFONT* pLogFont)
{
   ENSURE_ARG(pLogFont != nullptr);
   ASSERT(nIDS != 0);

   char szFontInfo[256];
   if (!::ca2::LoadString(nIDS, szFontInfo,_countof(szFontInfo)))
      return FALSE;

   char * lpszSize = _tcschr(szFontInfo, '\n');
   if (lpszSize != nullptr)
   {
      // get point size and convert to pixels
      pLogFont->lfHeight = _ttoi(lpszSize+1);
      pLogFont->lfHeight =
         MulDiv(pLogFont->lfHeight, afxData.cyPixelsPerInch, 72);
      *lpszSize = '\0';
   }
   ::ca2::tcsncpy_s(pLogFont->lfFaceName, _countof(pLogFont->lfFaceName), szFontInfo, _TRUNCATE);
   return TRUE;
}*/
#ifdef WINDOWS_DESKTOP
bool CLASS_DECL_APEX __is_combo_box_control(oswindow hWnd, ::u32 nStyle)
{
   if (hWnd == nullptr)
      return FALSE;
   // do cheap style compare first
   if ((::u32)(::GetWindowLong(hWnd, GWL_STYLE) & 0x0F) != nStyle)
      return FALSE;

   // do expensive classname compare next
   char szCompare[_countof("combobox")+1];
   ::GetClassName(hWnd, szCompare, _countof(szCompare));
   return ::__invariant_stricmp(szCompare, "combobox") == 0;
}

bool CLASS_DECL_APEX __compare_class_name(oswindow hWnd, const char * lpszClassName)
{
   ASSERT(::IsWindow(hWnd));
   char szTemp[32];
   ::GetClassName(hWnd, szTemp, _countof(szTemp));
   return ::__invariant_stricmp(szTemp, lpszClassName) == 0;
}


oswindow CLASS_DECL_APEX __child_window_from_point(oswindow hWnd, POINT32 point)
{
   ASSERT(hWnd != nullptr);

   // check child windows
   ::_001ClientToScreen(hWnd, &point);
   oswindow hWndChild = ::GetWindow(hWnd, GW_CHILD);
   for (; hWndChild != nullptr; hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT))
   {
      if (__get_dialog_control_id(hWndChild) != (::u16)0 &&
            (::GetWindowLong(hWndChild, GWL_STYLE) & WS_VISIBLE))
      {
         // see if point hits the child ::user::interaction_impl
         ::rect rect;
         ::get_window_rect(hWndChild, rect);
         if (rect.contains(point))
            return hWndChild;
      }
   }

   return nullptr;    // not found
}

void CLASS_DECL_APEX __set_window_text(::user::interaction * hWndCtrl, const char * lpszNew)
{
   hWndCtrl->set_window_text(lpszNew);
   /*ENSURE(hWndCtrl);
   ENSURE(lpszNew);

   int nNewLen = lstrlen(lpszNew);
   char szOld[256]="";
   // fast check to see if text really changes (reduces flash in controls)
   if (nNewLen > _countof(szOld) ||
      ::GetWindowText(hWndCtrl, szOld, _countof(szOld)) != nNewLen ||
      lstrcmp(szOld, lpszNew) != 0)
   {
      // change it
      ::SetWindowText(hWndCtrl, lpszNew);
   }*/
}

void CLASS_DECL_APEX __delete_object(HGDIOBJ* pObject)
{
   ENSURE_ARG(pObject != nullptr);
   if (*pObject != nullptr)
   {
      ::DeleteObject(*pObject);
      *pObject = nullptr;
   }
}
/*
void CLASS_DECL_APEX __cancel_modes(oswindow hWndRcvr)
{
   // if we receive a message destined for a ::user::interaction_impl, cancel any combobox
   //  popups that could be in toolbars or dialog bars
   oswindow hWndCancel = ::GetFocus();
   if (hWndCancel == nullptr)
      return;     // nothing to cancel

   if (hWndCancel == hWndRcvr)
      return;     // let input go to ::user::interaction_impl with focus

   // focus is in part of a combo-box
   if (!__is_combo_box_control(hWndCancel, (::u32)CBS_DROPDOWNLIST))
   {
      // check as a dropdown
      hWndCancel = ::get_parent(hWndCancel);   // parent of edit is combo
      if (hWndCancel == hWndRcvr)
         return;     // let input go to part of combo

      if (!__is_combo_box_control(hWndCancel, (::u32)CBS_DROPDOWN))
         return;     // not a combo-box that is active
   }

   // combo-box is active, but if receiver is a popup, do nothing
   if (hWndRcvr != nullptr &&
     (::GetWindowLong(hWndRcvr, GWL_STYLE) & WS_CHILD) != 0 &&
     ::get_parent(hWndRcvr) == ::get_desktop_window())
      return;

   // finally, we should cancel the mode!
   ::SendMessage(hWndCancel, CB_SHOWDROPDOWN, FALSE, 0L);
}*/

void CLASS_DECL_APEX __global_free(HGLOBAL hGlobal)
{
   if (hGlobal == nullptr)
      return;

   // avoid bogus warning error messages from various debugging tools
   ASSERT(GlobalFlags(hGlobal) != GMEM_INVALID_HANDLE);
   ::u32 nCount = GlobalFlags(hGlobal) & GMEM_LOCKCOUNT;
   while (nCount--)
      GlobalUnlock(hGlobal);

   // finally, really free the handle
   GlobalFree(hGlobal);
}


#endif


/////////////////////////////////////////////////////////////////////////////
// Special new handler for safety pool on temp maps

