#include "framework.h"
#include "acme/constant/id.h"



namespace str
{


   namespace international
   {

      ::map < ::atom, const ::atom &, ::atom, const ::atom & > * g_pmapRTL;

      void create_rtl_map()
      {

         g_pmapRTL = aaa_primitive_new ::map < ::atom,const ::atom &,::atom,const ::atom & >();

      }

      locale_schema::locale_schema()
      {

         m_atomSchema = "_std"; // __id(std)
         m_atomLocale = "_std"; // __id(std)

         m_idaLocale.allocate(0, 256);
         m_idaSchema.allocate(0, 256);

         m_bSchemaOnly           = false;
         m_bAddAlternateStyle    = true;

      }

      locale_schema::locale_schema(const locale_schema & ls)
      {

         operator = (ls);

      }


      locale_schema::~locale_schema()
      {
      }


      bool locale_schema::add_locale_variant(atom idLocale, atom idSchema)
      {

         if(m_atomLocale.is_empty())
         {
            m_atomLocale = idLocale;
            if(m_atomLocale.is_empty())
               m_atomLocale = "_std";
         }

         if(m_atomSchema.is_empty())
         {
            m_atomSchema = idSchema;
            if(m_atomSchema.is_empty())
               m_atomSchema = "_std";
         }

         atom idLocale2 = idLocale;
         atom idSchema2 = idSchema;

         if((idLocale2.is_empty() ) && (idSchema2.is_empty() ))
            return false;

         if(idLocale2.is_empty() )
            idLocale2 = m_atomLocale;

         if(idSchema2.is_empty() )
            idSchema2 = m_atomSchema;


         //if(defer_add_locale(idLocale2, idSchema2))
         //{
         // _add_locale_variant(idLocale2, idSchema2);
         //}

         if(defer_add_locale(idLocale2, idSchema2))
         {
            _add_locale_variant(idLocale2, idSchema2);
         }

         character_count iStart =idLocale2.str().get_length() + 1;
         character_count iEnd;
         character_count iLen;
         string str;
         bool bEnd = false;
         while(!bEnd)
         {
            iEnd = iStart - 1;
            if((iEnd - 1) < 0)
               break;
            iStart = idLocale2.str().rear_find('-', iEnd - 1);
            bEnd = iStart < 0;
            if(bEnd)
            {
               iStart = 0;
            }
            else
            {
               iStart++;
            }
            iLen = iEnd - iStart;
            ::atom atom = localeid(&idLocale2.m_psz[iStart], iLen);
            if(defer_add_locale(atom, idSchema2))
            {
               _add_locale_variant(atom, idSchema2);
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


      ::atom locale_schema::localeid(const ::scoped_string & scopedstrLocale, character_count iLen)
      {

         //if(iLen == 4)
         //{
         //   char ch1 = pszLocale[0];
         //   char ch2 = pszLocale[1];
         //   char ch3 = pszLocale[2];
         //   char ch4 = pszLocale[3];
         //   if(ch1 <= '_')
         //   {
         //      if(ch2 <= 's')
         //      {
         //         if(ch3 == 't')
         //         {
         //            if(ch4 == 'd')
         //            {
         //               return "_std";
         //            }
         //         }
         //      }
         //   }
         //}
         //else if(iLen == 2 || (iLen == 5 && pszLocale[2] == '-'))
         //{
         //   char ch1 = pszLocale[0];
         //   char ch2 = pszLocale[1];
         //   char ch4;
         //   char ch5;

         //   if(iLen == 5)
         //   {
         //      ch4 = pszLocale[3];
         //      ch5 = pszLocale[4];
         //   }
         //   else
         //   {
         //      ch4 = '\0';
         //      ch5 = '\0';
         //   }

         //   if(ch1 <= 'm')
         //   {
         //      if(ch1 <= 'f')
         //      {
         //         if(ch1 == 'a')
         //         {
         //            if(ch2 == 't')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(at);
         //               }
         //            }
         //         }
         //         else if(ch1 == 'b')
         //         {
         //            if(ch2 == 'r')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(br);
         //               }
         //            }
         //         }
         //         else if(ch1 == 'c')
         //         {
         //            if(ch2 == 'n')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(cn);
         //               }
         //            }
         //         }
         //         else if(ch1 == 'e')
         //         {
         //            if(ch2 == 'n')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(en);
         //               }
         //            }
         //            else if(ch2 == 's')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(es);
         //               }
         //            }
         //            else if(ch2 == 'c')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(ec);
         //               }
         //            }
         //         }
         //      }
         //      else // ch1 >= 'g'
         //      {
         //         if(ch1 == 'h')
         //         {
         //            if(ch2 == 'k')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(hk);
         //               }
         //            }
         //         }
         //         else if(ch1 == 'j')
         //         {
         //            if(ch2 == 'a')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(ja);
         //               }
         //            }
         //            else if(ch2 == 'p')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(jp);
         //               }
         //            }
         //         }
         //         else if(ch1 == 'm')
         //         {
         //            if(ch2 == 'x')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(mx);
         //               }
         //            }
         //         }
         //      }
         //   }
         //   else // ch1 >= 'n'
         //   {
         //      if(ch1 <=  's')
         //      {
         //         if(ch1 == 'p')
         //         {
         //            if(ch2 == 't')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(pt);
         //               }
         //               else if(ch4 == 'b' && ch5 == 'r')
         //               {
         //                  return __id(pt_br);
         //               }
         //            }
         //            else if(ch2 == 'e')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(pe);
         //               }
         //            }
         //         }
         //      }
         //      else // ch1 >= 't'
         //      {
         //         if(ch1 == 't')
         //         {
         //            if(ch2 == 'w')
         //            {
         //               if(iLen == 2)
         //               {
         //                  return __id(tw);
         //               }
         //            }
         //         }
         //      }
         //   }
         //}

         return string(scopedstrLocale, iLen);
      }


      bool locale_schema::_add_locale_variant(const ::scoped_string & scopedstr, character_count iLen, atom idSchema)
      {




         //if(iLen == 2)
         //{
         //   char ch1 = psz[0];
         //   char ch2 = psz[1];

         //   if(ch1 != '-' && ch2 != '-')
         //   {

         //      string str;

         //      str += ch1;

         //      str += ch2;

         //      str += '-';

         //      str += ch1;

         //      str += ch2;

         //      defer_add_locale(str, idSchema);

         //   }

         //   if(ch1 == 's' && ch2 == 'e')
         //   {
         //      defer_add_locale(__id(sv_se), idSchema);
         //      defer_add_locale(__id(sv), idSchema);
         //   }
         //   else if(ch1 == 's' && ch2 == 'v')
         //   {
         //      defer_add_locale(__id(sv_se), idSchema);
         //      defer_add_locale(__id(se), idSchema);
         //   }
         //   else if(ch1 <= 'm')
         //   {
         //      if(ch1 == 'a')
         //      {
         //         if(ch2 == 't')
         //         {
         //            // at
         //            defer_add_locale(__id(de_at), idSchema);
         //            defer_add_locale(__id(de), idSchema);
         //            defer_add_locale(__id(de_de), idSchema);
         //         }
         //      }
         //      else if(ch1 == 'b')
         //      {
         //         if(ch2 == 'r')
         //         {
         //            // br
         //            defer_add_locale(__id(pt_br), idSchema);
         //            defer_add_locale(__id(pt), idSchema);
         //            defer_add_locale(__id(es), idSchema);
         //         }
         //      }
         //      else if(ch1 == 'c')
         //      {
         //         if(ch2 == 'n')
         //         {
         //            // cn
         //            defer_add_locale(__id(zh_cn), idSchema);
         //            defer_add_locale(__id(zh_tw), idSchema);
         //         }
         //         else if(ch2 == 'a')
         //         {
         //            // acme
         //            defer_add_locale(__id(en_ca), idSchema);
         //            defer_add_locale(__id(en), idSchema);
         //            defer_add_locale(__id(fr_ca), idSchema);
         //            defer_add_locale(__id(fr), idSchema);
         //         }
         //      }
         //      else if(ch1 == 'e')
         //      {
         //         if(ch2 == 'n')
         //         {
         //            // en
         //            defer_add_locale(__id(en_us), idSchema);
         //            defer_add_locale(__id(std), idSchema);
         //         }
         //         else if(ch2 == 's')
         //         {
         //            // es
         //            defer_add_locale(__id(br), idSchema);
         //            defer_add_locale(__id(pt_br), idSchema);
         //            defer_add_locale(__id(pt), idSchema);
         //         }
         //         else if(ch2 == 'c')
         //         {
         //            defer_add_locale(__id(es), idSchema);
         //            defer_add_locale(__id(br), idSchema);
         //            defer_add_locale(__id(pt_br), idSchema);
         //            defer_add_locale(__id(pt), idSchema);
         //         }
         //      }
         //      else if(ch1 == 'h')
         //      {
         //         if(ch2 == 'k')
         //         {
         //            // hk
         //            defer_add_locale(__id(zh_cn), idSchema);
         //            defer_add_locale(__id(zh_tw), idSchema);
         //            defer_add_locale(__id(cn), idSchema);
         //         }
         //      }
         //      else if(ch1 == 'j')
         //      {
         //         if(ch2 == 'a')
         //         {
         //            // ja
         //            defer_add_locale(__id(ja_jp), idSchema);
         //            defer_add_locale(__id(jp), idSchema);
         //         }
         //         else if(ch2 == 'p')
         //         {
         //            // jp
         //            defer_add_locale(__id(ja_jp), idSchema);
         //            defer_add_locale(__id(ja), idSchema);
         //         }
         //      }
         //      else if(ch1 == 'm')
         //      {
         //         if(ch2 == 'x')
         //         {
         //            // mx
         //            defer_add_locale(__id(es), idSchema);
         //            defer_add_locale(__id(br), idSchema);
         //            defer_add_locale(__id(pt_br), idSchema);
         //            defer_add_locale(__id(pt), idSchema);
         //         }
         //      }
         //   }
         //   else
         //   {
         //      if(ch1 == 'p')
         //      {
         //         if(ch2 == 't')
         //         {
         //            // point
         //            defer_add_locale(__id(br), idSchema);
         //            defer_add_locale(__id(pt_br), idSchema);
         //            defer_add_locale(__id(es), idSchema);
         //         }
         //         else if(ch2 == 'e')
         //         {
         //            // pe
         //            defer_add_locale(__id(es), idSchema);
         //            defer_add_locale(__id(br), idSchema);
         //            defer_add_locale(__id(pt_br), idSchema);
         //            defer_add_locale(__id(pt), idSchema);
         //         }
         //      }
         //      else if(ch1 == 't')
         //      {
         //         if(ch2 == 'w')
         //         {
         //            defer_add_locale(__id(zh_tw), idSchema);
         //            defer_add_locale(__id(zh_cn), idSchema);
         //            defer_add_locale(__id(cn), idSchema);
         //         }
         //      }
         //      else if(ch1 == 'u')
         //      {
         //         if(ch2 == 'k')
         //         {
         //            defer_add_locale(__id(en_uk),idSchema);
         //            defer_add_locale(__id(en_us),idSchema);
         //         }
         //      }

         //   }
         //}

         return true;

      }




      bool locale_schema::defer_add_locale(atom idLocale, atom idSchema)
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
//               idSchema2 = __id(std);
//            }
//
//            for(int i = 0; i < m_idaLocale.get_count() && i < m_idaSchema.get_count(); i++)
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
//            idSchema2 = __id(std);
//         }
//
//         for(int i = 0; i < m_idaLocale.get_count() && i < m_idaSchema.get_count(); i++)
//         {
//            if(m_idaLocale[i] == idLocale && m_idaSchema[i] == idSchema2)
//               return bAdded;
//         }
//
//         m_idaLocale.add(idLocale);
//         m_idaSchema.add(idSchema2);

         return true;

      }

      inline atom rl_id(const ::atom & atom)
      {


         ::map < ::atom, const ::atom &, ::atom, const ::atom & >::pair * ppair = g_pmapRTL->plookup(atom);

         if(ppair != nullptr)
            return ppair->element2();

         string str;

         str = atom;

         ::atom idRl = str + "_rl";

         g_pmapRTL->set_at(atom, idRl);

         return idRl;

      }


      bool locale_schema::process_final_locale_schema(bool bRTLLayout)
      {
         static auto _std("_std");
         static auto _stdRl("_std_rl");

restart0:

         for(::collection::index i = 0; i < m_idaLocale.get_count(); i++)
         {

            atom idLocale = m_idaLocale[i];

            if(defer_add_locale(idLocale, idLocale))
               goto restart0;

         }

restart:
         for(::collection::index i = 0; i < m_idaLocale.get_count(); i++)
         {
            string strLocale = m_idaLocale[i];
            if(i >= m_idaSchema.get_count())
               m_idaSchema.add(m_atomSchema);
            atom idSchema = m_idaSchema[i];
            auto pFind = strLocale.find("-");
            if(::is_set(pFind))
            {
               atom idLocale2 = strLocale(0, pFind);
               if(m_idaLocale.find_first(idLocale2) < 0)
               {
                  m_idaLocale.insert_at(i + 1, idLocale2);
                  m_idaSchema.insert_at(i + 1, idSchema);
                  goto restart;
               }
               idLocale2 = strLocale(pFind + 1);
               if(idLocale2.is_empty() && m_idaLocale.find_first(idLocale2) < 0)
               {
                  m_idaLocale.insert_at(i + 1, idLocale2);
                  m_idaSchema.insert_at(i + 1, idSchema);
                  goto restart;
               }
            }

         }


         comparable_array < atom > idaLocaleAdd1;
         comparable_array < atom > idaSchemaAdd1;


         if(bRTLLayout)
         {

            idaLocaleAdd1.allocate(0, 256);
            idaSchemaAdd1.allocate(0, 256);

            if(m_idaLocale.get_count() > 256)
            {
               //informationf("What!!!!!!");
            }

            for(::collection::index i = 0; i < m_idaLocale.get_count(); i++)
            {
               atom idLocale2 = m_idaLocale[i];
               while(i >= m_idaSchema.get_count())
                  m_idaSchema.add(m_atomSchema);
               atom idSchema = m_idaSchema[i];
               if(idSchema != _std)
               {
                  idaLocaleAdd1.add(idLocale2);
                  idaSchemaAdd1.add(rl_id(idSchema));
               }
            }
         }
         if(bRTLLayout)
         {
            for(::collection::index i = 0; i < m_idaLocale.get_count(); i++)
            {
               atom idLocale2 = m_idaLocale[i];
               if(i >= m_idaSchema.get_count())
                  m_idaSchema.add(_std);
               atom idSchema = m_idaSchema[i];
               if(idSchema != _std)
               {
                  idaLocaleAdd1.add(idLocale2);
                  idaSchemaAdd1.add(_stdRl);
               }
            }
         }
         //if(!m_bSchemaOnly)
         //{
         //   for(::collection::index i = 0; i < m_idaLocale.get_count(); i++)
         //   {
         //      defer_add_locale(m_idaLocale[i], __id(std));
         //   }
         //}

         m_idaLocale.add(idaLocaleAdd1);
         m_idaSchema.add(idaSchemaAdd1);

         return true;

      }


      //bool locale_schema::process_final_locale_schema(bool bRightToLeftLayout)
      //{

      //   return process_final_locale_schema(bRightToLeftLayout);

      //}


      locale_schema & locale_schema::operator = (const locale_schema & ls)
      {

         if(&ls != this)
         {

            m_bSchemaOnly           = ls.m_bSchemaOnly;
            m_bAddAlternateStyle    = ls.m_bAddAlternateStyle;
            m_atomLocale              = ls.m_atomLocale;
            m_atomSchema              = ls.m_atomSchema;
            m_idaLocale             = ls.m_idaLocale;
            m_idaSchema             = ls.m_idaSchema;

         }

         return *this;

      }

      long long locale_schema::increment_reference_count()
      {
         return matter::increment_reference_count();
      }

      long long locale_schema::release()
      {
         return matter::release();
      }


   }  // namespace international


} // namespace str


