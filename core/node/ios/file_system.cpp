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


   ::e_status file_system::initialize(::context_object * pcontextobject)
   {
   
      auto estatus = ::file_system::initialize(pcontextobject);
      
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



