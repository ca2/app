#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC pane_impact : 
      public ::userex::pane_tab_impact
   {
   public:


      ::turboc::impact *                     m_pflagview;


      pane_impact(::particle * pparticle);
	   virtual ~pane_impact();

      
      void on_create_impact(::user::impact_data * pcreatordata);

      virtual void install_message_handling(::message::dispatch * pinterface);

	   // void assert_ok() const override;

      // void dump(dump_context & dumpcontext) const override;

	   DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace turboc













