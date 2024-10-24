#include "framework.h"
#include "file_system.h"
#include "acme/filesystem/filesystem/file_system.h"


file_system::file_system()
{

}


file_system::~file_system()
{


}


void file_system::initialize(::particle * pparticle)
{
   
   /*auto estatus = */ ::object::initialize(pparticle);
   
   //if(!estatus)
   //{
   //   
   //   return estatus;
   //   
   //}

   ::file::path pathModule = file_system()->module();

   m_pathModule = pathModule;

   //return estatus;

}


void file_system::init_system()
{
   
//   auto estatus = update_module_path();
//
//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//
   //return estatus;

   //return ::success;

}


//void file_system::update_module_path()
//{
//
//   return ::success;
//
//}



