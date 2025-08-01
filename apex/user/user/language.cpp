#include "framework.h"
#include "language.h"
#include "acme/exception/parsing.h"
//#include "acme/operating_system.h"
//#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/string/str.h"


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


   void language::initialize(::particle * pparticle)
   {

      //::e_status estatus = 
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}


      //return estatus;

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

      if (strPo.has_character())
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

//#ifdef WINDOWS_DESKTOP
//
//      int iPo = m_iPo;
//
//      return read_resource_as_string(nullptr, iPo, "PO", bOnlyHeader ? 4096 : -1);
//
//#elif defined(MACOS)
//
//      string strLang = m_strLanguageCode;
//      
//      auto psystem = system();
//
//      ::file::path pathCa2 = psystem->m_pdirectorysystem->m_pathCa2;
//
//      ::file::path path = pathCa2 / "Resources/po" / (strLang + ".po");
//
//      return file_system()->as_string(path, bOnlyHeader ? 4096 : -1);
//
//#else
//
//      string strLang = m_strLanguageCode;
//
//      auto pcontext = m_papplication;
//
//      ::file::path path = pcontext->directory()->module() / "po" / (strLang + ".po");
//
//      return file_system()->as_string(path, bOnlyHeader ? 4096 : -1);
//
//#endif

      throw ::exception(todo);

      return "";

   }


   string language::get_text(const ::scoped_string & scopedstrText)
   {

      string strTranslation = m_stringmap[scopedstrText];

      if (strTranslation.is_empty())
      {

         return scopedstrText;

      }

      return strTranslation;

   }


   bool language::parse_podata(const ::scoped_string & scopedstrPoData, bool bOnlyHeader)
   {

      string strPo = scopedstrPoData;

      strPo.case_insensitive_begins_eat(STR_BOM);

      string_array stra;

      stra.add_lines(strPo);

      int iState = -1;

      string strMsgId;

      string strText;

      avoid_parsing_exception avoidParsingException;

      int iStringCount = 0;

      string strLine;

      bool bOk = false;

      //const_char_pointer psz = nullptr;

      //const_char_pointer pszEnd = nullptr;

      string strName;

      string str;

      string strHeader;

      for (::collection::index i = 0; i < stra.get_count(); i++)
      {

         strLine = stra[i];

         auto range = strLine();

         range.consume_spaces(0);

         try
         {

            strName = range.consume_nc_name();

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

            range.consume_spaces(1);

            str = range.consume_quoted_value_ex();

            i++;

            while (i < stra.get_count())
            {

               strLine = stra[i];

               range = strLine();

               range.consume_spaces(0);

               strName = range.consume_nc_name();

               if (strName.has_character())
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

                        strHeader = range.consume_quoted_value_ex();

                        if (strHeader.has_character())
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

                  range.consume_spaces(0);

                  str += range.consume_quoted_value_ex();

               }

               i++;

            }

            str.replace_with("\n", "\\n");

            if (iState == 0)
            {

               strMsgId = str;

            }
            else if (iState == -1)
            {

               if (iStringCount > 0 || strMsgId.has_character() || strText.has_character())
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



