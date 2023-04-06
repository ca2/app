#include "framework.h"


// interesting function
/*int_bool CLASS_DECL_lnx ::windows_definition::CustomLogFont(::u32 nIDS, LOGFONT* pLogFont)
{
   ENSURE_ARG(pLogFont != nullptr);
   ASSERT(nIDS != 0);

   char szFontInfo[256];
   if (!::windows_definition::LoadString(nIDS, szFontInfo,_countof(szFontInfo)))
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
   _template::checked::tcsncpy_s(pLogFont->lfFaceName, _countof(pLogFont->lfFaceName), szFontInfo, _TRUNcaTE);
   return true;
}*/

/*
int_bool CLASS_DECL_lnx _::windows_definition::IsComboBoxControl(oswindow hWnd, ::u32 nStyle)
{
   if (hWnd == nullptr)
      return false;
   // do cheap style compare first
   if ((::u32)(::GetWindowLong(hWnd, GWL_STYLE) & 0x0F) != nStyle)
      return false;

   // do expensive classname compare next
   char szCompare[_countof("combobox")+1];
   ::GetClassName(hWnd, szCompare, _countof(szCompare));
   return ::::windows_definition::InvariantStrICmp(szCompare, "combobox") == 0;
}

int_bool CLASS_DECL_lnx _::windows_definition::CompareClassName(oswindow hWnd, const ::string & lpszClassName)
{
   ASSERT(::IsWindow(hWnd));
   char szTemp[32];
   ::GetClassName(hWnd, szTemp, _countof(szTemp));
   return ::::windows_definition::InvariantStrICmp(szTemp, lpszClassName) == 0;
}

oswindow CLASS_DECL_lnx _::windows_definition::ChildWindowFromPoint(oswindow hWnd, POINT_I32 pt)
{
   ASSERT(hWnd != nullptr);

   // check child windows
   ::client_to_screen(hWnd, &pt);
   oswindow hWndChild = ::GetWindow(hWnd, GW_CHILD);
   for (; hWndChild != nullptr; hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT))
   {
      if (_::windows_definition::GetDlgCtrlID(hWndChild) != (::u16)0 &&
         (::GetWindowLong(hWndChild, GWL_STYLE) & WS_VISIBLE))
      {
         // see if point_i32 hits the child ::interaction_impl
         ::rectangle_i32 rectangle;
         ::window_rectangle(hWndChild, rectangle);
         if (rectangle.contains(point))
            return hWndChild;
      }
   }

   return nullptr;    // not found
}



/*
void CLASS_DECL_lnx ::windows_definition::DeleteObject(HGDIOBJ* pObject)
{
   ENSURE_ARG(pObject != nullptr);
   if (*pObject != nullptr)
   {
      ::DeleteObject(*pObject);
      *pObject = nullptr;
   }
}*/

/*
void CLASS_DECL_lnx ::windows_definition::cancelModes(oswindow hWndRcvr)
{
   // if we receive a message destined for a ::interaction_impl, cancel any combobox
   //  popups that could be in toolbars or dialog bars
   oswindow hWndcancel = ::GetFocus();
   if (hWndcancel == nullptr)
      return;     // nothing to cancel

   if (hWndcancel == hWndRcvr)
      return;     // let input go to ::interaction_impl with focus

   // focus is in part of a combo-box
   if (!_::windows_definition::IsComboBoxControl(hWndcancel, (::u32)CBS_DROPDOWNLIST))
   {
      // check as a dropdown
      hWndcancel = ::get_parent(hWndcancel);   // parent of edit is combo
      if (hWndcancel == hWndRcvr)
         return;     // let input go to part of combo

      if (!_::windows_definition::IsComboBoxControl(hWndcancel, (::u32)CBS_DROPDOWN))
         return;     // not a combo-box that is active
   }

   // combo-box is active, but if receiver is a popup, do nothing
   if (hWndRcvr != nullptr &&
     (::GetWindowLong(hWndRcvr, GWL_STYLE) & WS_CHILD) != 0 &&
     ::get_parent(hWndRcvr) == ::get_desktop_window())
      return;

   // finally, we should cancel the mode!
   ::SendMessage(hWndcancel, CB_SHOWDROPDOWN, false, 0L);
}*/

/*
void CLASS_DECL_lnx ::windows_definition::GlobalFree(HGLOBAL hGlobal)
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
*/
