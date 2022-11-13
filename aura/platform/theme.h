#pragma once


#include "acme/primitive/primitive/object.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/primitive/collection/string_array.h"
#include "acme/primitive/collection/string_map.h"
#include "apex/filesystem/file/listener.h"


namespace aura
{

   class CLASS_DECL_AURA theme_listener :
      virtual public object
   {
   public:


      virtual void on_change_weather_state();


   };

   class CLASS_DECL_AURA theme :
      virtual public ::object,
      virtual public ::file::listener::base
   {
   public:


      class CLASS_DECL_AURA colors :
         virtual public ::object
      {
      public:


         ::color::color        m_colorBg;
         ::color::color        m_colorIconGlow;
         ::color::color        m_colorFg;
         ::color::color        m_colorMg;
         ::color::color        m_colorBack;
         ::color::color        m_colorText;


      };


      //::pointer<runner>                    m_prunnerChangeWeatherState;
      ::file::watch_id                       m_watchidWeather;


      string_array                           m_straTheme;
      string                                 m_strTheme;
      ::file::path                           m_pathTheme;
      string_map < ::pointer < colors > >    m_mapColors;
      ::pointer < colors >                   m_pcolors;
      pointer_array < theme_listener >       m_listenera;


      string                                 m_strWeatherState;
      string                                 m_strDayNight;
      string                                 m_strDayNightTheme;


      theme();
      ~theme() override;


      virtual void initialize(::particle * pparticle) override;


      virtual void initialize_contextualized_theme();
      virtual void on_change_weather_state();




      virtual string get_weather_state();
      virtual string get_day_night();
      virtual string get_day_night_theme();


      virtual void get_theme_text_color(::color::color & colorText, ::color::color & colorBack);

      virtual void sync_with_stored_theme();
      virtual string get_current_weather();
      virtual string get_default_theme();
      virtual string stored_theme();

      virtual void switch_context_theme();
      virtual void set_context_theme(string strTheme);
      virtual void on_change_theme();

      virtual string get_theme();


      virtual ::file::path   get_theme_path();

      

      
      ////////-----***!!!
      //
      //   CRASH!!!???
      //
      //   Is initialize_contextualized_theme called from aura::application
      //
      inline ::color::color get_theme_bg_color() { return m_pcolors->m_colorBg; }
      inline ::color::color get_theme_fg_color() { return m_pcolors->m_colorFg; }
      inline ::color::color get_theme_mg_color() { return m_pcolors->m_colorMg; }
      inline ::color::color get_theme_text_color() { return m_pcolors->m_colorText; }
      inline ::color::color get_theme_icon_glow_color() { return m_pcolors->m_colorIconGlow; }


      virtual void operator()(::file::action* ptopic) override;

   };

  

} // namespace sphere



