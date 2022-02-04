#pragma once


namespace userex
{


   class CLASS_DECL_CORE split_view :
      virtual public ::user::split_view
   {
   public:



      split_view();
      virtual ~split_view();


      void install_message_routing(::channel * pchannel) override;


      virtual bool on_new_view_creator_data(::user::impact_data * pimpactdata);

      virtual void on_command_probe(::message::command * pcommand) override;

      virtual void on_command(::message::command * pcommand) override;


      virtual void handle(::topic * psubject, ::context * pcontext) override;

      bool create_pane(i32 iPane, bool bFixedSize, ::id id);
      virtual bool on_prepare_impact_data(::user::impact_data* pimpactdata) override;

   };


} // namespace userex




