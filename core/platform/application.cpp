#include "framework.h"
#include "apex/platform/static_setup.h"


namespace core
{


   application::application()
   {

      m_pcoreapplication = this;

   }

   application::~application()
   {



      m_pcoreapplication = nullptr;

   }

   void application::common_construct()
   {


   }


   ::estatus application::initialize(::layered * pobjectContext)
   {

      auto estatus = ::base::application::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace core



