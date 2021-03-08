#include "framework.h"


namespace aqua
{


   application::application()
   {

      set_layer(LAYERED_AQUA, this);

   }


   application::~application()
   {

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

      if (::aqua::get_system()->m_pmultimedia)
      {

         ::aqua::get_system()->m_pmultimedia->_001OnFranceExit();

      }

      ::apex::application::_001OnFranceExit();

   }


} // namespace aqua



