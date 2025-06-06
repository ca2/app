//
//  session.cpp
//  acme
//
//  Created by camilo on 2022-12-01 11:30 BRT <3TBS_!!
//
#include "framework.h"
#include "session.h"
#include "system.h"
#include "acme/exception/interface_only.h"
#include "acme/handler/request.h"
#include "acme/prototype/text/context.h"
#include "acme/windowing/windowing.h"


namespace platform
{


   session::session()
   {

      // m_psession = this;
      // m_papexsession = nullptr;
      // m_paquasession = nullptr;
      // m_paurasession = nullptr;
      // m_paxissession = nullptr;
      // m_pbasesession = nullptr;
      // m_pbredsession = nullptr;
      // m_pcoresession = nullptr;
      m_bKeepRunningPostedProcedures = true;

   }


   session::~session()
   {

      printf_line("platform::session destroyed");

   }


   void session::destroy()
   {

      ::task::destroy();

      ::handler::handler::destroy();

      ::platform::application_container::destroy();

   }


   text::context* session::text_context()
   {

      return m_ptextcontext;
   }


   ::user::user* session::user()
   {

      throw ::interface_only("user requires aura layer or upper layer");

      return nullptr;

   }


   void session::on_request(::request* prequest)
   {

      if (prequest->m_ecommand == e_command_protocol)
      {

         m_pappCurrent->request(prequest);

         return;

      }

      information() << "::apex::session::on_request(::pointer<::create> " << ::type(this).name();

      //string strAppId = prequest->m_strAppId;

      //if (strAppId.is_empty())
      //{

      //   information() << "m_strAppId Is Empty!!";

      //   return;

      //}

      information() << "m_strAppId = " << prequest->m_strAppId;

      auto papplication = get_application(prequest->m_strAppId, true, prequest);

      if (!papplication)
      {

         throw ::exception(error_wrong_state, "request without application m_strAppId");

      }

      m_varCurrentImpactFile = prequest->m_payloadFile;

      papplication->post_request(prequest);

   }


   void session::process_init()
   {


      __construct_new(m_ptextcontext);

      //initialize_context();

   }

   void session::main()
   {

      //::platform::context::main();
      ::task::main();

   }


   void session::init()
   {


   }


   void session::init_task()
   {

      ::task::init_task();

      init_session();

      //auto estatus =

      //process_init();

      //if (!estatus)
      //{

      //   warning() <<"Failed at apex::session::init_thread after process_init";

      //   return estatus;

      //}

      //estatus =

      //init_session();

      //if (!estatus)
      //{

      //   warning() <<"Failed at apex::session::init_thread after init_session";

      //   return estatus;

      //}

      // // now there is attempt here
      //estatus = defer_initialize_host_window();

      //if(!estatus)
      //{

      //   throw ::exception(::exception(estatus));

      //}

      //information() << ".1";

      //return true;

      //return estatus;

   }


   void session::init1()
   {

      if (system()->acme_windowing()->m_ewindowingbias == ::windowing::e_bias_unknown)
      {

         system()->acme_windowing()->m_ewindowingbias = system()->acme_windowing()->calculate_windowing_bias();

      }

   }


   void session::init2()
   {


   }


   void session::term_task()
   {

      try
      {

         term_session();

      }
      catch (...)
      {

      }

      try
      {

         process_term();

      }
      catch (...)
      {

      }

      ::task::term_task();

   }

   void session::term()
   {


   }

   void session::init_session()
   {


      process_init();


      //auto estatus =
      init1();

      //if (!estatus)
      //{

      //   warning() <<"Failed to init1 the session (::apex::session or ::apex::session derived)";

      //   return estatus;

      //}

      //estatus =
      init2();

      //if (!estatus)
      //{

      //   warning() <<"Failed to init2 the session (::apex::session or ::apex::session derived)";

      //   return estatus;

      //}

      init();

      //if (!estatus)
      //{

      //   warning() <<"Failed to init() the session (::apex::session or ::apex::session derived)";

      //   return estatus;

      //}

      //      return ::success;

   }


   void session::term_session()
   {

      try
      {

         term2();

      }
      catch (...)
      {

      }

      try
      {

         term1();

      }
      catch (...)
      {

      }

      try
      {

         term();

      }
      catch (...)
      {

      }



   }



   void session::term2()
   {

      //auto psystem = system();

      //if (psystem)
      //{

      //   auto pacmewindowing = psystem->acme_windowing();

      //   if (pacmewindowing)
      //   {

      //      pacmewindowing->windowing_system_post_quit();

      //   }

      //}

   }


   void session::term1()
   {

   }


   void session::process_term()
   {

      auto psystem = system();

      if (::is_set(psystem))
      {

         auto iEdge = m_iEdge;

         psystem->post([psystem, iEdge]()
            {

               psystem->erase_session(iEdge);

            });

      }


   }


} // namespace platform



