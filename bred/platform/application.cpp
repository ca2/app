#include "framework.h"
#include "application.h"
#include "system.h"


namespace bred
{


   void initialize()
   {

      ::factory::add_factory_item < ::bred::system, class ::system >();

   }


   application::application()
   {

      ::bred::initialize();

   }


   application::~application()
   {

   }


   void application::common_construct()
   {


   }


   void application::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::application::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //__pointer(progress_control) application::show_progress(::user::interaction* puiParent, const ::string & pszTitle, ::count iProgressCount)
   //{

   //   auto pprogresscontrol = __create_new <  ::userex::progress_control >();

   //   pprogresscontrol->defer_show(puiParent, pszTitle, iProgressCount);

   //   return ::move(pprogresscontrol);

   //}


} // namespace bred



