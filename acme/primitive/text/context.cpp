#include "framework.h"
#include "acme/constant/id.h"
#include "acme/constant/idpool.h"
#include "acme/filesystem/file/file.h"
#include "acme/platform/context.h"
#include "acme/primitive/primitive/memory.h"
//#include "acme/primitive/collection/string_array.h"
#include "acme/primitive/string/parse.h"
#include "acme/primitive/string/str.h"
#include "context.h"


namespace text
{


   context::context()
   {


      m_plocaleschema = __new(::text::international::locale_schema);


   }


   context::~context()
   {

   }


   const comparable_array < ::atom > & context::locale_ex() const
   {

      return m_plocaleschema->m_idaLocale;

   }

   
   const comparable_array < ::atom > & context::schema_ex() const
   {

      return m_plocaleschema->m_idaLocale;

   }


   void context::set_table(table * ptable)
   {

      m_ptable = ptable;

   }


   void context::prepare()
   {

      //static ::atom idEn("en");
      //static ::atom idStd("_std");


      m_plocale               = nullptr;

      m_pschema               = nullptr;
      m_pschemaLocale         = nullptr;
      m_pschemaSchemaEn       = nullptr;
      m_pschemaSchemaStd      = nullptr;


      m_schemaptra.erase_all();


      if(m_plocaleschema != nullptr)
      {

         if(!m_plocaleschema->m_atomLocale.is_empty())
         {

            m_plocale = (locale *) m_ptable->get_locale(m_plocaleschema->m_atomLocale);

            if(m_plocale != nullptr)
            {

               if(!m_plocaleschema->m_atomSchema.is_empty() && m_plocaleschema->m_atomSchema != m_plocaleschema->m_atomLocale)
               {
                  m_pschema = (schema *) m_plocale->get_schema(m_plocaleschema->m_atomSchema);
               }
               m_pschemaLocale = (schema *)m_plocale->get_schema(m_plocaleschema->m_atomSchema);
            }
         }

         if(!m_plocaleschema->m_atomSchema.is_empty())
         {

            const locale * plocale = m_ptable->get_locale(m_plocaleschema->m_atomSchema);

            if(plocale != nullptr)
            {

               m_pschemaSchemaEn = (schema*)plocale->get_schema("en");

               m_pschemaSchemaStd = (schema*)plocale->get_schema("_std");

            }

         }

         string_array straFailedLocale;

         for(i32 i = 0; i < m_plocaleschema->m_idaLocale.get_count(); i++)
         {

            ::atom & idLocale = m_plocaleschema->m_idaLocale[i];


            if(straFailedLocale.contains(idLocale))
               continue;

            const locale * plocale = m_ptable->get_locale(idLocale);

            if(plocale == nullptr)
            {
               straFailedLocale.add(idLocale);
               continue;
            }

            ::atom & idSchema = m_plocaleschema->m_idaSchema[i];


            schema * pschema = (schema * ) plocale->get_schema(idSchema);

            if(pschema != nullptr)
            {

               m_schemaptra.add(pschema);

            }

            if(idLocale != idSchema)
            {

               schema * pschema = (schema * )plocale->get_schema(idLocale);

               if(pschema != nullptr)
               {

                  m_schemaptra.add(pschema);

               }

            }

            if("std" != idSchema)
            {

               schema * pschema = (schema *)plocale->get_schema("std");

               if(pschema != nullptr)
               {

                  m_schemaptra.add(pschema);

               }

            }

         }

      }

   }


   table::table()
   {

      m_map.InitHashTable(97);


      //defer_create_synchronization();

   }


   table::~table()
   {


   }


   void table::initialize(::particle * pparticle)
   {

      /*auto estatus =*/ ::particle::initialize(pparticle);

      m_pschemaEn = &operator[]("en")["en"];
      m_pschemaStd = &operator[]("_std")["_std"];


      //if (!estatus)
      //{

      //   return estatus;

      //}

//#ifdef _UWP
//
//      return estatus;
//
//#endif

      //return estatus;

   }


