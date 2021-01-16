#include "framework.h"



#define STR_BOM "\xEF\xBB\xBF"


namespace user
{


   language::language()
   {

      m_iPo = -1;

      m_stringmap.InitHashTable(257);

      m_stringmapHeader.InitHashTable(257);

      m_bLoadedDefaultResource = false;

      m_bLoadedDefaultResourceHeader = false;

      m_bLoadedDefaultResourceRet = false;

   }


   language::~language()
   {

   }


   ::e_status language::initialize(::layered * pobjectContext)
   {

      ::e_status estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }


      return estatus;

   }


   bool language::defer_load_resource_pofile(bool bOnlyHeader)
   {

      if (m_bLoadedDefaultResource || (bOnlyHeader && m_bLoadedDefaultResourceHeader))
      {

         return m_bLoadedDefaultResourceRet;

      }

      if (bOnlyHeader)
      {

         m_bLoadedDefaultResourceHeader = true;

      }
      else
      {

         m_bLoadedDefaultResourceHeader = true;
         m_bLoadedDefaultResource = true;

      }

      if (m_iPo < 0 || m_strLanguageCode.is_empty())
      {

         return false;

      }

      string strPo = load_podata(bOnlyHeader);

      if (strPo.has_char())
      {

         m_bLoadedDefaultResourceRet = parse_podata(strPo, bOnlyHeader);

      }
      else
      {

         m_bLoadedDefaultResourceRet = false;

      }



      return m_bLoadedDefaultResourceRet;

   }


   string language::load_podata(bool bOnlyHeader)
   {

#ifdef WINDOWS_DESKTOP

      int iPo = m_iPo;

      return read_resource_as_string(nullptr, iPo, "PO", bOnlyHeader ? 4096 : -1);

#elif defined(MACOS)

      string strLang = m_strLanguageCode;

      ::file::path pathCa2 = System.m_pdirsystem->m_pathCa2;

      ::file::path path = pathCa2 / "Resources/po" / (strLang + ".po");

      return file_as_string(path, bOnlyHeader ? 4096 : -1);

#else

      string strLang = m_strLanguageCode;

      ::file::path path = System.dir().module() / "po" / (strLang + ".po");

      return file_as_string(path, bOnlyHeader ? 4096 : -1);

#endif

   }


   string language::get_text(string strText)
   {

      string strTranslation = m_stringmap[strText];

      if (strTranslation.is_empty())
      {

         return strText;

      }

      return strTranslation;

   }


   bool language::parse_podata(string strPoData, bool bOnlyHeader)
   {

      string strPo = strPoData;

      ::str::begins_eat_ci(strPo, STR_BOM);

      string_array stra;

      stra.add_lines(strPo);

      int iState = -1;

      string strMsgId;

      string strText;

      avoid_parsing_exception avoidParsingException;

      int iStringCount = 0;

      string strLine;

      bool bOk = false;

      const char* psz = nullptr;

      const char* pszEnd = nullptr;

      string strName;

      string str;

      string strHeader;

      for (index i = 0; i < stra.get_count(); i++)
      {

         strLine = stra[i];

         psz = strLine;

         pszEnd = psz + strLine.get_length();

         ::str::consume_spaces(psz, 0, pszEnd);

         try
         {

            strName = ::str::consume_nc_name(psz);

            if (strName == "msgid")
            {

               iState = 0;

            }
            else if (strName == "msgstr")
            {

               iState = -1;

            }
            else if (strName.is_empty())
            {

               iState = 1;

            }

            ::str::consume_spaces(psz, 1, pszEnd);

            str = ::str::consume_quoted_value_ex(psz, pszEnd);

            i++;

            while (i < stra.get_count())
            {

               strLine = stra[i];

               psz = strLine;

               pszEnd = psz + strLine.get_length();

               ::str::consume_spaces(psz, 0, pszEnd);

               strName = ::str::consume_nc_name(psz);

               if (strName.has_char())
               {

                  i--;

                  break;

               }

               if (iStringCount == 0)
               {

                  if (iStringCount <= 1)
                  {

                     try
                     {

                        strHeader = ::str::consume_quoted_value_ex(psz, pszEnd);

                        if (strHeader.has_char())
                        {

                           string_array stra;

                           stra.explode(":", strHeader);

                           string& strKey = stra[0];

                           string strVal = stra.slice(1).implode(":");

                           m_stringmapHeader[strKey] = strVal;

                        }

                     }
                     catch (...)
                     {

                        if (iStringCount == 1)
                        {

                           iStringCount = 2;

                        }
                        else
                        {


                        }

                     }

                  }

               }
               else
               {

                  ::str::consume_spaces(psz, 0, pszEnd);

                  str += ::str::consume_quoted_value_ex(psz, pszEnd);

               }

               i++;

            }

            str.replace("\\n", "\n");

            if (iState == 0)
            {

               strMsgId = str;

            }
            else if (iState == -1)
            {

               if (iStringCount > 0 || strMsgId.has_char() || strText.has_char())
               {

                  m_stringmap[strMsgId] = str;

                  bOk = true;

                  if (bOnlyHeader)
                  {

                     if (strMsgId == "IDS_LANGUAGE")
                     {

                        return true;

                     }

                  }

                  iStringCount++;

               }
               else if (iStringCount <= 0)
               {

                  iStringCount = 1;

               }

            }

         }
         catch (...)
         {

         }

      }

      return bOk;

   }


} // namespace user



