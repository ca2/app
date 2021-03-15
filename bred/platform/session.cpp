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


   ::e_status session::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::apex::session::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __namespace_session_factory(session);


} // namespace bred



