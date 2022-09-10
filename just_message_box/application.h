#pragma once



#include "aura/platform/application.h"


namespace app_just_message_box
{


   class CLASS_DECL_APP_MESSAGE_BOX_APP application :
      virtual public ::aura::application
   {
   public:


      application();
      ~application() override;


      void init_instance() override;
      void term_application() override;


      void on_request(::create * pcreate) override;


#ifdef _DEBUG

      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;

#endif


      virtual void show_message_box();


   };


} // namespace app_just_message_box



