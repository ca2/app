#pragma once


#include "core/user/user/main_frame.h"


class CLASS_DECL_CORE simple_main_frame :
   virtual public ::user::main_frame
{
public:


   bool                       m_bPlacing;
   bool                       m_bExplicitTranslucency;


   simple_main_frame();
   ~simple_main_frame() override;


   void assert_ok() const override;
   void dump(dump_context & dumpcontext) const override;


   void install_message_routing(::channel * pchannel) override;


   DECLARE_MESSAGE_HANDLER(on_message_create);


};



