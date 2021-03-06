#include "framework.h"
#include "acme/filesystem/filesystem/acme_dir.h"


namespace aura
{


   theme::theme()
   {

      m_strTheme = "lite";

   }


   theme::~theme()
   {


   }


   ::e_status theme::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      //estatus = __compose_new(m_prunnerChangeWeatherState);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return estatus;

   }


   void theme::switch_context_theme()
   {

      output_debug_string("changing theme (::aura::theme::switch_contex_theme)\n");

      if (m_straTheme.get_size() <= 0)
      {

         return;

      }

      string strTheme = get_theme();

      strsize iFind = m_straTheme.find_first(strTheme);

      if (iFind < 0)
      {

         iFind = 0;

      }
      else
      {

         iFind++;

         iFind %= m_straTheme.get_size();

      }

      strTheme = m_straTheme[iFind];

      set_context_theme(strTheme);

   }


   void theme::set_context_theme(string strTheme)
   {


      if (strTheme == m_strTheme)
      {

         return;

      }

      string strContextTheme;

      strContextTheme = stored_theme();

      if (strContextTheme != strTheme)
      {

         __pointer(::aura::application) papplication = get_application();

         papplication->app_set("theme-" + get_current_weather(), strTheme);

      }

      m_strTheme = strTheme;

      on_change_theme();

   }



   void theme::on_change_theme()
   {

      string strTheme = get_theme();

      //__throw(todo("core"));
      // Sess(this).userex()->shell()->m_strShellThemePrefix = "desk/" + strTheme + "/";

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

      set_context_theme(stored_theme());

   }


   string theme::get_current_weather()
   {

#ifdef _UWP

      return "";

#endif

      ::file::path pathWeatherState = m_psystem->m_pacmedir->config() / "weather_state.txt";

      auto pcontext = get_context();

      string strState = pcontext->m_papexcontext->file().as_string(pathWeatherState);

      if (strState.is_empty())
      {

         return "";

      }

      string strContext;

      if (strState.contains_ci("night"))
      {

         strContext += ".night";

      }
      else
      {

         strContext += ".day";

      }

      if (strState.contains_ci("cloud") && !strState.contains_ci("partly"))
      {

         strContext += ".dampened";

      }
      else if (strState.contains_ci("rain"))
      {

         strContext += ".dampened";

      }

      return strContext;

   }


   string theme::get_default_theme()
   {

      string strTheme;

      string strWeather = get_current_weather();

      if (strWeather.find_ci(".night") >= 0 && m_straTheme.contains_ci("dark"))
      {

         strTheme = "dark";

      }
      else if (strWeather.find_ci(".dampened") && m_straTheme.contains_ci("blue"))
      {

         strTheme = "blue";

      }
      else if (strWeather.find_ci(".day") && m_straTheme.contains_ci("lite"))
      {

         strTheme = "lite";

      }
      else if (m_straTheme.contains_ci("dark"))
      {

         strTheme = "dark";

      }
      else if (m_straTheme.contains_ci("lite"))
      {

         strTheme = "blue";

      }
      else if (m_straTheme.has_elements())
      {

         strTheme = m_straTheme[0];

      }

      return strTheme;

   }


   string theme::stored_theme()
   {

      string strCurrentWeather = get_current_weather();

      __pointer(::aura::application) papplication = get_application();

      string strTheme = papplication->app_get("theme-" + strCurrentWeather);

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


   void theme::on_change_weather_state()
   {

      ::file::path pathWeatherState = m_psystem->m_pacmedir->config() / "weather_state.txt";

      auto pcontext = get_context();

      string strWeatherState = pcontext->m_papexcontext->file().as_string(pathWeatherState);

      m_strWeatherState = strWeatherState;

      bool bDay = m_strWeatherState.find_ci(".day") >= 0;

      string strDayNight;

      string strDayNightTheme;

      if (bDay)
      {

         strDayNight = "day";

         strDayNightTheme = "lite";

      }
      else
      {

         strDayNight = "night";

         strDayNightTheme = "dark";

      }

      m_strDayNight = strDayNight;

      m_strDayNightTheme = strDayNightTheme;

      __pointer(::aura::application) papplication = get_application();

      if (papplication->m_bContextTheme)
      {

         sync_with_stored_theme();

      }

      try
      {

         for (auto plistener : m_listenera.ptra())
         {

            try
            {

               plistener->on_change_weather_state();

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


   string theme::get_weather_state()
   {

      return m_strWeatherState;

   }


   string theme::get_day_night()
   {

      return m_strDayNight;

   }


   string theme::get_day_night_theme()
   {

      return m_strDayNightTheme;

   }


   ::e_status theme::initialize_contextualized_theme()
   {

      auto & dark = m_mapColors["dark"];
      auto & blue = m_mapColors["blue"];
      auto & lite = m_mapColors["lite"];

      dark = __new(colors());
      blue = __new(colors());
      lite = __new(colors());
      
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

      //__throw(todo("core"));
      //Sess(this).userex()->shell()->m_straThemeableIconName.add("google-android.ico");
      //Sess(this).userex()->shell()->m_straThemeableIconName.add("Folders-OS-Windows-8-Metro.ico");
      //Sess(this).userex()->shell()->m_straThemeableIconName.add("firefox_weather.ico");

      ::file::listing patha;

      auto pcontext = get_context();

      pcontext->m_papexcontext->dir().matter_ls("sphere/theme", patha);

      m_straTheme.add_unique("blue");
      m_straTheme.add_unique("dark");
      m_straTheme.add_unique("lite");

      for (auto& path : patha)
      {

         if (pcontext->m_papexcontext->dir().is(path))
         {

            string strTheme = path.name();

            m_straTheme.add_unique(strTheme);

         }

      }

      sync_with_stored_theme();

      m_watchidWeather = pcontext->m_papexcontext->dir().watcher().add_watch(m_psystem->m_pacmedir->config(), this, false);
      
      on_change_theme();

      return ::success;

   }


   void theme::handle_file_action(::file::action* psubject)
   {

      //if (psubject->m_pathFile.ends_ci("weather_state.txt"))
      //{

      //   (*m_prunnerChangeWeatherState)(millis(300), [this]()
      //      {

      //         on_change_weather_state();

      //      });

      //}

   }


   void theme_listener::on_change_weather_state()
   {


   }


} // namespace sphere



