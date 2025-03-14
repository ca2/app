#pragma once


#include "apex/message/message.h"


namespace user
{


   class CLASS_DECL_AURA message :
      virtual public ::message::message
   {
   public:


      ::channel *                      m_pchannel;
      ::pointer<::windowing::window>   m_pwindow;
      bool                             m_bConditional;
      bool                             m_bReflect;
      bool                             m_bDestroyed;
      bool                             m_bDoSystemDefault;


      message();
      ~message() override;


      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam) override;

      //inline void change(wparam wparam, ::lparam lparam) { set(m_oswindow, m_pwindow, m_emessage, wparam, lparam); }

      ::windowing::window * window() { return m_pwindow; }

      ::windowing::window * userinteractionimpl();

      ::user::interaction * userinteraction();


   };


} // namespace user



