#pragma once


#include "wait_message_dialog.h"


namespace userex
{


   class CLASS_DECL_CORE message_box :
      virtual public wait_message_dialog
   {
   public:


      //pointer< ::future < ::atom > >     m_pprocess;
      
      
      message_box();

      
      virtual void on_show(const ::scoped_string & scopedstrMatter) override;
      virtual bool on_timeout() override;
      virtual void on_timer_soft_reload(const class time & tickTimeout) override;


   };


} // namespace userex



