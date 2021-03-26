#pragma once


namespace turboc
{


   class CLASS_DECL_TURBOC pane_view : 
      public ::userex::pane_tab_view
   {
   public:


      ::turboc::view *                     m_pflagview;


      pane_view(::object * pobject);
	   virtual ~pane_view();

      
      void on_create_impact(::user::impact_data * pcreatordata);

      virtual void install_message_handling(::message::dispatch * pinterface);

	   virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

	   DECL_GEN_SIGNAL(on_message_create);

   };


} // namespace turboc













