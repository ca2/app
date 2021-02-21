#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_list_view:
      virtual public ::user::show < ::user::list >
   {
   public:



      

      typedef ::user::show < ::user::list > BASE;


      ::user::list_cache               m_listcache;
      millis m_millisLast123Update;


      operation_list_view();

      virtual void install_message_routing(::channel * pchannel) override;

      void _001InsertColumns() override;

      virtual void OnDraw(::draw2d::graphics_pointer & pgraphics);

      DECL_GEN_SIGNAL(on_message_create);
      void _001OnTimer(::timer * ptimer) override;

      virtual count _001GetItemCount() override;
      virtual void _001GetItemText(::user::mesh_item * pitem) override;

      void OnFileOperationStep(i32 iOperation,bool bFinal);


      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


      __pointer(operation_document) get_document();


   };


} // namespace filemanager














