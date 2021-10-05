// Created by Camilo on 2021-10-04 12:06 BRT <3ThomasBorregaardSørensen!!
#pragma once




//namespace acme
//{

//enum enum_flush
//{
//
//   e_flush,
//
//};



//inline ::tracer & log() { return *(::logger::t_ptracer ? ::logger::t_ptracer : ::logger::create()); }


////CLASS_DECL_ACME void __tracef(const ::matter * pmatter, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...);
////CLASS_DECL_ACME void __tracea(const ::matter * pmatter, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz);
////CLASS_DECL_ACME void __tracev(const ::matter * pmatter, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);
//
//
//extern const char * g_pszTraceLevelName[];
//extern char g_chaTraceLevel[];
//
//
//enum e_log
//{
//
//   log_this,
//
//};
//
//
//class CLASS_DECL_ACME trace_logger
//{
//public:
//
//
//   const ::matter *      m_pmatter;
//   const char * const    m_pszFunction;
//   const char * const    m_pszFile;
//   const i32             m_iLine;
//   e_trace_category        m_ecategory = e_trace_level_information;
//
//
//   trace_logger(const char * pszFunction, const char * pszFile, i32 iLine, const ::matter * pmatter) :
//      m_pszFunction(pszFunction), m_pszFile(pszFile), m_iLine(iLine), m_pmatter(pmatter)
//   {
//
//   }
//
//
//   inline trace_logger & operator << (e_trace_category ecategory) enum_trace_level elevel, const char * pszFormat, ...) const
//   {
//   m_ecategory = ecategory;
//   return *this;
//   }
//
//      va_list ptr;
//
//      va_start(ptr, pszFormat);
//
//      m_pmatter->__tracev(elevel, m_pszFunction, m_pszFile, m_iLine, pszFormat, ptr);
//
//      va_end(ptr);
//
//   }
//
//   template < typename T >
//   inline void __cdecl operator()(T & t) const
//   {
//
//      m_pmatter->__tracea(e_trace_level_information, m_pszFunction, m_pszFile, m_iLine, (const char *) t);
//
//   }
//
//
//   inline void __cdecl operator()(const char * pszFormat, ...) const
//   {
//
//      va_list valist;
//
//      va_start(valist, pszFormat);
//
//      m_pmatter->__tracev(e_trace_level_none, m_pszFunction, m_pszFile, m_iLine, pszFormat, valist);
//
//      va_end(valist);
//
//   }
//
//
//   inline void __cdecl operator()(e_log elog, const ::string & strContext, i32 iError, const ::string & strMessage) const
//   {
//
//      m_pmatter->__tracef(e_trace_level_none, m_pszFunction, m_pszFile, m_iLine, "%d %d %s", strContext.c_str(), iError, strMessage.c_str());
//
//   }
//
//
//   inline void __cdecl operator()(::matter * pmatter, const ::string & strContext, i32 iError, const ::string & strMessage) const
//   {
//
//      pmatter->__tracef(e_trace_level_none, m_pszFunction, m_pszFile, m_iLine, "%d %d %s", strContext.c_str(), iError, strMessage.c_str());
//
//   }
//
//
//};
//
//
//class CLASS_DECL_ACME trace_logger_level :
//   public trace_logger
//{
//public:
//
//
//   enum_trace_level           m_elevel;
//
//
//   trace_logger_level(const char * pszFunction, const char * pszFile, i32 iLine, const ::matter * pmatter, enum_trace_level elevel) :
//      trace_logger(pszFunction, pszFile, iLine, pmatter),
//      m_elevel(elevel)
//   {
//
//   }
//
//
//   inline void operator()(e_trace_category ecategory, const char * pszFormat, ...) const
//   {
//
//      va_list ptr;
//
//      va_start(ptr, pszFormat);
//
//      m_pmatter->__tracev(m_elevel, m_pszFunction, m_pszFile, m_iLine, pszFormat, ptr);
//
//      va_end(ptr);
//
//   }
//
//   template < typename T >
//   inline void operator()(T & t) const
//   {
//
//      m_pmatter->__tracea(m_elevel, m_pszFunction, m_pszFile, m_iLine, (const char *) t);
//
//   }
//
//   inline void operator()(const char * pszFormat, ...) const
//   {
//
//      if(m_pmatter->has(e_object_log_disable))
//      {
//
//         return;
//
//      }
//
//      va_list ptr;
//
//      va_start(ptr, pszFormat);
//
//      m_pmatter->__tracev(m_elevel, m_pszFunction, m_pszFile, m_iLine, pszFormat, ptr);
//
//      va_end(ptr);
//
//   }
//
//
//   inline void operator()(e_log elog, const ::string & strContext, i32 iError, const ::string & strMessage) const
//   {
//
//      if (iError == 0)
//      {
//
//         m_pmatter->__tracef(m_elevel, m_pszFunction, m_pszFile, m_iLine, "%s %s", strContext.c_str(), strMessage.c_str());
//
//      }
//      else
//      {
//
//         m_pmatter->__tracef(m_elevel, m_pszFunction, m_pszFile, m_iLine, "%s %s (%d)", strContext.c_str(), strMessage.c_str(), iError);
//
//      }
//
//   }
//
//
//   inline void operator()(matter * pmatter, const ::string & strContext, i32 iError, const ::string & strMessage) const
//   {
//
//      pmatter->__tracef(m_elevel, m_pszFunction, m_pszFile, m_iLine, "%d %d %s", strContext.c_str(), iError, strMessage.c_str());
//
//   }
//
//
//};


