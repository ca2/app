#include "framework.h"


namespace aqua
{


   application::application()
   {

      m_paquaapplication = this;

   }


   application::~application()
   {


      m_paquaapplication = nullptr;

   }


   void application::common_construct()
   {


   }


   ::estatus application::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::application::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace aqua



