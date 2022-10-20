#include "framework.h"
#include "file_system.h"
#include "acme/filesystem/filesystem/acme_file.h"


file_system::file_system()
{

}


file_system::~file_system()
{


}


void file_system::initialize(::object * pobject)
{
   
   /*auto estatus = */ ::object::initialize(pobject);
   
   //if(!estatus)
   //{
   //   
   //   return estatus;
   //   
   //}

   ::file::path pathModule = m_psystem->m_pacmefile->module();

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



