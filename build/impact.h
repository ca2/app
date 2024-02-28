#pragma once


#include "application.h"
#include "apex/platform/app_consumer.h"
#include "base/user/user/impact.h"
#include "apex/platform/array_union.h"


namespace app_build
{


   class CLASS_DECL_APP_BUILD impact :
      virtual public ::app_consumer < application, ::user::impact >
   {
   public:


      string_array                  m_straLinePrebuild;

      ::pointer<build>              m_pbuild;
      array_union < string_array >  m_straunion;


      impact();
      ~impact() override;

      void install_message_routing(::channel* pchannel) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);


      void handle(::topic* ptopic, ::context* pcontext) override;
//#ifdef _DEBUG
//      // void assert_ok() const override;
//      void dump(dump_context& dumpcontext) const override;
//#endif

      void _001OnDraw(::draw2d::graphics_pointer& pgraphics);


   };


} // namespace app_build




