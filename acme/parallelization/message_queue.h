#pragma once


#include "acme/operating_system/message.h"


using message_array = array < MESSAGE >;


//#include "acme/prototype/prototype/matter.h"
#include "acme/parallelization/manual_reset_happening.h"


class CLASS_DECL_ACME message_queue :
   virtual public particle
{
public:

   message_array                             m_messagea;
   ::pointer < manual_reset_happening >      m_phappeningNewMessage;
   itask                                     m_itask;
   bool                                      m_bQuit;


   message_queue();
   ~message_queue() override;


   void on_initialize_particle() override;


   bool peek_message(MESSAGE * pMsg, const ::operating_system::window & operatingsystemwindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, bool bRemoveMessage);
   ::e_status get_message(MESSAGE * pMsg, const ::operating_system::window & operatingsystemwindow, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, const class time & time = ::time::infinity());
   void post_message(const ::operating_system::window & operatingsystemwindow, ::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam);
   void post_message(const MESSAGE & message);

   void kick_idle() override;
   

};


//CLASS_DECL_ACME message_queue * aaa_get_message_queue(itask atom, bool bCreate);
//CLASS_DECL_ACME void aaa_clear_message_queue(itask idthread);

void _c_simple_message_loop();



