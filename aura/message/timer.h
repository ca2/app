#pragma once


//#include "message.h"
#include "aura/user/user/message.h"


namespace message
{


   class CLASS_DECL_AURA timer :
      virtual public ::user::message
   {
   public:


      ::u32 m_uEvent;


      timer() {}

      using ::user::message::set;
      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;



   };



} // namespace message



