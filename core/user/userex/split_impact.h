#pragma once


namespace userex
{


   class CLASS_DECL_CORE split_impact :
      virtual public ::user::split_impact
   {
   public:



      split_impact();
      virtual ~split_impact();


      void install_message_routing(::channel * pchannel) override;


      virtual bool on_new_impact_creator_data(::user::impact_data * pimpactdata);

      virtual void on_command_probe(::message::command * pcommand) override;

      virtual void on_command(::message::command * pcommand) override;


      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      bool create_pane(i32 iPane, bool bFixedSize, ::atom atom);
      virtual bool on_prepare_impact_data(::user::impact_data* pimpactdata) override;

   };


} // namespace userex




