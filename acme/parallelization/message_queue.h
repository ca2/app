#pragma once


class CLASS_DECL_ACME message_array :
   public raw_array < MESSAGE >
{


};


class CLASS_DECL_ACME message_queue :
   virtual public matter
{
public:


   message_array           m_messagea;
   manual_reset_event      m_eventNewMessage;
   itask_t               m_itask;
   bool                    m_bKickIdle;
   bool                    m_bQuit;


   message_queue();
   ~message_queue() override;


   int_bool peek_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);
   ::e_status get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, const ::duration & duration = ::duration::infinite());
   int_bool post_message(oswindow oswindow, const ::id & id, wparam wparam, lparam lparam);
   int_bool post_message(const MESSAGE & message);

   void kick_idle() override;
   

};


CLASS_DECL_ACME message_queue * get_message_queue(itask_t id, bool bCreate);
CLASS_DECL_ACME void clear_message_queue(itask_t idthread);

void _c_simple_message_loop();



