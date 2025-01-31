#pragma once


//#include "message.h"
#include "apex/user/user/message.h"
//#include "aura/user/user/message.h"


namespace message
{


   class CLASS_DECL_AURA timer :
      virtual public ::user::message
   {
   public:


      unsigned int m_uTimer;


      timer() {}

      //using ::user::message::set;
      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam) override;



   };



} // namespace message



