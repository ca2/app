#include "framework.h"
#include "theme.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/watcher/watch.h"
#include "acme/filesystem/watcher/watcher.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/platform/application.h"


namespace aura
{


   theme::theme()
   {

   }


   theme::~theme()
   {


   }


   void theme::initialize(::particle * pparticle)
   {

      ::object::initialize(pparticle);

      defer_create_synchronization();

   }


   void theme::switch_context_theme()
   {

      informationf("changing theme (::aura::theme::switch_contex_theme)\n");

      if (m_straTheme.get_size() <= 0)
      {

         return;

      }

      string strTheme = get_theme();

      auto iFind = m_straTheme.find_first(strTheme);

      if (not_found(iFind))
      {

         iFind = 0;

      }
      else
      {

         iFind++;

         iFind %= m_straTheme.get_size();

      }

      strTheme = m_straTheme[iFind];

      set_context_theme(strTheme, ::e_source_user);

   }


   void theme::set_context_theme(const ::scoped_string & scopedstrTheme, const ::action_context & actioncontext)
   {

      if (scopedstrTheme == m_strTheme)
      {

         return;

      }

      if (actioncontext.is_user_source())
      {

         string strContextTheme;

         strContextTheme = stored_theme();

         if (strContextTheme != scopedstrTheme)
         {

            ::pointer<::aura::application>papp = get_app();

            papp->app_set("theme-" + get_current_ambient(), scopedstrTheme);

            //papp->app_set("theme-" + get_current_weather(), strTheme);

         }

      }

      m_strTheme = scopedstrTheme;

      on_change_theme();

   }


   void theme::on_change_theme()
   {

      string strTheme = get_theme();

      //throw ::exception(todo("core"));
      // Sess(this).userex()->shell()->m_strShellThemePrefix = "app_core_desk/" + strTheme + "/";

      m_pcolors = m_mapColors[strTheme];

      m_pathTheme = ::file::path("theme") / get_theme();

      //auto applicationa = psystem->m_applicationa;

      //for (auto & papp : applicationa)
      //{

      //   papp->on_change_theme();

      //}

   }




   ::file::path theme::get_theme_path()
   {

      return m_pathTheme;

   }


   void theme::get_theme_text_color(::color::color & colorText, ::color::color & colorBack)
   {

      colorText = get_theme_text_color();

      colorBack = get_theme_icon_glow_color();

   }



   void theme::sync_with_stored_theme()
   {

      set_context_theme(stored_theme(), ::e_source_sync);

   }


//   string theme::get_current_weather()
//   {
//
//#ifdef UNIVERSAL_WINDOWS
//
//      return "";
//
//#endif
//
//      ::file::path pathWeatherState = directory_system()->config() / "weather_state.txt";
//
//      // auto pcontext = get_context();
//
//      string strState = file()->safe_get_string(pathWeatherState);
//
//      if (strState.is_empty())
//      {
//
//         return "";
//
//      }
//
//      string strContext;
//
//      if (strState.case_insensitive_contains("night"))
//      {
//
//         strContext += ".night";
//
//      }
//      else
//      {
//
//         strContext += ".day";
//
//      }
//
//      if (strState.case_insensitive_contains("cloud") && !strState.case_insensitive_contains("partly"))
//      {
//
//         strContext += ".dampened";
//
//      }
//      else if (strState.case_insensitive_contains("rain"))
//      {
//
//         strContext += ".dampened";
//
//      }
//
//      return strContext;
//
//   }


   string theme::get_current_ambient()
   {

#ifdef UNIVERSAL_WINDOWS

      return "";

#endif

      auto path = directory_system()->home() / ".ambient/ambient.txt";

      // auto pcontext = get_context();

      string strState = file()->safe_get_string(path);

      if (strState.is_empty())
      {

         return "lite";

      }

      return strState;

   }


   //string theme::get_default_theme()
   //{

   //   string strTheme;

   //   string strWeather = get_current_weather();

   //   if (strWeather.case_insensitive_contains(".night") && m_straTheme.case_insensitive_contains("dark"))
   //   {

   //      strTheme = "dark";

   //   }
   //   else if (strWeather.case_insensitive_contains(".dampened") && m_straTheme.case_insensitive_contains("blue"))
   //   {

   //      strTheme = "blue";

   //   }
   //   else if (strWeather.case_insensitive_contains(".day") && m_straTheme.case_insensitive_contains("lite"))
   //   {

   //      strTheme = "lite";

   //   }
   //   else if (m_straTheme.case_insensitive_contains("dark"))
   //   {

   //      strTheme = "dark";

   //   }
   //   else if (m_straTheme.case_insensitive_contains("lite"))
   //   {

   //      strTheme = "blue";

   //   }
   //   else if (m_straTheme.has_elements())
   //   {

   //      strTheme = m_straTheme[0];

   //   }

   //   return strTheme;

   //}


   string theme::get_default_theme()
   {

      string strTheme;

      string strAmbient = get_current_ambient();

      strTheme = strAmbient;

      return strTheme;

   }


   //string theme::stored_theme()
   //{

   //   string strCurrentWeather = get_current_weather();

   //   ::pointer<::aura::application>papp = get_app();

   //   string strTheme = papp->app_get("theme-" + strCurrentWeather);

   //   if (strTheme.is_empty())
   //   {

   //      strTheme = get_default_theme();

   //   }

   //   return strTheme;

   //}



   string theme::stored_theme()
   {

      string strCurrentAmbient = get_current_ambient();

      ::pointer<::aura::application>papp = get_app();

      string strTheme = papp->app_get("theme-" + strCurrentAmbient);

      if (strTheme.is_empty())
      {

         strTheme = get_default_theme();

      }

      return strTheme;

   }


