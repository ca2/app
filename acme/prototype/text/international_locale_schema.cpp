#include "framework.h"
#include "acme/constant/id.h"
#include "international_locale_schema.h"
#include "acme/prototype/collection/atom_map.h"


namespace text
{


   namespace international
   {


      string_to_string* g_pmapRTL;


      void create_rtl_map()
      {

         g_pmapRTL = ___new string_to_string();

      }


      locale_schema::locale_schema()
      {

         m_strSchema = "_std"; // "std"
         m_strLocale = "_std"; // "std"

         m_straLocale.m_countAddUp = 256;
         m_straSchema.m_countAddUp = 256;

         m_bSchemaOnly = false;
         m_bAddAlternateStyle = true;

      }

   
      locale_schema::locale_schema(const locale_schema& ls)
      {

         operator = (ls);

      }


      locale_schema::~locale_schema()
      {
      }


      bool locale_schema::_add_locale_variant(const ::scoped_string& scopedstrLocale, const ::scoped_string& scopedstrStyle)
      {

         if (scopedstrLocale.is_empty())
         {

            return false;

         }

         //return _add_locale_variant(idLocale, idStyle);

         return true;

      }


      bool locale_schema::add_locale_variant(const ::scoped_string& scopedstrLocale, const ::scoped_string& scopedstrSchema)
      {

         if (scopedstrLocale.is_empty() || scopedstrSchema.is_empty())
         {

            return false;

         }

         if (m_strLocale.is_empty())
         {

            m_strLocale = scopedstrLocale;

            if (m_strLocale.is_empty())
            {

               m_strLocale = "_std";

            }

         }

         if (m_strSchema.is_empty())
         {

            m_strSchema = scopedstrSchema;

            if (m_strSchema.is_empty())
            {

               m_strSchema = "_std";

            }

         }

         ::string strLocale2 = scopedstrLocale;

         ::string strSchema2 = scopedstrSchema;

         if (strLocale2.is_empty() && strSchema2.is_empty())
         {

            return false;

         }

         if (strLocale2.is_empty())
         {

            strLocale2 = m_strLocale;

         }

         if (strSchema2.is_empty())
         {

            strSchema2 = m_strSchema;

         }


         //if(defer_add_locale(idLocale2, idSchema2))
         //{
         // _add_locale_variant(idLocale2, idSchema2);
         //}

         if (defer_add_locale(strLocale2, strSchema2))
         {

            _add_locale_variant(strLocale2, strSchema2);

         }

         strsize iStart = strLocale2.length() + 1;
         strsize iEnd;
         strsize iLen;
         string str;
         bool bEnd = false;
         while (!bEnd)
         {
            iEnd = iStart - 1;
            if ((iEnd - 1) < 0)
               break;
            iStart = strLocale2(iEnd - 1).rear_find_index('-');
            bEnd = iStart < 0;
            if (bEnd)
            {
               iStart = 0;
            }
            else
            {
               iStart++;
            }

            iLen = iEnd - iStart;

            ::string strLocale = ::scoped_string(&strLocale2[iStart], iLen);

            if (defer_add_locale(strLocale, strSchema2))
            {

               _add_locale_variant(strLocale, strSchema2);

            }

         }

         return true;

      }


      bool locale_schema::end_prepare(bool bRtlLayout)
      {

         return process_final_locale_schema(bRtlLayout);

      }


      //void locale_schema::end_prepare()
      //{

      //   process_final_locale_schema();

      //}


      //::string locale_schema::localeid(const scoped_string & scopedstrLocale, strsize iLen)
      //{

