//
//  user_mouse.hpp
//  base
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 14/08/17.
//
//
#pragma once


#include "acme/platform/acme_message.h"
#include "acme/prototype/geometry2d/point.h"
#include "acme/user/user/key_state.h"


namespace user
{


   class CLASS_DECL_ACME mouse :
      virtual public ::acme::message
   {
   protected:
      friend class ::user::interaction;
      ::pointer<::windowing::cursor>        m_pwindowingcursor;
   public:

      ::user::key_state                      m_keystate;
      i32_point                              m_pointHost;
      i32_point                              m_pointAbsolute;
      i32_point                              m_pointDesired;
      //bool                                 m_bTranslated;
      ::pointer<::user::interaction>         m_puserinteractionHit;
      void *                                 m_pOsMouseDataOkIfOnStack = nullptr;

#ifdef _DEBUG

#ifdef _DEBUG


      ::i64 increment_reference_count() override;
      ::i64 decrement_reference_count() override;
      
#endif


#endif


      virtual ::u32 get_message()
      {
         return 0;
      }

      //bool has_screen_coordinates() const
      //{
      //   return m_pointScreen.x != I32_MINIMUM
      //      && m_pointScreen.y != I32_MINIMUM;

      //}



      
      ::user::mouse & operator = (const ::user::mouse & mouse);


   };


} // namespace user

