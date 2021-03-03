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


   ::e_status application::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::application::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void application::_001OnFranceExit()
   {

      if (System->m_pmultimedia)
      {

         System->m_pmultimedia->_001OnFranceExit();

      }

      ::apex::application::_001OnFranceExit();

   }


} // namespace aqua



