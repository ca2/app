// From windowing_win32/top_level_enum by camilo on 2026-09-06 02:42 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
// from win32.cpp by camilo on 2022-08-27 21:14 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "window_util.h"
#include "top_level_enum.h"


namespace windows
{


   top_level_enum::top_level_enum(bool bDesktop, bool bVisible) :
      m_bVisible(bVisible)
   {

      m_phwnda = allocateø ::windows::hwnd_array();

      if (bDesktop)
      {

         ::EnumDesktopWindows(nullptr, &top_level_enum::EnumWindowsProc, (lparam)this);

      }
      else
      {

         ::EnumWindows(&top_level_enum::EnumWindowsProc, (lparam)this);

      }

   }


   top_level_enum::~top_level_enum()
   {


   }


   BOOL CALLBACK top_level_enum::EnumWindowsProc(HWND hwnd, LPARAM lParam)
   {

      top_level_enum * ptoplevelenum = (top_level_enum *)lParam;

      if (ptoplevelenum->m_bVisible && !IsWindowVisible(hwnd))
      {

         return true;

      }

      ptoplevelenum->m_phwnda->add(hwnd);

      return true;

   }



   /// from top to bottom
   CLASS_DECL_ACME::pointer<::windows::hwnd_array>get_top_level_windows(bool bDesktop, bool bVisible)
   {

      /// from top to bottom
      ::windows::top_level_enum toplevelenum(bDesktop, bVisible);

      return toplevelenum.m_phwnda;

   }



} // namespace windows



