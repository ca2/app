#pragma once


#include "acme/multithreading/mq.h"

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
//   ITHREAD                 m_ithread;
//   bool                    m_bKickIdle;
//   bool                    m_bQuit;
//
//
//   mq();
//   virtual ~mq();
//
//   int_bool peek_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
//   int_bool get_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);
//   int_bool post_message(oswindow oswindow, UINT uMessage, WPARAM wParam, LPARAM lParam);
//   int_bool post_message(const MESSAGE & message);
//
//
//};

//
//CLASS_DECL_AURA __pointer(mq) get_mq(ITHREAD id, bool bCreate);
//
//void _c_simple_message_loop();


//CLASS_DECL_AURA int_bool mq_post_thread_message(ITHREAD idthread, const ::id & id, WPARAM wparam, LPARAM lparam);
CLASS_DECL_AURA int_bool mq_post_message(oswindow oswindow, const ::id & id, WPARAM wparam, LPARAM lparam);
//CLASS_DECL_AURA int_bool mq_peek_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
//CLASS_DECL_AURA int_bool mq_get_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);



