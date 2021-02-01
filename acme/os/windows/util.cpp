#include "framework.h"
#include "acme/operating_system.h"


bool CLASS_DECL_ACME __is_combo_box_control(HWND hwnd, ::u32 nStyle)
{
   if (hwnd == nullptr)
      return false;
   // do cheap style compare first
   if ((::u32)(::GetWindowLong(hwnd, GWL_STYLE) & 0x0F) != nStyle)
      return false;

   // do expensive classname compare next
   wchar_t szCompare[_countof("combobox")+1];
   ::GetClassNameW(hwnd, szCompare, _countof(szCompare));
   return ::wcsicmp(szCompare, L"combobox") == 0;
}


bool CLASS_DECL_ACME __compare_class_name(HWND hwnd, const char * pszClassName)
{

   ASSERT(::IsWindow(hwnd));

   wchar_t szTemp[32];

   ::GetClassNameW(hwnd, szTemp, _countof(szTemp));

   return ::wcsicmp(szTemp, wstring(pszClassName)) == 0;

}


HWND CLASS_DECL_ACME __child_window_from_point(HWND hwnd, const ::point_i32 & pointParam)
{
   ASSERT(hwnd != nullptr);
   ::point_i32 point(pointParam);
   // check child windows
   ::ClientToScreen(hwnd, (POINT *) &point);
   HWND oswindow_Child = ::GetWindow(hwnd, GW_CHILD);
   for (; oswindow_Child != nullptr; oswindow_Child = ::GetWindow(oswindow_Child, GW_HWNDNEXT))
   {
      if (::GetDlgCtrlID(oswindow_Child) != (::u16)0 &&
            (::GetWindowLong(oswindow_Child, GWL_STYLE) & WS_VISIBLE))
      {
         // see if point_i32 hits the child interaction_impl
         ::rectangle_i32 rectangle;
         ::GetWindowRect(oswindow_Child, (RECT *) &rectangle);
         if (rectangle.contains(point))
            return oswindow_Child;
      }
   }

   return nullptr;    // not found
}







