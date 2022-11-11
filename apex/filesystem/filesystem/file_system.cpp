#include "framework.h"
#include "file_system.h"
#include "acme/filesystem/filesystem/acme_file.h"


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

   ::file::path pathModule = acmefile()->module();

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



