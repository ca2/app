#pragma once


#include "axis/platform/system.h"


namespace berg
{


   class CLASS_DECL_BERG system:
      virtual public ::axis::system
   {
   public:


      system();
      ~system() override;

      
      void common_construct();
      //void on_set_platform() override;
      void on_initialize_particle() override;

      

      //void on_add_session(::platform::session * papexsession) override;

   };

   
} // namespace berg



