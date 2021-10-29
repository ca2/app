#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_info_view:
      virtual public ::user::impact

   {
   public:


      

      double m_dAnimation;

      operation_info_view();

      void assert_valid() const override;
      void dump(dump_context & action_context) const override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      __pointer(operation_document) get_document();

      void OnFileOperationStep(i32 iOperation,bool bFinal);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer) override;
      void install_message_routing(::channel * pchannel) override;

   };


} // namespace filemanager













