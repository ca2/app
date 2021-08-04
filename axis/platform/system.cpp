#include "framework.h"
#include "aqua/xml.h"
#include "apex/platform/app_core.h"
#include "acme/const/id.h"
#include "acme/platform/profiler.h"
#include "acme/platform/static_setup.h"
#include "axis/const/idpool.h"
//#include "axis/database/sqlitedb/database.h"


void __node_axis_factory_exchange(::factory_map * pfactorymap);


//int GetMainScreenRect(RECTANGLE_I32 * lprect);

//
//const char* g_pszMultimediaLibraryName = nullptr;
//
//
//CLASS_DECL_AXIS void multimedia_set_library_name(const ::string & psz)
//{
//
//   g_pszMultimediaLibraryName = psz;
//
//}


#ifdef CUBE
extern "C"
::acme::library * experience_get_new_library();
#endif


void ___compile_test_sort_array_21304528734();

void enum_display_monitors(::aura::system * psystem);

#ifdef WINDOWS_DESKTOP
CLASS_DECL_AXIS ::user::interaction * create_system_message_window(::object * pobject);
#endif


#ifdef LINUX
#include <sys/time.h>
#endif

extern string_map < __pointer(::acme::library) > * g_pmapLibrary;


CLASS_DECL_AXIS void __simple_tracea(::matter * pobject, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz);


#ifdef WINDOWS
#define FILE_SYSTEM_CASE_INSENSITIVE 1
#else
#define FILE_SYSTEM_CASE_INSENSITIVE 0
#endif


void os_post_quit();

//extern ::mutex * psystem->m_mutexLibrary;



#ifdef UNIT_TEST
void unit_test_primitive_var_aura_block();
#endif


void dappy(const ::string & psz);




namespace axis
{





   ::mutex * g_pmutexImage = nullptr;

   ::mutex * get_image_mutex()
   {

      return g_pmutexImage;

   }


   system::system()
   {

      m_paxissystem = this;

      m_pfactorymapsquare = new string_map < __pointer(::factory_map) >();

      create_factory < ::axis::application, ::application >();
      create_factory < ::axis::session, ::apex::session >();
      create_factory < ::axis::idpool, ::acme::idpool >();
      create_factory < ::geo::department >();

   }


   system::~system()
   {

   }


   void system::common_construct()
   {

      create_factory < ::aura::session >();
      //create_factory < ::imaging >();

      m_bSimpleMessageLoop = false;

      m_bFinalizeIfNoSession = false;
      m_bFinalizeIfNoSessionSetting = true;

      m_bFinalizeIfNoSessionSetting = true;
      m_bFinalizeIfNoSession = false;

   }


   ::e_status system::initialize(::object * pobject)
   {

      auto estatus = ::aura::system::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __compose_new(m_pemaildepartment);

      if (!estatus)
      {

         return estatus;

      }

      __node_axis_factory_exchange(::factory::get_factory_map());

      return estatus;

   }


   void system::on_add_session(::apex::session* papexsession)
   {

      ::aura::system::on_add_session(papexsession);

      if (papexsession->m_iEdge == 0)
      {

         if (!m_paxissession)
         {

            m_paxissession = papexsession->m_paxissession;

         }

      }

      papexsession->m_paxissystem = this;

   }


   ::e_status system::process_init()
   {

      auto estatus = ::aura::system::process_init();

      if (!estatus)
      {

         return estatus;

      }

      auto & factorymapsquare = *m_pfactorymapsquare;

      auto & pfactorySimpledb = factorymapsquare["simpledb"];

      if (!pfactorySimpledb)
      {

         estatus = __construct_new(pfactorySimpledb);

         if (!estatus)
         {

            return estatus;

         }



      }

      create_factory < ::database::field >();

      return true;

   }

//
//
//
//} // namespace axis
//

   ::e_status system::init()
   {

      auto estatus = ::aura::system::init();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::init1()
   {

      auto estatus = ::aura::system::init1();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::post_creation_requests()
   {

      auto estatus = ::aura::system::post_creation_requests();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::inline_init()
   {

      ::e_status estatus = ::aura::system::inline_init();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::inline_term()
   {

      ::e_status estatus = ::aura::system::inline_term();

      if (!estatus)
      {

         return estatus;

      }

      ::acme::del(m_pfactorymapsquare);

      return estatus;

   }


   ::e_status system::init_system()
   {

      auto estatus = aura::system::init_system();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   void system::term()
   {

      ::aura::system::term();

   }


   void system::term1()
   {

      ::aura::system::term1();

   }


   void system::term2()
   {

      ::aura::system::term2();

   }



   void system::term_system()
   {

      ::aura::system::term_system();

   }


   void system::TermSystem()
   {

      ::aura::system::TermSystem();

   }


   void system::process_term()
   {

      ::aura::system::process_term();

   }


   ::net::email_department& system::email()
   {

      return *m_pemaildepartment;

   }



   //::xml::department & system::xml()
   //{

   //   return *m_pxml;

   //}



   ::geo::department& system::geo()
   {

      if (!m_pgeo)
      {

         __compose(m_pgeo);

      }

      return *m_pgeo;

   }


   //void system::on_request(::create * pcreate)
   //{

   //   ::aura::system::on_request(pcreate);


   //}






//#ifdef ANDROID
//
//   bool system::android_set_user_wallpaper(string strUrl)
//   {
//
//      oslocal().m_strSetUserWallpaper = strUrl;
//
//      return true;
//
//   }
//
//   bool system::android_get_user_wallpaper(string & strUrl)
//   {
//
//      oslocal()->m_bGetUserWallpaper = true;
//
//      for(int i = 0; i < 10; i++)
//      {
//
//         if (!oslocal()->m_bGetUserWallpaper)
//         {
//
//
//         }
//
//         sleep(50_ms);
//
//      }
//
//      strUrl = oslocal()->m_strGetUserWallpaper;
//
//      return true;
//
//   }
//
//
//#endif
//

   __pointer(::account::user_set) system::userset()
   {

      return m_puserset;

   }


//   __pointer(regex) system::create_regular_expression(const ::string & pszStyle, const string& str)
//   {
//
//      string strStyle(pszStyle);
//
//      if (strStyle.compare_ci("pcre") == 0)
//      {
//
//         return create_pcre(str);
//
//      }
//
//      return nullptr;
//
//   }
//
//
//   __pointer(regex_context) system::create_regular_expression_context(const ::string & pszStyle, int iCount)
//   {
//
//      string strStyle(pszStyle);
//
//      if (strStyle.compare_ci("pcre") == 0)
//      {
//
//         return create_pcre_context(iCount);
//
//      }
//
//      return nullptr;
//
//   }






   ::e_status system::verb()
   {

      return ::aura::system::verb();

   }



   //CLASS_DECL_AXIS void black_body(float* r, float* g, float* b, ::u32 dwTemp);


   



   ::e_status system::init2()
   {

      auto estatus = ::aura::system::init2();

      if(!estatus)
      {
       
         return estatus;

      }


      return estatus;

   }


   void system::assert_valid() const
   {

      ::thread::assert_valid();

   }


   void system::dump(dump_context& context) const
   {

      ::thread::dump(context);

   }




   __namespace_system_factory(system);


} // namespace axis



void __node_axis_factory_exchange(::factory_map * pfactorymap)
{
   
}
