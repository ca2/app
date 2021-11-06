#include "framework.h"


shell_open::shell_open()
{


}


shell_open::~shell_open()
{


}


::e_status shell_open::initialize(::object * pobject)
{

   auto estatus = ::object::initialize(pobject);

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



