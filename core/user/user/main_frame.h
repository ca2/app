#pragma once


#include "base/user/simple/main_frame.h"


namespace user
{


   class CLASS_DECL_CORE main_frame : 
      public simple_main_frame
   {
   public:


      bool                                         m_bPlacing;
      __pointer(::user::rich_text::format_tool)    m_prichtextformattool;
      
      
      main_frame();
      ~main_frame() override;

      
      void install_message_routing(::channel * pchannel) override;


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);


      ::user::tool_window * tool_window(enum_tool etool, bool bCreate) override;


   };


} // namespace user


