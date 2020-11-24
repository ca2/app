//
//  user_create_struct.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 19/06/18.
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   create_struct::create_struct(const create_struct & createstruct)
   {

#ifdef WINDOWS
      CREATESTRUCTW::operator = (createstruct);
      set_class_name(string(createstruct.lpszClass));
      set_window_name(string(createstruct.lpszName));
#else
      CREATESTRUCTA::operator = (createstruct);
      set_class_name(createstruct.lpszClass);
      set_window_name(createstruct.lpszName);
#endif
      m_puserinteractionOwner = nullptr;

   }


   create_struct::create_struct(u32 uiExStyle, const char * pszClassName, const char * pszWindowName, u32 uStyle, ::rect rect, void * pvCreateParams) :
   create_struct(rect)
   {

      dwExStyle = uiExStyle;
      set_class_name(pszClassName);
      set_window_name(pszWindowName);
      style = uStyle;
#ifdef _UWP
      pCreateParams = pvCreateParams;
#else
      lpCreateParams = pvCreateParams;
#endif
      m_puserinteractionOwner = nullptr;

   }


   create_struct::create_struct(const ::rect & rect)
   {

#ifdef WINDOWS_DESKTOP
      xxf_zero_pointer((CREATESTRUCTW *) this);
#else
      xxf_zero_pointer((CREATESTRUCTA *) this);
#endif

      set_rect(rect);

   }


   void create_struct::set_class_name(const char * pszClassName)
   {

      m_strClassName = pszClassName;

      lpszClass = m_strClassName;

   }


   void create_struct::set_window_name(const char * pszWindowName)
   {

      m_strWindowName = pszWindowName;

      lpszName = m_strWindowName;

   }


   void create_struct::set_rect(const ::rect & rect)
   {

      x = rect.left;
      y = rect.top;
      cx = rect.width();
      cy = rect.height();

   }

   void create_struct::add_visible(bool bAdd)
   {

      if (!bAdd)
      {

         return;

      }

      if (!(style & WS_VISIBLE))
      {

          style |= WS_VISIBLE;

      }

   }

   void create_struct::get_rect(LPRECT32 lprect)
   {

      lprect->left = x;
      lprect->top = y;
      lprect->right = x + cx;
      lprect->bottom = y + cy;

   }


} // namespace user



