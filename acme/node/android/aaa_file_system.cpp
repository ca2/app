#include "framework.h"
#include "_android.h"


struct PROCESS_INFO_t
{


   string csProcess;
   u32 dwImageListIndex;


};


namespace android
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   ::e_status file_system::initialize(::matter * pobjectContext)
   {

      auto estatus = ::file_system::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   
   ::e_status file_system::update_module_path()
   {

      m_pathModule = ::file::app_module();

      m_pathCa2Module = m_pathModule;

      return true;

   }


} // namespace android



