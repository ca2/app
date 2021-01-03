#pragma once


namespace aura
{

   class CLASS_DECL_AURA theme_listener :
      virtual public context_object
   {
   public:


      virtual void on_change_weather_state();


   };

   class CLASS_DECL_AURA theme :
      virtual public ::object,
      virtual public ::file::listener
   {
   public:


      class CLASS_DECL_AURA colors :
         virtual public ::object
      {
      public:


         color32_t         m_crBg;
         color32_t         m_crIconGlow;
         color32_t         m_crFg;
         color32_t         m_crMg;
         color32_t         m_crBack;
         color32_t         m_crText;


      };


      //__composite(runner)        m_prunnerChangeWeatherState;
      ::file::watch_id           m_watchidWeather;


      string_array                    m_straTheme;
      string                     m_strTheme;
      ::file::path               m_pathTheme;
      string_map < __pointer(colors) >  m_mapColors;
      __pointer(colors)                 m_pcolors;
      __pointer_array(theme_listener)        m_listenera;


      string                     m_strWeatherState;
      string                     m_strDayNight;
      string                     m_strDayNightTheme;


      theme();
      virtual ~theme();


      virtual ::e_status initialize(::layered * pobjectContext) override;


      virtual ::e_status initialize_contextualized_theme();
      virtual void on_change_weather_state();




      virtual string get_weather_state();
      virtual string get_day_night();
      virtual string get_day_night_theme();


      virtual void get_theme_text_color(color32_t& crText, color32_t& crBack);

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
      inline color32_t get_theme_bg_color() { return m_pcolors->m_crBg; }
      inline color32_t get_theme_fg_color() { return m_pcolors->m_crFg; }
      inline color32_t get_theme_mg_color() { return m_pcolors->m_crMg; }
      inline color32_t get_theme_text_color() { return m_pcolors->m_crText; }
      inline color32_t get_theme_icon_glow_color() { return m_pcolors->m_crIconGlow; }


      virtual void handle_file_action(::file::action* psubject) override;

   };

  

} // namespace sphere



