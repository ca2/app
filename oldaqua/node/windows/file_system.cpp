#include "framework.h"
#include "_windows.h"


namespace windows
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   ::estatus file_system::init_system()
   {

      auto estatus = ::file_system::init_system();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   
   ::estatus file_system::update_module_path()
   {

      m_pathModule = ::path::module();

      m_pathCa2Module = ::path::module(::GetModuleHandleA("aqua.dll"));

      return true;

   }



} // namespace windows



