#include "framework.h"
#include "acme/platform/static_setup.h"
#include "core/user/user/_user.h"
#include "core/const/idpool.h"
#include "core/networking/ftp/file_status.h"


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

      m_pcoresystem = this;

      create_factory < ::core::application, ::application >();
      create_factory < ::core::session, ::apex::session >();
      create_factory < ::core::idpool, ::acme::idpool >();
      create_factory < ::core::user, ::user::user >();
      //create_factory < ::core::idpool, ::apex::idpool >();

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


   void system::on_add_session(::apex::session* papexsession)
   {

      ::bred::system::on_add_session(papexsession);

      if (papexsession->m_iEdge == 0)
      {

         if (!m_pcoresession)
         {

            m_pcoresession = papexsession->m_pcoresession;

         }

      }

      papexsession->m_pcoresystem = this;

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
      
      if (ftpFileStatus.m_timeModification > 0)
      {

         auto psystem = m_psystem;

         auto pdatetime = psystem->datetime();

         ftpFileStatus.m_strModificationTime = pdatetime->international().get_gmt_date_time(ftpFileStatus.m_timeModification);

      }

   }


   __namespace_system_factory(system);


} // namespace core