      //   //if(iLen == 4)
      //   //{
      //   //   char ch1 = pszLocale[0];
      //   //   char ch2 = pszLocale[1];
      //   //   char ch3 = pszLocale[2];
      //   //   char ch4 = pszLocale[3];
      //   //   if(ch1 <= '_')
      //   //   {
      //   //      if(ch2 <= 's')
      //   //      {
      //   //         if(ch3 == 't')
      //   //         {
      //   //            if(ch4 == 'd')
      //   //            {
      //   //               return "_std";
      //   //            }
      //   //         }
      //   //      }
      //   //   }
      //   //}
      //   //else if(iLen == 2 || (iLen == 5 && pszLocale[2] == '-'))
      //   //{
      //   //   char ch1 = pszLocale[0];
      //   //   char ch2 = pszLocale[1];
      //   //   char ch4;
      //   //   char ch5;

      //   //   if(iLen == 5)
      //   //   {
      //   //      ch4 = pszLocale[3];
      //   //      ch5 = pszLocale[4];
      //   //   }
      //   //   else
      //   //   {
      //   //      ch4 = '\0';
      //   //      ch5 = '\0';
      //   //   }

      //   //   if(ch1 <= 'm')
      //   //   {
      //   //      if(ch1 <= 'f')
      //   //      {
      //   //         if(ch1 == 'a')
      //   //         {
      //   //            if(ch2 == 't')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "at";
      //   //               }
      //   //            }
      //   //         }
      //   //         else if(ch1 == 'b')
      //   //         {
      //   //            if(ch2 == 'r')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "br";
      //   //               }
      //   //            }
      //   //         }
      //   //         else if(ch1 == 'c')
      //   //         {
      //   //            if(ch2 == 'n')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "cn";
      //   //               }
      //   //            }
      //   //         }
      //   //         else if(ch1 == 'e')
      //   //         {
      //   //            if(ch2 == 'n')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "en";
      //   //               }
      //   //            }
      //   //            else if(ch2 == 's')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "es";
      //   //               }
      //   //            }
      //   //            else if(ch2 == 'c')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "ec";
      //   //               }
      //   //            }
      //   //         }
      //   //      }
      //   //      else // ch1 >= 'g'
      //   //      {
      //   //         if(ch1 == 'h')
      //   //         {
      //   //            if(ch2 == 'k')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "hk";
      //   //               }
      //   //            }
      //   //         }
      //   //         else if(ch1 == 'j')
      //   //         {
      //   //            if(ch2 == 'a')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "ja";
      //   //               }
      //   //            }
      //   //            else if(ch2 == 'p')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "jp";
      //   //               }
      //   //            }
      //   //         }
      //   //         else if(ch1 == 'm')
      //   //         {
      //   //            if(ch2 == 'x')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "mx";
      //   //               }
      //   //            }
      //   //         }
      //   //      }
      //   //   }
      //   //   else // ch1 >= 'n'
      //   //   {
      //   //      if(ch1 <=  's')
      //   //      {
      //   //         if(ch1 == 'p')
      //   //         {
      //   //            if(ch2 == 't')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "pt";
      //   //               }
      //   //               else if(ch4 == 'b' && ch5 == 'r')
      //   //               {
      //   //                  return "pt_br";
      //   //               }
      //   //            }
      //   //            else if(ch2 == 'e')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "pe";
      //   //               }
      //   //            }
      //   //         }
      //   //      }
      //   //      else // ch1 >= 't'
      //   //      {
      //   //         if(ch1 == 't')
      //   //         {
      //   //            if(ch2 == 'w')
      //   //            {
      //   //               if(iLen == 2)
      //   //               {
      //   //                  return "tw";
      //   //               }
      //   //            }
      //   //         }
      //   //      }
      //   //   }
      //   //}

      //   return ::string(scopedstrLocale, iLen);

      //}


      //bool locale_schema::_add_locale_variant(const scoped_string & str, strsize iLen, string idSchema)
      //{




      //   //if(iLen == 2)
      //   //{
      //   //   char ch1 = psz[0];
      //   //   char ch2 = psz[1];

      //   //   if(ch1 != '-' && ch2 != '-')
      //   //   {

      //   //      string str;

      //   //      str += ch1;

      //   //      str += ch2;

      //   //      str += '-';

