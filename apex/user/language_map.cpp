#include "framework.h"


#define STR_BOM "\xEF\xBB\xBF"


namespace user
{


   language_map::language_map()
   {

      m_pintstring = NULL;

      m_pstringmap = NULL;

   }


   language_map::~language_map()
   {


   }


   void language_map::initialize(::object * pobject)
   {

      void estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void language_map::parse_podata(string strPoData)
   {

      m_planguage->parse_podata(strPoData);

   }


   bool language_map::set_language_resource_map(INT_STRING * pintstringLanguageResourceMap)
   {

      m_pintstring = pintstringLanguageResourceMap;

      int i = 0;

      while (m_pintstring[i].m_psz != nullptr)
      {

         string strLanguageCode(m_pintstring[i].m_psz);

         int iResourceId = m_pintstring[i].m_i;

         m_straLang.add(strLanguageCode);

         auto & planguage = m_languagemap[strLanguageCode];

         void estatus = ::success;

         if (planguage.is_null())
         {

            estatus = __construct_new(planguage);

         }

         planguage->m_iPo = iResourceId;

         planguage->m_strLanguageCode = strLanguageCode;

         i++;

      }

      return true;

   }


   string language_map::get_language()
   {

      if (::is_null(m_planguage))
      {

         return "";

      }

      return m_planguage->m_strLanguageCode;

   }


   /// return selected language in the list
   index language_map::get_language_list(string_array & stra)
   {

      return get_text_list(stra, "IDS_LANGUAGE", false);

   }

/// return selected language in the list
   index language_map::get_text_list(string_array & stra, string strId, bool bFull)
   {

      index iSel = -1;

      for (int i = 0; i < m_straLang.get_size(); i++)
      {

         if (m_straLang[i] == m_strLang)
         {

            iSel = i;

         }

      }

      if (iSel < 0)
      {

         iSel = 0;

      }

      for (int i = 0; i < m_straLang.get_size(); i++)
      {

         auto planguage = m_languagemap[m_straLang[i]];

         planguage->defer_load_resource_pofile(!bFull && iSel != i);

         string strText = planguage->m_stringmap[strId];

         stra.add(strText);

      }

      return iSel;

   }


   string_array language_map::get_text_list(string strText, bool bFull)
   {

      string_array stra;

      get_text_list(stra, strText, bFull);

      return stra;

   }

   /*bool language_map::set_language_sel(index iSel)
   {


      if (iSel < 0 ||
            iSel >= m_straLang.get_count())
      {
         return false;
      }

      return set_language(m_straLang[iSel]);

   }*/


   bool language_map::set_default_language(::application * papp)
   {

      if (m_pintstring != NULL)
      {

         if (m_straLang.is_empty())
         {

            return false;

         }

         return set_language(papp, m_straLang[0]);

      }
      else
      {

         return set_language(papp, "_std");

      }

   }


   bool language_map::set_language(::application * papp, string strLang)
   {

      if (strLang.is_empty())
      {

         return false;

      }

      auto & planguage = m_languagemap[strLang];

      void estatus = ::success;

      if (planguage.is_null())
      {

         estatus = __construct_new(planguage);

         planguage->m_strLanguageCode = strLang;

      }

      m_planguage = planguage;

      bool bOk = false;

      if (m_pintstring != NULL)
      {

         bOk = planguage->defer_load_resource_pofile();

      }
      else
      {

         for (index i = papp->m_straMatterLocator.get_upper_bound(); i >= 0; i--)
         {

            string strLocator = papp->m_straMatterLocator[i];

            string_array straMatterLocator;

            straMatterLocator.add(strLocator);

            ::file::path pathApplication = m_pcontext->m_papexcontext->dir().matter_from_locator("stringtable.po", straMatterLocator);

            string strPoData = m_pcontext->m_papexcontext->file().as_string(pathApplication);

            if (strPoData.has_char())
            {

               bOk = true;

            }

            parse_podata(strPoData);

         }

      }

      m_strLang = strLang;

      m_pstringmap = &m_planguage->m_stringmap;

      return bOk;

   }


   string language_map::__get_text(const ::string & strId)
   {

      if (::is_null(m_pstringmap))
      {

         return strId;

      }

      string strText = m_pstringmap->operator[](strId);

      if (strText.is_empty())
      {

         strText = strId;

      }

      //   ::file::path point1 = ::dir::appdata() / ("missing_translation_" + m_planguage->m_strLanguageCode + ".txt");

      //   string str1 = m_psystem->m_pacmefile->as_string(point1);

      //   str1 += "\nmsgid\"" + strId + "\"\n";
      //   str1 += "\nmsgstr\"" + strId + "\"\n";
      //   str1 += "\n";

      //   m_psystem->m_pacmefile->put_contents(point1, str1);

      //   strText = "!" + m_planguage->m_strLanguageCode + ":" + strId;

      //   m_pstringmap.operator[](strId) = strText;

      //}

      return strText;

   }


   string language_map::load_podata(string strLang, bool bOnlyHeader)
   {

      auto planguage = m_languagemap[strLang];

      if (!planguage)
      {

         return "";

      }

      return planguage->load_podata(bOnlyHeader);

   }


} // namespace user



