#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE save_as_edit_view :
      virtual public ::filemanager_show < ::user::show < ::user::plain_edit > >
   {
   public:


      bool m_bVoidSync;


      save_as_edit_view();


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      void handle(::subject * psubject, ::context * pcontext) override;

      void browse_sync(const ::action_context & action_context) override;


   };


   class CLASS_DECL_CORE save_as_button :
      virtual public ::filemanager_show < ::user::show < ::user::button > >
   {
   public:


      save_as_button();


      void install_message_routing(::channel * pchannel) override;


      virtual bool on_click(const ::item & item) override;
      virtual void handle(::subject * psubject, ::context * pcontext) override;


      virtual void save_document(::file::path path);

      virtual void cancel_save_document();


   };


   class CLASS_DECL_CORE save_as_view:
      virtual public ::filemanager_show < ::user::split_view >
   {
   public:

      
      save_as_edit_view *     m_pedit;
      save_as_button *        m_pbutton;


      save_as_view();


      void install_message_routing(::channel * pchannel) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual void on_create_split_impact() override;

   };


} // namespace filemanager





