#pragma once


#include "apex/message/message.h"
#include "acme/prototype/prototype/action_context.h"


namespace message
{


   enum enum_flag
   {

      e_flag_none,
      e_flag_synthesized = 1 << 0,

   };


   class key;
   class mouse;
   class particle;
   class context_menu;


   class CLASS_DECL_APEX message : virtual public ::acme::message
   {
   public:


      //::message::key *              m_pkey;
      //::message::mouse *            m_pmouse;

      ::message::dispatcher_array *m_pdispatchera;
      channel *m_pchannel;
      ::acme::windowing::window * m_pacmewindowingwindow;
      enumeration<enum_flag> m_eflagMessage;
      ::collection::index m_iRouteIndex;
      ::collection::index m_iParam;
      // bool                           m_bRet;
      unsigned int m_uiMessageFlags;
      ::e_status m_estatus;
      ::action_context m_actioncontext;
      ::int_point m_pointMessage;
      bool m_bProbing = false;
      bool m_bCommand = false;


      message(::user::enum_message eusermessage = ::user::e_message_undefined);
      ~message() override;


      // void common_construct();


      inline bool is_message() const { return m_eusermessage != ::user::e_message_undefined; }
      inline bool is_thread_message() const { return is_message() && ::is_null(m_pacmewindowingwindow); }


      virtual bool route_message();


      bool all_previous(); // returns bRet

      bool previous(); // returns bRet

      virtual void set_lresult(lresult lresult);
      // virtual void set(::acme::windowing::window * pacmewindowingwindow, ::windowing::window * pwindow, ::user::enum_message eusermessage,
      // ::wparam wparam, ::lparam lparam, const ::int_point & point); virtual void set(::acme::windowing::window * pacmewindowingwindow,
      // ::windowing::window* pwindow, ::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam);


      unsigned int GetNotifyCode() const { return __hiword(m_wparam.m_number); }

      unsigned int GetId() const { return __loword(m_wparam.m_number); }

      //oswindow get_oswindow() const { return m_pacmewindowingwindow; }


      message &operator=(const message &message);

      ::user::activation_token *user_activation_token() override;


   };


} // namespace message



