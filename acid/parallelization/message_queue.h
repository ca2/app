#pragma once


#include "acid/operating_system/message.h"


using message_array = array < MESSAGE >;


//#include "acid/primitive/primitive/matter.h"
#include "acid/parallelization/manual_reset_event.h"


class CLASS_DECL_ACID message_queue :
   virtual public particle
{
public:


   message_array           m_messagea;
   manual_reset_event      m_eventNewMessage;
   itask_t                 m_itask;
   bool                    m_bQuit;


   message_queue();
   ~message_queue() override;


   void on_initialize_particle() override;


   bool peek_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, bool bRemoveMessage);
   ::e_status get_message(MESSAGE * pMsg, oswindow oswindow, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, const class time & time = ::time::infinity());
   void post_message(oswindow oswindow, const ::atom & atom, wparam wparam, lparam lparam);
   void post_message(const MESSAGE & message);

   void kick_idle() override;
   

};


//CLASS_DECL_ACID message_queue * aaa_get_message_queue(itask_t atom, bool bCreate);
//CLASS_DECL_ACID void aaa_clear_message_queue(itask_t idthread);

void _c_simple_message_loop();