   string theme::get_theme()
   {

      return m_strTheme;

   }


   //void theme::on_change_weather_state()
   //{

   //   ::file::path pathWeatherState = directory_system()->config() / "weather_state.txt";

   //   // auto pcontext = get_context();

   //   string strWeatherState = file()->safe_get_string(pathWeatherState);

   //   m_strWeatherState = strWeatherState;

   //   bool bDay = m_strWeatherState.case_insensitive_contains(".day");

   //   string strDayNight;

   //   string strDayNightTheme;

   //   if (bDay)
   //   {

   //      strDayNight = "day";

   //      strDayNightTheme = "lite";

   //   }
   //   else
   //   {

   //      strDayNight = "night";

   //      strDayNightTheme = "dark";

   //   }

   //   m_strDayNight = strDayNight;

   //   m_strDayNightTheme = strDayNightTheme;

   //   ::pointer<::aura::application>papp = get_app();

   //   if (papp->m_bContextTheme)
   //   {

   //      sync_with_stored_theme();

   //   }

   //   try
   //   {

   //      for (auto plistener : m_listenera)
   //      {

   //         try
   //         {

   //            plistener->on_change_weather_state();

   //         }
   //         catch (...)
   //         {

   //         }

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //}

   void theme::defer_check_ambient_change()
   {

      _synchronous_lock synchronous_lock(this->synchronization());

      ::file::path pathAmbient = directory_system()->home() / ".ambient/ambient.txt";

      string strAmbientState = file()->safe_get_string(pathAmbient);

      if (strAmbientState != m_strAmbientState
         || m_strAmbientState.is_empty())
      {

         if (strAmbientState.is_empty())
         {

            strAmbientState = "lite";

         }

         m_strAmbientState = strAmbientState;

         synchronous_lock.unlock();

         ::pointer<::aura::application>papp = get_app();

         if (papp->m_bContextTheme)
         {

            sync_with_stored_theme();

         }

         try
         {

            for (auto plistener : m_listenera)
            {

               try
               {

                  //plistener->on_change_weather_state();

                  plistener->on_change_ambient();

               }
               catch (...)
               {

               }

            }

         }
         catch (...)
         {

         }

      }

   }


   ::string theme::get_ambient()
   {

      return m_strAmbientState;

   }


   //string theme::get_weather_state()
   //{

   //   return m_strWeatherState;

   //}


   //string theme::get_day_night()
   //{

   //   return m_strDayNight;

   //}


   //string theme::get_day_night_theme()
   //{

   //   return m_strDayNightTheme;

   //}


   void theme::initialize_contextualized_theme()
   {

      auto & dark = m_mapColors["dark"];
      auto & blue = m_mapColors["blue"];
      auto & lite = m_mapColors["lite"];

      dark = __allocate colors();
      blue = __allocate colors();
      lite = __allocate colors();
      
      m_pcolors = lite;

      dark->m_colorBg = argb(160, 0x16, 0x19, 0x1e);
      blue->m_colorBg = argb(160, 0x50, 0x58, 0x88);
      lite->m_colorBg = argb(160, 0xff, 0xff, 0xff);

      dark->m_colorIconGlow = argb(255, 0x16, 0x19, 0x1e);
      blue->m_colorIconGlow = argb(255, 0x40, 0x58, 0x68);
      lite->m_colorIconGlow = argb(255, 0xff, 0xff, 0xff);

      dark->m_colorMg = argb(151, 0x16, 0x19, 0x1e);
      blue->m_colorMg = argb(151, 0xA0, 0xA8, 0xB8);
      lite->m_colorMg = argb(140, 255, 255, 255);

      dark->m_colorFg = argb(255, 223, 223, 208);
      blue->m_colorFg = argb(255, 255, 255, 255);
      lite->m_colorFg = argb(255, 0, 0, 0);

      dark->m_colorText = argb(255, 155, 155, 155);
      blue->m_colorText = argb(255, 55, 50, 80);
      lite->m_colorText = argb(255, 0, 0, 0);

      dark->m_colorBack = argb(160, 0, 0, 0);
      blue->m_colorBack = argb(160, 205, 200, 250);
      lite->m_colorBack = argb(160, 255, 255, 255);

      //throw ::exception(todo("core"));
      //Sess(this).userex()->shell()->m_straThemeableIconName.add("google-android.ico");
      //Sess(this).userex()->shell()->m_straThemeableIconName.add("Folders-OS-Windows-8-Metro.ico");
      //Sess(this).userex()->shell()->m_straThemeableIconName.add("firefox_weather.ico");

      ::file::listing_base patha;

      // auto pcontext = get_context();

      directory()->matter_enumerate("sphere/theme", patha);

      m_straTheme.add_unique("blue");
      m_straTheme.add_unique("dark");
      m_straTheme.add_unique("lite");

      for (auto& path : patha)
      {

         if (directory()->is(path))
         {

            string strTheme = path.name();

            m_straTheme.add_unique(strTheme);

         }

      }

      sync_with_stored_theme();

      auto pathFolder = directory_system()->home() / ".ambient";

      directory_system()->create(pathFolder);

      m_pfilewatchWeather = file_watcher()->add_watch(pathFolder, this, false);
      
      defer_check_ambient_change();

      //return ::success;

   }


   void theme::operator()(::file::action* ptopic)
   {

      if (ptopic->m_pathFile.case_insensitive_ends("ambient.txt"))
      {

         application()->fork([this]()
            {

               preempt(1_s);

               defer_check_ambient_change();

            });

      }

   }


   void theme_listener::on_change_ambient()
   {


   }


} // namespace sphere



