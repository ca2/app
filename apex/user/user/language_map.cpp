#include "framework.h"
#include "language_map.h"
#include "language.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"


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


   void language_map::initialize(::particle * pparticle)
   {

      //::e_status estatus = 
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void language_map::parse_podata(const ::scoped_string & scopedstrPoData)
   {

      m_planguage->parse_podata(scopedstrPoData);

   }


   bool language_map::set_language_resource_map(::int_sz * pintstringLanguageResourceMap)
   {

      m_pintstring = pintstringLanguageResourceMap;

      int i = 0;

      while (m_pintstring[i].m_psz != nullptr)
      {

         string strLanguageCode(m_pintstring[i].m_psz);

         int iResourceId = m_pintstring[i].m_i;

         m_straLang.add(strLanguageCode);

         auto & planguage = m_languagemap[strLanguageCode];

         ::e_status estatus = ::success;

         if (planguage.is_null())
         {

            //estatus =
            __construct_new(planguage);

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
   ::collection::index language_map::get_language_list(string_array & stra)
   {

      return get_text_list(stra, "IDS_LANGUAGE", false);

   }

/// return selected language in the list
   ::collection::index language_map::get_text_list(string_array & stra, const ::scoped_string & scopedstrId, bool bFull)
   {

      ::collection::index iSel = -1;

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

         string strText = planguage->m_stringmap[scopedstrId];

         stra.add(strText);

      }

      return iSel;

   }


   string_array language_map::get_text_list(const ::scoped_string & scopedstrText, bool bFull)
   {

      string_array stra;

      get_text_list(stra, scopedstrText, bFull);

      return stra;

   }

   /*bool language_map::set_language_sel(::collection::index iSel)
   {


      if (iSel < 0 ||
            iSel >= m_straLang.get_count())
      {
         return false;
      }

      return set_language(m_straLang[iSel]);

   }*/


   bool language_map::set_default_language(::apex::application * papp)
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


   bool language_map::set_language(::apex::application * papp, const ::scoped_string & scopedstrLang)
   {

      if (scopedstrLang.is_empty())
      {

         return false;

      }

      auto & planguage = m_languagemap[scopedstrLang];

      ::e_status estatus = ::success;

      if (planguage.is_null())
      {

         //estatus = 
         __construct_new(planguage);

         planguage->m_strLanguageCode = scopedstrLang;

      }

      m_planguage = planguage;

      bool bOk = false;

      if (m_pintstring != NULL)
      {

         bOk = planguage->defer_load_resource_pofile();

      }
      else
      {

         for (::collection::index i = papp->m_straMatterLocator.get_upper_bound(); i >= 0; i--)
         {

            string strLocator = papp->m_straMatterLocator[i];

            string_array straMatterLocator;

            straMatterLocator.add(strLocator);

            ::file::path pathApplication = directory()->matter_from_locator("stringtable.po", straMatterLocator);

            string strPoData = file()->as_string(pathApplication);

            if (strPoData.has_character())
            {

               bOk = true;

            }

            parse_podata(strPoData);

         }

      }

      m_strLang = scopedstrLang;

      m_pstringmap = &m_planguage->m_stringmap;

      return bOk;

   }


   string language_map::__get_text(const ::scoped_string & scopedstrId)
   {

      if (::is_null(m_pstringmap))
      {

         return scopedstrId;

      }

      string strText = m_pstringmap->operator[](scopedstrId);

      if (strText.is_empty())
      {

         strText = scopedstrId;

      }

      //   ::file::path point1 = ::dir::appdata() / ("missing_translation_" + m_planguage->m_strLanguageCode + ".txt");

      //   string str1 = file_system()->as_string(point1);

      //   str1 += "\nmsgid\"" + strId + "\"\n";
      //   str1 += "\nmsgstr\"" + strId + "\"\n";
      //   str1 += "\n";

      //   file_system()->put_contents(point1, str1);

      //   strText = "!" + m_planguage->m_strLanguageCode + ":" + strId;

      //   m_pstringmap.operator[](strId) = strText;

      //}

      return strText;

   }


   string language_map::load_podata(const ::scoped_string & scopedstrLang, bool bOnlyHeader)
   {

      auto planguage = m_languagemap[scopedstrLang];

      if (!planguage)
      {

         return "";

      }

      return planguage->load_podata(bOnlyHeader);

   }


} // namespace user



