#include "framework.h"
#include "apex/platform/static_setup.h"


namespace bred
{


   session::session()
   {

      m_pbredsession = this;

   }


   session::~session()
   {



      m_pbredsession = nullptr;

   }

   void session::common_construct()
   {


   }


   ::estatus session::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::session::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __namespace_session_factory(session);


} // namespace bred



