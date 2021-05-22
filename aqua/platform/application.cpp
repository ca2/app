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


   ::e_status application::initialize(::object * pobject)
   {

      auto estatus = ::application::initialize(pobject);

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

      ::application::_001OnFranceExit();

   }


   void application::game_on_create()
   {



   }

   //LPWAVEOUT application::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   //{

   //   get_system()-

   //}



} // namespace aqua



