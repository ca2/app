#include "framework.h"
#include "application.h"
#include "system.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"


namespace cube
{


   //void initialize()
   //{

   //}


   application::application()
   {


   }


   application::~application()
   {


   }


   ::pointer < ::cube::application > application::start_cube_aplication()
   {

      auto pcubeapplication = __øcreate < cube::application>();

      return pcubeapplication;

   }


} // namespace cube



