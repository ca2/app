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


   ::e_status fs::initialize(::object * pobject)
   {

      auto estatus = ::acme::department::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }
//
//      if(get_application()->is_system())
//      {
//
///*       
//         create_factory <main_impact > ();
//         create_factory <tree > ();
//         create_factory <list > ();
//*/
//
//      }

      return estatus;

   }
 


} // namespace fs



