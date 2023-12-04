// From impact.cpp on 2023-01-15 09:25 <3ThomasBorregaardSorensen!!
#pragma once


#include "base/user/user/impact.h"
#include "apex/platform/app_consumer.h"


namespace app_integration
{


   class CLASS_DECL_APP_INTEGRATION menu :
      virtual public app_consumer < application, ::user::impact >
   {
   public:


      menu();
      ~menu() override;

      
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


#ifdef _DEBUG
      int64_t increment_reference_count() override;
      int64_t decrement_reference_count() override;
#endif


      virtual void install_message_routing(::channel * psender) override;

      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

   };


} // namespace simple_drawing


