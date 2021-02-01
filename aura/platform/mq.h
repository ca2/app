#pragma once


#include "acme/parallelization/mq.h"

//class CLASS_DECL_AURA message_array :
//   public raw_array < MESSAGE >
//{
//
//
//};

//
//class CLASS_DECL_AURA mq :
//   virtual public context_object
//{
//public:
//
//
//   message_array           m_messagea;
//   manual_reset_event      m_eventNewMessage;
//   ithread_t                 m_ithread;
//   bool                    m_bKickIdle;
//   bool                    m_bQuit;
//
//
//   mq();
//   virtual ~mq();
//
//   int_bool peek_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);
//   int_bool get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);
//   int_bool post_message(oswindow oswindow, ::u32 uMessage, wparam wParam, lparam lParam);
//   int_bool post_message(const MESSAGE & message);
//
//
//};

//
//CLASS_DECL_AURA __pointer(mq) get_mq(ithread_t id, bool bCreate);
//
//void _c_simple_message_loop();


//CLASS_DECL_AURA int_bool mq_post_thread_message(ithread_t idthread, const ::id & id, wparam wparam, lparam lparam);
CLASS_DECL_AURA int_bool mq_post_message(oswindow oswindow, const ::id & id, wparam wparam, lparam lparam);
//CLASS_DECL_AURA int_bool mq_peek_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);
//CLASS_DECL_AURA int_bool mq_get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);



