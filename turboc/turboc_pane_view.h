#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC pane_view : 
      public ::userex::pane_tab_view
   {
   public:


      ::turboc::impact *                     m_pflagview;


      pane_view(::object * pobject);
	   virtual ~pane_view();

      
      void on_create_impact(::user::impact_data * pcreatordata);

      virtual void install_message_handling(::message::dispatch * pinterface);

	   void assert_valid() const override;

      void dump(dump_context & dumpcontext) const override;

	   DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace turboc













