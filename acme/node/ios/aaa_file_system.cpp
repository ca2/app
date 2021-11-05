#include "framework.h"
#include "_ios.h"


#include <sys/stat.h>
#include <ctype.h>


struct PROCESS_INFO_t
{
   
   string csProcess;
   u32 dwImageListIndex;
   
};


namespace ios
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   ::e_status file_system::initialize(::matter * pobject)
   {
   
      auto estatus = ::file_system::initialize(pobject);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;
   
   }


   ::e_status file_system::update_module_path()
   {

      m_pathModule = apple_app_module_path();

      m_pathCa2Module = m_pathModule;

      return true;

   }


} // namespace ios



