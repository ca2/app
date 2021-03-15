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


   ::e_status fs::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::apex::department::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }
//
//      if(get_application()->is_system())
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



