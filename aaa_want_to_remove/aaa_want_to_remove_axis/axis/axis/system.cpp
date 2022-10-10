#include "framework.h"
#include "core/net/ftp/_.h"


namespace axis
{


   system::system()
   {

      add_factory_item < ::axis::session, ::aura::session >();

   }


   system::~system()
   {


   }


   void     system::initialize_system(::object * pobject, app_core * pappcore)
   {

      auto estatus = ::aura::system::initialize_system(pobject, pappcore);

      if (!estatus)
      {

         return estatus;

      }

      //estatus = ::axis::application::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}


      //add_factory_item < ::file::axis::system_dir, ::file::system_dir >();
      //add_factory_item < ::file::axis::system_file, ::file::system_file >();

      //::aura::application * papp = ::get_app(pobject);

      //m_XstrAppId = "axis_system";
      //m_strAppName = "axis_system";
      //m_strBaseSupportId = "axis_system";
      //m_strInstallToken = "axis_system";


      //m_datakey.m_bLocalData = true;

      g_pszCooperativeLevel = "axis";

      m_pDraw2dFactoryExchange = nullptr;

      m_puserstr = nullptr;

      ([a-z0-9_]+)_factory(::factory::factory * pfactory);


      //add_factory_item < ::file::axis::application_dir, ::file::application_dir >();
      //add_factory_item < ::file::axis::application_file, ::file::application_file >();



      return estatus;

   }


   void system::process_init()
   {

      add_factory_item < ::database::field >();

//#ifndef WINDOWS
//
//      i32 error = FT_Init_FreeType((FT_Library *)&m_ftlibrary);
//      if(error)
//      {
//         TRACE("an error occurred during Free Type library initialization");
//         return false;
//      }
//
//#endif

      //enum_display_monitors();

      //if (m_peengine != nullptr)
      //{

      //   m_peengine = memory_new ::exception_engine(this);

      //}


      //if(!::axis::application::process_init())
      //   return false;

      if(!::aura::system::process_init())
         return false;


      //m_spos.create(this);

      auto estatus = create_html();

      //if (m_psystem->m_phtml == nullptr)
      //{

      if (!estatus)
      {

         FATAL("axis::application::process_init .2");

         return false;

      }

      //m_psystem->m_phtml->construct(get_app());

   //}


      return true;

   }


   void system::init1()
   {

      if(!::aura::system::init1())
         return false;

      //if(!::axis::application::init1())
      //   return false;

      Sess(get_app()).m_ptextcontext->defer_ok(m_puserstr);

      return true;

   }


   void system::init2()
   {

      if(!::aura::system::init2())
         return false;

      //if(!::axis::application::init2())
      //   return false;


      return true;

   }


   void system::verb() // ambigous inheritance from ::aura::system/::axis::application
   {

      return ::aura::system::verb();

   }



   void system::init_system()
   {

      if (!::aura::system::init_system())
      {

         return false;

      }

      //if (!::axis::application::init_application())
      //{

      //   return false;

      //}

      return true;

   }


   void system::term()
   {

      //__wait_threading_count_except(this,::duration((5000) * 77));

      if (::ftp::command::info2::g_pTheOneAndOnly != nullptr)
      {

         try
         {

            delete ::ftp::command::info2::g_pTheOneAndOnly;

         }
         catch (...)
         {

            m_result.add(error_failed);

         }

      }


      //try
      //{

      //   if(m_spcrypto.is_set())
      //   {

      //      m_spcrypto.release();

      //   }

      //}
      //catch(...)
      //{

      //   m_result.add(error_failed);

      //}

      //try
      //{

      //   ::axis::application::term();

      //}
      //catch(...)
      //{

      //   m_result.add(error_failed);

      //}

      //try
      //{

      //   if(m_spfile.is_set())
      //   {

      //      m_spfile.release();

      //   }

      //}
      //catch(...)
      //{

      //   m_result.add(error_failed);

      //}

   }


   void system::init()
   {

      //if (!::axis::application::init())
      //{

      //   return false;

      //}

      if (!::aura::system::init())
      {

         return false;

      }

      return true;

   }


   void system::term_system()
   {

//      __wait_threading_count(::duration((5000) * 8));

      //axis::application::term_application();

      //::acme::del(m_phtml);

      try
      {

         ::aura::system::term_system();

      }
      catch(...)
      {

         m_result.add(error_failed);

      }

   }


   bool system::is_system() const
   {

      return true;

   }



   string system::crypto_md5_text(const ::string & str)
   {

      return crypto().md5(str);

   }


   //::pointer<::aura::session>system::on_create_session()
   //{

   //   return __new(::axis::session);

   //}


   void system::on_request(::create * pcreate)
   {

      ::aura::system::on_request(pcreate);

   }


} // namespace axis























#include "framework.h" // from "axis/user/user.h"

//void dappy(const ::string & psz);



namespace axis
{








   //::user::document * system::place_hold(::user::interaction * pinteraction)
   //{


   //   //if(m_pcubeInterface != nullptr)
   //   //{
   //   // return m_pcubeInterface->hold(pinteraction);
   //   //}

   //   return nullptr;

   //}


   //::aura::session * system::query_session(index iEdge)
   //{

   //   return nullptr;

   //}









   void system::hist_hist(const ::string & psz)
   {
   }

   //void system::on_request(::create * pcreate)
   //{

   //   ::axis::system::on_request(pcreate);

   //}

   //::user::interaction_impl * system::impl_from_handle(void * posdata)
   //{

   //   return nullptr;

   //}

   //::user::interaction * system::ui_from_handle(void * posdata)
   //{

   //   return nullptr;

   //}


   string system::url_encode(const ::string & str)
   {

      return m_purldepartment->url_encode(str);

   }



} // namespace axis













