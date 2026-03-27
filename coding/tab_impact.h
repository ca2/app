#pragma once


#include "apex/platform/app_consumer.h"
#include "berg/user/user/tab_impact.h"
#include "aura/user/user/form_callback.h"


namespace coding
{


   class CLASS_DECL_CODING tab_impact :
      virtual public ::app_consumer < application, ::user::tab_impact, ::user::form_callback >
   {
   public:


      tab_impact();
      ~tab_impact() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      void on_change_cur_sel() override;
      document* get_document();

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;



   };


} // namespace coding



