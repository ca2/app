#pragma once


#include "code_application.h"
#include "apex/platform/app_consumer.h"
#include "aura/user/user/form_callback.h"
#include "berg/user/user/tab_impact.h"


namespace coding
{


   class CLASS_DECL_CODING tab_impact :
      virtual public app_interaction < ::coding::code_application,  ::user::tab_impact >,
      virtual public ::user::form_callback
   {
   public:


      ::user::split_impact *                            m_ptopviewLast;
      ::user::impact_data *                           m_pimpactdataTopic;
      string                                          m_strTopicTitle;


      ::user::document *                              m_pdocMenu;
      bool                                            m_bSaveCurrentMode;


      tab_impact();
      ~tab_impact() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;

      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      void on_change_cur_sel() override;



   };


} // namespace coding