      //   //      str += ch1;

      //   //      str += ch2;

      //   //      defer_add_locale(str, idSchema);

      //   //   }

      //   //   if(ch1 == 's' && ch2 == 'e')
      //   //   {
      //   //      defer_add_locale("sv_se", idSchema);
      //   //      defer_add_locale("sv", idSchema);
      //   //   }
      //   //   else if(ch1 == 's' && ch2 == 'v')
      //   //   {
      //   //      defer_add_locale("sv_se", idSchema);
      //   //      defer_add_locale("se", idSchema);
      //   //   }
      //   //   else if(ch1 <= 'm')
      //   //   {
      //   //      if(ch1 == 'a')
      //   //      {
      //   //         if(ch2 == 't')
      //   //         {
      //   //            // at
      //   //            defer_add_locale("de_at", idSchema);
      //   //            defer_add_locale("de", idSchema);
      //   //            defer_add_locale("de_de", idSchema);
      //   //         }
      //   //      }
      //   //      else if(ch1 == 'b')
      //   //      {
      //   //         if(ch2 == 'r')
      //   //         {
      //   //            // br
      //   //            defer_add_locale("pt_br", idSchema);
      //   //            defer_add_locale("pt", idSchema);
      //   //            defer_add_locale("es", idSchema);
      //   //         }
      //   //      }
      //   //      else if(ch1 == 'c')
      //   //      {
      //   //         if(ch2 == 'n')
      //   //         {
      //   //            // cn
      //   //            defer_add_locale("zh_cn", idSchema);
      //   //            defer_add_locale("zh_tw", idSchema);
      //   //         }
      //   //         else if(ch2 == 'a')
      //   //         {
      //   //            // acme
      //   //            defer_add_locale("en_ca", idSchema);
      //   //            defer_add_locale("en", idSchema);
      //   //            defer_add_locale("fr_ca", idSchema);
      //   //            defer_add_locale("fr", idSchema);
      //   //         }
      //   //      }
      //   //      else if(ch1 == 'e')
      //   //      {
      //   //         if(ch2 == 'n')
      //   //         {
      //   //            // en
      //   //            defer_add_locale("en_us", idSchema);
      //   //            defer_add_locale("std", idSchema);
      //   //         }
      //   //         else if(ch2 == 's')
      //   //         {
      //   //            // es
      //   //            defer_add_locale("br", idSchema);
      //   //            defer_add_locale("pt_br", idSchema);
      //   //            defer_add_locale("pt", idSchema);
      //   //         }
      //   //         else if(ch2 == 'c')
      //   //         {
      //   //            defer_add_locale("es", idSchema);
      //   //            defer_add_locale("br", idSchema);
      //   //            defer_add_locale("pt_br", idSchema);
      //   //            defer_add_locale("pt", idSchema);
      //   //         }
      //   //      }
      //   //      else if(ch1 == 'h')
      //   //      {
      //   //         if(ch2 == 'k')
      //   //         {
      //   //            // hk
      //   //            defer_add_locale("zh_cn", idSchema);
      //   //            defer_add_locale("zh_tw", idSchema);
      //   //            defer_add_locale("cn", idSchema);
      //   //         }
      //   //      }
      //   //      else if(ch1 == 'j')
      //   //      {
      //   //         if(ch2 == 'a')
      //   //         {
      //   //            // ja
      //   //            defer_add_locale("ja_jp", idSchema);
      //   //            defer_add_locale("jp", idSchema);
      //   //         }
      //   //         else if(ch2 == 'p')
      //   //         {
      //   //            // jp
      //   //            defer_add_locale("ja_jp", idSchema);
      //   //            defer_add_locale("ja", idSchema);
      //   //         }
      //   //      }
      //   //      else if(ch1 == 'm')
      //   //      {
      //   //         if(ch2 == 'x')
      //   //         {
      //   //            // mx
      //   //            defer_add_locale("es", idSchema);
      //   //            defer_add_locale("br", idSchema);
      //   //            defer_add_locale("pt_br", idSchema);
      //   //            defer_add_locale("pt", idSchema);
      //   //         }
      //   //      }
      //   //   }
      //   //   else
      //   //   {
      //   //      if(ch1 == 'p')
      //   //      {
      //   //         if(ch2 == 't')
      //   //         {
      //   //            // point_i32
      //   //            defer_add_locale("br", idSchema);
      //   //            defer_add_locale("pt_br", idSchema);
      //   //            defer_add_locale("es", idSchema);
      //   //         }
      //   //         else if(ch2 == 'e')
      //   //         {
      //   //            // pe
      //   //            defer_add_locale("es", idSchema);
      //   //            defer_add_locale("br", idSchema);
      //   //            defer_add_locale("pt_br", idSchema);
      //   //            defer_add_locale("pt", idSchema);
      //   //         }
      //   //      }
      //   //      else if(ch1 == 't')
      //   //      {
      //   //         if(ch2 == 'w')
      //   //         {
      //   //            defer_add_locale("zh_tw", idSchema);
      //   //            defer_add_locale("zh_cn", idSchema);
      //   //            defer_add_locale("cn", idSchema);
      //   //         }
      //   //      }
      //   //      else if(ch1 == 'u')
      //   //      {
      //   //         if(ch2 == 'k')
      //   //         {
      //   //            defer_add_locale("en_uk",idSchema);
      //   //            defer_add_locale("en_us",idSchema);
      //   //         }
      //   //      }

