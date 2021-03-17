#include "framework.h"
#include "apex/platform/static_setup.h"


namespace core
{


   session::session()
   {

   }


   session::~session()
   {

   }


   void session::common_construct()
   {


   }


   ::e_status session::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::base::session::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __namespace_session_factory(session);


} // namespace core



