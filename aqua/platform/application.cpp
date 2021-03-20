#include "framework.h"


namespace aqua
{


   application::application()
   {

      m_paquaapplication = this;
      ///set_layer(LAYERED_AQUA, this);

   }


   application::~application()
   {

   }


   void application::common_construct()
   {


   }


   ::e_status application::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::apex::application::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void application::_001OnFranceExit()
   {

      if (get_system()->m_pmultimedia)
      {

         get_system()->m_pmultimedia->_001OnFranceExit();

      }

      ::apex::application::_001OnFranceExit();

   }


   //LPWAVEOUT application::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   //{

   //   get_system()-

   //}



} // namespace aqua



