#include "framework.h"
#include "acme/constant/id.h"
//#include "acme/constant/idpool.h"
#include "acme/filesystem/file/file.h"
#include "acme/platform/application.h"
#include "acme/prototype/prototype/memory.h"
//#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/string/parse.h"
#include "acme/prototype/string/str.h"
#include "context.h"


namespace text
{


   context::context()
   {


      m_plocaleschema = __allocate ::text::international::locale_schema();


   }


   context::~context()
   {

   }


   const string_array & context::locale_ex() const
   {

      return m_plocaleschema->m_straLocale;

   }

   
   const string_array & context::schema_ex() const
   {

      return m_plocaleschema->m_straLocale;

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

         if(!m_plocaleschema->m_strLocale.is_empty())
         {

            m_plocale = (locale *) m_ptable->get_locale(m_plocaleschema->m_strLocale);

            if(m_plocale != nullptr)
            {

               if(!m_plocaleschema->m_strSchema.is_empty() && m_plocaleschema->m_strSchema != m_plocaleschema->m_strLocale)
               {
                  m_pschema = (schema *) m_plocale->get_schema(m_plocaleschema->m_strSchema);
               }
               m_pschemaLocale = (schema *)m_plocale->get_schema(m_plocaleschema->m_strSchema);
            }
         }

         if(!m_plocaleschema->m_strSchema.is_empty())
         {

            const locale * plocale = m_ptable->get_locale(m_plocaleschema->m_strSchema);

            if(plocale != nullptr)
            {

               m_pschemaSchemaEn = (schema*)plocale->get_schema("en");

               m_pschemaSchemaStd = (schema*)plocale->get_schema("_std");

            }

         }

         string_array straFailedLocale;

         for(int i = 0; i < m_plocaleschema->m_straLocale.get_count(); i++)
         {

            auto & strLocale = m_plocaleschema->m_straLocale[i];

            if(straFailedLocale.contains(strLocale))
               continue;

            const locale * plocale = m_ptable->get_locale(strLocale);

            if(plocale == nullptr)
            {
               straFailedLocale.add(strLocale);
               continue;
            }

            auto & strSchema = m_plocaleschema->m_straSchema[i];


            schema * pschema = (schema * ) plocale->get_schema(strSchema);

            if(pschema != nullptr)
            {

               m_schemaptra.add(pschema);

            }

            if(strLocale != strSchema)
            {

               schema * pschema = (schema * )plocale->get_schema(strLocale);

               if(pschema != nullptr)
               {

                  m_schemaptra.add(pschema);

               }

            }

            if("std" != strSchema)
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

//#ifdef UNIVERSAL_WINDOWS
//
//      return estatus;
//
//#endif

      //return estatus;

   }


   bool table::load(const ::scoped_string & scopedstrBaseDir)
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


   void table::set(const ::atom & atom, const ::atom & strLocale, const ::atom & strSchema, const ::scoped_string & scopedstr)
   {

      (*this)[strLocale][strSchema][atom] = scopedstr;

   }


   string table::get(const ::text::context * pcontext,const ::atom & atom, bool bIdAsDefaultValue) const
   {

      if (pcontext == nullptr)
      {

         return "";

      }

      static auto idEn("en");
      static auto idStd("_std");

      string table;
      if(pcontext != nullptr)
      {

         //pcontext->defer_ok(this);

         if(pcontext->m_pschema != nullptr)
         {

            table = (*pcontext->m_pschema)[atom];

            if (table.has_character())
            {

               return table;

            }

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            
            table = (*pcontext->m_pschemaLocale)[atom];

            if (table.has_character())
            {

               return table;

            }

         }

         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            auto pschema = pcontext->m_schemaptra[i];

            if (::is_set(pschema))
            {

               table = (*pschema)[atom];

               if (table.has_character())
               {

                  return table;

               }

            }

         }

      }
      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {
         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.has_character())
            return table;
      }
      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.has_character())
         return table;
      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {
         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.has_character())
            return table;
      }

      table = (*m_pschemaStd)[atom]; // lang=_std style=_std

      if(table.has_character())
      {

         return table;

      }

      if(bIdAsDefaultValue)
      {

         return atom.as_string();

      }
      else
      {

         return {};

      }

   }


   string table::get(const ::text::context * pcontext,const ::atom & atom,const ::scoped_string & scopedstrLocale,const ::scoped_string & scopedstrSchema,bool bIdAsDefaultValue) const
   {

      if(!scopedstrLocale.is_empty())
      {
         string table;
         const locale * plocale = get_locale(scopedstrLocale);
         if(plocale != nullptr)
         {

            if(!scopedstrSchema.is_empty() && scopedstrSchema != scopedstrLocale)
            {
               const schema * pschema = plocale->get_schema(scopedstrSchema);
               if(pschema != nullptr)
               {
                  table = (*pschema)[atom];
                  if(table.has_character())
                     return table;
               }
            }

            const schema * pschema = plocale->get_schema(scopedstrLocale);
            if(pschema != nullptr)
            {
               auto ptable = pschema->find_item(atom);
               if(ptable && ptable->element2().has_character())
                  return ptable->element2();
            }
         }
      }
      return get(pcontext,atom,bIdAsDefaultValue);
   }


   void table::get(string_array & stra, const ::text::context * pcontext, const ::atom & atom) const
   {

      _get(stra, pcontext, atom);

      ::atom id2;

      ::collection::index i = 0;

      string_array stra2;

      do
      {

         stra2.erase_all();

         id2 = atom.m_str + "[" + ::as_string(i) + "]";

         _get(stra2, pcontext, id2);

         stra.append(stra2);

         i++;

      }
      while (stra2.get_count() > 0);


   }


   void table::_get(string_array & stra, const ::text::context * pcontext, const ::atom & atom) const
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
            if(table.has_character())
               stra.add(table);

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            table = (*pcontext->m_pschemaLocale)[atom];
            if(table.has_character())
               stra.add(table);
         }

         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            table = (*pcontext->m_schemaptra[i])[atom];
            if(table.has_character())
               stra.add(table);

         }

      }

      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.has_character())
            stra.add(table);

      }

      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.has_character())
         stra.add(table);

      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.has_character())
            stra.add(table);

      }

      table = (*m_pschemaStd)[atom]; // lang=_std style=_std
      if(table.has_character())
         stra.add(table);

   }

   //struct range_sz_item
   //{
   //   character_count s;
   //   character_count e;
   //};

   //struct range_sz
   //{

   //   range_sz_item stack[8];
   //   character_count m_pos = 0;

   //   char m_szAlloca[8 * 1024];
   //   char * m_szMerge = m_szAlloca;
   //   character_count m_iSize =0;
   //   character_count m_iMaxSize=sizeof(m_szAlloca);
   //   bool m_bOwn = false;


   //   ~range_sz()
   //   {
   //      if(m_szMerge != nullptr && m_szMerge != m_szAlloca && m_bOwn)
   //      {
   //         ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(m_szMerge);
   //      }
   //   }

   //   void append(character_count start,character_count end, ::range < const ::ansi_character * > range)
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

   //      character_count oldlen = m_iSize;

   //      character_count newlen;

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

   //         if(newlen >= m_iMaxSize) // extra 1 unsigned char
   //         {
   //            m_iMaxSize = newlen + 1024; // extra 1 unsigned char plus 1023
   //            if (comparison::ge(m_iMaxSize, sizeof(m_szAlloca)))
   //            {
   //               if(m_szMerge == m_szAlloca || !m_bOwn)
   //               {
   //                  m_szMerge = (char *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(m_iMaxSize);
   //                  ::memory_copy(m_szMerge,m_szAlloca,oldlen);
   //               }
   //               else
   //               {
   //                  m_szMerge = (char *)::memory_reallocate(m_szMerge,m_iMaxSize);
   //               }
   //               m_bOwn = true;
   //            }
   //         }

   //         character_count pos = 0;
   //         character_count len;
   //         for(::collection::index i = 0; i < m_pos; i++)
   //         {
   //            len = stack[i].e - stack[i].s;
   //            ::memory_copy(&m_szMerge[oldlen + pos],&pszTopic[stack[i].s],len);
   //            pos+=len;
   //         }

   //      }

   //      m_iSize = newlen;

   //      //m_szMerge[m_iSize] = '\0'; // for optmization purposes, m_szMerge is not forced to be 0 finished, so CHECK m_iSize!!

   //      m_pos = 0;

   //   }

   //   character_count calc_merge_len()
   //   {
   //      if(m_pos <= 0)
   //         return 0;
   //      if(m_pos == 1)
   //         return stack[0].e - stack[0].s;
   //      character_count len = 0;
   //      for(::collection::index i = 0; i < m_pos; i++)
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
//      character_count len;
//
//      auto strFile = mem.get_buffer<::ansi_character>(len);
//
//      ::tokenizer parse(strFile);
//
//      string table;
//
//      //int i = 0;
//
//      character_count start;
//
//      character_count end;
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
//      character_count l;
//
//      string str;
//
//      const ::ansi_character * pszEnd;
//
//      string strRoot;
//
//      string strBody;
//
//      string strToken;
//
//      while(parse.has_character())
//      {
//
//         str.empty();
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

   string table::body(const ::scoped_string & scopedstr)
   {
      string table(scopedstr);
      table.replace_with("\r", "\\r");
      table.replace_with("\n", "\\n");
      return table;
   }


   bool table::matches(const ::text::context * pcontext, const ::atom & atom, const ::scoped_string & scopedstr) const
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
            if(table.case_insensitive_equals(scopedstr))
               return true;

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            table = (*pcontext->m_pschemaLocale)[atom];
            if(table.case_insensitive_equals(scopedstr))
               return true;
         }

         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            table = (*pcontext->m_schemaptra[i])[atom];
            if(table.case_insensitive_equals(scopedstr))
               return true;

         }

      }

      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.case_insensitive_equals(scopedstr))
            return true;

      }

      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.case_insensitive_equals(scopedstr))
         return true;

      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.case_insensitive_equals(scopedstr))
            return true;

      }



      return false;


   }


   bool table::begins(const ::text::context * pcontext, const ::string &strTopic, const ::atom & atom) const
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
            if(table.has_character() && case_insensitive_string_begins(strTopic, table))
               return true;

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            table = (*pcontext->m_pschemaLocale)[atom];
            if(table.has_character() && case_insensitive_string_begins(strTopic, table))
               return true;
         }

         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            table = (*pcontext->m_schemaptra[i])[atom];
            if(table.has_character() && case_insensitive_string_begins(strTopic, table))
               return true;

         }

      }

      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.has_character() && case_insensitive_string_begins(strTopic, table))
            return true;

      }

      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.has_character() && case_insensitive_string_begins(strTopic, table))
         return true;

      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.has_character() && case_insensitive_string_begins(strTopic, table))
            return true;

      }



      return false;


   }


   bool table::begins_eat(const ::text::context * pcontext, string & strTopic, const ::atom & atom) const
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
            if(table.has_character() && strTopic.case_insensitive_begins_eat(table))
               return true;

         }

         if(pcontext->m_pschemaLocale != nullptr)
         {
            table = (*pcontext->m_pschemaLocale)[atom];
            if(table.has_character() && strTopic.case_insensitive_begins_eat(table))
               return true;
         }

         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
         {

            table = (*pcontext->m_schemaptra[i])[atom];
            if(table.has_character() && strTopic.case_insensitive_begins_eat(table))
               return true;

         }

      }

      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
         if(table.has_character() && strTopic.case_insensitive_begins_eat(table))
            return true;

      }

      table = (*m_pschemaEn)[atom]; // lang=en style=en
      if(table.has_character() && strTopic.case_insensitive_begins_eat(table))
         return true;

      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
      {

         table = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
         if(table.has_character() && strTopic.case_insensitive_begins_eat(table))
            return true;

      }


      return false;


   }


   //bool context::match(string_array & stra, const ::scoped_string & scopedstr, ::atom idExpression, ::atom idRoot) const
   //{

   //   synchronous_lock synchronouslock(this->synchronization());

   //   string_array straCandstrate;

   //   get(straCandstrate,idRoot);

   //   auto psystem = system();

   //   for(int i = 0; i < straCandstrate.get_count(); i++)
   //   {

   //      string strCandstrate = straCandstrate[i];

   //      strCandstrate.replace("-","\\-");

   //      string strExp(idExpression);

   //      strExp.replace("%1",strCandstrate);

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



