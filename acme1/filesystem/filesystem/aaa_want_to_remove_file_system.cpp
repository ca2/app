#include "framework.h"


file_system::file_system()
{

}


file_system::~file_system()
{


}


::estatus file_system::initialize(::generic * pobjectContext)
{
   
   auto estatus = ::generic::initialize(pobjectContext);
   
   if(!estatus)
   {
      
      return estatus;
      
   }

   return estatus;

}


::estatus file_system::init_system()
{
   
   auto estatus = update_module_path();
   
   if(!estatus)
   {
      
      return estatus;
      
   }

   return estatus;

}


::estatus file_system::update_module_path()
{

   return ::success;

}



