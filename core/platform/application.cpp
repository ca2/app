#include "framework.h"
#include "core/user/userex/_userex.h"
#include "apex/platform/static_setup.h"
#include "core/user/userex/progress.h"


namespace core
{


   application::application()
   {

   }


   application::~application()
   {

   }


   void application::common_construct()
   {


   }


   ::e_status application::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::base::application::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __pointer(progress_control) application::show_progress(::user::interaction* puiParent, const char* pszTitle, ::count iProgressCount)
   {

      auto pprogresscontrol = __create_new <  ::userex::progress_control >();

      pprogresscontrol->defer_show(puiParent, pszTitle, iProgressCount);

      return ::move(pprogresscontrol);

   }


} // namespace core



