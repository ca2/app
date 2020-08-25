#include "framework.h"
#include "aura/platform/static_setup.h"


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


   ::estatus application::initialize(::object* pobjectContext)
   {

      auto estatus = ::base::application::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace core



