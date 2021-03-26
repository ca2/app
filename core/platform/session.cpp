#include "framework.h"
#include "acme/platform/static_setup.h"


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


   ::e_status session::initialize(::object * pobject)
   {

      auto estatus = ::base::session::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __namespace_session_factory(session);


} // namespace core



