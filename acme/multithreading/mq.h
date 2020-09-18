#pragma once


class CLASS_DECL_ACME message_array :
   public raw_array < MESSAGE >
{


};


class CLASS_DECL_ACME mq :
   virtual public generic
{
public:


   message_array           m_messagea;
   manual_reset_event      m_eventNewMessage;
   ITHREAD                 m_ithread;
   bool                    m_bKickIdle;
   bool                    m_bQuit;


   mq();
   virtual ~mq();

   int_bool peek_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
   int_bool get_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);
   int_bool post_message(oswindow oswindow, UINT uMessage, WPARAM wParam, LPARAM lParam);
   int_bool post_message(const MESSAGE & message);


};


CLASS_DECL_ACME mq * get_mq(ITHREAD id, bool bCreate);
CLASS_DECL_ACME void set_mq(ITHREAD idthread, mq * pmq);

void _c_simple_message_loop();





