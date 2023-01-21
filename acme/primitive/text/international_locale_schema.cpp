#include "framework.h"
#include "acme/constant/id.h"
#include "international_locale_schema.h"
#include "acme/primitive/collection/atom_map.h"


namespace text
{


   namespace international
   {


      id_to_id* g_pmapRTL;


      void create_rtl_map()
      {

         g_pmapRTL = memory_new id_to_id;

      }


      locale_schema::locale_schema()
      {

         m_atomSchema = "_std"; // "std"
         m_atomLocale = "_std"; // "std"

         m_idaLocale.allocate(0, 256);
         m_idaSchema.allocate(0, 256);

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


      bool locale_schema::_add_locale_variant(const ::atom& idLocale, const ::atom& idStyle)
      {

         if (::is_empty(idLocale.m_str))
         {

            return false;

         }

         //return _add_locale_variant(idLocale, idStyle);

         return true;

      }


      bool locale_schema::add_locale_variant(const ::atom& idLocale, const ::atom& idSchema)
      {

         if (idLocale.is_empty() || idSchema.is_empty())
         {

            return false;

         }

         if (m_atomLocale.is_empty())
         {

            m_atomLocale = idLocale;

            if (m_atomLocale.is_empty())
            {

               m_atomLocale = "_std";

            }

         }

         if (m_atomSchema.is_empty())
         {

            m_atomSchema = idSchema;

            if (m_atomSchema.is_empty())
            {

               m_atomSchema = "_std";

            }

         }

         ::atom idLocale2 = idLocale;

         ::atom idSchema2 = idSchema;

         if (idLocale2.is_empty() && idSchema2.is_empty())
         {

            return false;

         }

         if (idLocale2.is_empty())
         {

            idLocale2 = m_atomLocale;

         }

         if (idSchema2.is_empty()) {

            idSchema2 = m_atomSchema;

         }


         //if(defer_add_locale(idLocale2, idSchema2))
         //{
         // _add_locale_variant(idLocale2, idSchema2);
         //}

         if (defer_add_locale(idLocale2, idSchema2))
         {
            _add_locale_variant(idLocale2, idSchema2);
         }

         strsize iStart = ::string(idLocale2).length() + 1;
         strsize iEnd;
         strsize iLen;
         string str;
         bool bEnd = false;
         while (!bEnd)
         {
            iEnd = iStart - 1;
            if ((iEnd - 1) < 0)
               break;
            iStart = ::string(idLocale2)(iEnd - 1).rear_find_index('-');
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

            ::atom atomLocale = ::scoped_string(&idLocale2.m_str[iStart], iLen);

            if (defer_add_locale(atomLocale, idSchema2))
            {

               _add_locale_variant(atomLocale, idSchema2);

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


      //::atom locale_schema::localeid(const scoped_string & scopedstrLocale, strsize iLen)
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


      //bool locale_schema::_add_locale_variant(const scoped_string & str, strsize iLen, atom idSchema)
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




      bool locale_schema::defer_add_locale(const ::atom & idLocale, const ::atom& idSchema)
      {



         bool bAdded = false;

         atom idSchema2;

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


      inline ::atom rl_id(const ::atom& atomLocale)
      {

         auto ppair = g_pmapRTL->plookup(atomLocale);

         if (::is_ok(ppair))
         {

            return ppair->element2();

         }

         string str;

         str = atomLocale;

         ::atom idRl = str + "_rl";

         g_pmapRTL->set_at(atomLocale, idRl);

         return idRl;

      }


      bool locale_schema::process_final_locale_schema(bool bRTLLayout)
      {
         static ::atom _std("_std");
         static ::atom _stdRl("_std_rl");

      restart0:

         for (index i = 0; i < m_idaLocale.get_count(); i++)
         {

            ::atom idLocale = m_idaLocale[i];

            if (defer_add_locale(idLocale, idLocale))
               goto restart0;

         }

      restart:
         for (index i = 0; i < m_idaLocale.get_count(); i++)
         {
            string strLocale = m_idaLocale[i];
            if (i >= m_idaSchema.get_count())
               m_idaSchema.add(m_atomSchema);
            ::atom idSchema = m_idaSchema[i];
            auto pFind = strLocale.find("-");
            if (::is_set(pFind))
            {
               ::atom idLocale2 = strLocale(0, pFind);
               if (m_idaLocale.find_first(idLocale2) < 0)
               {
                  m_idaLocale.insert_at(i + 1, idLocale2);
                  m_idaSchema.insert_at(i + 1, idSchema);
                  goto restart;
               }
               idLocale2 = strLocale(pFind + 1);
               if (idLocale2.is_empty() && m_idaLocale.find_first(idLocale2) < 0)
               {
                  m_idaLocale.insert_at(i + 1, idLocale2);
                  m_idaSchema.insert_at(i + 1, idSchema);
                  goto restart;
               }
            }

         }


         comparable_array < ::atom > idaLocaleAdd1;
         comparable_array < ::atom > idaSchemaAdd1;


         if (bRTLLayout)
         {

            idaLocaleAdd1.allocate(0, 256);
            idaSchemaAdd1.allocate(0, 256);

            if (m_idaLocale.get_count() > 256)
            {
               //TRACE("What!!!!!!");
            }

            for (index i = 0; i < m_idaLocale.get_count(); i++)
            {
               ::atom idLocale2 = m_idaLocale[i];
               while (i >= m_idaSchema.get_count())
                  m_idaSchema.add(m_atomSchema);
               ::atom idSchema = m_idaSchema[i];
               if (idSchema != _std)
               {
                  idaLocaleAdd1.add(idLocale2);
                  idaSchemaAdd1.add(rl_id(idSchema));
               }
            }
         }
         if (bRTLLayout)
         {
            for (index i = 0; i < m_idaLocale.get_count(); i++)
            {
               ::atom idLocale2 = m_idaLocale[i];
               if (i >= m_idaSchema.get_count())
                  m_idaSchema.add(_std);
               ::atom idSchema = m_idaSchema[i];
               if (idSchema != _std)
               {
                  idaLocaleAdd1.add(idLocale2);
                  idaSchemaAdd1.add(_stdRl);
               }
            }
         }
         //if(!m_bSchemaOnly)
         //{
         //   for(index i = 0; i < m_idaLocale.get_count(); i++)
         //   {
         //      defer_add_locale(m_idaLocale[i], "std");
         //   }
         //}

         m_idaLocale.append(idaLocaleAdd1);
         m_idaSchema.append(idaSchemaAdd1);

         return true;

      }


      locale_schema& locale_schema::operator = (const locale_schema& ls)
      {

         if (&ls != this)
         {

            m_bSchemaOnly = ls.m_bSchemaOnly;
            m_bAddAlternateStyle = ls.m_bAddAlternateStyle;
            m_atomLocale = ls.m_atomLocale;
            m_atomSchema = ls.m_atomSchema;
            m_idaLocale = ls.m_idaLocale;
            m_idaSchema = ls.m_idaSchema;

         }

         return *this;

      }


#ifdef _DEBUG

      i64 locale_schema::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
      {

         return particle::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }


      i64 locale_schema::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
      {

         return particle::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }


#endif


      //bool locale_schema::_add_locale_variant(const ::atom& idLocale, const ::atom& idStyle)
      //{

      //   if (::is_empty(idLocale.m_str))
      //   {

      //      return false;

      //   }

      //   //return _add_locale_variant(idLocale.m_str, idLocale.m_str.length(), idStyle);

      //   return true;

      //}


      //bool locale_schema::defer_add_locale(const scoped_string& strLocale, strsize iLen, const ::atom& idSchema)
      //{

      //   return defer_add_locale(localeid(pszLocale, iLen), idSchema);

      //}



   }  // namespace international


} // namespace text