      //   //   }
      //   //}

      //   return true;

      //}


      bool locale_schema::defer_add_locale(const ::scoped_string & scopedstrLocale, const ::scoped_string& scopedstrSchema)
      {

         bool bAdded = false;

         ::string strSchema2;

//         if(m_bAddAlternateStyle)
//         {
//
//            idSchema2 = idSchema;
//
//            if(idSchema2 == m_atomSchema && m_atomSchema == m_atomLocale) // if style is a locale and alternate style is locale too
//            {
//               idSchema2 = idLocale;
//            }
//
//            if(idSchema2.is_empty())
//            {
//               idSchema2 = "std";
//            }
//
//            for(i32 i = 0; i < m_idaLocale.get_count() && i < m_idaSchema.get_count(); i++)
//            {
//               if(m_idaLocale[i] == idLocale && m_idaSchema[i] == idSchema2)
//                  goto step2;
//            }
//
//            m_idaLocale.add(idLocale);
//            m_idaSchema.add(idSchema2);
//
//            bAdded = true;
//
//         }
//
//step2:
//
//         idSchema2 = m_atomSchema;
//
//         if(idSchema2.is_empty())
//         {
//            idSchema2 = "std";
//         }
//
//         for(i32 i = 0; i < m_idaLocale.get_count() && i < m_idaSchema.get_count(); i++)
//         {
//            if(m_idaLocale[i] == idLocale && m_idaSchema[i] == idSchema2)
//               return bAdded;
//         }
//
//         m_idaLocale.add(idLocale);
//         m_idaSchema.add(idSchema2);

         return true;

      }


      inline ::string rl_id(const ::scoped_string& scopedstrLocale)
      {

         auto ppair = g_pmapRTL->plookup(scopedstrLocale);

         if (::is_ok(ppair))
         {

            return ppair->element2();

         }

         string str;

         str = scopedstrLocale;

         ::string strRl = str + "_rl";

         g_pmapRTL->set_at(scopedstrLocale, strRl);

         return strRl;

      }


