#pragma once


#include "axis/platform/session.h"
#include "berg/user/user/document_manager_container.h"


namespace berg
{


   class CLASS_DECL_BERG session:
      virtual public ::axis::session
   {
   public:


      session();
      ~session() override;




#ifdef _DEBUG

      long long increment_reference_count() override;
      long long decrement_reference_count() override;

#endif


      virtual void initialize(::particle * pparticle) override;



      virtual void on_instantiate_application(::platform::application* papp) override;


      // ::berg::user* user() override;
      //
      //
      // ::berg::system* get_system();


   };


} // namespace berg



