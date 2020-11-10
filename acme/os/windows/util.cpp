#include "framework.h"
#include "acme/node/windows/_windows.h"



bool CLASS_DECL_ACME __is_combo_box_control(oswindow oswindow, ::u32 nStyle)
{
   if (oswindow == nullptr)
      return FALSE;
   // do cheap style compare first
   if ((::u32)(::GetWindowLong(oswindow, GWL_STYLE) & 0x0F) != nStyle)
      return FALSE;

   // do expensive classname compare next
   wchar_t szCompare[_countof("combobox")+1];
   ::GetClassNameW(oswindow, szCompare, _countof(szCompare));
   return ::wcsicmp(szCompare, L"combobox") == 0;
}


bool CLASS_DECL_ACME __compare_class_name(oswindow oswindow, const char * pszClassName)
{

   ASSERT(::IsWindow(oswindow));

   wchar_t szTemp[32];

   ::GetClassNameW(oswindow, szTemp, _countof(szTemp));

   return ::wcsicmp(szTemp, wstring(pszClassName)) == 0;

}


oswindow CLASS_DECL_ACME __child_window_from_point(oswindow oswindow, const ::point & pointParam)
{
   ASSERT(oswindow != nullptr);
   ::point point(pointParam);
   // check child windows
   ::ClientToScreen(oswindow, &point);
   ::oswindow oswindow_Child = ::GetWindow(oswindow, GW_CHILD);
   for (; oswindow_Child != nullptr; oswindow_Child = ::GetWindow(oswindow_Child, GW_HWNDNEXT))
   {
      if (__get_dialog_control_id(oswindow_Child) != (::u16)0 &&
            (::GetWindowLong(oswindow_Child, GWL_STYLE) & WS_VISIBLE))
      {
         // see if point hits the child interaction_impl
         ::rect rect;
         ::GetWindowRect(oswindow_Child, rect);
         if (rect.contains(point))
            return oswindow_Child;
      }
   }

   return nullptr;    // not found
}







