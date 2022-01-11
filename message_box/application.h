#pragma once


namespace app_message_box
{


   class CLASS_DECL_APP_MESSAGE_BOX application :
      virtual public ::aura::application
   {
   public:


      __composite(::app_message_box::main_window)        m_pmainwindow;


      application();
      ~application() override;


      virtual void init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


   };


} // namespace app_message_box