   bool table::load(const char * pszBaseDir)
   {

      return true;

//      synchronous_lock synchronouslock(this->synchronization());
//
//      string strMain = pszBaseDir;
//
//      ::file::listing locales(this);
//
//      locales.ignore(".svn").ls_dir(strMain);
//
//      for(auto & locale : locales)
//      {
//
//         ::file::listing schemas(this);
//
//         schemas.ignore(".svn").ls_dir(locale);
//
//         for(auto & schema : schemas)
//         {
//
//            ::file::listing listing(this);
//
//            listing.ignore(".svn").rls_file(schema / "uistr");
//
//            for(auto & path : listing)
//            {
//
//               load_uistr_file(locale.name(), schema.name(), path);
//
//            }
//
//         }
//
//      }
//
//      return true;

   }


   void table::set(const ::atom & atom, const ::atom & idLocale, const ::atom & idSchema, const char * psz)
   {

      (*this)[idLocale][idSchema][atom] = psz;

   }


   string table::get(const context * pcontext,const ::atom & atom, bool bIdAsDefaultValue) const
   {

      if (pcontext == nullptr)
      {

         return "";

      }

      static ::atom idEn("en");
      static ::atom idStd("_std");

      string table;
      if(pcontext != nullptr)
      {

         //pcontext->defer_ok(this);

         if(pcontext->m_pschema != nullptr)
         {

            table = (*pcontext->m_pschema)[atom];
            if(table.has_char())
               return table;

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            table = (*pcontext->m_pschemaLocale)[atom];
            if(table.has_char())
               return table;
         }

         for(i32 i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            table = (*pcontext->m_schemaptra[i])[atom];
            if(table.has_char())
               return table;

         }

      }
      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {
         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.has_char())
            return table;
      }
      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.has_char())
         return table;
      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {
         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.has_char())
            return table;
      }

      table = (*m_pschemaStd)[atom]; // lang=_std style=_std

      if(table.has_char())
      {

         return table;

      }

      if(bIdAsDefaultValue)
      {

         return atom;

      }
      else
      {

         return {};

      }

   }


   string table::get(const context * pcontext,const ::atom & atom,const ::atom & idLocale,const ::atom & idSchema,bool bIdAsDefaultValue) const
   {

      if(!idLocale.is_empty())
      {
         string table;
         const locale * plocale = get_locale(idLocale);
         if(plocale != nullptr)
         {

            if(!idSchema.is_empty() && idSchema != idLocale)
            {
               const schema * pschema = plocale->get_schema(idSchema);
               if(pschema != nullptr)
               {
                  table = (*pschema)[atom];
                  if(table.has_char())
                     return table;
               }
            }

            const schema * pschema = plocale->get_schema(idLocale);
            if(pschema != nullptr)
            {
               table = (*pschema)[atom];
               if(table.has_char())
                  return table;
            }
         }
      }
      return get(pcontext,atom,bIdAsDefaultValue);
   }


   void table::get(string_array & stra, const context * pcontext, const ::atom & atom) const
   {

      _get(stra, pcontext, atom);

      ::atom id2;

      index i = 0;

      string_array stra2;

      do
      {

         stra2.erase_all();

         id2 = atom.m_str + "[" + as_string(i) + "]";

         _get(stra2, pcontext, id2);

         stra.append(stra2);

         i++;

      }
      while (stra2.get_count() > 0);


   }


   void table::_get(string_array & stra, const context * pcontext, const ::atom & atom) const
   {

      if (pcontext == nullptr)
      {

         return;

      }

      static ::atom idEn("en");
      static ::atom idStd("_std");

      string table;
      if(pcontext != nullptr)
      {

         //pcontext->defer_ok(this);

         if(pcontext->m_pschema != nullptr)
         {

            table = (*pcontext->m_pschema)[atom];
            if(table.has_char())
               stra.add(table);

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            table = (*pcontext->m_pschemaLocale)[atom];
            if(table.has_char())
               stra.add(table);
         }

         for(i32 i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            table = (*pcontext->m_schemaptra[i])[atom];
            if(table.has_char())
               stra.add(table);

         }

      }

      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.has_char())
            stra.add(table);

      }

      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.has_char())
         stra.add(table);

      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.has_char())
            stra.add(table);

      }

      table = (*m_pschemaStd)[atom]; // lang=_std style=_std
      if(table.has_char())
         stra.add(table);

   }

   //struct range_sz_item
   //{
   //   strsize s;
   //   strsize e;
   //};

   //struct range_sz
   //{

   //   range_sz_item stack[8];
   //   strsize m_pos = 0;

   //   char m_szAlloca[8 * 1024];
   //   char * m_szMerge = m_szAlloca;
   //   strsize m_iSize =0;
   //   strsize m_iMaxSize=sizeof(m_szAlloca);
   //   bool m_bOwn = false;


   //   ~range_sz()
   //   {
   //      if(m_szMerge != nullptr && m_szMerge != m_szAlloca && m_bOwn)
   //      {
   //         memory_free(m_szMerge);
   //      }
   //   }

   //   void append(strsize start,strsize end, ::range < const ::ansi_character * > range)
   //   {
   //      stack[m_pos].s = start;
   //      stack[m_pos].e = end;
   //      m_pos++; if(m_pos >= 8)
   //      {
   //         merge(range);
   //      }
   //   }


   //   void merge(::range < const ::ansi_character * > range)
   //   {

   //      if(m_pos <= 0)
   //         return;

   //      strsize oldlen = m_iSize;

   //      strsize newlen;

   //      if(oldlen == 0 && m_pos == 1)
   //      {

   //         newlen = stack[0].e - stack[0].s;

   //         m_szMerge = &range.begin()[stack[0].s];

   //      }
   //      else
   //      {

   //         newlen = m_iSize + calc_merge_len();

   //         if(oldlen == newlen)
   //         {

   //            m_pos = 0;

   //            return;

   //         }

   //         if(newlen >= m_iMaxSize) // extra 1 byte
   //         {
   //            m_iMaxSize = newlen + 1024; // extra 1 byte plus 1023
   //            if (comparison::ge(m_iMaxSize, sizeof(m_szAlloca)))
   //            {
   //               if(m_szMerge == m_szAlloca || !m_bOwn)
   //               {
   //                  m_szMerge = (char *)::memory_allocate(m_iMaxSize);
   //                  ::memcpy_dup(m_szMerge,m_szAlloca,oldlen);
   //               }
   //               else
   //               {
   //                  m_szMerge = (char *)::memory_reallocate(m_szMerge,m_iMaxSize);
   //               }
   //               m_bOwn = true;
   //            }
   //         }

   //         strsize pos = 0;
   //         strsize len;
   //         for(index i = 0; i < m_pos; i++)
   //         {
   //            len = stack[i].e - stack[i].s;
   //            ::memcpy_dup(&m_szMerge[oldlen + pos],&pszTopic[stack[i].s],len);
   //            pos+=len;
   //         }

   //      }

   //      m_iSize = newlen;

   //      //m_szMerge[m_iSize] = '\0'; // for optmization purposes, m_szMerge is not forced to be 0 finished, so CHECK m_iSize!!

   //      m_pos = 0;

   //   }

   //   strsize calc_merge_len()
   //   {
   //      if(m_pos <= 0)
   //         return 0;
   //      if(m_pos == 1)
   //         return stack[0].e - stack[0].s;
   //      strsize len = 0;
   //      for(index i = 0; i < m_pos; i++)
   //      {
   //         len += stack[i].e - stack[i].s;
   //      }
   //      return len;
   //   }

   //   //char * get_string(char string & strTopic)
   //   //{
   //   //   merge(strTopic);
   //   //   if(m_iSize == 0)
   //   //      return nullptr;
   //   //   return m_szMerge;
   //   //}
   //   void clear()
   //   {
   //      m_iSize = 0;
   //      m_pos = 0;
   //   }
   //};


   bool table::load_uistr_file(const ::atom& pszLang, const ::atom& pszStyle, ::file::file *  pfile)
   {

      throw ::exception(todo);

//      memory mem;
//
//      pfile->as_memory(mem);
//
//      strsize len;
//
//      auto strFile = mem.get_string_buffer<::ansi_character>(len);
//
//      ::tokenizer parse(strFile);
//
//      string table;
//
//      //i32 i = 0;
//
//      strsize start;
//
//      strsize end;
//
//      char q;
//
////      ::table::utf8_char c;
//
//      bool bFinal;
//
//      //bool bEof = false;
//
//      const char * s;
//
//      char * wr;
//
//      const char * rd;
//
//      strsize l;
//
//      string str;
//
//      const char * pszEnd;
//
//      string strRoot;
//
//      string strBody;
//
//      string strToken;
//
//      while(parse.has_char())
//      {
//
//         str.Empty();
//
//         bFinal = false;
//
//         while(!bFinal)
//         {
//
//            parse.get_line(strToken);
//
//            rstr.append(start, end, strFile);
//
//         }
//
//         rstr.merge(strFile);
//
//         char * psz = rstr.m_szMerge;
//
//         pszEnd = psz + rstr.m_iSize;
//
//         while(unicode_is_whitespace(psz))
//         {
//            
//            psz += utf8_unicode_length(*psz);
//
//            if (psz >= pszEnd)
//            {
//
//               goto cont;
//
//            }
//
//         }
//
//         // going to consume a quoted value
//
//         q = *psz;
//
//         if(q != '\'' && q != '\"')
//         {
//            goto cont;
//         }
//
//         psz++;
//         s = psz;
//
//         while(*psz != q)
//         {
//            
//            psz += utf8_unicode_length(*psz);
//
//            if (psz >= pszEnd)
//            {
//
//               goto cont;
//
//            }
//         }
//         strRoot.assign(s, psz - s);
//         psz++;
//
//         while(unicode_is_whitespace(psz))
//         {
//            
//            psz += utf8_unicode_length(*psz);
//
//            if (psz >= pszEnd)
//            {
//
//               goto end;
//
//            }
//
//         }
//
//         if(*psz != '=')
//            continue;
//
//         psz++;
//
//         while(unicode_is_whitespace(psz))
//         {
//            
//            psz += utf8_unicode_length(*psz);
//
//            if (psz >= pszEnd)
//            {
//            
//               goto end;
//
//            }
//
//         }
//
//         // going to consume another quoted value
//
//         q = *psz;
//
//         if(q != '\'' && q != '\"')
//         {
//            goto cont;
//         }
//
//         psz++;
//         s = psz;
//         wr = psz;
//         rd = psz;
//         while(*rd != q)
//         {
//            if(*rd == '\\')
//            {
//               if(*(rd + 1) == 'r')
//               {
//                  *wr = '\r';
//                  wr++;
//                  rd+=2;
//                  goto cont2;
//               }
//               else if(*(rd + 1) == 'n')
//               {
//                  *wr = '\n';
//                  wr++;
//                  rd+=2;
//                  goto cont2;
//               }
//               else
//               {
//                  *wr = '\\';
//                  wr++;
//                  rd++;
//                  goto cont2;
//               }
//            }
//            
//            l = utf8_unicode_length(*psz);
//
//            if(wr != rd)
//            {
//               while(l > 0)
//               {
//                  *wr=*rd;
//                  wr++;
//                  rd++;
//                  l--;
//               }
//            }
//            else
//            {
//               wr+=l;
//               rd+=l;
//            }
//cont2:
//            if(rd >= pszEnd)
//               goto cont;
//         }
//         strBody.assign(s,wr - s);
//         //psz++;
//
//
//
//         //body(strBody)
//         //strBody.replace("\\r","\r");
//
//         //strBody.replace("\\n","\n"); already done
//
//         set(strRoot, pszLang, pszStyle, strBody);
//
//cont:;
//      }
//end:

      return true;
   }

   string table::body(const char * psz)
   {
      string table(psz);
      table.replace_with("\r", "\\r");
      table.replace_with("\n", "\\n");
      return table;
   }


   bool table::matches(const context * pcontext, const ::atom & atom, const char * psz) const
   {

      static ::atom idEn("en");
      static ::atom idStd("_std");

      string table;
      if(pcontext != nullptr)
      {

         //pcontext->defer_ok(this);

         if(pcontext->m_pschema != nullptr)
         {

            table = (*pcontext->m_pschema)[atom];
            if(table.case_insensitive_equals(psz))
               return true;

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            table = (*pcontext->m_pschemaLocale)[atom];
            if(table.case_insensitive_equals(psz))
               return true;
         }

         for(i32 i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            table = (*pcontext->m_schemaptra[i])[atom];
            if(table.case_insensitive_equals(psz))
               return true;

         }

      }

      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.case_insensitive_equals(psz))
            return true;

      }

      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.case_insensitive_equals(psz))
         return true;

      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.case_insensitive_equals(psz))
            return true;

      }



      return false;


   }


   bool table::begins(const context * pcontext, const char * pszTopic, const ::atom & atom) const
   {

      static ::atom idEn("en");
      static ::atom idStd("_std");

      string table;
      if(pcontext != nullptr)
      {

         //pcontext->defer_ok(this);

         if(pcontext->m_pschema != nullptr)
         {

            table = (*pcontext->m_pschema)[atom];
            if(table.has_char() && string_begins_ci(pszTopic, table))
               return true;

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            table = (*pcontext->m_pschemaLocale)[atom];
            if(table.has_char() && string_begins_ci(pszTopic, table))
               return true;
         }

         for(i32 i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            table = (*pcontext->m_schemaptra[i])[atom];
            if(table.has_char() && string_begins_ci(pszTopic, table))
               return true;

         }

      }

      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.has_char() && string_begins_ci(pszTopic, table))
            return true;

      }

      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.has_char() && string_begins_ci(pszTopic, table))
         return true;

      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.has_char() && string_begins_ci(pszTopic, table))
            return true;

      }



      return false;


   }


   bool table::begins_eat(const context * pcontext, string & strTopic, const ::atom & atom) const
   {

      static ::atom idEn("en");
      static ::atom idStd("_std");

      string table;
      if(pcontext != nullptr)
      {

         //pcontext->defer_ok(this);

         if(pcontext->m_pschema != nullptr)
         {

            table = (*pcontext->m_pschema)[atom];
            if(table.has_char() && strTopic.case_insensitive_begins_eat(table))
               return true;

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            table = (*pcontext->m_pschemaLocale)[atom];
            if(table.has_char() && strTopic.case_insensitive_begins_eat(table))
               return true;
         }

         for(i32 i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            table = (*pcontext->m_schemaptra[i])[atom];
            if(table.has_char() && strTopic.case_insensitive_begins_eat(table))
               return true;

         }

      }

      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.has_char() && strTopic.case_insensitive_begins_eat(table))
            return true;

      }

      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.has_char() && strTopic.case_insensitive_begins_eat(table))
         return true;

      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.has_char() && strTopic.case_insensitive_begins_eat(table))
            return true;

      }


      return false;


   }


   //bool context::match(string_array & stra, const char * psz, ::atom idExpression, ::atom idRoot) const
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   string_array straCandidate;

   //   get(straCandidate,idRoot);

   //   auto psystem = acmesystem();

   //   for(i32 i = 0; i < straCandidate.get_count(); i++)
   //   {

   //      string strCandidate = straCandidate[i];

   //      strCandidate.replace("-","\\-");

   //      string strExp(idExpression);

   //      strExp.replace("%1",strCandidate);

   //      string_array straResult;

   //      auto pregex = psystem->create_regular_expression("pcre", strExp);

   //      if(pregex->matches(straResult, psz) > 0)
   //      {

   //         stra = straResult;

   //         return true;

   //      }

   //   }

   //   return false;

   //}


} // namespace text



