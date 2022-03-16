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


   void file_context::initialize(::matter * pobject)
   {

      auto estatus = ::matter::initialize(pobject);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;


   }


   file_pointer file_context::get_file(const ::payload & payloadFile, const ::file::e_open & eopen)
   {

      return ::file_context::get_file(payloadFile, eopen);

   }


   void file_context::init_system()
   {

   auto estatus = ::file_context::init_system();

   if(!estatus)
   {

   return estatus;

   }

      return estatus;

   }


   void file_context::init_context()
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


   ::file::path file_context::dropbox_info_network_payload()
   {

      ::file::path pathNetworkPayload;

      pathNetworkPayload =          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedirectory;

pacmedir->home() / ".dropbox/info.network_payload";

      return pathNetworkPayload;

   }


} // namespace linux






