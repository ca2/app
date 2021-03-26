#include "framework.h"
#include "acme/platform/static_setup.h"
#include "core/user/user/_user.h"
#include "core/const/idpool.h"
#include "core/net/ftp/file_status.h"


bool __rich_text_initialize();


namespace core
{


   system::system()
   {

      common_construct();

   }


   system::~system()
   {

   }


   void system::common_construct()
   {

      create_factory < ::core::application, ::apex::application >();
      create_factory < ::core::session, ::apex::session >();
      create_factory < ::core::idpool, ::apex::idpool >();
      create_factory < ::core::user, ::user::user >();
      create_factory < ::core::idpool, ::apex::idpool >();

   }


   ::e_status system::initialize(::object * pobject)
   {

      auto estatus = ::base::system::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::initialize_rich_text()
   {

      if (!__rich_text_initialize())
      {

         return false;

      }

      return ::success;

   }


   void system::InsertTime(::ftp::file_status& ftpFileStatus)
   {
      //tm m = { 0 };
      if (ftpFileStatus.m_timeModification > 0)
      {

         ftpFileStatus.m_strModificationTime = datetime().international().get_gmt_date_time(ftpFileStatus.m_timeModification);

      }

   }


   __namespace_system_factory(system);


} // namespace core



