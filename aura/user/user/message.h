#pragma once


#include "apex/message/message.h"


namespace user
{


   class CLASS_DECL_AURA message :
      virtual public ::message::message
   {
   public:

      ::channel * m_pchannel;
      ::pointer<::windowing::window>  m_pwindow;
      bool                             m_bConditional;
      bool                             m_bReflect;
      bool                             m_bDestroyed;
      bool                             m_bDoSystemDefault;


      message();
      ~message() override;


      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam) override;

      inline void change(wparam wparam, ::lparam lparam) { set(m_oswindow, m_pwindow, m_atom, wparam, lparam); }

      ::windowing::window * window() { return m_pwindow; }

      ::user::interaction_impl * userinteractionimpl();

      ::user::interaction * userinteraction();


   };


} // namespace user



