#include "framework.h"



namespace youtube
{


   application::application(::particle * pparticle) :
      ::object(this),
      ::thread(this),
      ::aura::application(pparticle),
      ::axis::application(pparticle),
      ::base::application(pparticle),
      ::aura::application(pparticle),
      ::sphere::application(pparticle)
   {


   }


   application::~application()
   {

   }


   void application::construct()
   {


   }


   bool application::initialize_application()
   {

      if (!::resident::application::initialize_application())
         return false;

      return true;

   }


   void application::on_request(::request * prequest)
   {

      ::aura::application::on_request(spcreate);

   }


   i32 application::exit_application()
   {

      ::aura::application::exit_application();

      return 0;

   }


   ::pointer<comm>application::create_youtube_comm(::object * pdata)
   {

      return NULL;

   }




} // namespace youtube




