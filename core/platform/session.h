#pragma once


#include "bred/platform/session.h"


namespace core
{


   class CLASS_DECL_CORE session :
      virtual public ::bred::session
   {
   public:


      session();
      ~session() override;


      inline ::core::system* get_system() const;


      void common_construct();


      virtual void initialize(::object * pobject) override;


      virtual void on_instantiate_application(::application* papp) override;


   };


} // namespace core