      bool locale_schema::process_final_locale_schema(bool bRTLLayout)
      {
         static auto _std("_std");
         static auto _stdRl("_std_rl");

      restart0:

         for (::collection::index i = 0; i < m_straLocale.get_count(); i++)
         {

            ::string idLocale = m_straLocale[i];

            if (defer_add_locale(idLocale, idLocale))
               goto restart0;

         }

      restart:
         for (::collection::index i = 0; i < m_straLocale.get_count(); i++)
         {
            string strLocale = m_straLocale[i];
            if (i >= m_straSchema.get_count())
               m_straSchema.add(m_strSchema);
            ::string strSchema = m_straSchema[i];
            auto pFind = strLocale.find("-");
            if (::is_set(pFind))
            {
               ::string strLocale2 = strLocale(0, pFind);
               if (strLocale2.has_char() && !m_straLocale.contains(strLocale2))
               {
                  m_straLocale.insert_at(i + 1, strLocale2);
                  m_straSchema.insert_at(i + 1, strSchema);
                  goto restart;
               }
               strLocale2 = strLocale(pFind + 1);
               if (strLocale2.has_char() && !m_straLocale.contains(strLocale2))
               {
                  m_straLocale.insert_at(i + 1, strLocale2);
                  m_straSchema.insert_at(i + 1, strSchema);
                  goto restart;
               }
            }

         }


         ::string_array straLocaleAdd1;
         ::string_array straSchemaAdd1;


         if (bRTLLayout)
         {

            straLocaleAdd1.m_countAddUp = 256;
            straSchemaAdd1.m_countAddUp = 256;

            if (m_straLocale.get_count() > 256)
            {
               //informationf("What!!!!!!");
            }

            for (::collection::index i = 0; i < m_straLocale.get_count(); i++)
            {
               ::string strLocale2 = m_straLocale[i];
               while (i >= m_straSchema.get_count())
                  m_straSchema.add(m_strSchema);
               ::string strSchema = m_straSchema[i];
               if (strSchema != _std)
               {
                  straLocaleAdd1.add(strLocale2);
                  straSchemaAdd1.add(rl_id(strSchema));
               }
            }
         }
         if (bRTLLayout)
         {
            for (::collection::index i = 0; i < m_straLocale.get_count(); i++)
            {
               ::string strLocale2 = m_straLocale[i];
               if (i >= m_straSchema.get_count())
                  m_straSchema.add(_std);
               ::string strSchema = m_straSchema[i];
               if (strSchema != _std)
               {
                  straLocaleAdd1.add(strLocale2);
                  straSchemaAdd1.add(_stdRl);
               }
            }
         }
         //if(!m_bSchemaOnly)
         //{
         //   for(::collection::index i = 0; i < m_idaLocale.get_count(); i++)
         //   {
         //      defer_add_locale(m_idaLocale[i], "std");
         //   }
         //}

         m_straLocale.append(straLocaleAdd1);
         m_straSchema.append(straSchemaAdd1);

         return true;

      }


      locale_schema& locale_schema::operator = (const locale_schema& ls)
      {

         if (&ls != this)
         {

            m_bSchemaOnly = ls.m_bSchemaOnly;
            m_bAddAlternateStyle = ls.m_bAddAlternateStyle;
            m_strLocale = ls.m_strLocale;
            m_strSchema = ls.m_strSchema;
            m_straLocale = ls.m_straLocale;
            m_straSchema = ls.m_straSchema;

         }

         return *this;

      }


#ifdef _DEBUG

      i64 locale_schema::increment_reference_count()
      {

         return particle::increment_reference_count();

      }


      i64 locale_schema::release()
      {

         return particle::release();

      }


#endif


      //bool locale_schema::_add_locale_variant(const ::string& idLocale, const ::string& idStyle)
      //{

      //   if (::is_empty(idLocale.m_str))
      //   {

      //      return false;

      //   }

      //   //return _add_locale_variant(idLocale.m_str, idLocale.m_str.length(), idStyle);

      //   return true;

      //}


      //bool locale_schema::defer_add_locale(const scoped_string& strLocale, strsize iLen, const ::string& idSchema)
      //{

      //   return defer_add_locale(localeid(pszLocale, iLen), idSchema);

      //}



   }  // namespace international


} // namespace text



