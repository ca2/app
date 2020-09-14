#include "framework.h" 
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple_ui/_simple_ui.h"
#endif


namespace simple_ui
{


   style::style()
   {

      m_etheme = ::user::theme_dark;

   }

   style::~style()
   {

   }


   string style::calc_locale()
   {

#if defined(WINDOWS_DESKTOP)
      string strLocale;
      LANGID langid = ::GetUserDefaultLangID();
#define SPR_DEUTSCH LANG_GERMAN
      if (langid == LANG_SWEDISH)
      {
         strLocale = "se";
      }
      else if (langid == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN))
      {
         strLocale = "point-br";
      }
      else if (PRIMARYLANGID(langid) == SPR_DEUTSCH)
      {
         strLocale = "de";
      }
      else if (PRIMARYLANGID(langid) == LANG_ENGLISH)
      {
         strLocale = "en";
      }
      else if (PRIMARYLANGID(langid) == LANG_JAPANESE)
      {
         strLocale = "jp";
      }
      else if (PRIMARYLANGID(langid) == LANG_POLISH)
      {
         strLocale = "pl";
      }
      else
      {

         strLocale = "_std";
         
      }

      return strLocale;
#else

      return "se";
#endif

   }

   string style::calc_schema()
   {

      return calc_locale();

   }


   string style::defer_get_plugin()
   {

      return "";

   }


   string style::defer_get(const char * pszUrl)
   {

      string str;

      i32 iAttempt = 0;

   restart:

      defer_get_plugin();

      try
      {

         url_query_get_param(m_strLocale, "locale", str);

      }
      catch (...)
      {
      }

      try
      {

         url_query_get_param(m_strSchema, "schema", str);

      }
      catch (...)
      {
      }

      try
      {

         url_query_get_param(m_strRuri, "ruri", str);

      }
      catch (...)
      {

      }

      if (m_strLocale.is_empty())
      {
         iAttempt++;

         if (iAttempt > 3)
            goto default_case;

         goto restart;

      }

   default_case:

      //xxdebug_box("plugin::defer_get not logged", "defer get", 0);

      if (ansi_begins_ci(m_strSchema, "darker;") || ansi_ends_ci(m_strSchema, ";darker") || ansi_find_string_ci(m_strSchema, ";darker;")
         || ansi_begins_ci(m_strSchema, "darker%3B") || ansi_ends_ci(m_strSchema, "%3Bdarker") || ansi_find_string_ci(m_strSchema, "%3Bdarker%3B"))
      {

         m_etheme = ::user::theme_dark;

      }
      else
      {

         m_etheme = ::user::theme_lite;

      }

      if (m_strLocale.is_empty())
      {

         m_strLocale = calc_locale();

      }

      if (m_strSchema.is_empty())
      {

         m_strSchema = calc_schema();

      }

      return Application.http_get_locale_schema(pszUrl,m_strLocale,m_strSchema);

   }


} // namespace simple_ui


