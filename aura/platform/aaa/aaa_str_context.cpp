#include "framework.h"
//#include "acme/constant/id.h"
//#include "aura/const/idpool.h"
//
//
//namespace aura
//{
//
//
//   str_context::textcontext()
//   {
//
//
//      m_plocaleschema = __allocate ::text::international::locale_schema();
//
//
//      m_pstr = nullptr;
//
//
//   }
//
//   str_context::~textcontext()
//   {
//
//   }
//
//
//   const comparable_array < atom > & str_context::locale_ex() const
//   {
//
//      return m_plocaleschema->m_idaLocale;
//
//   }
//
//   
//   const comparable_array < atom > & str_context::schema_ex() const
//   {
//
//      return m_plocaleschema->m_idaLocale;
//
//   }
//
//
//   void str_context::set_str(str * pstr)
//   {
//
//      m_pstr = pstr;
//
//   }
//
//
//   void str_context::prepare()
//   {
//
//      static ::atom idEn("en");
//      static ::atom idStd("_std");
//
//
//      m_plocale               = nullptr;
//
//      m_pschema               = nullptr;
//      m_pschemaLocale         = nullptr;
//      m_pschemaSchemaEn       = nullptr;
//      m_pschemaSchemaStd      = nullptr;
//
//
//      m_schemaptra.erase_all();
//
//
//      if(m_plocaleschema != nullptr)
//      {
//
//         if(!m_plocaleschema->m_atomLocale.is_empty())
//         {
//
//            m_plocale = (str_locale *) m_pstr->get_locale(m_plocaleschema->m_atomLocale);
//
//            if(m_plocale != nullptr)
//            {
//
//               if(!m_plocaleschema->m_atomSchema.is_empty() && m_plocaleschema->m_atomSchema != m_plocaleschema->m_atomLocale)
//               {
//                  m_pschema = (str_schema *) m_plocale->get_schema(m_plocaleschema->m_atomSchema);
//               }
//               m_pschemaLocale = (str_schema *)m_plocale->get_schema(m_plocaleschema->m_atomSchema);
//            }
//         }
//
//         if(!m_plocaleschema->m_atomSchema.is_empty())
//         {
//
//            const str_locale * plocale = m_pstr->get_locale(m_plocaleschema->m_atomSchema);
//
//            if(plocale != nullptr)
//            {
//
//               m_pschemaSchemaEn = (str_schema *)plocale->get_schema(idEn);
//
//               m_pschemaSchemaStd = (str_schema *)plocale->get_schema(idStd);
//
//            }
//
//         }
//
//         strid_array stridaFailedLocale(false);
//
//         for(int i = 0; i < m_plocaleschema->m_idaLocale.get_count(); i++)
//         {
//
//            ::atom & idLocale = m_plocaleschema->m_idaLocale[i];
//
//
//            if(stridaFailedLocale.contains(idLocale))
//               continue;
//
//            const str_locale * plocale = m_pstr->get_locale(idLocale);
//
//            if(plocale == nullptr)
//            {
//               stridaFailedLocale.add(idLocale);
//               continue;
//            }
//
//            ::atom & idSchema = m_plocaleschema->m_idaSchema[i];
//
//
//            str_schema * pschema = (str_schema * ) plocale->get_schema(idSchema);
//
//            if(pschema != nullptr)
//            {
//
//               m_schemaptra.add(pschema);
//
//            }
//
//            if(idLocale != idSchema)
//            {
//
//               str_schema * pschema = (str_schema * )plocale->get_schema(idLocale);
//
//               if(pschema != nullptr)
//               {
//
//                  m_schemaptra.add(pschema);
//
//               }
//
//            }
//
//            if(__id(std) != idSchema)
//            {
//
//               str_schema * pschema = (str_schema *)plocale->get_schema(__id(std));
//
//               if(pschema != nullptr)
//               {
//
//                  m_schemaptra.add(pschema);
//
//               }
//
//            }
//
//         }
//
//      }
//
//   }
//
//
//   ::str::str()
//   {
//
//      m_map.InitHashTable(97);
//
//      m_pschemaEn    = &operator[]("en")["en"];
//      m_pschemaStd   = &operator[]("_std")["_std"];
//
//      //defer_create_synchronization();
//
//   }
//
//
//   ::str::~str()
//   {
//
//
//   }
//
//
//   void ::str::initialize(::particle * pparticle)
//   {
//
//      auto estatus = ::object::initialize(pparticle);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//#ifdef UNIVERSAL_WINDOWS
//
//      return estatus;
//
//#endif
//
//      auto strMain = pcontext->directory()->install() / "app/_appmatter/main";
//
//      if (!load(strMain))
//      {
//
//         return error_failed;
//
//      }
//
//      return estatus;
//
//   }
//
//
//   bool ::str::load(const ::scoped_string & scopedstrBaseDir)
//   {
//
//      return true;
//
////      synchronous_lock synchronouslock(this->synchronization());
////
////      string strMain = pszBaseDir;
////
////      ::file::listing locales(this);
////
////      locales.ignore(".svn").ls_dir(strMain);
////
////      for(auto & locale : locales)
////      {
////
////         ::file::listing schemas(this);
////
////         schemas.ignore(".svn").ls_dir(locale);
////
////         for(auto & schema : schemas)
////         {
////
////            ::file::listing listing(this);
////
////            listing.ignore(".svn").rls_file(schema / "uistr");
////
////            for(auto & path : listing)
////            {
////
////               load_uistr_file(locale.name(), schema.name(), path);
////
////            }
////
////         }
////
////      }
////
////      return true;
//
//   }
//
//
//   void ::str::set(const ::atom & atom, const ::atom & idLocale, const ::atom & idSchema, const ::scoped_string & scopedstr)
//   {
//
//      (*this)[idLocale][idSchema][atom] = psz;
//
//   }
//
//
//   string ::str::get(const str_context * pcontext,const ::atom & atom, bool bIdAsDefaultValue) const
//   {
//
//      if (pcontext == nullptr)
//      {
//
//         return "";
//
//      }
//
//      static ::atom idEn("en");
//      static ::atom idStd("_std");
//
//      string str;
//      if(pcontext != nullptr)
//      {
//
//         //pcontext->defer_ok(this);
//
//         if(pcontext->m_pschema != nullptr)
//         {
//
//            str = (*pcontext->m_pschema)[atom];
//            if(str.has_character())
//               return str;
//
//         }
//
//         if(pcontext->m_pschemaLocale != nullptr)
//         {
//            str = (*pcontext->m_pschemaLocale)[atom];
//            if(str.has_character())
//               return str;
//         }
//
//         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
//         {
//
//            str = (*pcontext->m_schemaptra[i])[atom];
//            if(str.has_character())
//               return str;
//
//         }
//
//      }
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
//      {
//         str = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
//         if(str.has_character())
//            return str;
//      }
//      str = (*m_pschemaEn)[atom]; // lang=en style=en
//      if(str.has_character())
//         return str;
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
//      {
//         str = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
//         if(str.has_character())
//            return str;
//      }
//
//      str = (*m_pschemaStd)[atom]; // lang=_std style=_std
//
//      if(str.has_character())
//      {
//
//         return str;
//
//      }
//
//      if(bIdAsDefaultValue)
//      {
//
//         return atom.to_string();
//
//      }
//      else
//      {
//
//         return "";
//
//      }
//
//   }
//
//   string ::str::get(const str_context * pcontext,const ::atom & atom,const ::atom & idLocale,const ::atom & idSchema,bool bIdAsDefaultValue) const
//   {
//
//      if(!idLocale.is_empty())
//      {
//         string str;
//         const str_locale * plocale = get_locale(idLocale);
//         if(plocale != nullptr)
//         {
//
//            if(!idSchema.is_empty() && idSchema != idLocale)
//            {
//               const str_schema * pschema = plocale->get_schema(idSchema);
//               if(pschema != nullptr)
//               {
//                  str = (*pschema)[atom];
//                  if(str.has_character())
//                     return str;
//               }
//            }
//
//            const str_schema * pschema = plocale->get_schema(idLocale);
//            if(pschema != nullptr)
//            {
//               str = (*pschema)[atom];
//               if(str.has_character())
//                  return str;
//            }
//         }
//      }
//      return get(pcontext,atom,bIdAsDefaultValue);
//   }
//
//
//   void ::str::get(string_array & stra, const str_context * pcontext, const ::atom & atom) const
//   {
//
//      _get(stra, pcontext, atom);
//
//      ::atom id2;
//
//      ::collection::index i = 0;
//
//      string_array stra2;
//
//      do
//      {
//
//         stra2.erase_all();
//
//         id2 = string(atom.m_psz) + "[" + as_string(i) + "]";
//
//         _get(stra2, pcontext, id2);
//
//         stra.add(stra2);
//
//         i++;
//
//      }
//      while (stra2.get_count() > 0);
//
//
//   }
//
//
//   void ::str::_get(string_array & stra, const str_context * pcontext, const ::atom & atom) const
//   {
//
//      if (pcontext == nullptr)
//      {
//
//         return;
//
//      }
//
//      static ::atom idEn("en");
//      static ::atom idStd("_std");
//
//      string str;
//      if(pcontext != nullptr)
//      {
//
//         //pcontext->defer_ok(this);
//
//         if(pcontext->m_pschema != nullptr)
//         {
//
//            str = (*pcontext->m_pschema)[atom];
//            if(str.has_character())
//               stra.add(str);
//
//         }
//
//         if(pcontext->m_pschemaLocale != nullptr)
//         {
//            str = (*pcontext->m_pschemaLocale)[atom];
//            if(str.has_character())
//               stra.add(str);
//         }
//
//         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
//         {
//
//            str = (*pcontext->m_schemaptra[i])[atom];
//            if(str.has_character())
//               stra.add(str);
//
//         }
//
//      }
//
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
//      {
//
//         str = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
//         if(str.has_character())
//            stra.add(str);
//
//      }
//
//      str = (*m_pschemaEn)[atom]; // lang=en style=en
//      if(str.has_character())
//         stra.add(str);
//
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
//      {
//
//         str = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
//         if(str.has_character())
//            stra.add(str);
//
//      }
//
//      str = (*m_pschemaStd)[atom]; // lang=_std style=_std
//      if(str.has_character())
//         stra.add(str);
//
//   }
//
//   struct range_sz_item
//   {
//      character_count s;
//      character_count e;
//   };
//
//   struct range_sz
//   {
//
//      range_sz_item stack[8];
//      character_count m_pos = 0;
//
//      char m_szAlloca[8 * 1024];
//      char * m_szMerge = m_szAlloca;
//      character_count m_iSize =0;
//      character_count m_iMaxSize=sizeof(m_szAlloca);
//      bool m_bOwn = false;
//
//
//      ~range_sz()
//      {
//         if(m_szMerge != nullptr && m_szMerge != m_szAlloca && m_bOwn)
//         {
//            ::system()->m_pheapmanagement->memory(::heap::e_memory_main)->free(m_szMerge);
//         }
//      }
//
//      void append(character_count start,character_count end,char * pszTopic)
//      {
//         stack[m_pos].s = start;
//         stack[m_pos].e = end;
//         m_pos++; if(m_pos >= 8)
//         {
//            merge(scopedstrTopic);
//         }
//      }
//
//      void merge(char * pszTopic)
//      {
//
//         if(m_pos <= 0)
//            return;
//
//         character_count oldlen = m_iSize;
//
//         character_count newlen;
//
//         if(oldlen == 0 && m_pos == 1)
//         {
//
//            newlen = stack[0].e - stack[0].s;
//
//            m_szMerge = &pszTopic[stack[0].s];
//
//         }
//         else
//         {
//
//            newlen = m_iSize + calc_merge_len();
//
//            if(oldlen == newlen)
//            {
//
//               m_pos = 0;
//
//               return;
//
//            }
//
//            if(newlen >= m_iMaxSize) // extra 1 unsigned char
//            {
//               m_iMaxSize = newlen + 1024; // extra 1 unsigned char plus 1023
//               if (comparison::ge(m_iMaxSize, sizeof(m_szAlloca)))
//               {
//                  if(m_szMerge == m_szAlloca || !m_bOwn)
//                  {
//                     m_szMerge = (char *)::system()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(m_iMaxSize);
//                     ::memory_copy(m_szMerge,m_szAlloca,oldlen);
//                  }
//                  else
//                  {
//                     m_szMerge = (char *)::memory_reallocate(m_szMerge,m_iMaxSize);
//                  }
//                  m_bOwn = true;
//               }
//            }
//
//            character_count pos = 0;
//            character_count len;
//            for(::collection::index i = 0; i < m_pos; i++)
//            {
//               len = stack[i].e - stack[i].s;
//               ::memory_copy(&m_szMerge[oldlen + pos],&pszTopic[stack[i].s],len);
//               pos+=len;
//            }
//
//         }
//
//         m_iSize = newlen;
//
//         //m_szMerge[m_iSize] = '\0'; // for optmization purposes, m_szMerge is not forced to be 0 finished, so CHECK m_iSize!!
//
//         m_pos = 0;
//
//      }
//
//      character_count calc_merge_len()
//      {
//         if(m_pos <= 0)
//            return 0;
//         if(m_pos == 1)
//            return stack[0].e - stack[0].s;
//         character_count len = 0;
//         for(::collection::index i = 0; i < m_pos; i++)
//         {
//            len += stack[i].e - stack[i].s;
//         }
//         return len;
//      }
//
//      //char * get_string(char string & strTopic)
//      //{
//      //   merge(strTopic);
//      //   if(m_iSize == 0)
//      //      return nullptr;
//      //   return m_szMerge;
//      //}
//      void clear()
//      {
//         m_iSize = 0;
//         m_pos = 0;
//      }
//   };
//
//
//   bool ::str::load_uistr_file(const ::atom & pszLang, const ::atom & pszStyle, const ::scoped_string & scopedstrFilePath)
//   {
//
//      memory mem;
//
//      file()->as_memory(scopedstrFilePath,mem);
//
//
//      character_count len;
//
//      char * pszFile = mem.get_psz(len);
//
//      ::parse parse(scopedstrFile, len);
//
//      string str;
//
//      //int i = 0;
//
//      character_count start;
//
//      character_count end;
//
//      char q;
//
////      ::str::utf8_char c;
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
//      range_sz rstr;
//
//      const ::ansi_character * pszEnd;
//
//      string strRoot;
//
//      string strBody;
//
//      while(parse.has_character())
//      {
//
//         rstr.clear();
//
//         bFinal = false;
//
//         while(!bFinal)
//         {
//
//            parse._get_expandable_line(start,end,bFinal);
//
//            rstr.append(start,end,pszFile);
//
//         }
//
//         rstr.merge(scopedstrFile);
//
//         char * psz = rstr.m_szMerge;
//
//         pszEnd = psz + rstr.m_iSize;
//
//         while(unicode_is_whitespace(scopedstr))
//         {
//            psz += str_uni_len(scopedstr);
//            if(scopedstr >= pszEnd)
//               goto cont;
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
//            psz += str_uni_len(scopedstr);
//            if(scopedstr >= pszEnd)
//               goto cont;
//         }
//         strRoot.assign(s, psz - s);
//         psz++;
//
//         while(unicode_is_whitespace(scopedstr))
//         {
//            psz += str_uni_len(scopedstr);
//            if(scopedstr >= pszEnd)
//               goto end;
//         }
//
//         if(*psz != '=')
//            continue;
//
//         psz++;
//
//         while(unicode_is_whitespace(scopedstr))
//         {
//            psz += str_uni_len(scopedstr);
//            if(scopedstr >= pszEnd)
//               goto end;
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
//            l = str_uni_len(scopedstr);
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
//
//      return true;
//   }
//
//   string ::str::body(const ::scoped_string & scopedstr)
//   {
//      string str(scopedstr);
//      str.replace("\\r", "\r");
//      str.replace("\\n", "\n");
//      return str;
//   }
//
//
//   bool ::str::matches(const str_context * pcontext, const ::atom & atom, const ::scoped_string & scopedstr) const
//   {
//
//      static ::atom idEn("en");
//      static ::atom idStd("_std");
//
//      string str;
//      if(pcontext != nullptr)
//      {
//
//         //pcontext->defer_ok(this);
//
//         if(pcontext->m_pschema != nullptr)
//         {
//
//            str = (*pcontext->m_pschema)[atom];
//            if(!str.case_insensitive_order(scopedstr))
//               return true;
//
//         }
//
//         if(pcontext->m_pschemaLocale != nullptr)
//         {
//            str = (*pcontext->m_pschemaLocale)[atom];
//            if(!str.case_insensitive_order(scopedstr))
//               return true;
//         }
//
//         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
//         {
//
//            str = (*pcontext->m_schemaptra[i])[atom];
//            if(!str.case_insensitive_order(scopedstr))
//               return true;
//
//         }
//
//      }
//
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
//      {
//
//         str = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
//         if(!str.case_insensitive_order(scopedstr))
//            return true;
//
//      }
//
//      str = (*m_pschemaEn)[atom]; // lang=en style=en
//      if(!str.case_insensitive_order(scopedstr))
//         return true;
//
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
//      {
//
//         str = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
//         if(!str.case_insensitive_order(scopedstr))
//            return true;
//
//      }
//
//
//
//      return false;
//
//
//   }
//
//
//   bool string_begins(const str_context * pcontext, const ::scoped_string & scopedstrTopic, const ::atom & atom) const
//   {
//
//      static ::atom idEn("en");
//      static ::atom idStd("_std");
//
//      string str;
//      if(pcontext != nullptr)
//      {
//
//         //pcontext->defer_ok(this);
//
//         if(pcontext->m_pschema != nullptr)
//         {
//
//            str = (*pcontext->m_pschema)[atom];
//            if(str.has_character() && case_insensitive_string_begins(scopedstrTopic, str))
//               return true;
//
//         }
//
//         if(pcontext->m_pschemaLocale != nullptr)
//         {
//            str = (*pcontext->m_pschemaLocale)[atom];
//            if(str.has_character() && case_insensitive_string_begins(scopedstrTopic, str))
//               return true;
//         }
//
//         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
//         {
//
//            str = (*pcontext->m_schemaptra[i])[atom];
//            if(str.has_character() && case_insensitive_string_begins(scopedstrTopic, str))
//               return true;
//
//         }
//
//      }
//
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
//      {
//
//         str = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
//         if(str.has_character() && case_insensitive_string_begins(scopedstrTopic, str))
//            return true;
//
//      }
//
//      str = (*m_pschemaEn)[atom]; // lang=en style=en
//      if(str.has_character() && case_insensitive_string_begins(scopedstrTopic, str))
//         return true;
//
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
//      {
//
//         str = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
//         if(str.has_character() && case_insensitive_string_begins(scopedstrTopic, str))
//            return true;
//
//      }
//
//
//
//      return false;
//
//
//   }
//
//
//   bool ::str::begins_eat(const str_context * pcontext, string & strTopic, const ::atom & atom) const
//   {
//
//      static ::atom idEn("en");
//      static ::atom idStd("_std");
//
//      string str;
//      if(pcontext != nullptr)
//      {
//
//         //pcontext->defer_ok(this);
//
//         if(pcontext->m_pschema != nullptr)
//         {
//
//            str = (*pcontext->m_pschema)[atom];
//            if(str.has_character() && strTopic.case_insensitive_begins_eat(str))
//               return true;
//
//         }
//
//         if(pcontext->m_pschemaLocale != nullptr)
//         {
//            str = (*pcontext->m_pschemaLocale)[atom];
//            if(str.has_character() && strTopic.case_insensitive_begins_eat(str))
//               return true;
//         }
//
//         for(int i = 0; i < pcontext->m_schemaptra.get_count(); i++)
//         {
//
//            str = (*pcontext->m_schemaptra[i])[atom];
//            if(str.has_character() && strTopic.case_insensitive_begins_eat(str))
//               return true;
//
//         }
//
//      }
//
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaEn != nullptr)
//      {
//
//         str = (*pcontext->m_pschemaSchemaEn)[atom];// lang=pszStyle style=en
//         if(str.has_character() && strTopic.case_insensitive_begins_eat(str))
//            return true;
//
//      }
//
//      str = (*m_pschemaEn)[atom]; // lang=en style=en
//      if(str.has_character() && strTopic.case_insensitive_begins_eat(str))
//         return true;
//
//      if(pcontext != nullptr && pcontext->m_pschemaSchemaStd != nullptr)
//      {
//
//         str = (*pcontext->m_pschemaSchemaStd)[atom];// lang=pszStyle style=en
//         if(str.has_character() && strTopic.case_insensitive_begins_eat(str))
//            return true;
//
//      }
//
//
//      return false;
//
//
//   }
//
//
//
//   bool str_context::match(string_array & stra, const ::scoped_string & scopedstr, atom idExpression, atom idRoot) const
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      string_array straCandidate;
//
//      get(straCandidate,idRoot);
//
//      for(int i = 0; i < straCandidate.get_count(); i++)
//      {
//
//         string strCandidate = straCandidate[i];
//
//         strCandidate.replace("-","\\-");
//
//         string strExp(idExpression);
//
//         strExp.replace("%1",strCandidate);
//
//         string_array straResult;
//
//         auto pregex = ::auraacmesystem()->create_regular_expression("pcre", strExp);
//
//         if(pregex->matches(straResult, psz) > 0)
//         {
//
//            stra = straResult;
//
//            return true;
//
//         }
//
//      }
//
//      return false;
//
//   }
//
//
//} // namespace user
//
//
//
