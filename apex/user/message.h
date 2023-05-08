// From aura/user/user/message by camilo on 2023-05-07 23:07 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/message/message.h"


namespace user
{


   class CLASS_DECL_APEX message :
      virtual public ::message::message
   {
   public:


      ::channel *                         m_pchannel;
      ::pointer < ::windowing::window >   m_pwindow;
      bool                                m_bConditional;
      bool                                m_bReflect;
      bool                                m_bDestroyed;
      bool                                m_bDoSystemDefault;


      message();
      ~message() override;


      ::windowing::window * window() { return m_pwindow; }

   };


} // namespace user



