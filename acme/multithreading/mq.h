#pragma once


struct mq_message 
{

   ::id        m_id;
   MESSAGE     m_message;

   mq_message(const ::id & id) :
      m_id(id)
   {
      m_message.message = id.umessage();

   }
   mq_message(const mq_message& message)
   {

      memcpy(this, &message, sizeof(mq_message));

   }

   mq_message(const MESSAGE& message) :
      m_id((enum_message) message.message)
   {

      memcpy(&m_message, &message, sizeof(MESSAGE));

   }

   mq_message& operator = (const mq_message& message)
   {

      if(this != &message) memcpy(this, &message, sizeof(mq_message));

      return *this;

   }

   mq_message& operator = (const MESSAGE& message)
   {


      m_id = (enum_message)message.message;

      memcpy(&m_message, &message, sizeof(MESSAGE));

      return *this;

   }

};


class CLASS_DECL_ACME mq_message_array :
   public raw_array < mq_message >
{


};


class CLASS_DECL_ACME mq :
   virtual public matter
{
public:


   mq_message_array        m_messagea;
   manual_reset_event      m_eventNewMessage;
   ithread_t                 m_ithread;
   bool                    m_bKickIdle;
   bool                    m_bQuit;


   mq();
   virtual ~mq();

   int_bool peek_message(LPMESSAGE pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);
   int_bool get_message(LPMESSAGE pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);
   int_bool post_message(oswindow oswindow, const ::id & id, WPARAM wParam, LPARAM lParam);
   int_bool post_message(const mq_message & message);


};


CLASS_DECL_ACME mq * get_mq(ithread_t id, bool bCreate);
CLASS_DECL_ACME void clear_mq(ithread_t idthread);

void _c_simple_message_loop();





