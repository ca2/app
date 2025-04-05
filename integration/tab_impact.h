#pragma once


#include "base/user/user/tab_impact.h"
#include "aura/user/user/form_callback.h"
#include "apex/platform/app_consumer.h"


namespace app_integration
{


   class CLASS_DECL_APP_INTEGRATION tab_impact :
      virtual public app_interaction < application, ::user::tab_impact >,
      virtual public ::user::form_callback
   {
   public:


      ::user::split_impact *                            m_ptopviewLast;
      //::pointer<::app_integration::impact>       m_pimpactDrawing;
      string                                          m_strTopicTitle;


      ::pointer<::user::document>               m_pdocMenu;


      tab_impact();
      ~tab_impact() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;

      // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;


      DECLARE_MESSAGE_HANDLER(on_message_create);


      void on_change_cur_sel() override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   };


} // namespace simple_drawing




