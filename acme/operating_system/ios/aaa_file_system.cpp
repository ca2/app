#include "framework.h"
#include "_ios.h"


#include <sys/stat.h>
#include <ctype.h>


struct PROCESS_INFO_t
{
   
   string csProcess;
   unsigned int dwImageListIndex;
   
};


namespace ios
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   void file_system::initialize(::particle * pparticle)
   {
   
      auto estatus = ::file_system::initialize(pparticle);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;
   
   }


   void file_system::update_module_path()
   {

      m_pathModule = apple_app_module_path();

      m_pathCa2Module = m_pathModule;

      return true;

   }


} // namespace ios



