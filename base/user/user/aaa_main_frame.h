#pragma once


#include "base/user/simple/main_frame.h"


namespace user
{


   class CLASS_DECL_BASE main_frame : 
      public main_frame
   {
   public:


      bool           m_bPlacing;
      
      
      main_frame();
      virtual ~main_frame();

      void install_message_routing(::channel * pchannel) override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace user


