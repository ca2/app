#include "framework.h"
#include "acme/constant/id.h"
#include "axis/networking/email_department.h"
#include "axis/platform/geo_department.h"
#include "acme/platform/profiler.h"
#include "acme/platform/system_setup.h"
#include "axis/constant/idpool.h"
#include "system.h"
#include "axis/account/user_set.h"
#include "session.h"
#include "application.h"
#include "axis/database/database/field.h"


void axis_factory(::factory::factory * pfactory);


//int get_main_screen_rectangle(RECTANGLE_I32 * lprect);

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
CLASS_DECL_AXIS ::user::interaction * create_system_message_window(::particle * pparticle);
#endif


#ifdef LINUX
#include <sys/time.h>
#endif

extern string_map < ::pointer<::acme::library >>* g_pmapLibrary;


CLASS_DECL_AXIS void __simple_tracea(::particle * pparticle, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz);


#ifdef WINDOWS
#define FILE_SYSTEM_CASE_INSENSITIVE 1
#else
#define FILE_SYSTEM_CASE_INSENSITIVE 0
#endif


void os_post_quit();

//extern ::pointer< ::mutex > psystem->m_pmutexLibrary;



#ifdef UNIT_TEST
void unit_test_primitive_var_aura_block();
#endif


void dappy(const ::string & psz);




namespace axis
{





   ::pointer< ::mutex > g_pmutexImage = nullptr;

   ::pointer< ::mutex > get_image_mutex()
   {

      return g_pmutexImage;

   }


   system::system()
   {


      common_construct();

      



   }


   system::~system()
   {

   }


   void system::common_construct()
   {

      m_paxissystem = this;

      ::factory::add_factory_item < ::axis::application, ::apex::application >();
      ::factory::add_factory_item < ::axis::session, ::apex::session >();
      //::factory::add_factory_item < ::axis::idpool, ::acme::idpool >();
      ::factory::add_factory_item < ::geo::department >();
      //add_factory_item < ::imaging >();

      m_bSimpleMessageLoop = false;

      m_bFinalizeIfNoSession = false;
      m_bFinalizeIfNoSessionSetting = true;

      m_bFinalizeIfNoSessionSetting = true;
      m_bFinalizeIfNoSession = false;

   }


   void system::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::aura::system::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __construct_new(m_pemaildepartment);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      axis_factory(::factory::get_factory());

      //return estatus;

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


   void system::process_init()
   {

      //auto estatus = 
      
      ::aura::system::process_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //auto & factorymapsquare = *m_pfactorysquare;

      //auto & pfactorySimpledb = factorymapsquare["simpledb"];

      //if (!pfactorySimpledb)
      //{

      //   estatus = __construct_new(pfactorySimpledb);

      //   if (!estatus)
      //   {

      //      return estatus;

      //   }



      //}

      ::factory::add_factory_item < ::database::field >();

      //return true;

   }

//
//
//
//} // namespace axis
//

   void system::init()
   {

      //auto estatus =
      
      ::aura::system::init();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::init1()
   {

      //auto estatus = 
      
      ::aura::system::init1();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::post_creation_requests()
   {

      //auto estatus =
      
      ::aura::system::post_creation_requests();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::inline_init()
   {

      //::e_status estatus = 
      
      ::aura::system::inline_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void system::inline_term()
   {

      //::e_status estatus =
      
      ::aura::system::inline_term();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_pfactorysquare.release();

      //return estatus;

   }


   void system::init_system()
   {

      //auto estatus =
      
      aura::system::init_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

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


   ::networking::email_department& system::email()
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

         __construct(m_pgeo);

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
//      operating_system_driver::get().m_strSetUserWallpaper = strUrl;
//
//      return true;
//
//   }
//
//   bool system::android_get_user_wallpaper(string & strUrl)
//   {
//
//      operating_system_driver::get()->m_bGetUserWallpaper = true;
//
//      for(int i = 0; i < 10; i++)
//      {
//
//         if (!operating_system_driver::get()->m_bGetUserWallpaper)
//         {
//
//
//         }
//
//         sleep(50_ms);
//
//      }
//
//      strUrl = operating_system_driver::get()->m_strGetUserWallpaper;
//
//      return true;
//
//   }
//
//
//#endif
//

   ::pointer<::account::user_set>system::userset()
   {

      return m_puserset;

   }


//   ::pointer<regex>system::create_regular_expression(const ::string & pszStyle, const string& str)
//   {
//
//      string strStyle(pszStyle);
//
//      if (strStyle.compare_ci("pcre") == 0)
//      {
//
//         return compile_pcre(str);
//
//      }
//
//      return nullptr;
//
//   }
//
//
//   ::pointer<regex_context>system::create_regular_expression_context(const ::string & pszStyle, int iCount)
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






   void system::verb()
   {

      return ::aura::system::verb();

   }



   //CLASS_DECL_AXIS void black_body(float* r, float* g, float* b, ::u32 dwTemp);


   



   void system::init2()
   {

      //auto estatus = 
      
      ::aura::system::init2();

      //if(!estatus)
      //{
      // 
      //   return estatus;

      //}


      //return estatus;

   }


//   void system::assert_ok() const
//   {
//
//      ::thread::assert_ok();
//
//   }
//
//
//   void system::dump(dump_context& context) const
//   {
//
//      ::thread::dump(context);
//
//   }





} // namespace axis



void axis_factory(::factory::factory * pfactory)
{
   
}
