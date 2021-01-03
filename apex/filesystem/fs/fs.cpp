#include "framework.h"
#include "apex/filesystem/fs/_fs.h"


namespace fs
{


   fs::fs()
   {

   }


   fs::~fs()
   {

   }


   ::e_status fs::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }
//
//      if(get_context_application()->is_system())
//      {
//
///*       
//         create_factory <main_view > ();
//         create_factory <tree > ();
//         create_factory <list > ();
//*/
//
//      }

      return estatus;

   }
 


} // namespace fs



