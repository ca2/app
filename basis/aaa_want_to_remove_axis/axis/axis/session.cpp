#include "framework.h"
#include "axis/filesystem/fs/_fs.h"



namespace axis
{


   session::session()
   {

   }


   ::e_status session::initialize(::object * pobject)
   {

      auto estatus = ::aura::session::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      //m_XstrAppId                    = "axis_session";
      //m_strAppName                  = "axis_session";
      //m_strBaseSupportId            = "axis_session";
      //m_strInstallToken             = "axis_session";

      //m_datakey.m_bLocalData        = true;

      m_bIfs                        = true;

      m_pkeyboard                   = nullptr;

      m_puserpresence               = nullptr;

      return estatus;

   }


   //void session::construct(::object * pobject, int iPhase)
   //{

   //   if(iPhase == 0)
   //   {


   //   }

   //}

   session::~session()
   {


   }


   bool session::is_session() const
   {

      return true;

   }


   void session::on_user_logon(::account::user * puser)
   {

      ::aura::session::on_user_logon(puser);

   }


   size  session::get_window_minimum_size()
   {

      return size(300, 300);

   }


   ::e_status session::process_init()
   {

      INFORMATION("axis::session::process_init");

      if (!::aura::session::process_init())
      {

         FATAL("axis::session::process_init");

         return false;

      }

      INFORMATION(".1");

      if (!m_pifs)
      {

         __compose(m_pifs, __new(ifs("")));

      }

      if (!m_premotefs)
      {

         __compose(m_premotefs, __new(::fs::remote_native("")));

      }

      if (!m_pftpfs)
      {

         auto pftpfs = __new(ftpfs);

         auto estatus = pftpfs->initialize_ftpfs(this, "");
         
         if(!estatus)
         {
            
            m_result.add(estatus);
            
         }
         
         __compose(m_pftpfs, pftpfs);

      }

      if (!m_pfsdata)
      {

         auto pset  = __create_new<::fs::set>();

         auto plink  = __create_new < ::fs::link>();

         plink->fill_os_user();

         pset->m_spafsdata.add(plink);

         pset->m_spafsdata.add(__create_new < ::fs::native>());

         __compose(m_pfsdata, pset);

      }

      INFORMATION(".2");

      //if (!::axis::application::process_init())
      //{

      //   ERROR(".2");

      //   return false;

      //}

      //fill_locale_schema(*textcontext()->m_plocaleschema);

      INFORMATION("success");

      return true;

   }


   ::e_status session::init1()
   {

      auto estatus = __compose_new(m_pfs);

      if(!estatus)
      {

         m_result.add(estatus);

         return false;

      }

      //m_pfs->construct(this);

      //if(!m_pfs->initialize())
      //{

        // return false;

      //}

      //m_spcopydesk.create(this);

      //if(!m_spcopydesk->initialize())
      //   return false;

      if(!::aura::session::init1())
      {

         return false;

      }

      //if(!::axis::application::init1())
      //{

      //   return false;

      //}

      estatus = __construct_new(m_puserpresence);

      if(!estatus)
      {

         m_result.add(estatus);

         TRACE("Failed to create new User Presence");

         return false;

      }

      //try
      //{

      //   m_puserpresence->construct(this);

      //}
      //catch(...)
      //{

      //   TRACE("Failed to construct User Presence");

      //   return false;

      //}

      //if(!m_puserpresence->initialize())
      //{

      //   TRACE("Failed to initialize User Presence");

      //   return false;

      //}

      return true;

   }


   ::e_status session::init2()
   {

      if(!::aura::session::init2())
      {

         return false;

      }

      //if(!::axis::application::init2())
      //{

      //   return false;

      //}

      return true;

   }


   ::e_status session::init_session()
   {

      if (!m_paccount->init_instance())
      {

         return false;

      }

//      if(papplication->has_property("uninstall")
//            || papplication->has_property("install"))
//      {
//
////         if(!m_paccount->open_local("system"))
////         {
////
////            return false;
////
////         }
//
//      }
//
      if (!::aura::session::init_session())
      {

         return false;

      }

      //if (!::axis::application::init_application())
      //{

      //   return false;

      //}

      return true;

   }


