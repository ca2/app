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

      auto pcubeapplication = øcreate < cube::application>();

      return pcubeapplication;

   }


} // namespace graphics3d



