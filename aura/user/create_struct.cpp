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
      m_createstruct = createstruct.m_createstruct;
      set_class_name(string(createstruct.m_createstruct.lpszClass));
      set_window_name(string(createstruct.m_createstruct.lpszName));
#else
      m_createstruct = createstruct.m_createstruct;
      set_class_name(createstruct.m_createstruct.lpszClass);
      set_window_name(createstruct.m_createstruct.lpszName);
#endif
      m_puserinteractionOwner = nullptr;
      m_routineFailure = createstruct.m_routineFailure;
      m_routineSuccess = createstruct.m_routineSuccess;
      m_createstruct.CREATE_STRUCT_P_CREATE_PARAMS = (::user::create_struct *) this;
   }


   create_struct::create_struct(u32 uiExStyle, const char * pszClassName, const char * pszWindowName, u32 uStyle, ::rect rect, ::create * pcreate) :
   create_struct(rect)
   {

      m_createstruct.dwExStyle = uiExStyle;
      set_class_name(pszClassName);
      set_window_name(pszWindowName);
      m_createstruct.style = uStyle;
      //m_createstruct.CREATE_STRUCT_P_CREATE_PARAMS = pvCreateParams;
      m_pcreate = pcreate;
      m_puserinteractionOwner = nullptr;

   }


   create_struct::create_struct(const ::rect & rect)
   {

      xxf_zero(m_createstruct);

      set_rect(rect);

      m_createstruct.CREATE_STRUCT_P_CREATE_PARAMS = (::user::create_struct *)this;

   }


   void create_struct::set_class_name(const char * pszClassName)
   {

      m_strClassName = pszClassName;

      m_createstruct.lpszClass = m_strClassName;

   }


   void create_struct::set_window_name(const char * pszWindowName)
   {

      m_strWindowName = pszWindowName;

      m_createstruct.lpszName = m_strWindowName;

   }


   void create_struct::set_rect(const ::rect & rect)
   {

      m_createstruct.x = rect.left;
      m_createstruct.y = rect.top;
      m_createstruct.cx = rect.width();
      m_createstruct.cy = rect.height();

   }

   void create_struct::add_visible(bool bAdd)
   {

      if (!bAdd)
      {

         return;

      }

      if (!(m_createstruct.style & WS_VISIBLE))
      {

         m_createstruct.style |= WS_VISIBLE;

      }

   }

   void create_struct::get_rect(LPRECT32 lprect)
   {

      lprect->left = m_createstruct.x;
      lprect->top = m_createstruct.y;
      lprect->right = m_createstruct.x + m_createstruct.cx;
      lprect->bottom = m_createstruct.y + m_createstruct.cy;

   }


} // namespace user



