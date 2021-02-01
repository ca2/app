#include "framework.h"
#include "apex/operating_system.h"
#include "_windows.h"


namespace windows
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   ::e_status file_system::init_system()
   {

      auto estatus = ::file_system::init_system();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   
   ::e_status file_system::update_module_path()
   {

      m_pathModule = ::path::module(nullptr);

      m_pathCa2Module = ::path::module(::GetModuleHandleA("apex.dll"));

      return true;

   }



} // namespace windows



