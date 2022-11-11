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


   void file_context::initialize(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

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

      struct stat stat;

      __zero(stat);

      if(lstat(strPath, &stat) != 0)
      {

         return false;

      }

      if(S_ISLNK(stat.st_mode))
      {

         return true;

      }

      return false;

   }


   ::file::path file_context::dropbox_info_network_payload()
   {

      ::file::path pathNetworkPayload;

      pathNetworkPayload =          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->home() / ".dropbox/info.network_payload";

      return pathNetworkPayload;

   }


} // namespace linux






