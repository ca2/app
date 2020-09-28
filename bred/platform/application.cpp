#include "framework.h"


namespace bred
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


   //__pointer(progress_control) application::show_progress(::user::interaction* puiParent, const char* pszTitle, ::count iProgressCount)
   //{

   //   auto pprogresscontrol = __create_new <  ::userex::progress_control >();

   //   pprogresscontrol->defer_show(puiParent, pszTitle, iProgressCount);

   //   return ::move(pprogresscontrol);

   //}


} // namespace bred



