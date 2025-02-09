//
// Created by camilo on 6/23/21 08:19 BRT <3ThomasBS_!!
//
#pragma once


////#include "acme/prototype/prototype/property_object.h"
//#include "acme/prototype/mathematics/c_number.h"
#include "acme/prototype/geometry2d/point.h"


namespace acme
{


   class CLASS_DECL_ACME message :
      virtual public ::property_object
   {
   public:


      message_union        m_union;

      class ::time         m_time;
      long long         m_iTimestamp;
      ::double_point       m_pointMessage;
      ::enum_message       m_emessage;
      wparam               m_wparam;
      lparam               m_lparam;
      lresult              m_lresult;
      bool                 m_bRet = false;


      virtual ::user::activation_token * user_activation_token();

   private:

      int id() { return 0; }

   };


} // namespace acme



