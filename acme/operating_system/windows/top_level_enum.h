// From windowing_win32/top_level_enum by camilo on 2026-09-06 02:41 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


#include "acme/_operating_system.h"
#include "acme/operating_system/windows/window_util.h"


namespace windows
{


   template < typename PRED >
   class top_level_boolean_predicate
   {
   public:


      PRED     m_predicate;
      HWND     m_hwnd;


      top_level_boolean_predicate(PRED pred, HWND hwndDefault = nullptr) : m_predicate(pred), m_hwnd(hwndDefault) {}


      bool found(HWND hwnd)
      {

         return m_predicate(hwnd);

      }


#ifdef WINDOWS_DESKTOP

      static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
      {

         top_level_boolean_predicate * ppred = (top_level_boolean_predicate *)lParam;

         if (ppred->found(hwnd))
         {

            ppred->m_hwnd = hwnd;

            return false;

         }

         return true;

      }

#endif

   };





   /// from top to bottom
   class CLASS_DECL_ACME top_level_enum
   {
   public:


      ::pointer<::windows::hwnd_array>   m_phwnda;
      bool                                m_bVisible;


      top_level_enum(bool bDestkop = true, bool bVisible = true);
      ~top_level_enum();


      /// from top to bottom
      static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);


   };


   template < typename PRED >
   bool _top_level_contains_predicate(PRED pred)
   {

      top_level_boolean_predicate<PRED> boolean_predicate(pred);

      EnumWindows(&top_level_boolean_predicate<PRED>::EnumWindowsProc, (LPARAM)&boolean_predicate);

      return boolean_predicate.m_hwnd != nullptr;

   }


   template < typename PREDICATE >
   bool _top_level_contains_bool_member(PREDICATE predicate)
   {

      top_level_boolean_predicate<PREDICATE> boolean_predicate(predicate);

      EnumWindows(&top_level_boolean_predicate<PREDICATE>::EnumWindowsProc, (LPARAM)&boolean_predicate);

      return boolean_predicate.m_hwnd != nullptr;

   }



} // namespace windowing_win32



