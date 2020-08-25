#pragma once


namespace userex
{


   class CLASS_DECL_CORE message_box :
      virtual public wait_message_dialog
   {
   public:
      
      
      message_box();

      
      virtual void on_show(const char * pszMatter) override;
      virtual bool on_timeout() override;
      virtual void on_timer_soft_reload(tick tickTimeout) override;


   };


} // namespace userex



