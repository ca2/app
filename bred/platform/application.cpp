#include "framework.h"
#include "application.h"
#include "system.h"


namespace bred
{


   //void initialize()
   //{

   //}


   application::application()
   {

      //::bred::initialize();

      m_pbredapplication = this;


      factory()->add_factory_item < ::bred::system, ::acme::system >();



   }


   application::~application()
   {

   }


   void application::common_construct()
   {


   }


   void application::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::axis::application::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //::pointer<progress_control>application::show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::count iProgressCount)
   //{

   //   auto pprogresscontrol = __create_new <  ::userex::progress_control >();

   //   pprogresscontrol->defer_show(puiParent, pszTitle, iProgressCount);

   //   return ::transfer(pprogresscontrol);

   //}


} // namespace bred



