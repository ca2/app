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


      return ::success;

   }

   
   ::estatus file_system::update_module_path()
   {

      m_pathModule = ::path::module();

      m_pathCa2Module = ::path::module(::GetModuleHandleA("aura.dll"));

      return true;

   }



} // namespace windows



