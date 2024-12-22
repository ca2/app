// From aura/user/user/message by camilo on 2023-05-07 23:07 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/message/message.h"


namespace user
{


   class CLASS_DECL_APEX message :
      virtual public ::message::message
   {
   public:


      ::cast < ::windowing::window >      m_pwindow;
      ::cast < ::user::interaction >      m_puserinteraction;
      bool                                m_bConditional;
      bool                                m_bReflect;
      bool                                m_bDestroyed;
      bool                                m_bDoSystemDefault;


      message();
      ~message() override;


      ::windowing::window * window() { return m_pwindow; }

      ::user::interaction * user_interaction() { return m_puserinteraction; }


      message & operator = (const message & message);


   };


} // namespace user



