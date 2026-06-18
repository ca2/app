#pragma once


#include "core/filesystem/filemanager/_.h"
#include "berg/user/user/impact.h"


namespace filemanager
{


   class CLASS_DECL_CORE operation_info_impact:
      virtual public ::user::impact

   {
   public:


      

      ::f64 m_dAnimation;

      operation_info_impact();

      // void assert_ok() const override;
      //void dump(dump_context & action_context) const override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      ::pointer<operation_document>get_document();

      void OnFileOperationStep(::i32 iOperation,bool bFinal);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void operator()(::timer * ptimer) override;
      void install_message_routing(::channel * pchannel) override;

   };


} // namespace filemanager













