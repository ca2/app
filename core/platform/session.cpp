#include "framework.h"
#include "apex/platform/static_setup.h"


namespace core
{


   session::session()
   {

      m_pcoresession = this;

   }


   session::~session()
   {



      m_pcoresession = nullptr;

   }

   void session::common_construct()
   {


   }


   ::estatus session::initialize(::layered * pobjectContext)
   {

      auto estatus = ::base::session::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __namespace_session_factory(session);


} // namespace core



