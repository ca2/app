#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_info_view:
      virtual public ::user::impact

   {
   public:


      

      double m_dAnime;

      operation_info_view();

      void assert_valid() const;
      void dump(dump_context & action_context) const;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      __pointer(operation_document) get_document();

      void OnFileOperationStep(i32 iOperation,bool bFinal);

      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);
      virtual void install_message_routing(::channel * pchannel);

   };


} // namespace filemanager













