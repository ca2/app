#pragma once


#include "axis/platform/session.h"
#include "base/user/user/document_manager_container.h"


namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public ::user::document_manager_container
   {
   public:


      session();
      virtual ~session();


      virtual void initialize(::particle * pparticle) override;



      virtual void on_instantiate_application(::acme::application* papp) override;


      ::base::user* baseuser();


      ::base::system* get_system();


   };


} // namespace base



