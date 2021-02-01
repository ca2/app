#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "windowing.h"
#include "top_level_enum.h"


#define ___TEMP_CLASS_NAME_SIZE 4096


CLASS_DECL_AURA int_bool os_init_windowing()
{

   return true;

}


CLASS_DECL_AURA void os_term_windowing()
{

}


/// from top to bottom
CLASS_DECL_AURA __pointer(::user::oswindow_array) get_top_level_windows(bool bDesktop, bool bVisible)
{

   /// from top to bottom
   top_level_enum toplevelenum(bDesktop, bVisible);

   return toplevelenum.m_poswindowa;

}


top_level_enum::top_level_enum(bool bDesktop, bool bVisible) :
   m_bVisible(bVisible)
{

   __construct_new(m_poswindowa);

   if (bDesktop)
   {

      ::EnumDesktopWindows(nullptr, &::top_level_enum::EnumWindowsProc, (lparam)this);

   }
   else
   {

      ::EnumWindows(&::top_level_enum::EnumWindowsProc, (lparam)this);

   }

}


top_level_enum::~top_level_enum()
{


}


BOOL CALLBACK top_level_enum::EnumWindowsProc(oswindow oswindow, lparam lParam)
{

   top_level_enum * ptoplevelenum = (top_level_enum *) lParam;

   if (ptoplevelenum->m_bVisible && !IsWindowVisible(oswindow))
   {

      return true;

   }

   ptoplevelenum->m_poswindowa->add(oswindow);

   return true;

}


int_bool point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin)
{

   auto poswindowa = get_top_level_windows();

   if (poswindowa->is_empty())
   {

      return false;

   }

   ::rectangle_i32 rectWindow;

   for(auto & oswindow : *poswindowa)
   {

      if(oswindow != oswindowExclude)
      {

         if (!IsWindowVisible(oswindow))
         {

            continue;

         }

         if (::GetWindowRect(oswindow, rectWindow))
         {

            ::rectangle_i32 rectHitTest;
            
            rectHitTest.set(rectWindow.origin(), ::size());

            rectHitTest.inflate(iMargin + 1);

            if (rectHitTest.contains(ptHitTest))
            {

               return true;

            }

            //return true;

         }

      }

   }

   return false;

}


void window_create_caret(oswindow oswindow, HBITMAP hbitmap)
{

   ASSERT(::IsWindow(oswindow));

   ::CreateCaret(oswindow, hbitmap, 0, 0);

}


void window_create_solid_caret(oswindow oswindow, i32 nWidth, i32 nHeight)
{

   ASSERT(::IsWindow(oswindow));

   ::CreateCaret(oswindow, (HBITMAP)nullptr, nWidth, nHeight);

}


void window_create_gray_caret(oswindow oswindow, i32 nWidth, i32 nHeight)
{

   ASSERT(::IsWindow(oswindow));

   ::CreateCaret(oswindow, (HBITMAP)1, nWidth, nHeight);

}


CLASS_DECL_AURA string message_box_result_to_string(int iResult);


void defer_term_ui()
{


}


int_bool get_cursor_pos(POINT_I32 * ppoint)
{

   return ::GetCursorPos(ppoint);

}


CLASS_DECL_AURA int erelative_get_window(enum_relative erelative)
{

   switch (erelative)
   {
   case e_relative_first_child:
      return GW_CHILD;
   default:
      return -1;

   };

}


CLASS_DECL_AURA oswindow get_window(oswindow oswindow, enum_relative erelative)
{

   int iGetWindow = erelative_get_window(erelative);

   if (iGetWindow < 0)
   {

      ::output_debug_string("Unknown Get Window (GW_*) for enum_relative");

      return nullptr;

   }

   return ::GetWindow(oswindow, iGetWindow);

}



