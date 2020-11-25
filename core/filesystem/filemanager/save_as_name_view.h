#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE save_as_edit_view :
      virtual public ::user::show < ::user::plain_edit >,
      virtual public ::filemanager::impact
   {
   public:


      


      bool m_bVoidSync;


      save_as_edit_view();


      virtual void install_message_routing(::channel * pchannel);

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void on_subject(::promise::subject * psubject, ::promise::context * pcontext);

      virtual void browse_sync(const ::action_context & action_context);


   };


   class CLASS_DECL_CORE save_as_button :
      virtual public ::user::show < ::user::button >,
      virtual public ::filemanager::impact
   {
   public:


      

      save_as_button();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual bool on_click(const ::user::item & item) override;
      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


      virtual void save_document(::file::path path);

      virtual void cancel_save_document();


   };


   class CLASS_DECL_CORE save_as_view:
      virtual public ::user::split_view,
      virtual public ::filemanager::impact
   {
   public:

      
      save_as_edit_view *     m_pedit;
      save_as_button *        m_pbutton;


      save_as_view();


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      virtual void on_create_split_impact() override;

   };


} // namespace filemanager





