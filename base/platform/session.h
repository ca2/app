#pragma once


#include "axis/platform/session.h"
#include "base/user/user/document_manager_container.h"


namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session
   {
   public:


      session();
      ~session() override;




#ifdef _DEBUG

      i64 increment_reference_count() override;
      i64 decrement_reference_count() override;

#endif


      virtual void initialize(::particle * pparticle) override;



      virtual void on_instantiate_application(::acme::application* papp) override;


      ::base::user* baseuser() override;


      ::base::system* get_system();


   };


} // namespace base



