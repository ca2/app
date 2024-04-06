#pragma once


#include "dialog.h"


namespace userex
{


   class CLASS_DECL_CORE wait_message_dialog :
      virtual public dialog
   {
   public:


      class ::time            m_timeStart;
      class ::time            m_timeDelay;
      atom                    m_atomResponse;
      class ::time            m_time;


      wait_message_dialog();
      ~wait_message_dialog() override;


      //void install_message_routing(::channel * pchannel) override;

      virtual void on_show(const ::string & pszMatter) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void _001OnTimer(::timer * ptimer) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual bool on_timeout_check();
      virtual bool on_timeout();
      virtual void on_timer_soft_reload(const class time & tickTimeout);

      
      //void handle(::topic * ptopic, ::context * pcontext) override;
      

   };


} // namespace userex