#undef __trace_logger


#define __trace_logger(trace_context) trace_logger(__FUNCTION__, __FILE__, __LINE__, trace_object(trace_context))


#undef TRACE
#undef _S_TRACE


#define TRACE __trace_logger(ALOG_CONTEXT)
#define _S_TRACE __trace_logger(_S_ALOG_CONTEXT)


#undef WARN
#undef INFO
#undef ERR
#undef FATAL


#undef __trace_logger_level


#define __trace_logger_level(trace_context, trace_level) trace_logger_level(__FUNCTION__, __FILE__, __LINE__, trace_object(trace_context), trace_level)


#define CWARN(category_radix) __trace_logger_level(::trace_object(trace_category_ ## category_radix), e_trace_level_warning)
#define CINFO(category_radix) __trace_logger_level(::trace_object(trace_category_ ## category_radix), e_trace_level_information)
#define CERR(category_radix) __trace_logger_level(::trace_object(trace_category_ ## category_radix), e_trace_level_error)
#define CFATAL(category_radix) __trace_logger_level(::trace_object(trace_category_ ## category_radix), e_trace_level_fatal)


#define WARN __trace_logger_level(ALOG_CONTEXT, e_trace_level_warning)
#define INFO __trace_logger_level(ALOG_CONTEXT, e_trace_level_information)
#define ERR __trace_logger_level(ALOG_CONTEXT, e_trace_level_error)
#define FATAL __trace_logger_level(ALOG_CONTEXT, e_trace_level_fatal)


#define _S_WARN __trace_logger_level(_S_ALOG_CONTEXT, e_trace_level_warning)
#define _S_INFO __trace_logger_level(_S_ALOG_CONTEXT, e_trace_level_information)
#define _S_ERR __trace_logger_level(_S_ALOG_CONTEXT, e_trace_level_error)
#define _S_FATAL __trace_logger_level(_S_ALOG_CONTEXT, e_trace_level_fatal)


CLASS_DECL_ACME void raw_trace_v(const char *pszFileName,i32 nLine,u32 dwCategory,u32 nLevel,const char * pszFmt,va_list args);

//
//namespace trace
//{
//

   class trace;


   // Declare a global instance of this class to automatically register a custom trace category at startup
   class CLASS_DECL_ACME trace_category
   {
   public:


      enum_trace_category        m_etracecategory;
      const char *               m_pszName;
      enum_trace_level           m_etracelevelMinimum;
      bool                       m_bEnabled;


      trace_category();
      ~trace_category();


      enum_trace_level get_trace_level() const { return m_etracelevelMinimum; }
      void set_trace_level(enum_trace_level etracelevel) { m_etracelevelMinimum = etracelevel;  }
      bool is_enabled() const { return m_bEnabled; }
      void enable(bool bEnable = true) { m_bEnabled = bEnable; }

      operator enum_trace_category () const { return m_etracecategory; }


   };


   class CLASS_DECL_ACME trace :
      virtual public ::matter
   {
   public:


      ::trace_category       m_tracecategorya[e_trace_category_count];


      trace();
      ~trace() override;


      ::trace_category * operator[](enum_trace_category etracecategory)
      {

         if (etracecategory < e_trace_category_general || etracecategory >= e_trace_category_count)
         {

            return nullptr;

         }

         return &m_tracecategorya[etracecategory];

      }


      ::trace_category * enabled_get(enum_trace_category etracecategory, enum_trace_level etracelevel)
      {

         auto ptracecategory = operator[](etracecategory);

         if (ptracecategory == nullptr)
         {

            return nullptr;

         }

         if (!ptracecategory->is_enabled() || etracelevel < ptracecategory->m_etracelevelMinimum)
         {

            return nullptr;

         }

         return ptracecategory;

      }


      //void print(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * pszFunction, const char * pszFileName, i32 nLine, const char * psz) override;


   };


//} // namespace trace


CLASS_DECL_ACME const char * get_windows_message_name(::u32 nMsg);



