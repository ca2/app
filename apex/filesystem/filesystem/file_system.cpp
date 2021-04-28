#include "framework.h"


file_system::file_system()
{

}


file_system::~file_system()
{


}


::e_status file_system::initialize(::object * pobject)
{
   
   auto estatus = ::object::initialize(pobject);
   
   if(!estatus)
   {
      
      return estatus;
      
   }

   return estatus;

}


::e_status file_system::init_system()
{
   
   auto estatus = update_module_path();
   
   if(!estatus)
   {
      
      return estatus;
      
   }

   return estatus;

}


::e_status file_system::update_module_path()
{

   return ::success;

}



