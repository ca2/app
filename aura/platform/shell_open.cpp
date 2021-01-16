#include "framework.h"


shell_open::shell_open()
{


}


shell_open::~shell_open()
{


}


::e_status shell_open::initialize(::layered * pobjectContext)
{

   auto estatus = ::object::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status shell_open::initialize_shell_open()
{

   return ::success;

}



