#include "framework.h"
#include "application.h"
#include "session.h"
#include "system.h"
////#include "acme/exception/exception.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/platform/system_setup.h"
#include "aura/user/user/interaction.h"
#include "core/networking/ftp/file_status.h"
#include "core/user/user/user.h"


void rich_text_factory_exchange(::factory::factory* pfactory);


namespace core
{


   system::system()
   {

      common_construct();

      factory()->add_factory_item < ::core::session, ::platform::session >();
      factory()->add_factory_item < ::core::user, ::user::user >();


   }


   system::~system()
   {

   }


   void system::common_construct()
   {

      //m_pcoresystem = this;

      //factory()->add_factory_item < ::core::idpool, ::acme::idpool >();
      //factory()->add_factory_item < ::core::user, ::user::user >();
      //add_factory_item < ::core::idpool, ::apex::idpool >();

   }


   // void system::initialize(::particle * pparticle)
   // {
   //
   //    //auto estatus =
   //
   //    ::base::system::initialize(pparticle);
   //
   //
   //
   //    //if (!estatus)
   //    //{
   //
   //    //   return estatus;
   //
   //    //}
   //
   //    //return estatus;
   //
   // }

   //
   // void system::on_set_platform()
   // {
   //
   //    bred::system::on_set_platform();
   //
   //    // factory()->add_factory_item < ::core::session, ::platform::session >();
   //    // factory()->add_factory_item < ::core::user, ::user::user >();
   //    //
   //
   // }
   //

   //void system::on_add_session(::apex::session* papexsession)
   //{

   //   ::bred::system::on_add_session(papexsession);

   //   if (papexsession->m_iEdge == 0)
   //   {

   //      if (!m_pcoresession)
   //      {

   //         m_pcoresession = papexsession;

   //      }

   //   }

   //   papexsession = this;

   //}


   void system::initialize_rich_text()
   {

      rich_text_factory_exchange(this->factory());

   }


   void system::InsertTime(::ftp::file_status& ftpFileStatus)
   {
      
      if (ftpFileStatus.m_timeModification > 0)
      {

         auto pdatetime = datetime();

         ftpFileStatus.m_strModificationTime = pdatetime->date_time_text(ftpFileStatus.m_timeModification);

      }

   }


   //__namespace_system_factory(system);


} // namespace core



