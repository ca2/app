#include "framework.h"
#include "acme/id.h"



namespace str
{


   namespace international
   {

      ::map < ::id, const ::id &, ::id, const ::id & > * g_pmapRTL;

      void create_rtl_map()
      {

         g_pmapRTL = new ::map < ::id,const ::id &,::id,const ::id & >();

      }

      locale_schema::locale_schema()
      {

         m_idSchema = "_std"; // __id(std)
         m_idLocale = "_std"; // __id(std)

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


      bool locale_schema::add_locale_variant(id idLocale, id idSchema)
      {

         if(m_idLocale.is_empty())
         {
            m_idLocale = idLocale;
            if(m_idLocale.is_empty())
               m_idLocale = "_std";
         }

         if(m_idSchema.is_empty())
         {
            m_idSchema = idSchema;
            if(m_idSchema.is_empty())
               m_idSchema = "_std";
         }

         id idLocale2 = idLocale;
         id idSchema2 = idSchema;

         if((idLocale2.is_empty() ) && (idSchema2.is_empty() ))
            return false;

         if(idLocale2.is_empty() )
            idLocale2 = m_idLocale;

         if(idSchema2.is_empty() )
            idSchema2 = m_idSchema;


         //if(defer_add_locale(idLocale2, idSchema2))
         //{
         // _add_locale_variant(idLocale2, idSchema2);
         //}

         if(defer_add_locale(idLocale2, idSchema2))
         {
            _add_locale_variant(idLocale2, idSchema2);
         }

         strsize iStart =idLocale2.str().get_length() + 1;
         strsize iEnd;
         strsize iLen;
         string str;
         bool bEnd = false;
         while(!bEnd)
         {
            iEnd = iStart - 1;
            if((iEnd - 1) < 0)
               break;
            iStart = idLocale2.str().reverse_find('-', iEnd - 1);
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
            ::id id = localeid(&idLocale2.m_psz[iStart], iLen);
            if(defer_add_locale(id, idSchema2))
            {
               _add_locale_variant(id, idSchema2);
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


      ::id locale_schema::localeid(const char * pszLocale, strsize iLen)
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

         return string(pszLocale, iLen);
      }


      bool locale_schema::_add_locale_variant(const char * psz, strsize iLen, id idSchema)
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




      bool locale_schema::defer_add_locale(id idLocale, id idSchema)
      {



         bool bAdded = false;

         id idSchema2;

//         if(m_bAddAlternateStyle)
//         {
//
//            idSchema2 = idSchema;
//
//            if(idSchema2 == m_idSchema && m_idSchema == m_idLocale) // if style is a locale and alternate style is locale too
//            {
//               idSchema2 = idLocale;
//            }
//
//            if(idSchema2.is_empty())
//            {
//               idSchema2 = __id(std);
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
//         idSchema2 = m_idSchema;
//
//         if(idSchema2.is_empty())
//         {
//            idSchema2 = __id(std);
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

      inline id rl_id(const ::id & id)
      {


         ::map < ::id, const ::id &, ::id, const ::id & >::pair * ppair = g_pmapRTL->plookup(id);

         if(ppair != nullptr)
            return ppair->element2();

         string str;

         str = id;

         ::id idRl = str + "_rl";

         g_pmapRTL->set_at(id, idRl);

         return idRl;

      }


      bool locale_schema::process_final_locale_schema(bool bRTLLayout)
      {
         static id _std("_std");
         static id _stdRl("_std_rl");

restart0:

         for(index i = 0; i < m_idaLocale.get_count(); i++)
         {

            id idLocale = m_idaLocale[i];

            if(defer_add_locale(idLocale, idLocale))
               goto restart0;

         }

restart:
         for(index i = 0; i < m_idaLocale.get_count(); i++)
         {
            string strLocale = m_idaLocale[i];
            if(i >= m_idaSchema.get_count())
               m_idaSchema.add(m_idSchema);
            id idSchema = m_idaSchema[i];
            strsize iFind = strLocale.find("-");
            if(iFind >= 0)
            {
               id idLocale2 = strLocale.Left(iFind);
               if(m_idaLocale.find_first(idLocale2) < 0)
               {
                  m_idaLocale.insert_at(i + 1, idLocale2);
                  m_idaSchema.insert_at(i + 1, idSchema);
                  goto restart;
               }
               idLocale2 = strLocale.Mid(iFind + 1);
               if(idLocale2.is_empty() && m_idaLocale.find_first(idLocale2) < 0)
               {
                  m_idaLocale.insert_at(i + 1, idLocale2);
                  m_idaSchema.insert_at(i + 1, idSchema);
                  goto restart;
               }
            }

         }


         comparable_array < id > idaLocaleAdd1;
         comparable_array < id > idaSchemaAdd1;


         if(bRTLLayout)
         {

            idaLocaleAdd1.allocate(0, 256);
            idaSchemaAdd1.allocate(0, 256);

            if(m_idaLocale.get_count() > 256)
            {
               //TRACE("What!!!!!!");
            }

            for(index i = 0; i < m_idaLocale.get_count(); i++)
            {
               id idLocale2 = m_idaLocale[i];
               while(i >= m_idaSchema.get_count())
                  m_idaSchema.add(m_idSchema);
               id idSchema = m_idaSchema[i];
               if(idSchema != _std)
               {
                  idaLocaleAdd1.add(idLocale2);
                  idaSchemaAdd1.add(rl_id(idSchema));
               }
            }
         }
         if(bRTLLayout)
         {
            for(index i = 0; i < m_idaLocale.get_count(); i++)
            {
               id idLocale2 = m_idaLocale[i];
               if(i >= m_idaSchema.get_count())
                  m_idaSchema.add(_std);
               id idSchema = m_idaSchema[i];
               if(idSchema != _std)
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
            m_idLocale              = ls.m_idLocale;
            m_idSchema              = ls.m_idSchema;
            m_idaLocale             = ls.m_idaLocale;
            m_idaSchema             = ls.m_idaSchema;

         }

         return *this;

      }

      i64 locale_schema::add_ref(OBJ_REF_DBG_PARAMS_DEF)
      {
         return elemental::add_ref(OBJ_REF_DBG_ARGS);
      }

      i64 locale_schema::release(OBJ_REF_DBG_PARAMS_DEF)
      {
         return elemental::release(OBJ_REF_DBG_ARGS);
      }


   }  // namespace international


} // namespace str


