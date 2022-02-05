#pragma once


namespace userex
{


   class CLASS_DECL_CORE message_box :
      virtual public wait_message_dialog
   {
   public:


      //__pointer(::future < ::atom >)     m_pprocess;
      
      
      message_box();

      
      virtual void on_show(const ::string & pszMatter) override;
      virtual bool on_timeout() override;
      virtual void on_timer_soft_reload(::duration tickTimeout) override;


   };


} // namespace userex



