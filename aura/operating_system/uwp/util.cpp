#include "framework.h"
//#include "universal_windows.h"
//#include <malloc.h>


// interesting function
/*bool CLASS_DECL_AURA __custom_log_font(::u32 nIDS, LOGFONT* pLogFont)
{
   ENSURE_ARG(pLogFont != nullptr);
   ASSERT(nIDS != 0);

   char szFontInfo[256];
   if (!::ca2::LoadString(nIDS, szFontInfo,_countof(szFontInfo)))
      return false;

   char * lpszSize = _tcschr(szFontInfo, '\n');
   if (lpszSize != nullptr)
   {
      // get point_i32 size_i32 and convert to pixels
      pLogFont->lfHeight = _ttoi(lpszSize+1);
      pLogFont->lfHeight =
         MulDiv(pLogFont->lfHeight, ::windows_definition::Data.cyPixelsPerInch, 72);
      *lpszSize = '\0';
   }
   ::ca2::tcsncpy_s(pLogFont->lfFaceName, _countof(pLogFont->lfFaceName), szFontInfo, _TRUNCATE);
   return true;
}*/
#ifdef WINDOWS_DESKTOP
bool CLASS_DECL_AURA __is_combo_box_control(oswindow hWnd, ::u32 nStyle)
{
   if (hWnd == nullptr)
      return false;
   // do cheap style compare first
   if ((::u32)(::GetWindowLong(hWnd, GWL_STYLE) & 0x0F) != nStyle)
      return false;

   // do expensive classname compare next
   char szCompare[_countof("combobox")+1];
   ::GetClassName(hWnd, szCompare, _countof(szCompare));
   return ::__invariant_stricmp(szCompare, "combobox") == 0;
}

bool CLASS_DECL_AURA __compare_class_name(oswindow hWnd, const ::string & lpszClassName)
{
   ASSERT(::IsWindow(hWnd));
   char szTemp[32];
   ::GetClassName(hWnd, szTemp, _countof(szTemp));
   return ::__invariant_stricmp(szTemp, lpszClassName) == 0;
}


oswindow CLASS_DECL_AURA __child_window_from_point(oswindow hWnd, POINT_I32 point_i32)
{
   ASSERT(hWnd != nullptr);

   // check child windows
   ::client_to_screen(hWnd, &point);
   oswindow hWndChild = ::GetWindow(hWnd, GW_CHILD);
   for (; hWndChild != nullptr; hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT))
   {
      if (__get_dialog_control_id(hWndChild) != (::u16)0 &&
            (::GetWindowLong(hWndChild, GWL_STYLE) & WS_VISIBLE))
      {
         // see if point_i32 hits the child ::user::interaction_impl
         ::rectangle_i32 rectangle;
         ::get_window_rect(hWndChild, rectangle);
         if (rectangle.contains(point))
            return hWndChild;
      }
   }

   return nullptr;    // not found
}

void CLASS_DECL_AURA __set_window_text(::user::interaction * hWndCtrl, const ::string & lpszNew)
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

void CLASS_DECL_AURA __delete_object(HGDIOBJ* pObject)
{
   ENSURE_ARG(pObject != nullptr);
   if (*pObject != nullptr)
   {
      ::DeleteObject(*pObject);
      *pObject = nullptr;
   }
}
/*
void CLASS_DECL_AURA __cancel_modes(oswindow hWndRcvr)
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
   ::SendMessage(hWndCancel, CB_SHOWDROPDOWN, false, 0L);
}*/

void CLASS_DECL_AURA __global_free(HGLOBAL hGlobal)
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
// Special memory_new handler for safety pool on temp maps

