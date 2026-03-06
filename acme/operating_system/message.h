// From acme/include/_.h by camilo on 2022-10-22 21:34 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/mathematics/c_number.h"
#include "acme/prototype/prototype/atom.h"
#include "acme/prototype/geometry2d/point.h"
#include "acme/operating_system/window.h"

struct MESSAGE
{

   
   ::operating_system::window    m_operatingsystemwindow;
   ::user::enum_message          m_eusermessage = ::user::e_message_null;
   wparam                        m_wparam;
   lparam                        m_lparam;
   ::int_point                   m_point;
   unsigned long long            m_time = 0;


   MESSAGE() {}

   MESSAGE(const MESSAGE & message)
   {
      
      operator=(message);

   }

   
   MESSAGE & operator = (const MESSAGE & message)
   {
      
      m_operatingsystemwindow = message.m_operatingsystemwindow;
      m_eusermessage = message.m_eusermessage;
      m_wparam = message.m_wparam;
      m_lparam = message.m_lparam;
      m_point = message.m_point;
      m_time = message.m_time;

      return *this;

   }

};



