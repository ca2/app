#pragma once


#include "base/user/user/split_impact.h"


namespace userex
{


   class CLASS_DECL_CORE split_impact :
      virtual public ::user::split_impact
   {
   public:



      split_impact();
      ~split_impact() override;


      void install_message_routing(::channel * pchannel) override;


      virtual bool on_new_impact_creator_data(::user::impact_data * pimpactdata);

      void on_command_probe(::message::command * pcommand) override;

      void on_command(::message::command * pcommand) override;


      void handle(::topic * ptopic, ::handler_context * pcontext) override;

      bool create_pane(int iPane, bool bFixedSize, ::atom atom);

      bool on_prepare_impact_data(::user::impact_data* pimpactdata) override;


   };


} // namespace userex