   ::e_status session::init()
   {

      if (!::aura::session::init())
      {

         return false;

      }

      //if (!::axis::application::init())
      //{

      //   return false;

      //}

      __pointer(::fs::set) pfsset = m_pfsdata;

      if(m_bIfs)
      {

         if (m_pfsdata.is_null())
         {

            __compose(m_pfsdata, __new(::fs::set));

         }

         pfsset = m_pfsdata;

         if(pfsset.is_null())
         {

            pfsset->m_spafsdata.add_unique(m_pifs);

            pfsset->m_spafsdata.add_unique(m_premotefs);

         }

         ::file::listing patha;

         m_pfsdata->root_ones(patha);

      }

      if (pfsset.is_set())
      {
         pfsset->m_spafsdata.add_unique(m_pftpfs);

      }

      return true;

   }


   void session::term()
   {

      //try
      //{

      //   ::axis::application::term();

      //}
      //catch(...)
      //{

      //   m_result.add(error_failed);

      //}

      try
      {

         ::acme::del(m_pmapKeyPressed);

      }
      catch (...)
      {

         m_result.add(error_failed);

      }

      try
      {

         if (m_puserpresence.is_set())
         {

            m_puserpresence->destroy();

            m_puserpresence.release();

         }

      }
      catch (...)
      {

         m_result.add(error_failed);

      }


      //try
      //{

      //   m_pfsdata.release();

      //}
      //catch (...)
      //{

      //   m_result.add(error_failed);

      //}


      //try
      //{

      //   m_pifs.release();

      //}
      //catch (...)
      //{

      //   m_result.add(error_failed);

      //}

      //try
      //{

      //   m_premotefs.release();

      //}
      //catch (...)
      //{

      //   m_result.add(error_failed);

      //}

      //try
      //{

      //   m_pftpfs.release();

      //}
      //catch (...)
      //{

      //   m_result.add(error_failed);

      //}


      try
      {

         m_paccount.release();

      }
      catch (...)
      {

         m_result.add(error_failed);

      }

      try
      {

         ::aura::session::term();

      }
      catch(...)
      {

         m_result.add(error_failed);

      }

   }


   void session::term_session()
   {

      try
      {

         if(m_pcopydesk.is_set())
         {

            m_pcopydesk->destroy();

            m_pcopydesk.release();

         }

      }
      catch(...)
      {

      }

      m_pkeyboard.release();

      //::axis::application::term_application();

      ::aura::session::term_session();

   }


   ::u32 session::get_Long_PhRESSing_time()
   {

      return m_dwLongPhRESSingTime;

   }


   void session::defer_initialize_user_presence()
   {

      ::aura::session::defer_initialize_user_presence();

      userpresence().defer_initialize_user_presence();

   }


   void session::on_request(::create * pcreate)
   {

      ::aura::session::on_request(pcreate);

   }


//   string session::interactive_credentials(::account::credentials * pcredentials)
//   {
//
//      string str = ::account::get_cred(papp,strUsername,strPassword,strToken);
//
//      if(str == "ok")
//      {
//
//         return "ok";
//
//      }
//
//      return "failed";
//
//   }

   bool session::on_create_frame_window()
   {

      if(!::aura::session::on_create_frame_window())
      {

         return false;

      }

      if (m_pcopydesk != nullptr)
      {

         return true;

      }

      auto estatus = __construct(m_pcopydesk);

      if (!estatus)
      {

         return false;

      }

      return true;

   }





//   string session::account_get_user_sessid(const ::string & str)
//   {
//
//      return interactive_get_user()->get_sessid(str);
//
//   }


   void session::translate_os_key_message(::user::key * pkey)
   {

      psession->keyboard().translate_os_key_message(pkey);

   }


} // namespace axis



