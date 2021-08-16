#include "framework.h"
#include "_linux.h"
#include <sys/types.h>
#include <sys/stat.h>


struct PROCESS_INFO_t
{
   string csProcess;
   u32 dwImageListIndex;
};


namespace linux
{


   file_context::file_context()
   {
   }


   file_context::~file_context()
   {

   }


   ::e_status file_context::initialize(::matter * pobject)
   {

      auto estatus = ::matter::initialize(pobject);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;


   }


   file_transport file_context::get_file(const ::payload & varFile, const ::file::e_open & eopen)
   {

      return ::file_context::get_file(varFile, eopen);

   }


   ::e_status file_context::init_system()
   {

   auto estatus = ::file_context::init_system();

   if(!estatus)
   {

   return estatus;

   }

      return estatus;

   }


   ::e_status file_context::init_context()
   {

   auto estatus = ::file_context::init_context();

   if(!estatus)
   {

   return estatus;

   }

      return estatus;

   }


   bool file_context::is_link(string strPath)
   {

      return file_path_is_link(strPath);

   }


   ::file::path file_context::dropbox_info_json()
   {

      ::file::path pathJson;

      pathJson =          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->home() / ".dropbox/info.json";

      return pathJson;

   }


} // namespace linux






